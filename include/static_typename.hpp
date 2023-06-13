#pragma once
#include<string_view>
namespace nostd{
namespace detail{
template<typename _Type>
struct __StaticTypename final{
    consteval __StaticTypename()noexcept{
        this->__init_data();
    }
    static consteval auto data()noexcept{
        return __StaticTypename<_Type>().data_;
    }
private:
    consteval void __init_data()noexcept{
        using data_t=decltype(this->data_);
    // gcc||clang||msvc with clang||mingw
    #if defined(__GUNC__)||defined(__clang__)|| \
        defined(__MINGW32__)||defined(__MINGW64__)
        data_t result{__PRETTY_FUNCTION__};
        auto front_index=result.find_first_of('=')+1;
        auto back_index=result.find_last_of(']')-1;
    // msvc without clang
    #elif defined(_MSC_VER)
        data_t result{__FUNCSIG__};
        auto front_index=result.find_first_of('<')+1;
        auto back_index=result.find_last_of('>')-1;
    #endif
        front_index=result.find_first_not_of(' ',front_index);
        back_index=result.find_last_not_of(' ',back_index);
        this->data_=result.substr(front_index,back_index-front_index+1);
    }
    ::std::string_view data_;
};
// namespace nostd::detail
}
// Get the compile-time typename string of _Type
template<typename _Type>
consteval auto static_typename()noexcept{
    return detail::__StaticTypename<_Type>::data();
}
// namespace nostd
}
