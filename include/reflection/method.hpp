#pragma once
#include<utility>
#include<type_traits>
#include<vector>
#include"nostd_function_traits.hpp"
#include"type.hpp"
#include"function.hpp"
class Method{
    Function data_;
    Type class_type_;
    Type func_type_;
    Type result_type_;
    ::std::vector<Type> parameter_type_list_;
    template<template<typename...>class _MetaFunc,typename..._Types>
    inline ::std::vector<Type> _get_parameter_type_list(_MetaFunc<_Types...>&&)noexcept{
        return ::std::vector<Type>{::make_type<_Types>()...};
    }
public:
    inline Method() noexcept
        :data_()
        ,class_type_()
        ,func_type_()
        ,result_type_()
        ,parameter_type_list_()
    {}
    template<typename _ClassType,typename _FuncType>
    requires ::std::is_function_v<_FuncType>
    inline Method(_FuncType _ClassType::* member_func) noexcept
        :Method(){
        this->data_=member_func;
        this->class_type_=::make_type<_ClassType>();
        this->func_type_=::make_type<_FuncType>();
        this->result_type_=::make_type<typename ::nostd::FunctionTraits<_FuncType>::result_type>();
        this->parameter_type_list_=this->_get_parameter_type_list(
            typename ::nostd::FunctionTraits<_FuncType>::parameter_list()
        );
    }
    inline Type const& class_type()const noexcept{
        return this->class_type_;
    }
    inline Type const& result_type()const noexcept{
        return this->result_type_;
    }
    inline ::std::vector<Type> const& parameter_type_list()const noexcept{
        return this->parameter_type_list_;
    }
    template<typename...ArgumentTypes,::std::enable_if_t<
        sizeof...(ArgumentTypes)!=0
    ,int>_=0>
    Object invoke_by_args(ArgumentTypes&&...args)const{
        return this->data_.invoke_by_args(::std::forward<ArgumentTypes>(args)...);
    }
    Object invoke_by_args()const{
        return this->data_.invoke_by_args();
    }
    Object invoke_by_objects(::std::vector<Object>const& args)const{
        return this->data_.invoke_by_objects(args);
    }
    Object invoke_by_objects()const{
        return this->data_.invoke_by_objects();
    }
};