﻿#pragma once
#include<string>
#include<iostream>
#include<source_location>
// META FUNTION NAME
#if defined(__GUNC__)
    #define META_FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(__clang__)
    #define META_FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
    #define META_FUNCTION_NAME __FUNCSIG__
#elif defined(__MINGW32__) || defined(__MINGW64__)
    #define META_FUNCTION_NAME __PRETTY_FUNCTION__
#else
    #define META_FUNCTION_NAME __FUNCTION__
#endif

namespace meta{
// meta::compiler_name
static constexpr auto&& compiler_name=
#if defined(__GUNC__)
    "GUNC"
#elif defined(__clang__)
    "clang"
#elif defined(_MSC_VER)
    "MSVC"
#elif defined(__MINGW32__) || defined(__MINGW64__)
    "MINGW"
#else
    "others"
#endif
;

namespace detail{ // namespace meta::detail
template<typename _Type>
struct __BaseTypeInfo{
private:
    ::std::string mutable name_;
    constexpr void __name_detail()const{
    #if defined(_MSC_VER)
        ::std::string type_name{__FUNCSIG__};
        auto begin=type_name.find_first_of('<')+1;
        auto end=type_name.find_last_of('>');
    #elif defined(__GUNC__) || defined(__clang__) || \
          defined(__MINGW32__) || defined(__MINGW64__)
        ::std::string type_name{__PRETTY_FUNCTION__};
        auto begin=type_name.find_first_of('=')+1;
        auto end=type_name.find_last_of(']');
    #else
        ::std::string type_name{typeid(_Type).name()};
        auto begin=0;
        auto end=type_name.size();
    #endif
        while(::std::isspace(type_name[begin])){++begin;}
        while(::std::isspace(type_name[end])){--end;}
        this->name_=type_name.substr(begin,end-begin);
    }
    constexpr auto __name()const{
        return this->name_;
    }
public:
    constexpr __BaseTypeInfo(){
        this->__name_detail();
    }
    static constexpr auto name(){
        return __BaseTypeInfo<_Type>().__name();
    }
};

template<typename _Type>
struct __TypeInfo{
    static constexpr auto name(){
        return __BaseTypeInfo<_Type>::name();
    }
};

#define __META_TYPE_INFO_BASE(__EXT__) \
template<typename _Type> \
struct __TypeInfo<_Type __EXT__>{ \
    static constexpr auto name(){ \
        return ::std::string("{") \
            .append(__TypeInfo<_Type>::name()) \
            .append("}"#__EXT__); \
    } \
};

__META_TYPE_INFO_BASE(const)
__META_TYPE_INFO_BASE(volatile)
__META_TYPE_INFO_BASE(const volatile)
__META_TYPE_INFO_BASE(*)
__META_TYPE_INFO_BASE(&)
__META_TYPE_INFO_BASE(&&)
__META_TYPE_INFO_BASE([])
__META_TYPE_INFO_BASE(const[])
__META_TYPE_INFO_BASE(volatile[])
__META_TYPE_INFO_BASE(const volatile[])
#undef __META_TYPE_INFO_BASE

#define __META_TYPE_INFO_ARRAY(__EXT__) \
template<typename _Type,::std::size_t _N> \
struct __TypeInfo<_Type __EXT__[_N]>{ \
    static constexpr auto name(){ \
        return ::std::string{"{"} \
            .append(__TypeInfo<_Type>::name()) \
            .append("}"#__EXT__"[") \
            .append(::std::to_string(_N)) \
            .append("]"); \
    } \
};

// C Style Array[_N]
__META_TYPE_INFO_ARRAY() 
__META_TYPE_INFO_ARRAY(const) 
__META_TYPE_INFO_ARRAY(volatile) 
__META_TYPE_INFO_ARRAY(const volatile) 
#undef __META_TYPE_INFO_ARRAY

template<typename _ClassType,typename _Type>
struct __TypeInfo<_Type _ClassType::*>{
    static constexpr auto name(){
        return ::std::string("{")
            .append(__TypeInfo<_Type>::name())
            .append("}{")
            .append(__TypeInfo<_ClassType>::name())
            .append("}::*");
    }
};

#define __META_TYPE_INFO_FUNCTION(__EXT__) \
template<typename _RetType,typename..._Types> \
struct __TypeInfo<_RetType(_Types...)__EXT__>{ \
    static constexpr auto name(){ \
        if constexpr(sizeof...(_Types)!=0){ \
            ::std::string arg_list=( \
                __TypeInfo<_Types>::name() \
                .append(",")+... \
            ); \
            arg_list.pop_back(); \
            return ::std::string("{") \
                .append(__TypeInfo<_RetType>::name()) \
                .append("}(") \
                .append(arg_list) \
                .append(")"#__EXT__); \
        } \
        else { \
            return ::std::string("{") \
                .append(__TypeInfo<_RetType>::name()) \
                .append("}(void)"#__EXT__); \
        } \
    } \
};\
template<typename _RetType,typename..._Types> \
struct __TypeInfo<_RetType(_Types...,...)__EXT__>{ \
    static constexpr auto name(){ \
        if constexpr (sizeof...(_Types)!=0){ \
            ::std::string arg_list=( \
                __TypeInfo<_Types>::name() \
                .append(",")+...\
            ); \
            return ::std::string("{") \
                .append(__TypeInfo<_RetType>::name()) \
                .append("}(") \
                .append(arg_list) \
                .append("...)"#__EXT__); \
        } \
        else { \
            return ::std::string("{") \
                .append(__TypeInfo<_RetType>::name()) \
                .append("}(...)"#__EXT__); \
        } \
    } \
};

// execept
__META_TYPE_INFO_FUNCTION()
__META_TYPE_INFO_FUNCTION(const)
__META_TYPE_INFO_FUNCTION(volatile)
__META_TYPE_INFO_FUNCTION(const volatile)
__META_TYPE_INFO_FUNCTION(&)
__META_TYPE_INFO_FUNCTION(const&)
__META_TYPE_INFO_FUNCTION(volatile&)
__META_TYPE_INFO_FUNCTION(const volatile&)
__META_TYPE_INFO_FUNCTION(&&)
__META_TYPE_INFO_FUNCTION(const&&)
__META_TYPE_INFO_FUNCTION(volatile&&)
__META_TYPE_INFO_FUNCTION(const volatile&&)
// noexcept
__META_TYPE_INFO_FUNCTION(noexcept)
__META_TYPE_INFO_FUNCTION(const noexcept)
__META_TYPE_INFO_FUNCTION(volatile noexcept)
__META_TYPE_INFO_FUNCTION(const volatile noexcept)
__META_TYPE_INFO_FUNCTION(&noexcept)
__META_TYPE_INFO_FUNCTION(const&noexcept)
__META_TYPE_INFO_FUNCTION(volatile&noexcept)
__META_TYPE_INFO_FUNCTION(const volatile&noexcept)
__META_TYPE_INFO_FUNCTION(&&noexcept)
__META_TYPE_INFO_FUNCTION(const&&noexcept)
__META_TYPE_INFO_FUNCTION(volatile&&noexcept)
__META_TYPE_INFO_FUNCTION(const volatile&&noexcept)
#undef __META_TYPE_INFO_FUNCTION

} // namespace meta::detail

// meta::type_name()
template<typename _Type>
constexpr auto type_name(){
    return detail::__TypeInfo<_Type>::name();
}
template<typename _Type>
constexpr auto base_type_name(){
    return detail::__BaseTypeInfo<_Type>::name();
}

#define META_TYPE_NAME_OF(__EXPR__) \
    ::meta::type_name<decltype(__EXPR__)>()

#define META_BASE_TYPE_NAME_OF(__EXPR__) \
    ::meta::base_type_name<decltype(__EXPR__)>()

} // namespace ::meta

namespace meta::test{ // namespace meta::test
void test_compiler_name(){
    ::std::cout<<"meta::compiler_name -> "
        <<::meta::compiler_name<<::std::endl;
}
template<typename _Type>
void test_function_name(){
    ::std::cout<<"C_STD __func__ -> "<<__func__<<::std::endl;
    auto location=::std::source_location::current();
    ::std::cout<<"CXX_STD ::std::source_location::function_name() -> "<<
        location.function_name()<<::std::endl;
    ::std::cout<<"META_FUNCTION_NAME -> "<<META_FUNCTION_NAME<<::std::endl;
}
template<typename _Type>
void test_type_name(){
    ::std::cout<<"CXX_STD typeid().name() -> "
        <<typeid(_Type).name()<<::std::endl;
    ::std::cout<<"meta::type_name_base() -> "
        <<::meta::base_type_name<_Type>()<<::std::endl;
    ::std::cout<<"meta::type_name() -> "
        <<::meta::type_name<_Type>()<<::std::endl;
}
} // namespace meta::test

