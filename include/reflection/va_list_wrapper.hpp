#pragma once
#include<cstdarg>
#include<utility>
#include<type_traits>
class VaListWrapper final{
public:
    VaListWrapper(){
        va_end(this->va_list_); // set 0
    };
    VaListWrapper(va_list const& _va_list)
        :VaListWrapper(){
        va_copy(this->va_list_,const_cast<va_list&>(_va_list));
    }
    VaListWrapper(VaListWrapper const& wrapper)
        :VaListWrapper(){
        (*this)=wrapper;
    }
    VaListWrapper& operator=(VaListWrapper const& wrapper){
        if(this!=&wrapper){
            va_copy(this->va_list_,const_cast<VaListWrapper&>(wrapper).va_list_);
        }
        return *this;
    }
    template<typename _ValueType,typename..._ValueTypes>
    VaListWrapper(::std::decay_t<_ValueType> prev_value,::std::decay_t<_ValueTypes>...values)
        :VaListWrapper(){
        this->start(prev_value);
    }
    template<typename _ValueType>
    VaListWrapper& start(::std::decay_t<_ValueType> value){
        va_start(this->va_list_,value);
        return *this;
    }
    template<typename _Type>
    _Type arg(){
        return va_arg(this->va_list_, _Type);
    }
    ~VaListWrapper(){
        va_end(this->va_list_); // set 0
    }
private:
    va_list va_list_;
};
#include<iostream>
struct TestVaListWrapper{
    static void print_nums_0(int count,...){
        va_list list;
        va_start(list,count);
        print_nums_1(count,VaListWrapper{list});
        va_end(list);
    }
    static void print_nums_1(int count,VaListWrapper wrapper){
        while(count!=0){
            ::std::cout<<wrapper.arg<int>()<<::std::endl;
            --count;
        }
    }
    static void print_nums_2(int count,...){
        va_list list;
        while(count!=0){
            ::std::cout<<va_arg(list,int)<<::std::endl;
            --count;
        }
        va_end(list);
    }
    //static void print_nums_3(int count,VaList const& valist){
    //    valist.invoke(
    //        valist.bind(print_nums_2,count)
    //    );
    //}
};
void test_va_list_wrapper(){
    TestVaListWrapper::print_nums_0(4,0,1,2,3);
}
#include<type_traits>
struct ArgType{
    template<typename _ValType>
        requires requires{!::std::is_reference_v<_ValType>;}
    ArgType(_ValType val){
        //T/T const/T volatile/T const volatile
    }
    template<typename _LValRef>
        requires ::std::is_lvalue_reference_v<_LValRef>
    ArgType(_LValRef lval_ref){
        //&/const&/volaile&/const volatile&
    }
    template<typename _RValRef>
        requires ::std::is_rvalue_reference_v<_RValRef>
    ArgType(_RValRef rval_ref){
       //&&/const&&/volatile&&/const volatile&&
    }
};
#include<tuple>
template<typename..._ValueTypes>
constexpr auto _va_list_to_tuple_impl(_ValueTypes...values){
    return [&]{
        struct _Object{
            constexpr auto as_tuple(){
                return ::std::make_tuple(values...);
            }
        }object;
        return object;
    }();
}
using type = decltype(_va_list_to_tuple_impl(int(0),double(100.0)).as_tuple());