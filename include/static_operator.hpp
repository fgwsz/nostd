#pragma once
#include<type_traits>
namespace nostd{
//
#define __NOSTD_BINARY_OPERATOR(__OP__,__CLASS_NAME__,__ALIAS_NAME__) \
template<typename _Constant_1,typename _Constant_2> \
struct Operator##__CLASS_NAME__{ \
private: \
    static constexpr auto value= \
        _Constant_1::value __OP__ _Constant_2::value; \
    using value_type=::std::remove_cvref_t<decltype(value)>; \
public: \
    using type=::std::integral_constant<value_type,value>; \
}; \
template<typename _Constant_1,typename _Constant_2> \
using operator_##__ALIAS_NAME__##_t= \
    typename Operator##__CLASS_NAME__<_Constant_1,_Constant_2>::type; \
//
#define __NOSTD_UNARY_OPERATOR(__OP__,__CLASS_NAME__,__ALIAS_NAME__) \
template<typename _Constant> \
struct Operator##__CLASS_NAME__{ \
private: \
    static constexpr auto value=__OP__ _Constant::value; \
    using value_type=::std::remove_cvref_t<decltype(value)>; \
public: \
    using type=::std::integral_constant<value_type,value>; \
}; \
template<typename _Constant> \
using operator_##__ALIAS_NAME__##_t= \
    typename Operator##__CLASS_NAME__<_Constant>::type; \
//
__NOSTD_BINARY_OPERATOR(+ ,Add          ,add            )
__NOSTD_BINARY_OPERATOR(- ,Sub          ,sub            )
__NOSTD_BINARY_OPERATOR(* ,Mul          ,mul            )
__NOSTD_BINARY_OPERATOR(/ ,Div          ,div            )
__NOSTD_BINARY_OPERATOR(% ,Mod          ,mod            )
__NOSTD_UNARY_OPERATOR (+ ,Positive     ,positive       )
__NOSTD_UNARY_OPERATOR (- ,Negative     ,negative       )
__NOSTD_BINARY_OPERATOR(==,EqualTo      ,equal_to       )
__NOSTD_BINARY_OPERATOR(!=,NotEqualTo   ,not_equal_to   )
__NOSTD_BINARY_OPERATOR(> ,Greater      ,greater        )
__NOSTD_BINARY_OPERATOR(< ,Less         ,less           )
__NOSTD_BINARY_OPERATOR(>=,GreaterEqual ,greater_equal  )
__NOSTD_BINARY_OPERATOR(<=,LessEqual    ,less_equal     )
__NOSTD_BINARY_OPERATOR(&&,And          ,and            )
__NOSTD_BINARY_OPERATOR(||,Or           ,or             )
__NOSTD_UNARY_OPERATOR (! ,Not          ,not            )
__NOSTD_BINARY_OPERATOR(& ,BitAnd       ,bit_and        )
__NOSTD_BINARY_OPERATOR(| ,BitOr        ,bit_or         )
__NOSTD_UNARY_OPERATOR (~ ,BitNot       ,bit_not        )
__NOSTD_BINARY_OPERATOR(^ ,BitXor       ,bit_xor        )
__NOSTD_BINARY_OPERATOR(<<,BitLeftShift ,bit_left_shift )
__NOSTD_BINARY_OPERATOR(>>,BitRightShift,bit_right_shift)
#undef __NOSTD_UNARY_OPERATOR
#undef __NOSTD_BINARY_OPERATOR
}