#pragma once
#include<iostream>
#include"type.hpp"
void test(){
    ::std::cout<<make_type<int const volatile&&>().name()<<::std::endl;
}