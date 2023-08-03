#pragma once
#include<type_traits>
#include<tuple>
#include<cstdarg>
namespace nostd{
struct undefined_type;
struct CStyleVaList{
    CStyleVaList(...){}
};
using c_style_va_list_t=CStyleVaList;
}
namespace nostd::function_traits{
#define __NOSTD_TYPE_FIELD_DEFINE(__NAME__) \
template<typename _Type> \
struct __TypeField_##__NAME__{ \
    using __NAME__=_Type; \
}; \
//
__NOSTD_TYPE_FIELD_DEFINE(is_function)
__NOSTD_TYPE_FIELD_DEFINE(is_member_function_pointer)
__NOSTD_TYPE_FIELD_DEFINE(result_type)
__NOSTD_TYPE_FIELD_DEFINE(class_type)
__NOSTD_TYPE_FIELD_DEFINE(argument_list)
__NOSTD_TYPE_FIELD_DEFINE(has_c_style_va_list)
__NOSTD_TYPE_FIELD_DEFINE(has_const)
__NOSTD_TYPE_FIELD_DEFINE(has_volatile)
__NOSTD_TYPE_FIELD_DEFINE(has_left_value_reference)
__NOSTD_TYPE_FIELD_DEFINE(has_right_value_reference)
__NOSTD_TYPE_FIELD_DEFINE(has_noexcept)
__NOSTD_TYPE_FIELD_DEFINE(function_base_type)
#undef __NOSTD_TYPE_FIELD_DEFINE
//
#define __NOSTD_TYPE_FIELD_SET(__NAME__,...) \
__TypeField_##__NAME__<__VA_ARGS__>
//
template<typename _FunctionType>
struct __FunctionTraits
    :__NOSTD_TYPE_FIELD_SET(is_function,::std::false_type)
    ,__NOSTD_TYPE_FIELD_SET(is_member_function_pointer,::std::false_type)
    ,__NOSTD_TYPE_FIELD_SET(result_type,::nostd::undefined_type)
    ,__NOSTD_TYPE_FIELD_SET(class_type,::nostd::undefined_type)
    ,__NOSTD_TYPE_FIELD_SET(argument_list,::nostd::undefined_type)
    ,__NOSTD_TYPE_FIELD_SET(has_c_style_va_list,::std::false_type)
    ,__NOSTD_TYPE_FIELD_SET(has_const,::std::false_type)
    ,__NOSTD_TYPE_FIELD_SET(has_volatile,::std::false_type)
    ,__NOSTD_TYPE_FIELD_SET(has_left_value_reference,::std::false_type)
    ,__NOSTD_TYPE_FIELD_SET(has_right_value_reference,::std::false_type)
    ,__NOSTD_TYPE_FIELD_SET(has_noexcept,::std::false_type)
    ,__NOSTD_TYPE_FIELD_SET(function_base_type,::nostd::undefined_type)
{};
#define __NOSTD_EMPTY_MACRO
#define __NOSTD_FUNCTION_TRAITS(__EXT__,__C__,__V__,__LVR__,__RVR__,__N__) \
template< \
    typename _ResultType, \
    typename..._Arguments \
> \
struct __FunctionTraits \
    <_ResultType(_Arguments...)__EXT__> \
    :__NOSTD_TYPE_FIELD_SET(is_function,::std::true_type) \
    ,__NOSTD_TYPE_FIELD_SET(is_member_function_pointer,::std::false_type) \
    ,__NOSTD_TYPE_FIELD_SET(result_type,_ResultType) \
    ,__NOSTD_TYPE_FIELD_SET(class_type,::nostd::undefined_type) \
    ,__NOSTD_TYPE_FIELD_SET(argument_list,::std::tuple<_Arguments...>) \
    ,__NOSTD_TYPE_FIELD_SET(has_c_style_va_list,::std::false_type) \
    ,__NOSTD_TYPE_FIELD_SET(has_const,__C__) \
    ,__NOSTD_TYPE_FIELD_SET(has_volatile,__V__) \
    ,__NOSTD_TYPE_FIELD_SET(has_left_value_reference,__LVR__) \
    ,__NOSTD_TYPE_FIELD_SET(has_right_value_reference,__RVR__) \
    ,__NOSTD_TYPE_FIELD_SET(has_noexcept,__N__) \
    ,__NOSTD_TYPE_FIELD_SET(function_base_type,_ResultType(_Arguments...)) \
{}; \
template< \
    typename _ResultType, \
    typename..._Arguments \
