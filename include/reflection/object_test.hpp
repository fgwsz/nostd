#pragma once
#include<cassert>
#include<iostream>
#include<source_location>
#include"object.hpp"
void test_ctor_1(){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    int mval=100;
    Object obj_mval(OBJECT_CTOR_ARG(mval));
    ::std::cout<<obj_mval.type().name()<<"\n";
    int const cval=100;
    Object obj_cval(OBJECT_CTOR_ARG(cval));
    ::std::cout<<obj_cval.type().name()<<"\n";
    int& mref=mval;
    Object obj_mref(OBJECT_CTOR_ARG(mref));
    ::std::cout<<obj_mref.type().name()<<"\n";
    int const& cref=cval;
    Object obj_cref(OBJECT_CTOR_ARG(cref));
    ::std::cout<<obj_cref.type().name()<<"\n";
    int&& rref=::std::move(100);
    Object obj_rref(OBJECT_CTOR_ARG(rref));
    ::std::cout<<obj_rref.type().name()<<"\n";
}
void test_ctor_2(){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    int mval=100;
    Object obj_mval(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_MVAL,mval));
    ::std::cout<<obj_mval.type().name()<<"\n";
    int const cval=100;
    Object obj_cval(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_CVAL,cval));
    ::std::cout<<obj_cval.type().name()<<"\n";
    int& mref=mval;
    Object obj_mref(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_MREF,mref));
    ::std::cout<<obj_mref.type().name()<<"\n";
    int const& cref=cval;
    Object obj_cref(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_CREF,cref));
    ::std::cout<<obj_cref.type().name()<<"\n";
    int&& rref=::std::move(100);
    Object obj_rref(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_MVAL,rref));
    ::std::cout<<obj_rref.type().name()<<"\n";
}
void test_cast_1(){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    auto func_1=[](int num){
        ::std::cout<<"int num="<<num<<::std::endl;
    };
    auto func_2=[](int const num){
        ::std::cout<<"int const num="<<num<<::std::endl;
    };
    auto func_3=[](int& num){
        ::std::cout<<"int& num="<<num<<::std::endl;
    };
    auto func_4=[](int const& num){
        ::std::cout<<"int const& num="<<num<<::std::endl;
    };
    int mval=100;
    Object obj_mval(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_MVAL,mval));
    func_1(obj_mval);
    int const cval=100;
    Object obj_cval(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_CVAL,cval));
    func_2(obj_cval);
    int& mref=mval;
    Object obj_mref(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_MREF,mref));
    func_3(obj_mref); 
    int const& cref=cval;
    Object obj_cref(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_CREF,cref));
    func_4(obj_cref);
}
void test_cast_2(){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    int mval=100;
    int& mref=mval;
    Object obj_mref(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_MREF,mref));
    obj_mref.get<int&>()=200;
    assert(mval==200);
    mref=300;
    assert(obj_mref.get<int const&>()==300);
    Object obj_empty;
    static_cast<void>(obj_empty);
}
void test_assign(){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    int mval=100;
    int const cval=200;
    int tmp_1=300;
    int& mref=tmp_1;
    int const tmp_2=400;
    int const& cref=tmp_2;
    Object obj_100(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_MVAL,mval));
    Object obj_200(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_CVAL,cval));
    Object obj_300(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_MREF,mref));
    Object obj_400(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_CREF,cref));

    Object obj_mval(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_MVAL,0));
    obj_mval=obj_100;
    assert(obj_mval.get<int const&>()==100);
    obj_mval=obj_200;
    assert(obj_mval.get<int const&>()==200);
    obj_mval=obj_300;
    assert(obj_mval.get<int const&>()==300);
    obj_mval=obj_400;
    assert(obj_mval.get<int const&>()==400);

    int tmp_3=0;
    int& tmp_4=tmp_3;
    Object obj_mref(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_MREF,tmp_4));
    obj_mref=obj_100;
    assert(obj_mref.get<int const&>()==100);
    obj_mref=obj_200;
    assert(obj_mref.get<int const&>()==200);
    obj_mref=obj_300;
    assert(obj_mref.get<int const&>()==300);
    obj_mref=obj_400;
    assert(obj_mref.get<int const&>()==400);
}
void test(){
    test_ctor_1();
    test_ctor_2();
    test_cast_1();
    test_cast_2();
    test_assign();
}