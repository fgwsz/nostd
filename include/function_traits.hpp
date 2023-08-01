#pragma once
//
namespace nostd{ namespace function_traits{
//
struct __NoneType;
using __none_type=__NoneType;

struct __CStyleVaList;

template<bool _value>
struct __BoolConstant{
	static constexpr bool value=_value;
};
using __true_type=__BoolConstant<true>;
using __false_type=__BoolConstant<false>;

template<typename...>
struct __ArgumentList{};

template<typename _IsFunctionType>
struct __Field_IsFunctionType{
	using is_function_type=_IsFunctionType;
};
template<typename _IsMemberFuncitonType>
struct __Field_IsMemberFunctionType{
	using is_member_function_type=_IsMemberFuncitonType;
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

template<typename _FunctionType>
struct __FunctionTraits
	:__Field_IsFunctionType<__false_type>
	,__Field_IsMemberFunctionType<__false_type>
	,__Field_ResultType<__none_type>
	,__Field_ClassType<__none_type>
	,__Field_ArgumentList<__none_type>
	,__Field_HasCStyleVaList<__false_type>
	,__Field_HasConst<__false_type>
	,__Field_HasVolatile<__false_type>
	,__Field_HasLeftValueReference<__false_type>
	,__Field_HasRightValueReference<__false_type>
	,__Field_HasNoexcept<__false_type>
{};
/*
	<_ResultType(_Arguments...)>
	<_ResultType(_Arguments...)const>
	<_ResultType(_Arguments...)volatile>
	<_ResultType(_Arguments...)const volatile>

	<_ResultType(_Arguments...)&>
	<_ResultType(_Arguments...)const&>
	<_ResultType(_Arguments...)volatile&>
	<_ResultType(_Arguments...)const volatile&>

	<_ResultType(_Arguments...)&&>
	<_ResultType(_Arguments...)const&&>
	<_ResultType(_Arguments...)volatile&&>
	<_ResultType(_Arguments...)const volatile&&>

	<_ResultType(_Arguments...)noexcept>
	<_ResultType(_Arguments...)const noexcept>
	<_ResultType(_Arguments...)volatile noexcept>
	<_ResultType(_Arguments...)const volatile noexcept>

	<_ResultType(_Arguments...)&noexcept>
	<_ResultType(_Arguments...)const&noexcept>
	<_ResultType(_Arguments...)volatile&noexcept>
	<_ResultType(_Arguments...)const volatile&noexcept>

	<_ResultType(_Arguments...)&&noexcept>
	<_ResultType(_Arguments...)const&&noexcept>
	<_ResultType(_Arguments...)volatile&&noexcept>
	<_ResultType(_Arguments...)const volatile&&noexcept>

	<_ResultType(_Arguments...,...)>
	<_ResultType(_Arguments...,...)const>
	<_ResultType(_Arguments...,...)volatile>
	<_ResultType(_Arguments...,...)const volatile>

	<_ResultType(_Arguments...,...)&>
	<_ResultType(_Arguments...,...)const&>
	<_ResultType(_Arguments...,...)volatile&>
	<_ResultType(_Arguments...,...)const volatile&>

	<_ResultType(_Arguments...,...)&&>
	<_ResultType(_Arguments...,...)const&&>
	<_ResultType(_Arguments...,...)volatile&&>
	<_ResultType(_Arguments...,...)const volatile&&>

	<_ResultType(_Arguments...,...)noexcept>
	<_ResultType(_Arguments...,...)const noexcept>
	<_ResultType(_Arguments...,...)volatile noexcept>
	<_ResultType(_Arguments...,...)const volatile noexcept>

	<_ResultType(_Arguments...,...)&noexcept>
	<_ResultType(_Arguments...,...)const&noexcept>
	<_ResultType(_Arguments...,...)volatile&noexcept>
	<_ResultType(_Arguments...,...)const volatile&noexcept>

	<_ResultType(_Arguments...,...)&&noexcept>
	<_ResultType(_Arguments...,...)const&&noexcept>
	<_ResultType(_Arguments...,...)volatile&&noexcept>
	<_ResultType(_Arguments...,...)const volatile&&noexcept>

	<_ResultType(_ClassType::*)(_Arguments...)>
	<_ResultType(_ClassType::*)(_Arguments...)const>
	<_ResultType(_ClassType::*)(_Arguments...)volatile>
	<_ResultType(_ClassType::*)(_Arguments...)const volatile>

	<_ResultType(_ClassType::*)(_Arguments...)&>
	<_ResultType(_ClassType::*)(_Arguments...)const&>
	<_ResultType(_ClassType::*)(_Arguments...)volatile&>
	<_ResultType(_ClassType::*)(_Arguments...)const volatile&>

	<_ResultType(_ClassType::*)(_Arguments...)&&>
	<_ResultType(_ClassType::*)(_Arguments...)const&&>
	<_ResultType(_ClassType::*)(_Arguments...)volatile&&>
	<_ResultType(_ClassType::*)(_Arguments...)const volatile&&>

	<_ResultType(_ClassType::*)(_Arguments...)noexcept>
	<_ResultType(_ClassType::*)(_Arguments...)const noexcept>
	<_ResultType(_ClassType::*)(_Arguments...)volatile noexcept>
	<_ResultType(_ClassType::*)(_Arguments...)const volatile noexcept>

	<_ResultType(_ClassType::*)(_Arguments...)&noexcept>
	<_ResultType(_ClassType::*)(_Arguments...)const&noexcept>
	<_ResultType(_ClassType::*)(_Arguments...)volatile&noexcept>
	<_ResultType(_ClassType::*)(_Arguments...)const volatile&noexcept>

	<_ResultType(_ClassType::*)(_Arguments...)&&noexcept>
	<_ResultType(_ClassType::*)(_Arguments...)const&&noexcept>
	<_ResultType(_ClassType::*)(_Arguments...)volatile&&noexcept>
	<_ResultType(_ClassType::*)(_Arguments...)const volatile&&noexcept>

	<_ResultType(_ClassType::*)(_Arguments...,...)>
	<_ResultType(_ClassType::*)(_Arguments...,...)const>
	<_ResultType(_ClassType::*)(_Arguments...,...)volatile>
	<_ResultType(_ClassType::*)(_Arguments...,...)const volatile>

	<_ResultType(_ClassType::*)(_Arguments...,...)&>
	<_ResultType(_ClassType::*)(_Arguments...,...)const&>
	<_ResultType(_ClassType::*)(_Arguments...,...)volatile&>
	<_ResultType(_ClassType::*)(_Arguments...,...)const volatile&>

	<_ResultType(_ClassType::*)(_Arguments...,...)&&>
	<_ResultType(_ClassType::*)(_Arguments...,...)const&&>
	<_ResultType(_ClassType::*)(_Arguments...,...)volatile&&>
	<_ResultType(_ClassType::*)(_Arguments...,...)const volatile&&>

	<_ResultType(_ClassType::*)(_Arguments...,...)noexcept>
	<_ResultType(_ClassType::*)(_Arguments...,...)const noexcept>
	<_ResultType(_ClassType::*)(_Arguments...,...)volatile noexcept>
	<_ResultType(_ClassType::*)(_Arguments...,...)const volatile noexcept>

	<_ResultType(_ClassType::*)(_Arguments...,...)&noexcept>
	<_ResultType(_ClassType::*)(_Arguments...,...)const&noexcept>
	<_ResultType(_ClassType::*)(_Arguments...,...)volatile&noexcept>
	<_ResultType(_ClassType::*)(_Arguments...,...)const volatile&noexcept>

	<_ResultType(_ClassType::*)(_Arguments...,...)&&noexcept>
	<_ResultType(_ClassType::*)(_Arguments...,...)const&&noexcept>
	<_ResultType(_ClassType::*)(_Arguments...,...)volatile&&noexcept>
	<_ResultType(_ClassType::*)(_Arguments...,...)const volatile&&noexcept>
*/
#define __NONE
#define __FUNCTION_TRAITS(__EXT__,__C__,__V__,__LVR__,__RVR__,__N__) \
template< \
	typename _ResultType, \
	typename..._Arguments \
> \
struct __FunctionTraits \
	<_ResultType(_Arguments...)__EXT__> \
	:__Field_IsFunctionType<__true_type> \
	,__Field_IsMemberFunctionType<__false_type> \
	,__Field_ResultType<_ResultType> \
	,__Field_ClassType<__none_type> \
	,__Field_ArgumentList<__ArgumentList<_Arguments...>> \
	,__Field_HasCStyleVaList<__false_type> \
	,__Field_HasConst<__C__> \
	,__Field_HasVolatile<__V__> \
	,__Field_HasLeftValueReference<__LVR__> \
	,__Field_HasRightValueReference<__RVR__> \
	,__Field_HasNoexcept<__N__> \
{}; \
template< \
	typename _ResultType, \
	typename..._Arguments \
> \
struct __FunctionTraits \
	<_ResultType(_Arguments...,...)__EXT__> \
	:__Field_IsFunctionType<__true_type> \
	,__Field_IsMemberFunctionType<__false_type> \
	,__Field_ResultType<_ResultType> \
	,__Field_ClassType<__none_type> \
	,__Field_ArgumentList<__ArgumentList<_Arguments...,__CStyleVaList>> \
	,__Field_HasCStyleVaList<__true_type> \
	,__Field_HasConst<__C__> \
	,__Field_HasVolatile<__V__> \
	,__Field_HasLeftValueReference<__LVR__> \
	,__Field_HasRightValueReference<__RVR__> \
	,__Field_HasNoexcept<__N__> \
{}; \
template< \
	typename _ResultType, \
	typename _ClassType, \
	typename..._Arguments \
> \
struct __FunctionTraits \
	<_ResultType(_ClassType::*)(_Arguments...)__EXT__> \
	:__Field_IsFunctionType<__true_type> \
	,__Field_IsMemberFunctionType<__true_type> \
	,__Field_ResultType<_ResultType> \
	,__Field_ClassType<_ClassType> \
	,__Field_ArgumentList<__ArgumentList<_Arguments...>> \
	,__Field_HasCStyleVaList<__false_type> \
	,__Field_HasConst<__C__> \
	,__Field_HasVolatile<__V__> \
	,__Field_HasLeftValueReference<__LVR__> \
	,__Field_HasRightValueReference<__RVR__> \
	,__Field_HasNoexcept<__N__> \
{}; \
template< \
	typename _ResultType, \
	typename _ClassType, \
	typename..._Arguments \
> \
struct __FunctionTraits \
	<_ResultType(_ClassType::*)(_Arguments...,...)__EXT__> \
	:__Field_IsFunctionType<__true_type> \
	,__Field_IsMemberFunctionType<__true_type> \
	,__Field_ResultType<_ResultType> \
	,__Field_ClassType<_ClassType> \
	,__Field_ArgumentList<__ArgumentList<_Arguments...,__CStyleVaList>> \
	,__Field_HasCStyleVaList<__true_type> \
	,__Field_HasConst<__C__> \
	,__Field_HasVolatile<__V__> \
	,__Field_HasLeftValueReference<__LVR__> \
	,__Field_HasRightValueReference<__RVR__> \
	,__Field_HasNoexcept<__N__> \
{}; \
//               (__EXT__                 ,__C__       ,__V__       ,__LVR__     ,__RVR__     ,__N__       )
__FUNCTION_TRAITS(__NONE                  ,__false_type,__false_type,__false_type,__false_type,__false_type)
__FUNCTION_TRAITS(const                   ,__true_type ,__false_type,__false_type,__false_type,__false_type)
__FUNCTION_TRAITS(volatile                ,__false_type,__true_type ,__false_type,__false_type,__false_type)
__FUNCTION_TRAITS(const volatile          ,__true_type ,__true_type ,__false_type,__false_type,__false_type)

__FUNCTION_TRAITS(&                       ,__false_type,__false_type,__true_type ,__false_type,__false_type)
__FUNCTION_TRAITS(const&                  ,__true_type ,__false_type,__true_type ,__false_type,__false_type)
__FUNCTION_TRAITS(volatile&               ,__false_type,__true_type ,__true_type ,__false_type,__false_type)
__FUNCTION_TRAITS(const volatile&         ,__true_type ,__true_type ,__true_type ,__false_type,__false_type)

__FUNCTION_TRAITS(&&                      ,__false_type,__false_type,__false_type,__true_type ,__false_type)
__FUNCTION_TRAITS(const&&                 ,__true_type ,__false_type,__false_type,__true_type ,__false_type)
__FUNCTION_TRAITS(volatile&&              ,__false_type,__true_type ,__false_type,__true_type ,__false_type)
__FUNCTION_TRAITS(const volatile&&        ,__true_type ,__true_type ,__false_type,__true_type ,__false_type)

__FUNCTION_TRAITS(noexcept                ,__false_type,__false_type,__false_type,__false_type,__true_type )
__FUNCTION_TRAITS(const noexcept          ,__true_type ,__false_type,__false_type,__false_type,__true_type )
__FUNCTION_TRAITS(volatile noexcept       ,__false_type,__true_type ,__false_type,__false_type,__true_type )
__FUNCTION_TRAITS(const volatile noexcept ,__true_type ,__true_type ,__false_type,__false_type,__true_type )

__FUNCTION_TRAITS(&noexcept               ,__false_type,__false_type,__true_type ,__false_type,__true_type )
__FUNCTION_TRAITS(const&noexcept          ,__true_type ,__false_type,__true_type ,__false_type,__true_type )
__FUNCTION_TRAITS(volatile&noexcept       ,__false_type,__true_type ,__true_type ,__false_type,__true_type )
__FUNCTION_TRAITS(const volatile&noexcept ,__true_type ,__true_type ,__true_type ,__false_type,__true_type )

__FUNCTION_TRAITS(&&noexcept              ,__false_type,__false_type,__false_type,__true_type ,__true_type )
__FUNCTION_TRAITS(const&&noexcept         ,__true_type ,__false_type,__false_type,__true_type ,__true_type )
__FUNCTION_TRAITS(volatile&&noexcept      ,__false_type,__true_type ,__false_type,__true_type ,__true_type )
__FUNCTION_TRAITS(const volatile&&noexcept,__true_type ,__true_type ,__false_type,__true_type ,__true_type )
#undef __FUNCTION_TRAITS
//
}}
//