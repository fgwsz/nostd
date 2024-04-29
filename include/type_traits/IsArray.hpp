#pragma once
#include"bool_constant.hpp"
#include"size_t.h"
template<typename _Type>
struct IsArray
    :false_type
{};
template<typename _Type>
struct IsArray
    <_Type[]>
    :true_type
{};
template<typename _Type,size_t _size>
struct IsArray
    <_Type[_size]>
    :true_type
{};
template<typename _Type>
using is_array=typename IsArray<_Type>::type;
template<typename _Type>
static constexpr auto is_array_v=is_array<_Type>::value;
