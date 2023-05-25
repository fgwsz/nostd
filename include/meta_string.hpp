#pragma once
namespace meta{
template<typename _CharType,SizeType _length>
struct CStr{
    static constexpr auto length=_length;
    _CharType value[_length]{};
    constexpr CStr(_CharType const(&c_str)[_length]){
        for(SizeType index=0;index<_length;++index){
            this->value[index]=c_str[index];
        }
    }
    constexpr CStr& operator=(CStr const&)=default;
};
template<typename _CharType,SizeType _length,CStr<_CharType,_length> _value>
struct String{
    static constexpr auto c_str(){
        return _value;
    }
};
template<typename _CharType,SizeType _length>
constexpr SizeType c_str_length(_CharType const(&c_str)[_length]){
    return _length;
}
template<typename _CharType,SizeType _length>
constexpr _CharType c_str_char_type(_CharType const(&c_str)[_length]){
    return c_str[0];
}
} // namespace meta
#define META_STRING(__C_STYLE_STRING_LITERAL__) \
::meta::String< \
    decltype(::meta::c_str_char_type(__C_STYLE_STRING_LITERAL__)), \
    ::meta::c_str_length(__C_STYLE_STRING_LITERAL__), \
    __C_STYLE_STRING_LITERAL__ \
>

