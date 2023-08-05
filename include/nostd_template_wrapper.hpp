#pragma once
namespace nostd{
//
template<template<typename...>typename _Template>
struct TemplateWrapper{
    template<typename..._Parameters>
    using unwrap=_Template<_Parameters...>;
};
//
template<typename _TemplateInstance>
struct TemplateInstanceToWrapper;
template<
    template<typename...>typename _Template,
    typename..._Parameters
>
struct TemplateInstanceToWrapper<_Template<_Parameters...>>{
    using type=TemplateWrapper<_Template>;
};
//
template<typename _TemplateInstance>
using template_instance_to_wrapper_t=
    typename TemplateInstanceToWrapper<_TemplateInstance>::type;
//
template<typename _TemplateWrapper,typename..._Parameters>
struct TemplateWrapperToInstance{
    using type=
        typename _TemplateWrapper::template unwrap<_Parameters...>;
};
//
template<typename _TemplateWrapper,typename..._Parameters>
using template_wrapper_to_instance_t=
    typename TemplateWrapperToInstance<_TemplateWrapper,_Parameters...>::type;
//
template<typename _TemplateWrapper,typename..._FrontParameters>
struct TemplateWrapperBindFront{
private:
    template<typename..._BackParameters>
    struct __Binder
        :_TemplateWrapper::template unwrap<_FrontParameters...,_BackParameters...>
    {};
public:
    using type=TemplateWrapper<__Binder>;
};
//
template<typename _TemplateWrapper,typename..._FrontParameters>
using template_wrapper_bind_front_t=
    typename TemplateWrapperBindFront<_TemplateWrapper,_FrontParameters...>::type;
//
template<typename _TemplateWrapper,typename..._BackParameters>
struct TemplateWrapperBindBack{
private:
    template<typename..._FrontParameters>
    struct __Binder
        :_TemplateWrapper::template unwrap<_FrontParameters...,_BackParameters...>
    {};
public:
    using type=TemplateWrapper<__Binder>;
};
//
template<typename _TemplateWrapper,typename..._BackParameters>
using template_wrapper_bind_back_t=
    typename TemplateWrapperBindBack<_TemplateWrapper,_BackParameters...>::type;
} // namespace nostd