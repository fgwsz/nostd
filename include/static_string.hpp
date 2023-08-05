#pragma once
#include<type_traits>
#include<algorithm>
#include<utility>
namespace nostd{
//
template<typename _CharType,::std::size_t _length>
struct CStr{
    _CharType value[_length]{};
    consteval CStr(_CharType const(&c_str)[_length]){
        ::std::copy(::std::begin(c_str),::std::end(c_str),::std::begin(value));
    }
    using char_type=_CharType;
    static constexpr auto length=_length;
};
//
template<CStr _c_str>
struct StaticString{
    using char_type=
        typename ::std::remove_cvref_t<decltype(_c_str)>::char_type;
    static constexpr auto size=_c_str.length-1;
    static constexpr decltype(auto) value=(_c_str.value);
};
//
template<
    typename _StaticString,
    ::std::size_t...Indexs
>
static consteval auto __staticStringToIntegerSequence(
    ::std::index_sequence<Indexs...>&&
){
    return ::std::integer_sequence<
        typename _StaticString::char_type,
        _StaticString::value[Indexs]...
    >{};
}
template<typename _StaticString>
static consteval auto staticStringToIntegerSequence()
->decltype(::nostd::__staticStringToIntegerSequence<_StaticString>(
    ::std::declval<::std::make_index_sequence<_StaticString::size>>()
));
//
template<typename _StaticString>
using static_string_to_integer_sequence_t=
    decltype(::nostd::staticStringToIntegerSequence<_StaticString>());
//
}