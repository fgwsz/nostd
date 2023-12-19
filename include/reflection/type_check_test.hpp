#pragma once
#include<iostream>
#include"reflection/type_check.hpp"
template<
    typename _Type,
    enable_if_t<
        type_check_is_same_id_v<_Type,TypeCheckID::TYPE>||
        type_check_is_same_id_v<_Type,TypeCheckID::TYPE_CONST>||
        type_check_is_same_id_v<_Type,TypeCheckID::TYPE_VOLATILE>||
        type_check_is_same_id_v<_Type,TypeCheckID::TYPE_CONST_VOLATILE>
        ,int
    > _=0
>
void foo(_Type arg){
    ::std::cout<<"type\n";
}
template<
    typename _Type,
    enable_if_t<
        type_check_is_same_id_v<_Type,TypeCheckID::TYPE_LVALUE_REFERENCE>||
        type_check_is_same_id_v<_Type,TypeCheckID::TYPE_CONST_LVALUE_REFERENCE>||
        type_check_is_same_id_v<_Type,TypeCheckID::TYPE_VOLATILE_LVALUE_REFERENCE>||
        type_check_is_same_id_v<_Type,TypeCheckID::TYPE_CONST_VOLATILE_LVALUE_REFERENCE>
        ,int
    > _=0
>
void foo(_Type arg){
    ::std::cout<<"type&\n";
}
template<
    typename _Type,
    enable_if_t<
        type_check_is_same_id_v<_Type,TypeCheckID::TYPE_RVALUE_REFERENCE>||
        type_check_is_same_id_v<_Type,TypeCheckID::TYPE_CONST_RVALUE_REFERENCE>||
        type_check_is_same_id_v<_Type,TypeCheckID::TYPE_VOLATILE_RVALUE_REFERENCE>||
        type_check_is_same_id_v<_Type,TypeCheckID::TYPE_CONST_VOLATILE_RVALUE_REFERENCE>
        ,int
    > _=0
>
void foo(_Type arg){
    ::std::cout<<"type&&\n";
}
int test(void){
    int num=10;
    foo<decltype(num)>(num);
    int& num_lval_ref=num;
    foo<decltype(num_lval_ref)>(num_lval_ref);
    foo<int&&>(::std::move(int{100}));
    int const num_const=10;
    foo<decltype(num_const)>(num_const);
    return 0;
}