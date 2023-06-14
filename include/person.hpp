#pragma once
#include"c_str_view.hpp"
struct Person{
    size_t age;
    char* name;
};
NOSTD_REGIST_TYPE(Person)
