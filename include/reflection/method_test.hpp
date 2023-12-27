#pragma once
#include<cstddef>
#include<cassert>
#include<string>
#include<iostream>
#include"method.hpp"
struct Person{
    ::std::string name_;
    size_t age_;
    inline void set(::std::string const& name,size_t age)noexcept{
        this->name_=name;
        this->age_=age;
    }
    inline ::std::string& get_name()noexcept{
        return this->name_;
    }
    inline size_t& get_age()noexcept{
        return this->age_;
    }
};
void test_(){
    Person p;
    Object p_ref=make_object(p);
    Method m1(&Person::set);
    ::std::cout<<"class:"<<m1.class_type().name()<<"\n";
    ::std::cout<<"result:"<<m1.result_type().name()<<"\n";
    ::std::cout<<"parameters:[";
    for(auto const& element:m1.parameter_type_list()){
        ::std::cout<<element.name()<<",";
    }
    ::std::cout<<"]\n";
    m1.invoke_by_args(p,::std::string{"Tom"},size_t{20});
    assert(p.name_=="Tom");
    assert(p.age_==20);
    m1.invoke_by_objects(::std::vector<Object>{
        p_ref,
        ::make_object(::std::string{"Jerry"}),
        ::make_object(size_t{100})
    });
    assert(p.name_=="Jerry");
    assert(p.age_==100);
}
void test(){
    test_();
}