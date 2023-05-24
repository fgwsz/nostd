#pragma once
#include<string>
#include<iostream>
#include<source_location>
// META FUNTION NAME
#if defined(__GUNC__)
    #define META_FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(__clang__)
    ::std::cout<<"clang"<<::std::endl;
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
#if defined(__GUNC__)
    static constexpr auto&& compiler_name="GUNC";
#elif defined(__clang__)
    static constexpr auto&& compiler_name="clang";
#elif defined(_MSC_VER)
    static constexpr auto&& compiler_name="MSVC";
#elif defined(__MINGW32__) || defined(__MINGW64__)
    static constexpr auto&& compiler_name="MINGW";
#else
    static constexpr auto&& compiler_name="others";
#endif

template<typename _Type>
struct TypeInfo final{
private:
    ::std::string mutable name_;
    constexpr void name_detail()const noexcept{
    #if defined(_MSC_VER)
        ::std::string type_name{__FUNCSIG__};
        auto begin=type_name.find_first_of('<')+1;
        auto end=type_name.find_last_of('>');
    #elif defined(__GUNC__) || defined(__clang__) || defined(__MINGW32__) || defined(__MINGW64__)
        ::std::string type_name{__PRETTY_FUNCTION__};
        auto begin=type_name.find_first_of('=')+1;
        auto end=type_name.find_last_of(']');
    #else
        ::std::string type_name{typeid(_Type).name()};
        auto begin=0;
        auto end=type_name.size();
    #endif
        for(auto index=begin;;++begin){
            if(!::std::isspace(type_name[begin])){
                break;
            }
        }
        for(auto index=end;;--end){
            if(!::std::isspace(type_name[end])){
                break;
            }
        }
        this->name_=type_name.substr(begin,end-begin);
    }
public:
    constexpr TypeInfo()noexcept{
        this->name_detail();
    }
    constexpr decltype(auto) name()const noexcept{
        return this->name_;
    }
};
// meta::type_name()
template<typename _Type>
constexpr ::std::string type_name()noexcept{
    return TypeInfo<_Type>().name();
}
void test_compiler_name(){
    ::std::cout<<"meta::compiler_name -> "<<::meta::compiler_name<<::std::endl;
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
    ::std::cout<<"CXX_STD typeid().name() -> "<<typeid(_Type).name()<<::std::endl;
    ::std::cout<<"meta::type_name() -> "<<::meta::type_name<_Type>()<<::std::endl;
}
} // namespace meta
