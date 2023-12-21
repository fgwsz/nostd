#pragma once
#include<type_traits>
#include<functional>
#include<stdexcept>
#include"value.hpp"
#include"reference.hpp"

// 在构造时可选四种不同的底层存储类型:
// T/T const/T&/T const&
// 支持用值类型存储右值T&&，但会退化为值类型T进行存储
// 不支持volatile
// T/T const值类型不支持函数类型ret(arg...)和数组类型type[n]
// T/T const值类型支持函数指针类型ret(*)(arg...)和数组指针类型type(*)[n]
// T&/T const&引用类型支持函数引用类型ret(&)(arg...)和数组引用类型type(&)[n]
// 运行时（构造后非空时）底层存储类型不可变的强类型
class Object{
    template<typename _BaseType>
    static void mval_assign_from_mval(Value& to,Value const& from){
        to.get<_BaseType&>()=from.get<_BaseType const&>();
    }
    template<typename _BaseType>
    static void mval_assign_from_cval(Value& to,Value const& from){
        to.get<_BaseType&>()=from.get<_BaseType const&>();
    }
    template<typename _BaseType>
    static void mval_assign_from_mref(Value& to,Value const& from){
        to.get<_BaseType&>()=from.get<Reference<_BaseType>const&>().get();
    }
    template<typename _BaseType>
    static void mval_assign_from_cref(Value& to,Value const& from){
        to.get<_BaseType&>()=from.get<Reference<_BaseType const>const&>().get();
    }
    template<typename _BaseType>
    static void mref_assign_from_mval(Value& to,Value const& from){
        to.get<Reference<_BaseType>&>().get()=from.get<_BaseType const&>();
    }
    template<typename _BaseType>
    static void mref_assign_from_cval(Value& to,Value const& from){
        to.get<Reference<_BaseType>&>().get()=from.get<_BaseType const&>();
    }
    template<typename _BaseType>
    static void mref_assign_from_mref(Value& to,Value const& from){
        to.get<Reference<_BaseType>&>().get()=from.get<Reference<_BaseType>const&>().get();
    }
    template<typename _BaseType>
    static void mref_assign_from_cref(Value& to,Value const& from){
        to.get<Reference<_BaseType>&>().get()=from.get<Reference<_BaseType const>const&>().get();
    }
    Value data_;
    Type type_;
    Type base_type_;
    void(*mval_assign_from_mval_)(Value&,Value const&);
    void(*mval_assign_from_cval_)(Value&,Value const&);
    void(*mval_assign_from_mref_)(Value&,Value const&);
    void(*mval_assign_from_cref_)(Value&,Value const&);
    void(*mref_assign_from_mval_)(Value&,Value const&);
    void(*mref_assign_from_cval_)(Value&,Value const&);
    void(*mref_assign_from_mref_)(Value&,Value const&);
    void(*mref_assign_from_cref_)(Value&,Value const&);
    enum class Info{
        NIL,
        MVAL,
        CVAL,
        MREF,
        CREF
    } info_;
public:
    inline Object()noexcept
        :data_()
        ,type_()
        ,base_type_()
        ,mval_assign_from_mval_(nullptr)
        ,mval_assign_from_cval_(nullptr)
        ,mval_assign_from_mref_(nullptr)
        ,mval_assign_from_cref_(nullptr)
        ,mref_assign_from_mval_(nullptr)
        ,mref_assign_from_cval_(nullptr)
        ,mref_assign_from_mref_(nullptr)
        ,mref_assign_from_cref_(nullptr)
        ,info_(Info::NIL)
    {}
    // T        -> decay_t<T>
    // T const  -> decay_t<T const>
    // T&       -> remove_cvref_t<T&>
    // T const& -> remove_cvref_t<T const&>
    // T&&      -> remove_cvref_t<T&&>
    template<typename _Type>
    using get_base_type_t=::std::conditional_t<
        ::std::is_reference_v<_Type>,
        ::std::remove_cvref_t<_Type>,
        ::std::decay_t<_Type>
    >;
    template<typename _Type,
        ::std::enable_if_t<!::std::is_const_v<_Type>,int> _=0>
    inline Object(TypeHelper<_Type> place_holder,_Type arg)noexcept
        :Object(){
        // 值类型不支持函数类型ret(arg...)和数组类型type[n]
        using base_type=get_base_type_t<_Type>;
        this->data_=Value(arg);
        this->type_=make_type<base_type>();
        this->base_type_=make_type<base_type>();
        this->mval_assign_from_mval_=this->mval_assign_from_mval<base_type>;
        this->mval_assign_from_cval_=this->mval_assign_from_cval<base_type>;
        this->mval_assign_from_mref_=this->mval_assign_from_mref<base_type>;
        this->mval_assign_from_cref_=this->mval_assign_from_cref<base_type>;
        this->mref_assign_from_mval_=this->mref_assign_from_mval<base_type>;
        this->mref_assign_from_cval_=this->mref_assign_from_cval<base_type>;
        this->mref_assign_from_mref_=this->mref_assign_from_mref<base_type>;
        this->mref_assign_from_cref_=this->mref_assign_from_cref<base_type>;
        this->info_=Info::MVAL;
    }
    template<typename _Type>
    inline Object(TypeHelper<_Type const> place_holder,_Type const arg)noexcept
        :Object(){
        // 值类型不支持函数类型ret(arg...)和数组类型type[n]
        using base_type=get_base_type_t<_Type const>;
        this->data_=Value(arg);
        this->type_=make_type<base_type const>();
        this->base_type_=make_type<base_type>();
        this->mval_assign_from_mval_=this->mval_assign_from_mval<base_type>;
        this->mval_assign_from_cval_=this->mval_assign_from_cval<base_type>;
        this->mval_assign_from_mref_=this->mval_assign_from_mref<base_type>;
        this->mval_assign_from_cref_=this->mval_assign_from_cref<base_type>;
        this->mref_assign_from_mval_=this->mref_assign_from_mval<base_type>;
        this->mref_assign_from_cval_=this->mref_assign_from_cval<base_type>;
        this->mref_assign_from_mref_=this->mref_assign_from_mref<base_type>;
        this->mref_assign_from_cref_=this->mref_assign_from_cref<base_type>;
        this->info_=Info::CVAL;
    }
    template<typename _Type,
        ::std::enable_if_t<!::std::is_const_v<_Type>,int> _=0>
    inline Object(TypeHelper<_Type&> place_holder,_Type& arg)noexcept
        :Object(){
        // 引用类型支持函数引用类型ret(&)(arg...)和数组引用类型type(&)[n]
        using base_type=get_base_type_t<_Type&>;
        this->data_=Value(Reference<base_type>(arg));
        this->type_=make_type<base_type&>();
        this->base_type_=make_type<base_type>();
        this->mval_assign_from_mval_=this->mval_assign_from_mval<base_type>;
        this->mval_assign_from_cval_=this->mval_assign_from_cval<base_type>;
        this->mval_assign_from_mref_=this->mval_assign_from_mref<base_type>;
        this->mval_assign_from_cref_=this->mval_assign_from_cref<base_type>;
        this->mref_assign_from_mval_=this->mref_assign_from_mval<base_type>;
        this->mref_assign_from_cval_=this->mref_assign_from_cval<base_type>;
        this->mref_assign_from_mref_=this->mref_assign_from_mref<base_type>;
        this->mref_assign_from_cref_=this->mref_assign_from_cref<base_type>;
        this->info_=Info::MREF;
    }
    template<typename _Type>
    inline Object(TypeHelper<_Type const&> place_holder,_Type const& arg)noexcept
        :Object(){
        // 常量引用类型支持函数引用类型ret(const&)(arg...)和数组引用类型type(const&)[n]
        using base_type=get_base_type_t<_Type const&>;
        this->data_=Value(Reference<base_type const>(arg));
        this->type_=make_type<base_type const&>();
        this->base_type_=make_type<base_type>();
        this->mval_assign_from_mval_=this->mval_assign_from_mval<base_type>;
        this->mval_assign_from_cval_=this->mval_assign_from_cval<base_type>;
        this->mval_assign_from_mref_=this->mval_assign_from_mref<base_type>;
        this->mval_assign_from_cref_=this->mval_assign_from_cref<base_type>;
        this->mref_assign_from_mval_=this->mref_assign_from_mval<base_type>;
        this->mref_assign_from_cval_=this->mref_assign_from_cval<base_type>;
        this->mref_assign_from_mref_=this->mref_assign_from_mref<base_type>;
        this->mref_assign_from_cref_=this->mref_assign_from_cref<base_type>;
        this->info_=Info::CREF;
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
    // from\to |T      |T const |T&      |T const&
    // T       |O      |X       |O       |X        
    // T const |O      |X       |O       |X        
    // T&      |O      |X       |O       |X        
    // T const&|O      |X       |O       |X        
    inline Object& operator=(Object const& obj){
        if(this!=&obj){
            if(this->empty()&&!obj.empty()){
                this->data_=obj.data_;
                this->type_=obj.type_;
                this->base_type_=obj.base_type_;
                this->mval_assign_from_mval_=obj.mval_assign_from_mval_;
                this->mval_assign_from_cval_=obj.mval_assign_from_cval_;
                this->mval_assign_from_mref_=obj.mval_assign_from_mref_;
                this->mval_assign_from_cref_=obj.mval_assign_from_cref_;
                this->mref_assign_from_mval_=obj.mref_assign_from_mval_;
                this->mref_assign_from_cval_=obj.mref_assign_from_cval_;
                this->mref_assign_from_mref_=obj.mref_assign_from_mref_;
                this->mref_assign_from_cref_=obj.mref_assign_from_cref_;
                this->info_=obj.info_;
            }else if(!this->empty()&&obj.empty()){
                throw ::std::runtime_error("Object Assign Error:Object(Not Empty) Assign by Nil");
            }else if(this->base_type_!=obj.base_type_){
                throw ::std::runtime_error("Object Assign Error:Object Base Type Not Equal");
            }else if(this->info_==Info::CVAL||this->info_==Info::CREF){
                throw ::std::runtime_error("Object Assign Error:Object(CVal/CRef) Can't be Assign");
            }else if(this->info_==Info::MVAL&&obj.info_==Info::MVAL){
                this->mval_assign_from_mval_(this->data_,obj.data_);
            }else if(this->info_==Info::MVAL&&obj.info_==Info::CVAL){
                this->mval_assign_from_cval_(this->data_,obj.data_);
            }else if(this->info_==Info::MVAL&&obj.info_==Info::MREF){
                this->mval_assign_from_mref_(this->data_,obj.data_);
            }else if(this->info_==Info::MVAL&&obj.info_==Info::CREF){
                this->mval_assign_from_cref_(this->data_,obj.data_);
            }else if(this->info_==Info::MREF&&obj.info_==Info::MVAL){
                this->mref_assign_from_mval_(this->data_,obj.data_);
            }else if(this->info_==Info::MREF&&obj.info_==Info::CVAL){
                this->mref_assign_from_cval_(this->data_,obj.data_);
            }else if(this->info_==Info::MREF&&obj.info_==Info::MREF){
                this->mref_assign_from_mref_(this->data_,obj.data_);
            }else if(this->info_==Info::MREF&&obj.info_==Info::CREF){
                this->mref_assign_from_cref_(this->data_,obj.data_);
            }
        }
        return *this;
    }
    // from\to |T      |T const |T&      |T const&
    // T       |O      |O       |X       |O        
    // T const |O      |O       |X       |O        
    // T&      |O      |O       |O       |O        
    // T const&|O      |O       |X       |O        
    template<typename _Type>
    inline operator _Type()const{
        if constexpr(::std::is_void_v<_Type>){
            if(this->empty()){
                return;
            }else{
                throw ::std::runtime_error("Value Cast Error:Value Is Not Empty,Can't Cast To Void");
            }
        }
        using base_type=get_base_type_t<_Type>;
        if(make_type<base_type>()!=this->base_type_){
            throw ::std::runtime_error("Object Cast Error:Object Base Type Not Equal");
        }
        if constexpr( // to T
            !::std::is_reference_v<_Type>&&
            ::std::is_convertible_v<base_type,_Type>
        ){
            if(this->info_==Info::MVAL){
                return this->data_.get<base_type const&>();
            }else if(this->info_==Info::CVAL){
                return this->data_.get<base_type const&>();
            }else if(this->info_==Info::MREF){
                return this->data_.get<Reference<base_type>const&>().get();
            }else if(this->info_==Info::CREF){
                return this->data_.get<Reference<base_type const>const&>().get();
            }
        }else if constexpr( // to T const
            !::std::is_reference_v<_Type>&&
            ::std::is_convertible_v<base_type const,_Type>
        ){
            if(this->info_==Info::MVAL){
                return this->data_.get<base_type const&>();
            }else if(this->info_==Info::CVAL){
                return this->data_.get<base_type const&>();
            }else if(this->info_==Info::MREF){
                return this->data_.get<Reference<base_type>const&>().get();
            }else if(this->info_==Info::CREF){
                return this->data_.get<Reference<base_type const>const&>().get();
            }
        }else if constexpr( // to T&
            ::std::is_reference_v<_Type>&&
            !::std::is_const_v<::std::remove_reference_t<_Type>>&&
            ::std::is_convertible_v<base_type&,_Type>
        ){
            if(this->info_==Info::MVAL){
                throw ::std::runtime_error("Object Cast Error:T =X=> T&");
            }else if(this->info_==Info::CVAL){
                throw ::std::runtime_error("Object Cast Error:T const =X=> T&");
            }else if(this->info_==Info::MREF){
                return this->data_.get<Reference<base_type>const&>().get();
            }else if(this->info_==Info::CREF){
                throw ::std::runtime_error("Object Cast Error:T const& =X=> T&");
            }
        }else if constexpr( // to T const&
            ::std::is_reference_v<_Type>&&
            ::std::is_const_v<::std::remove_reference_t<_Type>>&&
            ::std::is_convertible_v<base_type const&,_Type>
        ){
            if(this->info_==Info::MVAL){
                return this->data_.get<base_type const&>();
            }else if(this->info_==Info::CVAL){
                return this->data_.get<base_type const&>();
            }else if(this->info_==Info::MREF){
                return this->data_.get<Reference<base_type>const&>().get();
            }else if(this->info_==Info::CREF){
                return this->data_.get<Reference<base_type const>const&>().get();
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
    inline constexpr bool is_mval()const noexcept{
        return this->info_==Info::MVAL;
    }
    inline constexpr bool is_cval()const noexcept{
        return this->info_==Info::CVAL;
    }
    inline constexpr bool is_mref()const noexcept{
        return this->info_==Info::MREF;
    }
    inline constexpr bool is_cref()const noexcept{
        return this->info_==Info::CREF;
    }
};
// 此宏用于Object类构造函数中传入非Object类的参数时使用
// 使用示例如下：
// int arg;
// Object obj(OBJECT_CTOR_ARG(arg));
// 构建此宏的用意：
// 依据输入参数__arg__的实际类型来选择Object对应的构造函数
// T         -> Object(TypeHelper<T>        ,T         __arg__)
// T const   -> Object(TypeHelper<T const>  ,T const   __arg__)
// T &       -> Object(TypeHelper<T &>      ,T &       __arg__)
// T const & -> Object(TypeHelper<T const &>,T const & __arg__)
// T &&      -> Object(TypeHelper<T>        ,T         __arg__)
#define OBJECT_CTOR_ARG(...) \
    TypeHelper< \
        ::std::conditional_t< \
            ::std::is_rvalue_reference_v<decltype(__VA_ARGS__)>, \
            ::std::remove_cvref_t<decltype(__VA_ARGS__)>, \
            decltype(__VA_ARGS__) \
        > \
    >(),(__VA_ARGS__) \
//

// 放入OBJECT_CTOR_OF宏的第一个参数来选择Object对应的构造函数
// OBJECT_CTOR_FLAG_MVAL -> Object(TypeHelper<T>        ,T         __arg__)
#define OBJECT_CTOR_FLAG_MVAL 
// 放入OBJECT_CTOR_OF宏的第一个参数来选择Object对应的构造函数
// OBJECT_CTOR_FLAG_CVAL -> Object(TypeHelper<T const>  ,T const   __arg__)
#define OBJECT_CTOR_FLAG_CVAL const
// 放入OBJECT_CTOR_OF宏的第一个参数来选择Object对应的构造函数
// OBJECT_CTOR_FLAG_MREF -> Object(TypeHelper<T &>      ,T &       __arg__)
#define OBJECT_CTOR_FLAG_MREF &
// 放入OBJECT_CTOR_OF宏的第一个参数来选择Object对应的构造函数
// OBJECT_CTOR_FLAG_CREF -> Object(TypeHelper<T const &>,T const & __arg__)
#define OBJECT_CTOR_FLAG_CREF const&

// 此宏用于Object类构造函数中传入非Object类的参数时使用
// 使用示例如下：
// int arg_1=100;
// Object obj_1(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_MVAL,arg_1));
// int const arg_2=200;
// Object obj_2(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_CVAL,arg_2));
// int& arg_3=arg_1;
// Object obj_3(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_MREF,arg_3));
// int const& arg_4=arg_2;
// Object obj_4(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_CREF,arg_4));
// 构建此宏的用意：
// 依据 __object_ctor_flag__ 来选择Object对应的构造函数
// OBJECT_CTOR_FLAG_MVAL -> Object(TypeHelper<T>        ,T         __arg__)
// OBJECT_CTOR_FLAG_CVAL -> Object(TypeHelper<T const>  ,T const   __arg__)
// OBJECT_CTOR_FLAG_MREF -> Object(TypeHelper<T &>      ,T &       __arg__)
// OBJECT_CTOR_FLAG_CREF -> Object(TypeHelper<T const &>,T const & __arg__)
#define OBJECT_CTOR_OF(__object_ctor_flag__,...) \
    TypeHelper< \
        Object::get_base_type_t<decltype(__VA_ARGS__)>__object_ctor_flag__ \
    >(),(__VA_ARGS__) \
//
