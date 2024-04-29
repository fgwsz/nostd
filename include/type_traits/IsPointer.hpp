#pragma once
#include"bool_constant.hpp"
template<typename _Type>
struct IsPointer
    :false_type
{};
template<typename _Type>
struct IsPointer
    <_Type*>
    :true_type
{};
template<typename _Type>
struct IsPointer
    <_Type*const>
    :true_type
{};
template<typename _Type>
struct IsPointer
    <_Type*volatile>
    :true_type
{};
template<typename _Type>
struct IsPointer
    <_Type*const volatile>
    :true_type
{};
template<typename _Type>
using is_pointer=typename IsPointer<_Type>::type;
template<typename _Type>
static constexpr auto is_pointer_v=is_pointer<_Type>::value;
