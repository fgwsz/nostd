#pragma once
#include<utility>
#include<type_traits>
#include<string>
#include<iostream>
#include"type.hpp"
#define TYPE_WRAPPER(__VARIABLE__) TypeHelper<decltype(__VARIABLE__)>(),(__VARIABLE__)
#define RVLALUE_REFERENCE_WRAPPER(__VARIABLE__) TypeHelper<decltype(__VARIABLE__)>(),::std::move(__VARIABLE__)
template<typename _Type>
void foo(TypeHelper<_Type> _,_Type arg){
    ::std::cout<<"value\n";
}
template<typename _Type,
    ::std::enable_if_t<!::std::is_const_v<_Type>,int> _num=0>
void foo(TypeHelper<_Type&> _,_Type& arg){
    ::std::cout<<"lval_ref\n";
}
template<typename _Type>
void foo(TypeHelper<_Type const&> _,_Type const& arg){
    ::std::cout<<"lval_cref\n";
}
template<typename _Type>
void foo(TypeHelper<_Type&&> _,_Type&& arg){
    ::std::cout<<"rval_ref\n";
}
void test(){
    ::std::string value="hello";
    foo(TYPE_WRAPPER(value));
    ::std::string& lval_ref=value;
    foo(TYPE_WRAPPER(lval_ref));
    ::std::string const& lval_cref=value;
    foo(TYPE_WRAPPER(lval_cref));
    ::std::string&& rval_ref=::std::move(value);
    foo(RVLALUE_REFERENCE_WRAPPER(rval_ref));
    //foo(TypeHelper<::std::string>(),::std::move(rval_ref)); // value
}