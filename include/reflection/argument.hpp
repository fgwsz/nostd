#pragma once
#include<any>
#include<type_traits>
#include<utility>
class Argument{
    enum class Info{
        VAL,
        LVAL_REF,
        LVAL_CREF,
        RVAL_REF
    };
    ::std::any data_;
    Info info_;
    Argument()
        :data_(){
    }
    template<typename _Value>
        requires requires{!::std::is_reference_v<_Value>;}
    Argument(_Value value)
        :Argument(){
        static_assert(::std::is_convertible_v<_Value,::std::decay_t<_Value>>>,"value argument decay error!");
        this->data_=static_cast<::std::decay_t<_Value>>(value);
        this->info_=Info::VAL;
    }
    template<typename _LVRef>
        requires requires{::std::is_lvalue_reference_v<_LVRef>;}
    Argument(_LVRef lv_ref)
        :Argument(){
        if constexpr(::std::is_const_v<::std::remove_reference_t<_LVRef>>){
            this->data_=::std::cref(lv_ref);
            this->info_=Info::LVAL_CREF;
        }else{
            this->data_=::std::ref(lv_ref);
            this->info_=Info::LVAL_REF;
        }
    }
    template<typename _RVRef>
        requires requires{::std::is_rvalue_reference_v<_RVRef>;}
    Argument(_RVRef lv_ref)
        :Argument(){
        this->data_=::std::move(lv_ref);
        this->info_=Info::RVAL_REF;
    }
    Argument(Argument const& arg)
        :Argument(){
        (*this)=arg;
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
        }
        return *this;
    }
};