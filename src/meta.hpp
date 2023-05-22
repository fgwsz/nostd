#pragma once
namespace meta{
// _Type: Type
// _value: value
// Constant<...> / typename Constant<...>::Type
// Constant<...>::value / Constant<...>::Type::value
template<typename _Type,_Type _value>
struct Constant{
    static constexpr _Type value=_value;
    using Type=Constant;
};
// _Template: class template
// Template<...> / typename Template<...>::Type
// Template<...>::template Self / Template<...>::Type::template Self
template<template<typename...>class _Template>
struct Template{
    template<typename..._Types>
    using Self=_Template<_Types...>;
    using Type=Template;
};
// _Template: Template
// _Types: Type
// Invoke<...> <=> Template<class template>::template Self<Types...>
template<typename _Template,typename..._Types>
using Invoke=_Template::template Self<_Types...>;
// _value: bool value
template<bool _value>
using Boolean=Constant<bool,_value>;
// True
using True=Constant<bool,true>;
// False
using False=Constant<bool,false>;
// _Condition: Boolean
// _Then: Type
// _Else: Type
// typename IF<...>::Type
// IF(_Condition==True){ return _Then; }
// Else{ return _Else; }
template<typename _Condition,typename _Then,typename _Else>
struct IF;
template<typename _Then,typename _Else>
struct IF<True,_Then,_Else>{
    using Type=_Then;
};
template<typename _Then,typename _Else>
struct IF<False,_Then,_Else>{
    using Type=_Else;
};
// _Types: Type
// template DoNothing<...>::Type = void
template<typename..._Types>
struct DoNothing{
    using Type=void;
};
} // namespace meta
