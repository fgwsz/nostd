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
// [info] type of Constant<bool,true>
// [out] ::value [info] static constance true
// [out] ::ValueType [info] type of ::value
// [out] ::Type [info] type of self instance
// [out] self instance [info] type of Constant<> Instance
using True=Auto<true>;
// false type
// [info] type of Constant<bool,false>
// [out] ::value [info] static constance false
// [out] ::ValueType [info] type of ::value
// [out] ::Type [info] type of self instance
// [out] self instance [info] type of Constant<> Instance
using False=Auto<false>;
// static if
// [info] class template
// [in] _Condition [info] type of Constant<bool,...> Instance
// [in] _Then [info] type
// [in] _Else [info] type
// [out] ::Type [info] type of static if result
template<typename _Condition,typename _Then,typename _Else>
struct IF;
// class template of no return
// [info] class template
// [in] _Types [info] type...
template<typename..._Types>
struct NoReturn;
// class template of do nothing and return _ReturnType
// [info] class template
// [in] _ReturnType [info] type
// [out] ::Type [info] type of _ReturnType
template<typename _ReturnType,typename..._Types>
struct Return;
// static enable if
// [info] alias template
// [in] _Condition [info] type of Constant<bool,...> Instance
// [in] _ReturnType [info] type default is void
// [out] self instance [info] type of _Condition?_ReturnType:Static Error
template<typename _Condition,typename _ReturnType=void>
using Enable=typename Invoke<
    typename IF<_Condition,
        /*?*/Template<Return>,
        /*:*/Template<NoReturn>
    >::Type,
    _ReturnType
>::Type;

#define __META_OPERATOR_BINARY(__OPERATOR__,__OPERATOR_NAME__) \
template<typename _Constant_1,typename _Constant_2> \
struct Operator_##__OPERATOR_NAME__{ \
private: \
    static constexpr decltype(auto) value= \
        (_Constant_1::value) __OPERATOR__ (_Constant_2::value); \
public: \
    using Type=Auto<value>; \
};

#define __META_OPERATOR_UNARY(__OPERATOR__,__OPERATOR_NAME__) \
template<typename _Constant> \
struct Operator_##__OPERATOR_NAME__{ \
private: \
    static constexpr decltype(auto) value= \
        __OPERATOR__ (_Constant::value); \
public: \
    using Type=Auto<value>; \
};

__META_OPERATOR_BINARY(+,Plus      )
__META_OPERATOR_BINARY(-,Minus     )
__META_OPERATOR_BINARY(*,Multiplies)
__META_OPERATOR_BINARY(/,Divides   )
__META_OPERATOR_BINARY(%,Modulus   )
__META_OPERATOR_UNARY (-,Negate    )

__META_OPERATOR_BINARY(==,EqualTo     )
__META_OPERATOR_BINARY(!=,NotEqualTo  )
__META_OPERATOR_BINARY(> ,Greater     )
__META_OPERATOR_BINARY(< ,Less        )
__META_OPERATOR_BINARY(>=,GreaterEqual)
__META_OPERATOR_BINARY(<=,LessEqual   )

__META_OPERATOR_BINARY(&&,LogicalAnd)
__META_OPERATOR_BINARY(||,LogicalOr )
__META_OPERATOR_UNARY (! ,LogicalNot)

__META_OPERATOR_BINARY(&,BitAnd)
__META_OPERATOR_BINARY(|,BitOr )
__META_OPERATOR_BINARY(^,BitXor)
__META_OPERATOR_UNARY (!,BitNot)

__META_OPERATOR_BINARY(<<,LeftShift )
__META_OPERATOR_BINARY(>>,RightShift)

#undef __META_OPERATOR_UNARY
#undef __META_OPERATOR_BINARY

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
struct NoReturn{};
template<typename _ReturnType,typename..._Types>
struct Return{
    using Type=_ReturnType;
};
} // namespace meta
