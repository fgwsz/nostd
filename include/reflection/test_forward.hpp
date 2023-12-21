#pragma once
#include<utility>
#include<type_traits>
#include<iostream>
#include"nostd_type_name.hpp"
// T&&/T&/Tconst&
template<typename _Type>
auto foo(_Type&& arg){
    ::std::cout<<"_Type        ="<<::nostd::type_name<_Type>()<<"\n";
    ::std::cout<<"_Type&&      ="<<::nostd::type_name<_Type&&>()<<"\n";
    ::std::cout<<"decltype(arg)="<<::nostd::type_name<decltype(arg)>()<<"\n";
}
void test(){
    int mval=100;
    int const cval=100;
    int& lval_mref=mval;
    int const& lval_cref=cval;
    int&& rval_ref=::std::move(100);
    ::std::cout<<"foo(arg=int)\n";
    foo(mval);
    ::std::cout<<"foo(arg=int const)\n";
    foo(cval);
    ::std::cout<<"foo(arg=int&)\n";
    foo(lval_mref);
    ::std::cout<<"foo(arg=int const&)\n";
    foo(lval_cref);
    ::std::cout<<"foo(arg=int&&)\n";
    foo(::std::move(rval_ref));
}