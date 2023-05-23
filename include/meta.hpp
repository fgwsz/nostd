#pragma once
namespace meta{
// static constance to type
// [info] class template
// [in] _Type [info] type
// [in] _value [info] static constance
// [out] ::value [info] static constance equal _value
// [out] ::ValueType [info] type of ::value
// [out] ::Type [info] type of self instance
// [out] self instance [info] type
template<typename _Type,_Type _value>
struct Constant;
// class template to type
// [info] class template
// [in] _ClassTemplate [info] class template
// [out] ::Self [info] alias template of _ClassTemplate
// [out] ::Type [info] type of self instance
// [out] self instance [info] type
template<template<typename...>class _ClassTemplate>
struct Template;
// invoke Template<> instance Self class template
// [info] alias template
// [in] _TemplateInstance [info] type of Template<> Instance
// [in] _Types [info] type... 
//     as arguments of Template<> Instance Self class template
// [out] self instance [info] type
template<typename _TemplateInstance,typename..._Types>
using Invoke=_TemplateInstance::template Self<_Types...>;
// alias template of Constant
// [info] alias template
// [in] _value [info] static constance
// [out] ::value [info] static constance equal _value
// [out] ::ValueType [info] type of ::value
// [out] ::Type [info] type of self instance
// [out] self instance [info] type
template<auto _value>
using Auto=Constant<decltype(_value),_value>;
// true type
// [info] type
// [out] ::value [info] static constance true
// [out] ::ValueType [info] type of ::value
// [out] ::Type [info] type of self instance
// [out] self instance [info] type of Constant<> Instance
using True=Auto<true>;
// false type
// [info] type
// [out] ::value [info] static constance false
// [out] ::ValueType [info] type of ::value
// [out] ::Type [info] type of self instance
// [out] self instance [info] type of Constant<> Instance
using False=Auto<false>;
// static if
// [info] class template
// [in] _Condition [info] type of Constance<bool,...> Instance
// [in] _Then [info] type
// [in] _Else [info] type
// [out] ::Type [info] type of static if result
template<typename _Condition,typename _Then,typename _Else>
struct IF;
// class template of and do nothing
// [info] class template
// [in] _Types [info] type... 
// [out] ::Type [info] type of void
template<typename..._Types>
struct DoNothing;

// ===========================================================================
// IMPL
// ===========================================================================

template<typename _Type,_Type _value>
struct Constant{
    static constexpr _Type value=_value;
    using ValueType=_Type;
    using Type=Constant;
};
template<template<typename...>class _ClassTemplate>
struct Template{
    template<typename..._Types>
    using Self=_ClassTemplate<_Types...>;
    using Type=Template;
};
template<typename _Then,typename _Else>
struct IF<True,_Then,_Else>{
    using Type=_Then;
};
template<typename _Then,typename _Else>
struct IF<False,_Then,_Else>{
    using Type=_Else;
};
template<typename..._Types>
struct DoNothing{
    using Type=void;
};
} // namespace meta
