#pragma once
#include<iostream>
#include"object.hpp"
void test(){
    //Object obj(OBJECT_CTOR_ARG(test));
    Object obj(OBJECT_CTOR_ARG(&test));
    int volatile arr[10];
    //Object obj(OBJECT_CTOR_ARG(arr));
    auto& arr_ref=arr;
    Object obj_1(OBJECT_CTOR_ARG(arr_ref));
    ::std::cout<<obj_1.type().name()<<::std::endl;
    auto const& arr_cref=arr;
    Object obj_2(OBJECT_CTOR_ARG(arr_cref));
    ::std::cout<<obj_2.type().name()<<::std::endl;
}