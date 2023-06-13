#pragma once
#include<type_traits>
#include<string_view>
namespace nostd{
template<typename _CharType,_CharType..._chars>
struct CharSequence final{
    using type=CharSequence<_CharType,_chars...>;
    using char_type=_CharType;
    static constexpr auto size=sizeof...(_chars);
    static constexpr char_type value[size+1]{_chars...,'\0'};
};
template<typename _CharType,size_t _length>
struct CStr final{
    _CharType value[_length];
    consteval CStr(_CharType const(&c_str)[_length])noexcept{
        for(size_t index=0;index<_length;++index){
            this->value[index]=c_str[index];
        }
    }
    using char_type=_CharType;
    static constexpr size_t length=_length;
};
template<CStr _c_str>
struct CStrView final{
    using c_str_type=::std::remove_cvref_t<decltype(_c_str)>;
    static constexpr c_str_type c_str=_c_str;
    using char_type=typename c_str_type::char_type;
    static constexpr size_t size=c_str_type::length-1;
    static consteval decltype(auto) value()noexcept{
        return (c_str.value);
    }
};
// c str view to char sequence
namespace detail{
template<typename _CStrView>
consteval auto __c_str_view_to_index_sequence(
    _CStrView c_str_view
)noexcept{
    return ::std::make_index_sequence<c_str_view.size>{};
}
template<typename _CStrView,size_t...indexs>
consteval auto __c_str_view_to_char_sequence(
    _CStrView c_str_view,
    ::std::integer_sequence<size_t,indexs...>
)noexcept{
    return CharSequence<
        typename _CStrView::char_type,
        c_str_view.value()[indexs]...
    >{};
}
} // namespace nostd::detail
template<typename _CStrView>
consteval auto c_str_view_to_char_sequence(
    _CStrView c_str_view
)noexcept{
    return ::nostd::detail::__c_str_view_to_char_sequence(
        c_str_view,
        ::nostd::detail::__c_str_view_to_index_sequence(c_str_view)
    );
}
template<typename _CStrView>
using c_str_view_to_char_sequence_t=decltype(
    ::nostd::c_str_view_to_char_sequence(_CStrView{})
);
// char sequence to c str view
template<typename _CharSequence>
using char_sequence_to_c_str_view_t=CStrView<
    _CharSequence::value
>;
// char sequence concat
namespace detail{
template<typename _CharSequence_1,typename _CharSequence_2>
struct __CharSequence_Concat;
template<typename _CharType,_CharType..._chars_1,_CharType..._chars_2>
struct __CharSequence_Concat<
    CharSequence<_CharType,_chars_1...>,
    CharSequence<_CharType,_chars_2...>
>{
    using type=CharSequence<_CharType,_chars_1...,_chars_2...>;
};
} // namespace nostd::detail
template<typename _CharSequence,typename..._CharSequences>
struct CharSequence_Concat;
template<typename _CharSequence>
struct CharSequence_Concat<_CharSequence>{
    using type=_CharSequence;
};
template<
    typename _CharSequence_1,
    typename _CharSequence_2,
    typename..._CharSequences
>
struct CharSequence_Concat<
    _CharSequence_1,
    _CharSequence_2,
    _CharSequences...
>{
private:
    using current_result=typename detail::__CharSequence_Concat<
        _CharSequence_1,
        _CharSequence_2
    >::type;
public:
    using type=typename CharSequence_Concat<
        current_result,
        _CharSequences...
    >::type;
};
template<typename _CharSequence,typename..._CharSequences>
using char_sequence_concat_t=typename CharSequence_Concat<
    _CharSequence,
    _CharSequences...
>::type;
// c str view to string view
template<typename _CStrView>
consteval ::std::string_view c_str_view_to_string_view(
    _CStrView c_str_view
)noexcept{
    return ::std::string_view{
        ::nostd::c_str_view_to_char_sequence(c_str_view).value
    };
}
// string view to c str view
// TODO
struct StringView{
    char const* data;
    size_t size;
    consteval StringView(::std::string_view const std_sv)noexcept{
        this->data=std_sv.data();
        this->size=std_sv.size();
    }
};
template<StringView _value>
struct StringViewHelper{
    static constexpr auto value=_value;
    static consteval auto at(size_t index)noexcept{
        return value.data[index];
    }
    static constexpr auto size=value.size;
};
} // namespace nostd