> \
struct __FunctionTraits \
    <_ResultType(_Arguments...,...)__EXT__> \
    :__NOSTD_TYPE_FIELD_SET(is_function,::std::true_type) \
    ,__NOSTD_TYPE_FIELD_SET(is_member_function_pointer,::std::false_type) \
    ,__NOSTD_TYPE_FIELD_SET(result_type,_ResultType) \
    ,__NOSTD_TYPE_FIELD_SET(class_type,::nostd::undefined_type) \
    ,__NOSTD_TYPE_FIELD_SET(argument_list,::std::tuple<_Arguments...,::nostd::c_style_va_list_t>) \
    ,__NOSTD_TYPE_FIELD_SET(has_c_style_va_list,::std::true_type) \
    ,__NOSTD_TYPE_FIELD_SET(has_const,__C__) \
    ,__NOSTD_TYPE_FIELD_SET(has_volatile,__V__) \
    ,__NOSTD_TYPE_FIELD_SET(has_left_value_reference,__LVR__) \
    ,__NOSTD_TYPE_FIELD_SET(has_right_value_reference,__RVR__) \
    ,__NOSTD_TYPE_FIELD_SET(has_noexcept,__N__) \
    ,__NOSTD_TYPE_FIELD_SET(function_base_type,_ResultType(_Arguments...,...)) \
{}; \
template< \
    typename _ResultType, \
    typename _ClassType, \
    typename..._Arguments \
> \
struct __FunctionTraits \
    <_ResultType(_ClassType::*)(_Arguments...)__EXT__> \
    :__NOSTD_TYPE_FIELD_SET(is_function,::std::true_type) \
    ,__NOSTD_TYPE_FIELD_SET(is_member_function_pointer,::std::true_type) \
    ,__NOSTD_TYPE_FIELD_SET(result_type,_ResultType) \
    ,__NOSTD_TYPE_FIELD_SET(class_type,_ClassType) \
    ,__NOSTD_TYPE_FIELD_SET(argument_list,::std::tuple<_Arguments...>) \
    ,__NOSTD_TYPE_FIELD_SET(has_c_style_va_list,::std::false_type) \
    ,__NOSTD_TYPE_FIELD_SET(has_const,__C__) \
    ,__NOSTD_TYPE_FIELD_SET(has_volatile,__V__) \
    ,__NOSTD_TYPE_FIELD_SET(has_left_value_reference,__LVR__) \
    ,__NOSTD_TYPE_FIELD_SET(has_right_value_reference,__RVR__) \
    ,__NOSTD_TYPE_FIELD_SET(has_noexcept,__N__) \
    ,__NOSTD_TYPE_FIELD_SET(function_base_type,_ResultType(_Arguments...)) \
{}; \
template< \
    typename _ResultType, \
    typename _ClassType, \
    typename..._Arguments \
