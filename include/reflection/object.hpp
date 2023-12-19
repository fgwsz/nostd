#pragma once
#include<type_traits>
#include<functional>
#include<stdexcept>
#include"value.hpp"
#include"reference.hpp"
// 此宏用于Object类构造函数中传入非Object类的参数时使用
// 使用示例如下：
// int arg;
// Object obj(OBJECT_CTOR_ARG(arg));
// 构建此宏的用意：
// 依据 __arg__ 的实际类型来选择Object对应的构造函数
// T         -> Object(TypeHelper<T>        ,T         __arg__)
// T &       -> Object(TypeHelper<T &>      ,T &       __arg__)
// T const & -> Object(TypeHelper<T const &>,T const & __arg__)
// T &&      -> Object(TypeHelper<T>        ,T         __arg__)
#define OBJECT_CTOR_ARG(__arg__) \
    TypeHelper< \
        ::std::conditional_t< \
            ::std::is_rvalue_reference_v<decltype(__arg__)>, \
            ::std::remove_cvref_t<decltype(__arg__)>, \
            decltype(__arg__) \
        > \
    >,(__arg__) \
//

// 在构造时可选三种不同的底层存储类型，值类型，左值引用，左值常量引用
// 运行时底层存储类型不可变的强类型
class Object{
    Value data_;
    Type type_;
    Type base_type_;
    enum class Info{
        NIL,
        VAL,
        REF,
        CREF
    } info_;
    ::std::function<void(Value&,Value const&)> copy_func_;
public:
    inline Object()noexcept
        :data_()
        ,type_()
        ,base_type_()
        ,info_(Info::NIL)
        ,copy_func_()
    {}
    template<typename _Type>
    inline Object(TypeHelper<_Type> place_holder,_Type arg)noexcept
        :Object(){
        this->data_=Value(arg);
        this->type_=this->data_.type();
        this->base_type_=this->type_;
        this->info_=Info::VAL;
        this->copy_func_=[](Value& to,Value const& from){
            to=from;
        };
    }
    template<typename _Type,
        ::std::enable_if_t<!::std::is_const_v<_Type>,int> _=0>
    inline Object(TypeHelper<_Type&> place_holder,_Type& arg)noexcept
        :Object(){
        using value_type=::std::decay_t<::std::remove_cvref_t<_Type>>;
        this->data_=Value(Reference<value_type>(arg));
        this->type_=make_type<value_type&>();
        this->base_type_=make_type<value_type>();
        this->info_=Info::REF;
        this->copy_func_=[](Value& to,Value const& from){
            to=Value(from.get<Reference<value_type>&>().get());
        }
    }
    template<typename _Type>
    inline Object(TypeHelper<_Type const&> place_holder,_Type const& arg)noexcept
        :Object(){
        using value_type=::std::decay_t<::std::remove_cvref_t<_Type>>;
        this->data_=Value(Reference<value_type const>(arg));
        this->type_=make_type<value_type const&>();
        this->base_type_=make_type<value_type>();
        this->info_=Info::CREF;
        this->copy_func_=[](Value& to,Value const& from){
            to=Value(from.get<Reference<value_type const>&>().get());
        }
    }
    inline constexpr Type const& type()const noexcept{
        return this->type_;
    }
    inline constexpr bool empty()const noexcept{
        return this->info_==Info::NIL;
    }
    inline Object(Object const& obj)noexcept
        :Object(){
        (*this)=obj;
    }
    // from\to |T      |T&      |T const&
    // T       |O      |O       |X        
    // T&      |O      |O       |X        
    // T const&|O      |O       |X        
    inline Object& operator=(Object const& obj){
        if(this!=&obj){
            if(this->empty()&&!obj.empty()){
                this->data_=obj.data_;
                this->type_=obj.type_;
                this->base_type_=obj.base_type_;
                this->info_=obj.info_;
                this->copy_func_=obj.copy_func_;
                return *this;
            }else if(!this->empty()&&obj.empty()){
                throw ::std::runtime_error("Object Assign Error:Object(Not Empty) Assign by Nil");
                return *this;
            }else if(this->base_type_!=obj.base_type_){
                throw ::std::runtime_error("Object Assign Error:Object Base Type Not Equal");
                return *this;
            }else if(this->info_==Info::CREF){
                throw ::std::runtime_error("Object Assign Error:Object(CRef) Can't be Assign");
                return *this;
            }else{
                obj.copy_func_(this->data_,obj.data_);
            }
        }
        return *this;
    }
    // from\to |T      |T&      |T const&
    // T       |O      |X       |O        
    // T&      |O      |O       |O        
    // T const&|O      |X       |O        
    template<typename _Type>
    inline operator _Type()const{
        if(this->empty()){
            throw ::std::runtime_error("Object Cast Error:Object Is Empty");
        }
        using value_type=::std::decay_t<::std::remove_cvref_t<_Type>>;
        if(make_type<value_type>()!=this->base_type_){
            throw ::std::runtime_error("Object Cast Error:Object Base Type Not Equal");
        }
        // check T& ->cast-> T/T&/T const& ->cast-> _Type
        static_assert(::std::is_convertible_v<value_type&,_Type>);
        if constexpr( // to T
            !::std::is_reference_v<_Type>&&
            ::std::is_convertible_v<value_type,_Type>
        ){
            if(this->info_==Info::VAL){
                return this->data_.get<value_type>();
            }else if(this->info_==Info::REF){
                return this->data_.get<Reference<value_type>>().get();
            }else if(this->info_==Info::CREF){
                return this->data_.get<Reference<value_type const>>().get();
            }
        }else if constexpr( // to T&
            ::std::is_reference_v<_Type>&&
            !::std::is_const_v<::std::remove_reference_t<_Type>>&&
            ::std::is_convertible_v<value_type&,_Type>
        ){
            if(this->info_==Info::VAL){
                throw ::std::runtime_error("Object Cast Error:T =X=> T&");
            }else if(this->info_==Info::REF){
                return this->data_.get<Reference<value_type>>().get();
            }else if(this->info_==Info::CREF){
                throw ::std::runtime_error("Object Cast Error:T const& =X=> T&");
            }
        }else if constexpr( // to T const&
            ::std::is_reference_v<_Type>&&
            ::std::is_const_v<::std::remove_reference_t<_Type>>&&
            ::std::is_convertible_v<value_type const&,_Type>
        ){
            if(this->info_==Info::VAL){
                return this->data_.get<value_type>();
            }else if(this->info_==Info::REF){
                return this->data_.get<Reference<value_type>>().get();
            }else if(this->info_==Info::CREF){
                return this->data_.get<Reference<value_type const>>().get();
            }
        }
        throw ::std::runtime_error("Object Cast Error:_Type Not Match");
    }
    template<typename _Type>
    inline _Type get()const{
        return this->operator _Type();
    }
    inline constexpr Type const& base_type()const noexcept{
        return this->base_type_;
    }
    inline constexpr bool is_base_value()const noexcept{
        return this->info_==Info::VAL;
    }
    inline constexpr bool is_mutable_ref()const noexcept{
        return this->info_==Info::REF;
    }
    inline constexpr bool is_const_ref()const noexcept{
        return this->info_==Info::CREF;
    }
};