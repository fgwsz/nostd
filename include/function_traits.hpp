#pragma once
#include<type_traits>
#include<cstdarg>
namespace nostd{
struct Undefined;
using undefined_t=Undefined;
struct CStyleVaList{
    ::std::size_t  count_;
    ::std::va_list start_;
};
using c_style_va_list_t=CStyleVaList;
template<typename..._Types>
struct ParameterList{};
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
static constexpr auto is_member_function_pointer_v=
    ::std::is_member_function_pointer_v<::std::remove_cvref_t<_Type>>;
template<typename _Type>
static constexpr auto is_functor_v=requires{
    ::std::remove_cvref_t<_Type>::operator();
};
template<typename _Type>
static constexpr auto is_function_v=
    ::nostd::is_unmember_function_v<_Type>||
    ::nostd::is_unmember_function_pointer_v<_Type>||
    ::nostd::is_member_function_pointer_v<_Type>||
    ::nostd::is_functor_v<_Type>;
template<typename _Type>
using is_unmember_function=
    ::std::bool_constant<::nostd::is_unmember_function_v<_Type>>;
template<typename _Type>
using is_unmember_function_pointer=
    ::std::bool_constant<::nostd::is_unmember_function_pointer_v<_Type>>;
template<typename _Type>
using is_member_function_pointer=
    ::std::bool_constant<::nostd::is_member_function_pointer_v<_Type>>;
template<typename _Type>
using is_functor=
    ::std::bool_constant<::nostd::is_functor_v<_Type>>;
template<typename _Type>
using is_function=
    ::std::bool_constant<::nostd::is_function_v<_Type>>;
namespace function_traits{
template<typename _FunctionType>
struct __FunctionTraits{
    using result_type                 =::nostd::undefined_t;
    using class_type                  =::nostd::undefined_t;
    using parameter_list               =::nostd::undefined_t;
    using has_c_style_va_list         =::std::false_type;
    using has_const                   =::std::false_type;
    using has_volatile                =::std::false_type;
    using has_left_value_reference    =::std::false_type;
    using has_right_value_reference   =::std::false_type;
    using has_noexcept                =::std::false_type;
    using function_base_type          =::nostd::undefined_t;
    using function_type               =::nostd::undefined_t;
};
#define __NOSTD_EMPTY_MACRO
#define __NOSTD_FUNCTION_TRAITS(__EXT__,__C__,__V__,__LVR__,__RVR__,__N__) \
template< \
    typename _ResultType, \
    typename..._Parameters \
> \
struct __FunctionTraits<_ResultType(_Parameters...)__EXT__>{ \
    using result_type                 =_ResultType; \
    using class_type                  =::nostd::undefined_t; \
    using parameter_list               =::nostd::ParameterList<_Parameters...>; \
    using has_c_style_va_list         =::std::false_type; \
    using has_const                   =__C__; \
    using has_volatile                =__V__; \
    using has_left_value_reference    =__LVR__; \
    using has_right_value_reference   =__RVR__; \
    using has_noexcept                =__N__; \
    using function_base_type          =_ResultType(_Parameters...); \
    using function_type               =_ResultType(_Parameters...)__EXT__; \
}; \
template< \
    typename _ResultType, \
    typename..._Parameters \
> \
struct __FunctionTraits<_ResultType(_Parameters...,...)__EXT__>{ \
    using result_type                 =_ResultType; \
    using class_type                  =::nostd::undefined_t; \
    using parameter_list               =::nostd::ParameterList<_Parameters...,::nostd::c_style_va_list_t>; \
    using has_c_style_va_list         =::std::true_type; \
    using has_const                   =__C__; \
    using has_volatile                =__V__; \
    using has_left_value_reference    =__LVR__; \
    using has_right_value_reference   =__RVR__; \
    using has_noexcept                =__N__; \
    using function_base_type          =_ResultType(_Parameters...,...); \
    using function_type               =_ResultType(_Parameters...,...)__EXT__; \
}; \
template< \
    typename _ResultType, \
    typename _ClassType, \
    typename..._Parameters \
> \
struct __FunctionTraits<_ResultType(_ClassType::*)(_Parameters...)__EXT__>{ \
    using result_type                 =_ResultType; \
    using class_type                  =_ClassType; \
    using parameter_list               =::nostd::ParameterList<_Parameters...>; \
    using has_c_style_va_list         =::std::false_type; \
    using has_const                   =__C__; \
    using has_volatile                =__V__; \
    using has_left_value_reference    =__LVR__; \
    using has_right_value_reference   =__RVR__; \
    using has_noexcept                =__N__; \
    using function_base_type          =_ResultType(_Parameters...); \
    using function_type               =_ResultType(_ClassType::*)(_Parameters...)__EXT__; \
}; \
template< \
    typename _ResultType, \
    typename _ClassType, \
    typename..._Parameters \
> \
struct __FunctionTraits<_ResultType(_ClassType::*)(_Parameters...,...)__EXT__>{ \
    using result_type                 =_ResultType; \
    using class_type                  =_ClassType; \
    using parameter_list               =::nostd::ParameterList<_Parameters...,::nostd::c_style_va_list_t>; \
    using has_c_style_va_list         =::std::true_type; \
    using has_const                   =__C__; \
    using has_volatile                =__V__; \
    using has_left_value_reference    =__LVR__; \
    using has_right_value_reference   =__RVR__; \
    using has_noexcept                =__N__; \
    using function_base_type          =_ResultType(_Parameters...,...); \
    using function_type               =_ResultType(_ClassType::*)(_Parameters...,...)__EXT__; \
};
/*
__NOSTD_FUNCTION_TRAITS(__EXT__                 ,__C__            ,__V__            ,__LVR__          ,__RVR__          ,__N__            )
*/
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
struct __GetArgument_Case0{// unmember_function_pointer
    template<typename _Type>
    using apply_t=::std::remove_pointer_t<::std::remove_cvref_t<_Type>>;
};
struct __GetArgument_Case1{// functor
    template<typename _Type>
    using apply_t=decltype(&::std::remove_cvref_t<_Type>::operator());
};
struct __GetArgument_Case2{// unmember_function||member_function_pointer
    template<typename _Type>
    using apply_t=::std::remove_cvref_t<_Type>;
};
struct __GetArgument_Case3{// !function
    template<typename _Type>
    using apply_t=_Type;
};
template<typename _Type>
using __get_argument_t=typename ::std::conditional_t<
    // unmember_function_pointer
    ::nostd::is_unmember_function_pointer_v<_Type>,__GetArgument_Case0,
    ::std::conditional_t<
        // functor
        ::nostd::is_functor_v<_Type>,__GetArgument_Case1,
        ::std::conditional_t<
            // unmember_function||member_function_pointer
            ::nostd::is_function_v<_Type>,__GetArgument_Case2,
            /* !function */__GetArgument_Case3
        >
    >
>::template apply_t<_Type>;
}
template<typename _Type>
struct FunctionTraits
    :public ::nostd::function_traits::__FunctionTraits<
        ::nostd::function_traits::__get_argument_t<_Type>
    >{
    using is_function                 =::nostd::is_function<_Type>;
    using is_unmember_function        =::nostd::is_unmember_function<_Type>;
    using is_unmember_function_pointer=::nostd::is_unmember_function_pointer<_Type>;
    using is_member_function_pointer  =::nostd::is_member_function_pointer<_Type>;
    using is_functor                  =::nostd::is_functor<_Type>;
    using raw_type                    =_Type;
};
template<typename _Type>
static constexpr auto function_traits_of(_Type&& value)noexcept{
    return ::nostd::FunctionTraits<decltype(::std::forward<_Type>(value))>{};
};
}