> \
struct __FunctionTraits \
    <_ResultType(_ClassType::*)(_Arguments...,...)__EXT__> \
    :__NOSTD_TYPE_FIELD_SET(is_function,::std::true_type) \
    ,__NOSTD_TYPE_FIELD_SET(is_member_function_pointer,::std::true_type) \
    ,__NOSTD_TYPE_FIELD_SET(result_type,_ResultType) \
    ,__NOSTD_TYPE_FIELD_SET(class_type,_ClassType) \
    ,__NOSTD_TYPE_FIELD_SET(argument_list,::std::tuple<_Arguments...,::nostd::c_style_va_list_t>) \
    ,__NOSTD_TYPE_FIELD_SET(has_c_style_va_list,::std::true_type) \
    ,__NOSTD_TYPE_FIELD_SET(has_const,__C__) \
    ,__NOSTD_TYPE_FIELD_SET(has_volatile,__V__) \
    ,__NOSTD_TYPE_FIELD_SET(has_left_value_reference,__LVR__) \
    ,__NOSTD_TYPE_FIELD_SET(has_right_value_reference,__RVR__) \
    ,__NOSTD_TYPE_FIELD_SET(has_noexcept,__N__) \
    ,__NOSTD_TYPE_FIELD_SET(function_base_type,_ResultType(_Arguments...,...)) \
{}; \
//
/*
__NOSTD_FUNCTION_TRAITS(__EXT__                 ,__C__            ,__V__            ,__LVR__          ,__RVR__          ,__N__            )
*/
//
__NOSTD_FUNCTION_TRAITS(__NOSTD_EMPTY_MACRO     ,::std::false_type,::std::false_type,::std::false_type,::std::false_type,::std::false_type)
__NOSTD_FUNCTION_TRAITS(const                   ,::std::true_type ,::std::false_type,::std::false_type,::std::false_type,::std::false_type)
__NOSTD_FUNCTION_TRAITS(volatile                ,::std::false_type,::std::true_type ,::std::false_type,::std::false_type,::std::false_type)
__NOSTD_FUNCTION_TRAITS(const volatile          ,::std::true_type ,::std::true_type ,::std::false_type,::std::false_type,::std::false_type)

__NOSTD_FUNCTION_TRAITS(&                       ,::std::false_type,::std::false_type,::std::true_type ,::std::false_type,::std::false_type)
__NOSTD_FUNCTION_TRAITS(const&                  ,::std::true_type ,::std::false_type,::std::true_type ,::std::false_type,::std::false_type)
__NOSTD_FUNCTION_TRAITS(volatile&               ,::std::false_type,::std::true_type ,::std::true_type ,::std::false_type,::std::false_type)
__NOSTD_FUNCTION_TRAITS(const volatile&         ,::std::true_type ,::std::true_type ,::std::true_type ,::std::false_type,::std::false_type)

__NOSTD_FUNCTION_TRAITS(&&                      ,::std::false_type,::std::false_type,::std::false_type,::std::true_type ,::std::false_type)
__NOSTD_FUNCTION_TRAITS(const&&                 ,::std::true_type ,::std::false_type,::std::false_type,::std::true_type ,::std::false_type)
__NOSTD_FUNCTION_TRAITS(volatile&&              ,::std::false_type,::std::true_type ,::std::false_type,::std::true_type ,::std::false_type)
__NOSTD_FUNCTION_TRAITS(const volatile&&        ,::std::true_type ,::std::true_type ,::std::false_type,::std::true_type ,::std::false_type)

__NOSTD_FUNCTION_TRAITS(noexcept                ,::std::false_type,::std::false_type,::std::false_type,::std::false_type,::std::true_type )
__NOSTD_FUNCTION_TRAITS(const noexcept          ,::std::true_type ,::std::false_type,::std::false_type,::std::false_type,::std::true_type )
__NOSTD_FUNCTION_TRAITS(volatile noexcept       ,::std::false_type,::std::true_type ,::std::false_type,::std::false_type,::std::true_type )
__NOSTD_FUNCTION_TRAITS(const volatile noexcept ,::std::true_type ,::std::true_type ,::std::false_type,::std::false_type,::std::true_type )

