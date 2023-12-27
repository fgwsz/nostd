#pragma once
#include<cstddef>
#include<cassert>
#include<string>
#include"field.hpp"
struct Person{
    ::std::string name_;
    size_t age_;
};
void test_get(){
    Person p{"Tom",20};
    Field name_field(&Person::name_);
    assert(name_field.get(make_object(p)).safe_cast<::std::string const&>()=="Tom");
    Field age_field(&Person::age_);
    assert(age_field.get(make_object(p)).safe_cast<size_t const&>()==20);
}
void test_set(){
    Person p{"Tom",20};
    Object p_ref=make_object(p);
    Field name_field(&Person::name_);
    name_field.set(p_ref,make_object(::std::string{"Jerry"}));
    assert(p.name_=="Jerry");
    Field age_field(&Person::age_);
    age_field.set(p_ref,make_object(size_t{100}));
    assert(p.age_==100);
}
void test(){
    test_get();
    test_set();
}