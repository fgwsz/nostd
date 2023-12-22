#pragma once
#include<iostream>
#include<source_location>
#include"function.hpp"
int foo_1(int,double){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    return 0;
}
void foo_2(int,double){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
}
int foo_3(){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    return 0;
}
void foo_4(){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
}
void test(){
    Function f1(&foo_1);
    ::std::array<Object,2> arr={
        make_object(1),
        make_object(3.14)
    };
    f1(arr);
    Function f2(&foo_2);
    f2(::std::array{
        make_object(1),
        make_object(3.14)
    });
    Function f3(&foo_3);
    int ret_3=f3();
    Function f4(&foo_4);
    auto ret_4=f4();
}