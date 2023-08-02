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
template<typename _IsFunction>
struct __Field_IsFunction{
    using is_function=_IsFunction;
};
template<typename _IsMemberFunctionPointer>
struct __Field_IsMemberFunctionPointer{
    using is_member_function_pointer=_IsMemberFunctionPointer;
};
template<typename _ResultType>
struct __Field_ResultType{
    using result_type=_ResultType;
};
template<typename _ClassType>
struct __Field_ClassType{
    using class_type=_ClassType;
};
template<typename _ArgumentList>
struct __Field_ArgumentList{
    using argument_list=_ArgumentList;
};
template<typename _HasCStyleVaList>
struct __Field_HasCStyleVaList{
    using has_c_style_va_list=_HasCStyleVaList;
};
template<typename _HasConst>
struct __Field_HasConst{
    using has_const=_HasConst;
};
template<typename _HasVolatile>
struct __Field_HasVolatile{
    using has_volatile=_HasVolatile;
};
template<typename _HasLeftValueReference>
struct __Field_HasLeftValueReference{
    using has_left_value_reference=_HasLeftValueReference;
};
template<typename _HasRightValueReference>
struct __Field_HasRightValueReference{
    using has_right_value_reference=_HasRightValueReference;
};
template<typename _HasNoexcept>
struct __Field_HasNoexcept{
    using has_noexcept=_HasNoexcept;
};
template<typename _FunctionBaseType>
struct __Field_FunctionBaseType{
    using function_base_type=_FunctionBaseType;
};

template<typename _FunctionType>
struct __FunctionTraits
    :__Field_IsFunction<::std::false_type>
    ,__Field_IsMemberFunctionPointer<::std::false_type>
    ,__Field_ResultType<::nostd::undefined_type>
    ,__Field_ClassType<::nostd::undefined_type>
    ,__Field_ArgumentList<::nostd::undefined_type>
    ,__Field_HasCStyleVaList<::std::false_type>
    ,__Field_HasConst<::std::false_type>
    ,__Field_HasVolatile<::std::false_type>
    ,__Field_HasLeftValueReference<::std::false_type>
    ,__Field_HasRightValueReference<::std::false_type>
    ,__Field_HasNoexcept<::std::false_type>
    ,__Field_FunctionBaseType<::nostd::undefined_type>
{};
#define __NOSTD_EMPTY_MACRO
#define __NOSTD_FUNCTION_TRAITS(__EXT__,__C__,__V__,__LVR__,__RVR__,__N__) \
template< \
    typename _ResultType, \
    typename..._Arguments \
> \
struct __FunctionTraits \
    <_ResultType(_Arguments...)__EXT__> \
    :__Field_IsFunction<::std::true_type> \
    ,__Field_IsMemberFunctionPointer<::std::false_type> \
    ,__Field_ResultType<_ResultType> \
    ,__Field_ClassType<::nostd::undefined_type> \
    ,__Field_ArgumentList<::std::tuple<_Arguments...>> \
    ,__Field_HasCStyleVaList<::std::false_type> \
    ,__Field_HasConst<__C__> \
    ,__Field_HasVolatile<__V__> \
    ,__Field_HasLeftValueReference<__LVR__> \
    ,__Field_HasRightValueReference<__RVR__> \
    ,__Field_HasNoexcept<__N__> \
    ,__Field_FunctionBaseType<_ResultType(_Arguments...)> \
{}; \
template< \
    typename _ResultType, \
    typename..._Arguments \
> \
struct __FunctionTraits \
    <_ResultType(_Arguments...,...)__EXT__> \
    :__Field_IsFunction<::std::true_type> \
    ,__Field_IsMemberFunctionPointer<::std::false_type> \
    ,__Field_ResultType<_ResultType> \
    ,__Field_ClassType<::nostd::undefined_type> \
    ,__Field_ArgumentList<::std::tuple<_Arguments...,::nostd::c_style_va_list_t>> \
    ,__Field_HasCStyleVaList<::std::true_type> \
    ,__Field_HasConst<__C__> \
    ,__Field_HasVolatile<__V__> \
    ,__Field_HasLeftValueReference<__LVR__> \
    ,__Field_HasRightValueReference<__RVR__> \
    ,__Field_HasNoexcept<__N__> \
    ,__Field_FunctionBaseType<_ResultType(_Arguments...,...)> \
{}; \
template< \
    typename _ResultType, \
    typename _ClassType, \
    typename..._Arguments \
> \
struct __FunctionTraits \
    <_ResultType(_ClassType::*)(_Arguments...)__EXT__> \
    :__Field_IsFunction<::std::true_type> \
    ,__Field_IsMemberFunctionPointer<::std::true_type> \
    ,__Field_ResultType<_ResultType> \
    ,__Field_ClassType<_ClassType> \
    ,__Field_ArgumentList<::std::tuple<_Arguments...>> \
    ,__Field_HasCStyleVaList<::std::false_type> \
    ,__Field_HasConst<__C__> \
    ,__Field_HasVolatile<__V__> \
    ,__Field_HasLeftValueReference<__LVR__> \
    ,__Field_HasRightValueReference<__RVR__> \
    ,__Field_HasNoexcept<__N__> \
    ,__Field_FunctionBaseType<_ResultType(_Arguments...)> \
{}; \
template< \
    typename _ResultType, \
    typename _ClassType, \
    typename..._Arguments \
> \
struct __FunctionTraits \
    <_ResultType(_ClassType::*)(_Arguments...,...)__EXT__> \
    :__Field_IsFunction<::std::true_type> \
    ,__Field_IsMemberFunctionPointer<::std::true_type> \
    ,__Field_ResultType<_ResultType> \
    ,__Field_ClassType<_ClassType> \
    ,__Field_ArgumentList<::std::tuple<_Arguments...,::nostd::c_style_va_list_t>> \
    ,__Field_HasCStyleVaList<::std::true_type> \
    ,__Field_HasConst<__C__> \
    ,__Field_HasVolatile<__V__> \
    ,__Field_HasLeftValueReference<__LVR__> \
    ,__Field_HasRightValueReference<__RVR__> \
    ,__Field_HasNoexcept<__N__> \
    ,__Field_FunctionBaseType<_ResultType(_Arguments...,...)> \
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
}
namespace nostd{
template<typename _Function>
using function_traits_t=::nostd::function_traits::__FunctionTraits<
    ::std::remove_cvref_t<
        ::std::remove_pointer_t<
            ::std::remove_cvref_t<_Function>
        >
    >
>;
template<auto _function>
using function_traits_of=::nostd::function_traits_t<decltype(_function)>;
}