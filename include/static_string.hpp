#pragma once
#include<type_traits>
namespace nostd{
using size_t=unsigned long long;
template<typename _CharType,_CharType..._chars>
struct StaticCharSequence final{
    using type=StaticCharSequence<_CharType,_chars...>;
    using char_type=_CharType;
    static constexpr auto size=sizeof...(_chars);
    static constexpr char_type value[size+1]{_chars...,'\0'};
};
template<typename _CharType,size_t _length>
struct StaticCStr final{
    _CharType value[_length];
    consteval StaticCStr(_CharType const(&c_str)[_length])noexcept{
        for(size_t index=0;index<_length;++index){
            this->value[index]=c_str[index];
        }
    }
    using char_type=_CharType;
    static constexpr size_t length=_length;
};
template<typename _CharType,size_t _length,
    StaticCStr<_CharType,_length> _static_c_str>
struct StaticString final{
    static consteval auto c_str()noexcept{
        return _static_c_str;
    }
    using char_type=_CharType;
    static constexpr size_t length=_length;
    static constexpr size_t size=length-1;
};
template<typename _StaticString>
struct static_string_to_char_sequence{
    using char_type=typename _StaticString::char_type;
    static constexpr size_t size=_StaticString::size;
    using index_sequence=::std::make_index_sequence<size>;
    using index_type=typename index_sequence::value_type;
    template<index_type...indexs>
    static constexpr auto match(
        ::std::integer_sequence<index_type,indexs...>
    )noexcept{
        return StaticCharSequence<char_type,(_StaticString::c_str().value)[indexs]...>{};
    };
    using type=decltype(static_string_to_char_sequence::match(index_sequence{}));
};
using tts=typename static_string_to_char_sequence<StaticString<char,6,"hello">>::type;
} // namespace nostd