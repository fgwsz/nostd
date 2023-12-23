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
class Foo{
public:
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
private:
    void _foo_impl(){
        ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    }
};
void test_func_ctor(){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    char temp='A';
    Function f1(&foo_1);
    ::std::cout<<f1.type().name()<<"\n";
    int ret_1=f1(1,3.14,temp,::std::string("hello"));
    Function f2(&foo_2);
    ::std::cout<<f2.type().name()<<"\n";
    f2(1,3.14,temp,::std::string("hello"));
    Function f3(&foo_3);
    ::std::cout<<f3.type().name()<<"\n";
    int ret_3=f3();
    Function f4(&foo_4);
    ::std::cout<<f4.type().name()<<"\n";
    f4();
}
void test_mem_func_ctor(){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    char temp='A';
    Foo obj;
    Function mf1(&Foo::foo_1);
    ::std::cout<<mf1.type().name()<<"\n";
    int ret_1=mf1(obj,1,3.14,temp,::std::string("hello"));
    Function mf2(&Foo::foo_2);
    ::std::cout<<mf2.type().name()<<"\n";
    mf2(obj,1,3.14,temp,::std::string("hello"));
    Function mf3(&Foo::foo_3);
    ::std::cout<<mf3.type().name()<<"\n";
    int ret_3=mf3(obj);
    Function mf4(&Foo::foo_4);
    ::std::cout<<mf4.type().name()<<"\n";
    mf4(obj);
}
void test_func_assign(){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    char temp='A';
    Function f1(&foo_1);
    Function f2(&foo_2);
    Function f3(&foo_3);
    Function f4(&foo_4);
    Function fn;
    fn=f1;
    ::std::cout<<fn.type().name()<<"\n";
    int ret_1=fn(1,3.14,temp,::std::string("hello"));
    fn=f2;
    ::std::cout<<fn.type().name()<<"\n";
    fn(1,3.14,temp,::std::string("hello"));
    fn=f3;
    ::std::cout<<fn.type().name()<<"\n";
    int ret_3=fn();
    fn=f4;
    ::std::cout<<fn.type().name()<<"\n";
    auto ret_4=fn();
}
void test_mem_func_assign(){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    char temp='A';
    Foo obj;
    Function mf1(&Foo::foo_1);
    Function mf2(&Foo::foo_2);
    Function mf3(&Foo::foo_3);
    Function mf4(&Foo::foo_4);
    Function mfn;
    mfn=mf1;
    ::std::cout<<mfn.type().name()<<"\n";
    int ret_1=mfn(obj,1,3.14,temp,::std::string("hello"));
    mfn=mf2;
    ::std::cout<<mfn.type().name()<<"\n";
    mfn(obj,1,3.14,temp,::std::string("hello"));
    mfn=mf3;
    ::std::cout<<mfn.type().name()<<"\n";
    int ret_3=mfn(obj);
    mfn=mf4;
    ::std::cout<<mfn.type().name()<<"\n";
    mfn(obj);
}
void test_access(){
    // auto mem_func=&Foo::_foo_impl; // 无法访问类私有成员
    // Function mf1(mem_func);
    // Foo obj;
    // mf1(obj);
}
void test(){
    test_func_ctor();
    test_mem_func_ctor();
    test_func_assign();
    test_mem_func_assign();
}