__NOSTD_FUNCTION_TRAITS(&noexcept               ,::std::false_type,::std::false_type,::std::true_type ,::std::false_type,::std::true_type )
__NOSTD_FUNCTION_TRAITS(const&noexcept          ,::std::true_type ,::std::false_type,::std::true_type ,::std::false_type,::std::true_type )
__NOSTD_FUNCTION_TRAITS(volatile&noexcept       ,::std::false_type,::std::true_type ,::std::true_type ,::std::false_type,::std::true_type )
__NOSTD_FUNCTION_TRAITS(const volatile&noexcept ,::std::true_type ,::std::true_type ,::std::true_type ,::std::false_type,::std::true_type )

__NOSTD_FUNCTION_TRAITS(&&noexcept              ,::std::false_type,::std::false_type,::std::false_type,::std::true_type ,::std::true_type )
__NOSTD_FUNCTION_TRAITS(const&&noexcept         ,::std::true_type ,::std::false_type,::std::false_type,::std::true_type ,::std::true_type )
__NOSTD_FUNCTION_TRAITS(volatile&&noexcept      ,::std::false_type,::std::true_type ,::std::false_type,::std::true_type ,::std::true_type )
__NOSTD_FUNCTION_TRAITS(const volatile&&noexcept,::std::true_type ,::std::true_type ,::std::false_type,::std::true_type ,::std::true_type )
#undef __NOSTD_FUNCTION_TRAITS
#undef __NOSTD_EMPTY_MACRO
#undef __NOSTD_TYPE_FIELD_SET
}
namespace nostd{
template<typename _Type>
static constexpr auto is_unmember_function_v=
    ::std::is_function_v<::std::remove_cvref_t<_Type>>;
template<typename _Type>
static constexpr auto is_unmember_function_pointer_v=
    ::std::is_pointer_v<::std::remove_cvref_t<_Type>>&&
    ::nostd::is_unmember_function_v<
        ::std::remove_pointer_t<::std::remove_cvref_t<_Type>>
    >;
template<typename _Type>
static constexpr auto is_functor_v=requires{
    ::std::remove_cvref_t<_Type>::operator();
};
template<typename _Type>
static constexpr auto is_member_function_pointer_v=
    ::std::is_member_function_pointer_v<::std::remove_cvref_t<_Type>>;
template<typename _Type>
static constexpr auto is_function_v=
    ::nostd::is_unmember_function_v<_Type>||
    ::nostd::is_unmember_function_pointer_v<_Type>||
    ::nostd::is_functor_v<_Type>||
    ::nostd::is_member_function_pointer_v<_Type>;
}
namespace nostd::function_traits{
struct __GetFunctionCase0{
    template<typename _Type>
    struct Apply{
        using type=::std::remove_pointer_t<::std::remove_cvref_t<_Type>>;
    };
};
struct __GetFunctionCase1{
    template<typename _Type>
    struct Apply{
        using type=decltype(&::std::remove_cvref_t<_Type>::operator());
    };
};
struct __GetFunctionCase2{
    template<typename _Type>
    struct Apply{
        using type=::std::remove_cvref_t<_Type>;
    };
};
struct __GetFunctionCase3{
    template<typename _Type>
    struct Apply{
        using type=_Type;
    };
};
template<typename _Type>
using __get_function_type=typename ::std::conditional_t<
    ::nostd::is_unmember_function_pointer_v<_Type>,
    __GetFunctionCase0,
    ::std::conditional_t<
        ::nostd::is_functor_v<_Type>,
        __GetFunctionCase1,
        ::std::conditional_t<
            ::nostd::is_function_v<_Type>,
            __GetFunctionCase2,
            __GetFunctionCase3
        >
    >
>::template Apply<_Type>::type;
}
namespace nostd{
template<typename _Type>
using function_traits_t=::nostd::function_traits::__FunctionTraits<
    ::nostd::function_traits::__get_function_type<_Type>
>;
#define NOSTD_FUNCTION_TRAITS_OF(...) \
    ::nostd::function_traits_t<decltype(__VA_ARGS__)> \
//
}