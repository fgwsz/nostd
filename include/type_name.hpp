#pragma once
#include<string_view>
#include<iostream>
namespace nostd{
namespace detail{
template<typename _Type>
struct __TypeName final{
    consteval __TypeName()noexcept{
        this->__init_data();
    }
    static consteval auto data()noexcept{
        return __TypeName<_Type>().data_;
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
// namespace nostd::detail end
}
// Get the compile-time type name string of ${_Type}
// input<${_Type}>
// return constexpr ::std::string_view
template<typename _Type>
consteval auto type_name()noexcept{
    return detail::__TypeName<_Type>::data();
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
