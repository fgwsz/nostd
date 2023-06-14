#pragma once
#include<string_view>
#include<iostream>
namespace nostd{
// Get the compile-time type name string of ${_Type}
// input<${_Type}>
// return constexpr ::std::string_view
template<typename _Type>
consteval auto type_name()noexcept{
// gcc||clang||msvc with clang||mingw
#if defined(__GUNC__)||defined(__clang__)|| \
    defined(__MINGW32__)||defined(__MINGW64__)
    ::std::string_view result{__PRETTY_FUNCTION__};
    auto front_index=result.find_first_of('=')+1;
    auto back_index=result.find_last_of(']')-1;
// msvc without clang
#elif defined(_MSC_VER)
    ::std::string_view result{__FUNCSIG__};
    auto front_index=result.find_first_of('<')+1;
    auto back_index=result.find_last_of('>')-1;
#endif
    front_index=result.find_first_not_of(' ',front_index);
    back_index=result.find_last_not_of(' ',back_index);
    return result.substr(front_index,back_index-front_index+1);
}
// namespace nostd end
}
// Get the compile-time type name string of ${type}
// input(...) is ${type}
// return constexpr ::std::string_view
#define NOSTD_TYPE_NAME(...) \
::nostd::type_name<__VA_ARGS__>()
// Get the compile-time type name string of ${expr}
// input(...) is ${expr}
// return constexpr ::std::string_view
#define NOSTD_TYPE_NAME_OF(...) \
::nostd::type_name<decltype(__VA_ARGS__)>()
// Log type name string of type
// input(...) is ${type}
// return void
#define NOSTD_LOG_TYPE_NAME(...) \
do{ \
    ::std::cout<<#__VA_ARGS__<<"=" \
        <<NOSTD_TYPE_NAME(__VA_ARGS__) \
        <<::std::endl; \
}while(0)
// Log type name string of ${expr}
// input(...) is ${expr}
// return void
#define NOSTD_LOG_TYPE_NAME_OF(...) \
do{ \
    ::std::cout<<"{"<<#__VA_ARGS__<<"}->" \
        <<NOSTD_TYPE_NAME_OF(__VA_ARGS__) \
        <<::std::endl; \
}while(0)
