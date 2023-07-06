#pragma once
#include<string_view>
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
