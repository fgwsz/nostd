#pragma once
#include<cassert>
#include"reference.hpp"
void test_ctor_1(){
    Reference<int> ref;
    assert(ref.empty());
}
void test_ctor_2(){
    int num=100;
    Reference<int> ref(num);
    ref.get()=200;
    assert(num==200);
}
void test_ctor_3(){
    int num=100;
    int& num_ref=num;
    Reference<int> ref_1(num_ref);
    Reference ref_2=ref_1;
    assert(&num_ref==&(ref_2.get()));
}
void test_assign(){
    int num=100;
    Reference<int> ref_1(num);
    Reference<int> ref_2;
    ref_1=ref_2;
    assert(ref_1.empty());
    ref_2=Reference(num);
    ref_1=ref_2;
    assert(ref_1.get()==100);
    int num_2=200;
    ref_2.reset();
    ref_2=Reference(num_2);
    ref_1=ref_2;
    assert((&(ref_1.get())==&num)&&(ref_1.get()==200));
}
void test(){
    test_ctor_1();
    test_ctor_2();
    test_ctor_3();
    test_assign();
}