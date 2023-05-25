#pragma once
#include"meta.hpp"
namespace meta{
template<typename _CharType,SizeType _length>
struct CStr{
    using CharType=_CharType;
    static constexpr auto length=_length;
    _CharType value[_length]{};
    consteval CStr(_CharType const(&c_str)[_length]){
        for(SizeType index=0;index<_length;++index){
            this->value[index]=c_str[index];
        }
    }
    constexpr CStr& operator=(CStr const&)=default;
};
template<
    typename _CharType,
    SizeType _length,
    CStr<_CharType,_length> _c_str
>
struct StringHelper{
    static consteval auto c_str(){
        return _c_str;
    }
};
template<typename _StringHelper>
static consteval auto __string_helper_char_type(_StringHelper string_helper)
{
    return typename decltype(string_helper.c_str())::CharType{};
}
template<typename _StringHelper>
static consteval auto __string_helper_length(_StringHelper string_helper){
    return string_helper.c_str().length;
}
template<typename _StringHelper>
static consteval auto __string_helper_indexs(_StringHelper string_helper){
    return typename Sequence_MakeIndexs<
        Auto<SizeType(0)>,
        Auto<__string_helper_length(string_helper)>
    >::Type{};
}
template<typename _StringHelper,SizeType..._indexs>
static consteval auto __string_helper_to_sequence_detail(
    _StringHelper string_helper,
    Sequence<SizeType,_indexs...> indexs
){
    return Sequence<
        decltype(__string_helper_char_type(string_helper)),
        string_helper.c_str().value[_indexs]...
    >{};
}
template<typename _StringHelper>
static consteval auto __string_helper_to_sequence(
    _StringHelper string_helper
){
    return __string_helper_to_sequence_detail(
        string_helper,
        __string_helper_indexs(string_helper)
    );
}
} // namespace meta

#define __META_STRING_HELPER(__C_STYLE_STRING_LITERAL__) \
::meta::StringHelper< \
    typename decltype(::meta::CStr(__C_STYLE_STRING_LITERAL__))::CharType, \
    decltype(::meta::CStr(__C_STYLE_STRING_LITERAL__))::length, \
    ::meta::CStr(__C_STYLE_STRING_LITERAL__) \
>

#define META_STRING(__C_STYLE_STRING_LITERAL__) \
decltype( \
    ::meta::__string_helper_to_sequence( \
        __META_STRING_HELPER(__C_STYLE_STRING_LITERAL__){} \
    ) \
)

