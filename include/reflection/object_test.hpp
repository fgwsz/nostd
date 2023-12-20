#pragma once
#include<iostream>
#include"object.hpp"
void test(){
    int mval=100;
    Object obj_mval(OBJECT_CTOR_ARG(mval));
    ::std::cout<<obj_mval.type().name()<<"\n";
    int const cval=100;
    Object obj_cval(OBJECT_CTOR_ARG(cval));
    ::std::cout<<obj_cval.type().name()<<"\n";
    int& mref=mval;
    Object obj_mref(OBJECT_CTOR_ARG(mref));
    ::std::cout<<obj_mref.type().name()<<"\n";
    int const cref=cval;
    Object obj_cref(OBJECT_CTOR_ARG(cref));
    ::std::cout<<obj_cref.type().name()<<"\n";
    //Object obj(OBJECT_CTOR_ARG(test));
    //Object obj(OBJECT_CTOR_ARG(&test));
    //int arr;
    //Object obj(OBJECT_CTOR_ARG(arr));
    //auto& arr_ref=arr;
    //Object obj_1(OBJECT_CTOR_ARG(arr_ref));
    //::std::cout<<obj_1.type().name()<<::std::endl;
    //auto const& arr_cref=arr;
    //Object obj_2(OBJECT_CTOR_ARG(arr_cref));
    //::std::cout<<obj_2.type().name()<<::std::endl;
}