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
    #if defined(_MSC_VER)
        data_t result{__FUNCSIG__};
        auto begin=result.find_first_of('<')+1;
        auto end=result.find_last_of('>');
    #else
        data_t result{__PRETTY_FUNCTION__};
        auto begin=result.find_first_of('=')+1;
        auto end=result.find_last_of(']');
    #endif
        while(result[begin]==' '){++begin;}
        while(result[end]==' '){--end;}
        this->data_=result.substr(begin,end-begin);
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