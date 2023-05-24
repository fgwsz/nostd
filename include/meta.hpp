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

// static constance sequence to type
// [info] class template
// [in] _Type [info] type
// [in] _values [info] static constance...
// [out] ::value [info] static constance array assign by _values
// [out] ::length [info] static constance element number(>0) of ::value
// [out] ::ValueType [info] type of ::value element
// [out] ::Type [info] type of self instance
// [out] self instance [info] type
template<typename _Type,_Type..._values>
struct Sequence;
// type trait of is same
// [info] class template
// [in] _Type_1 [info] type
// [in] _Type_2 [info] type
// [out] ::Type [info] type of _Type_1==_Type_2?True:False
template<typename _Type_1,typename _Type_2>
struct IsSame;
// concat static constance sequences
// [info] class template
// [in] _Sequence_1 [info] type of Sequence<> Instance
// [in] _Sequence_2 [info] type of Sequence<> Instance
// [in] _Sequences [info] types... of Sequence<> Instance
// [out] ::Type [info] type of Sequence<> Instance
template<typename _Sequence_1,typename _Sequence_2,typename..._Sequences>
struct Sequence_Concat;
// size type
// [info] type alias of unsigned long long
// [out] self instance [info] type
using SizeType=unsigned long long;
// create a static constance sequences of [_BeginIndex,_EndIndex)
// [info] class template
// [in] _BeginIndex [info] type of Constant<SizeType,...> Instance
// [in] _EndIndex [info] type of Constant<SizeType,...> Instance
// [out] ::Type [info] type of Sequence<SizeType,...> Instance
template<typename _BeginIndex,typename _EndIndex>
struct Sequence_MakeIndexs;

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
template<typename _Type,_Type..._values>
struct Sequence{
    static constexpr auto length=sizeof...(_values);
    static constexpr _Type value[length]={_values...};
    using ValueType=_Type;
    using Type=Sequence;
};
template<typename _Type_1,typename _Type_2>
struct IsSame{
    using Type=False;
};
template<typename _Type>
struct IsSame<_Type,_Type>{
    using Type=True;
};
template<typename _Sequence_1,typename _Sequence_2>
struct __Sequence_Concat_Helper;
template<typename _Type,_Type..._values_1,_Type..._values_2>
struct __Sequence_Concat_Helper<
    Sequence<_Type,_values_1...>,
    Sequence<_Type,_values_2...>
>{
    using Type=Sequence<_Type,_values_1...,_values_2...>;
};
template<typename _Sequence_1,typename _Sequence_2,typename..._Sequences>
struct Sequence_Concat{
    using Type=typename __Sequence_Concat_Helper<
        _Sequence_1,
        typename Invoke<
            typename IF<Auto<sizeof...(_Sequences)!=0>,
                Template<Sequence_Concat>,
                Template<Return>
            >::Type,
            _Sequence_2,
            _Sequences...
        >::Type
    >::Type;
};
template<typename _BeginIndex,typename _EndIndex>
struct Sequence_MakeIndexs{
private:
    static_assert(_BeginIndex::value<_EndIndex::value,
        "_BeginIndex must be less than _EndIndex");
    using LoopEnd=Auto<_BeginIndex::value+1==_EndIndex::value>;
    using NextBeginIndex=Constant<SizeType,_BeginIndex::value+1>;
    /*
    if(LoopEnd) { 
        return Sequence<SizeType,_BeginIndex>; 
    }
    else { 
        return Sequenec_Concat(
            Sequence<SizeType,_BeginIndex>,
            Sequence_MakeIndexs<_BeginIndex+1,_EndIndex>
        );
    }
    */
public:
    using Type=typename Invoke<
        typename IF<LoopEnd,
            Template<Return>,
            Template<Sequence_Concat>
        >::Type,
        Sequence<SizeType,_BeginIndex::value>,
        typename Invoke<
            typename IF<LoopEnd,
                Template<Return>,
                Template<Sequence_MakeIndexs>
            >::Type,
            NextBeginIndex,
            _EndIndex
        >::Type
    >::Type;
};
} // namespace meta
