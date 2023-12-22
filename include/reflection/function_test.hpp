#pragma once
#include<iostream>
#include<source_location>
#include"function.hpp"
int foo_1(int arg_0,double const arg_1,char& arg_2,::std::string const& arg_3){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    ::std::cout<<"arg_0:"<<arg_0<<"\n";
    ::std::cout<<"arg_1:"<<arg_1<<"\n";
    ::std::cout<<"arg_2:"<<arg_2<<"\n";
    ::std::cout<<"arg_3:"<<arg_3<<"\n";
    return 0;
}
void foo_2(int arg_0,double const arg_1,char& arg_2,::std::string const& arg_3){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    ::std::cout<<"arg_0:"<<arg_0<<"\n";
    ::std::cout<<"arg_1:"<<arg_1<<"\n";
    ::std::cout<<"arg_2:"<<arg_2<<"\n";
    ::std::cout<<"arg_3:"<<arg_3<<"\n";
}
int foo_3(){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    return 0;
}
void foo_4(){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
}
void test(){
    char temp='A';
    Function f1(&foo_1);
    f1(1,3.14,temp,::std::string("hello"));
    Function f2(&foo_2);
    f2(1,3.14,temp,::std::string("hello"));
    Function f3(&foo_3);
    int ret_3=f3();
    Function f4(&foo_4);
    auto ret_4=f4();
    //Function f5=f1;
    //f1(1,3.14,temp,::std::string("hello"));
}