#pragma once
#include<type_traits>
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
    using value_type=char_type const(&)[c_str_type::length];
    static constexpr value_type value=c_str.value;
    constexpr operator value_type()const noexcept{
        return this->value;
    }
};
// c str view to char sequence
template<typename _CStrView>
consteval auto c_str_view_to_char_sequence(
    _CStrView c_str_view
)noexcept{
    constexpr auto to_char_sequence=[&]
    <typename _View,size_t..._indexs>(
        _View view,
        ::std::integer_sequence<size_t,_indexs...>
    )noexcept{
        return CharSequence<
            typename ::std::remove_cvref_t<_View>::char_type,
            view.value[_indexs]...
        >{};
    };
    return to_char_sequence(
        c_str_view,
        ::std::make_index_sequence<c_str_view.size>{}
    );
}
template<typename _CStrView>
using c_str_view_to_char_sequence_t=::std::remove_cvref_t<decltype(
    ::nostd::c_str_view_to_char_sequence(_CStrView{})
)>;
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
// c str view concat
template<typename _CStrView,typename..._CStrViews>
struct CStrView_Concat{
    using type=char_sequence_concat_t<
        c_str_view_to_char_sequence_t<_CStrView>,
        c_str_view_to_char_sequence_t<_CStrViews>...
    >;
};
template<typename _CStrView,typename..._CStrViews>
using c_str_view_concat_t=typename CStrView_Concat<
    _CStrView,
    _CStrViews...
>::type;
// c str view find first of
// c str view find last of
// c str view find first not of
// c str view find last not of
// c str view substr
// c str view push back
// c str view pop back
} // namespace nostd