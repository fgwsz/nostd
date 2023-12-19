#pragma once
#include<cassert>
#include<iostream>
#include<string>
#include"value.hpp"
void test_ctor_1(){
    Value value;
    assert(value.empty());
}
void test_ctor_2(){
    int num=100;
    Value value(num);
    assert(!value.empty());
    assert(value.type()==make_type<int>());
    ::std::string str="hello";
    value=Value(str);
    assert(!value.empty());
    assert(value.type()==make_type<::std::string>());
    value.get<::std::string&>()="world";
    str=value.get<::std::string const&>();
    assert(str=="world");
}
void test_cast(){
    Value value=Value(100);
    value.get<int&>()=200;
    assert(value.get<int>()==200);
    int num=value;
    assert(num==200);
}
void test(){
    test_ctor_1();
    test_ctor_2();
    test_cast();
}