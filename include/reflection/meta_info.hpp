#pragma once
#include<string_view>
#include"field.hpp"
#include"method.hpp"
#include"ordered_map.hpp"
using string_t=::std::string_view;
struct ClassMetaInfo{
    string_t name_;
    OrderedMap<string_t,Field> fields_;
    OrderedMap<string_t,Method> methods_;
};
struct Person{
    string_t name_;
    size_t age_;
};
ClassMetaInfo class_info{
    .name_="::Person",
    .fields_={
        {"name",Field(&Person::name_)},
        {"age",Field(&Person::age_)}
    },
    .methods_={}
};