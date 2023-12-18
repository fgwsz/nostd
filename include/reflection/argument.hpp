#pragma once
#include<any>
#include<utility>
#include<type_traits>
#include"nostd_type_name.hpp"
class Argument{
public:
    enum class Info{
        EMPTY,
        VAL,
        LVAL_REF,
        LVAL_CREF,
        RVAL_REF
    };
    Argument()
        :data_()
        ,info_(Info::EMPTY)
        ,type_(::nostd::type_name<void>()){
    }
    //template<typename _Type>
    //Argument(_Type arg)
    //    :Argument(){
    //    this->data_=arg;
    //    this->info_=Info::VAL;
    //    this->type_=::nostd::type_name<_Type>();
    //}
    template<typename _Type>
    Argument(_Type&& arg)
        :Argument(){
        if constexpr(::std::is_lvalue_reference_v<_Type&&>){
            if constexpr(::std::is_const_v<::std::remove_reference_t<_Type&&>>){
                this->data_=::std::cref(::std::forward<_Type>(arg)); // reference_wrapper<const T>
                this->info_=Info::LVAL_CREF;
                this->type_=::nostd::type_name<decltype(::std::forward<_Type>(arg))>();
            }else{
                this->data_=::std::ref(::std::forward<_Type>(arg)); // reference_wrapper<T>
                this->info_=Info::LVAL_REF;
                this->type_=::nostd::type_name<decltype(::std::forward<_Type>(arg))>();
            }
        }else if constexpr(::std::is_rvalue_reference_v<_Type&&>){
            this->data_=::std::forward<_Type>(arg);
            this->info_=Info::RVAL_REF;
            this->type_=::nostd::type_name<decltype(::std::forward<_Type>(arg))>();
        }        
    }
    Argument(Argument const& arg)
        :Argument(){
        (*this)=arg;
    }
    bool is_empty() const{
        return this->info_==Info::EMPTY;
    }
    bool is_val()const{
        return this->info_==Info::VAL;
    }
    bool is_lval_ref()const{
        return this->info_==Info::LVAL_REF;
    }
    bool is_lval_cref()const{
        return this->info_==Info::LVAL_CREF;
    }
    bool is_rval_ref()const{
        return this->info_==Info::RVAL_REF;
    }
    Argument& operator=(Argument const&arg){
        if(this!=&arg){
            this->data_=this->data_;
            this->info_=this->info_;
            this->type_=this->type_;
        }
        return *this;
    }
    template<typename _Type>
    operator _Type()const{
        return ::std::any_cast<_Type>(this->data_);
    }
    Info get_info()const{
        return this->info_;
    }
    ::std::string_view const& get_type()const{
        return this->type_;
    }
private:
    ::std::any data_;
    Info info_;
    ::std::string_view type_;
};
template<typename _Type>
    requires ::std::is_rvalue_reference_v<_Type&&>
class RValRefWrapper{
    _Type&& data_;
public:
    RValRefWrapper(_Type&& data){
        this->data_=::std::move(data);
    }
    _Type&& get_data(){
        return ::std::move(this->data_);
    }
};
enum class TypeCheckID{
    TYPE,
    TYPE_CONST,
    TYPE_VOLATILE,
    TYPE_CONST_VOLATILE,
    TYPE_LVALUE_REFERENCE,
    TYPE_CONST_LVALUE_REFERENCE,
    TYPE_VOLATILE_LVALUE_REFERENCE,
    TYPE_CONST_VOLATILE_LVALUE_REFERENCE,
    TYPE_RVALUE_REFERENCE,
    TYPE_CONST_RVALUE_REFERENCE,
    TYPE_VOLATILE_RVALUE_REFERENCE,
    TYPE_CONST_VOLATILE_RVALUE_REFERENCE
};
template<typename _Type>
struct TypeCheck{
    static constexpr auto id=TypeCheckID::TYPE;
    using base_type=_Type;
};
template<typename _Type>
struct TypeCheck<_Type const>{
    static constexpr auto id=TypeCheckID::TYPE_CONST;
    using base_type=_Type;
};
template<typename _Type>
struct TypeCheck<_Type volatile>{
    static constexpr auto id=TypeCheckID::TYPE_VOLATILE;
    using base_type=_Type;
};
template<typename _Type>
struct TypeCheck<_Type const volatile>{
    static constexpr auto id=TypeCheckID::TYPE_CONST_VOLATILE;
    using base_type=_Type;
};
template<typename _Type>
struct TypeCheck<_Type&>{
    static constexpr auto id=TypeCheckID::TYPE_LVALUE_REFERENCE;
    using base_type=_Type;
};
template<typename _Type>
struct TypeCheck<_Type const&>{
    static constexpr auto id=TypeCheckID::TYPE_CONST_LVALUE_REFERENCE;
    using base_type=_Type;
};
template<typename _Type>
struct TypeCheck<_Type volatile&>{
    static constexpr auto id=TypeCheckID::TYPE_VOLATILE_LVALUE_REFERENCE;
    using base_type=_Type;
};
template<typename _Type>
struct TypeCheck<_Type const volatile&>{
    static constexpr auto id=TypeCheckID::TYPE_CONST_VOLATILE_LVALUE_REFERENCE;
    using base_type=_Type;
};
template<typename _Type>
struct TypeCheck<_Type&&>{
    static constexpr auto id=TypeCheckID::TYPE_RVALUE_REFERENCE;
    using base_type=_Type;
};
template<typename _Type>
struct TypeCheck<_Type const&&>{
    static constexpr auto id=TypeCheckID::TYPE_CONST_RVALUE_REFERENCE;
    using base_type=_Type;
};
template<typename _Type>
struct TypeCheck<_Type volatile&&>{
    static constexpr auto id=TypeCheckID::TYPE_VOLATILE_RVALUE_REFERENCE;
    using base_type=_Type;
};
template<typename _Type>
struct TypeCheck<_Type const volatile&&>{
    static constexpr auto id=TypeCheckID::TYPE_CONST_VOLATILE_RVALUE_REFERENCE;
    using base_type=_Type;
};