#pragma once
#include<type_traits>
namespace nostd{
/*--------------------------------------------------------------------------------------*/
// 通用数据类型
/*--------------------------------------------------------------------------------------*/

// 未定义类型
struct Undefined;
// 布尔类型
using bool_t=bool;
// 无符号整数类型
using usize_t=unsigned long long;

/*--------------------------------------------------------------------------------------*/
// 通用标签类型
/*--------------------------------------------------------------------------------------*/

// 常量外覆类tag类
struct TagOfConstantWrapper;
// 模板外覆类tag类
struct TagOfTemplateWrapper;
// 变长模板参数外覆类tag类
struct TagOfArgumentsWrapper;

/*--------------------------------------------------------------------------------------*/
// 通用域相关
/*--------------------------------------------------------------------------------------*/

// type域
// public继承此类实例化类型获得type类型别名域
template<typename _Type>
struct TypeField{
    using type=_Type;
};
// value域
// public继承此类实例化类型获得value静态成员变量域
template<typename _Type,_Type _value>
struct ValueField{
    static constexpr _Type value=_value;
};
// apply域
// public继承此类实例化类型获得apply别名模板域
template<template<typename...>typename _Template>
struct ApplyField{
    template<typename..._Types>
    using apply=_Template<_Types...>;
};
// tag域
// public继承此类实例化类型获得tag类型别名域
template<typename _Tag>
struct TagField{
    using tag=_Tag;
};
// 得到类型的type域
template<typename _Type>
using get_field_type=
    typename _Type::type;
// 得到类型的value域
template<typename _Type>
static constexpr decltype(auto) get_field_value=
    _Type::value;
// 得到类型的apply域
template<typename _Type,typename..._Types>
using get_field_apply=
    typename _Type::template apply<_Types...>;
// 得到类型的apply域的调用结果(apply<>::type) 
template<typename _Type,typename..._Types>
using get_field_apply_type=
    get_field_type<get_field_apply<_Type,_Types...>>;
// 得到类型的apply域的调用结果(apply<>::value) 
template<typename _Type,typename..._Types>
static constexpr decltype(auto) get_field_apply_value=
    get_field_value<get_field_apply<_Type,_Types...>>;
// 得到类型的tag域
template<typename _Type>
using get_field_tag=
    typename _Type::tag;
// 查看类型是否存在tag域
template<typename _Type>
concept has_field_tag=requires{
    typename _Type::tag;
};
// 查看类型的tag域是否是模板参数中指定的类型
template<typename _Type,typename _Tag>
concept check_field_tag=has_field_tag<_Type>&&
    ::std::is_same_v<get_field_tag<_Type>,_Tag>;

/*--------------------------------------------------------------------------------------*/
// 通用外覆类模板
/*--------------------------------------------------------------------------------------*/

// 常量外覆类 
template<typename _Type,_Type _value>
struct ConstantWrapper
    :ValueField<_Type,_value>
    ,TagField<TagOfConstantWrapper>
{
    using value_type=_Type;
};
// 布尔类型常量
template<bool_t _value>
using bool_constant=ConstantWrapper<bool_t,_value>;
// true布尔类型常量
using true_constant=bool_constant<true>;
// false布尔类型常量
using false_constant=bool_constant<false>;
// 无符号类型常量
template<usize_t _value>
using usize_constant=ConstantWrapper<usize_t,_value>;
// 模板外覆类
template<template<typename...>typename _Template>
struct TemplateWrapper
    :ApplyField<_Template>
    ,TagField<TagOfTemplateWrapper>
{};
// 变长模板参数外覆类
template<typename..._Arguments>
struct ArgumentsWrapper;
template<>
struct ArgumentsWrapper<>
    :TagField<TagOfArgumentsWrapper>
{
    using first_argument=Undefined;
    using tail=ArgumentsWrapper<>;
    static constexpr usize_t size=0;
};
template<typename _FirstArgument,typename..._Arguments>
struct ArgumentsWrapper<_FirstArgument,_Arguments...>
    :TagField<TagOfArgumentsWrapper>
{
    using first_argument=_FirstArgument;
    using tail=ArgumentsWrapper<_Arguments...>;
    static constexpr usize_t size=1+sizeof...(_Arguments);
};

/*--------------------------------------------------------------------------------------*/
// 通用模板参数检查
/*--------------------------------------------------------------------------------------*/

// 检查类型是否为ConstantWrapper的实例化类型
template<typename _Type,typename _ValueType>
concept check_constant=check_field_tag<_Type,TagOfConstantWrapper>&&
    ::std::is_same_v<typename _Type::value_type,_ValueType>;
// 检查类型是否为bool_constant的实例化类型
template<typename _Type>
concept check_bool_constant=check_constant<_Type,bool_t>;
// 检查类型是否为usize_constant的实例化类型
template<typename _Type>
concept check_usize_constant=check_constant<_Type,usize_t>;

/*--------------------------------------------------------------------------------------*/
// 通用元函数
/*--------------------------------------------------------------------------------------*/

// 模板实例化类型转化为模板外覆类
template<typename _TemplateInstance>
struct TemplateInstanceToWrapper
    :TypeField<Undefined>
{};
template<template<typename...>typename _Template,typename..._Types>
struct TemplateInstanceToWrapper<_Template<_Types...>>
    :TypeField<TemplateWrapper<_Template>>
{};
// 模板外覆类实例化类型转化为模板实例化类型
template<check_field_tag<TagOfTemplateWrapper> _TemplateWrapperInstance,typename..._Types>
struct TemplateWrapperToInstance
    :TypeField<get_field_apply<_TemplateWrapperInstance,_Types...>>
{};
// 判断两个模板是否为同一个模板
template<
    template<typename...>typename _Template_1,
    template<typename...>typename _Template_2
>struct IsSameTemplate
    :false_constant
{};
template<template<typename...>typename _Template>
struct IsSameTemplate<_Template,_Template>
    :true_constant
{};
// 二重分支结构if then else
template<
    check_bool_constant _condition,
    typename _Then,
    typename _Else
>struct IfThenElse;
template<
    typename _Then,
    typename _Else
>struct IfThenElse<true_constant,_Then,_Else>
    :TypeField<_Then>
{};
template<
    typename _Then,
    typename _Else
>struct IfThenElse<false_constant,_Then,_Else>
    :TypeField<_Else>
{};
// TODO
// _Condition,_Then,_Else is meta_function
/*
if(_Condition())then
    return _Then()
else
    return _Else()
*/
// 多重分支结构辅助数据类
// 多重分支结构switch
}
