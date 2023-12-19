#pragma once
#include<cassert>
#include<iostream>
#include"value.hpp"
void test_ctor_1(){
    Value value;
    assert(value.empty());
}
void test_ctor_2(){
    int num=100;
    Value value(num);
    assert(!value.empty());
}
void test(){
    test_ctor_1();
    test_ctor_2();
    Value value=Value(100);
    value.get<int&>()=200;
    assert(value.get<int>()==200);
    int num=value;
    assert(num==200);
}