#pragma once
// 常用概念

// 元函数(meta function)
// 满足如下条件：
// 0.本身是一个类模板
// 1.模板参数列表的形式适配<typename...>
// 2.含有成员类型::type，表示元函数调用的结果类型

// 元函数类(meta function class)
// 为元函数的外覆类，
// 这么做的目的：
// 1) 让元函数能作为类型传入其他元函数的参数列表
// 2) 让元函数调用的结果类型也可以是一个元函数
// 满足如下条件：
// 0.本身是一个类型
// 1.含有成员模板::template apply，表示所代表的元函数

// 编译期常量(static constant)
// 满足如下条件：
// 0.本身是一个类型
// 1.含有成员变量::value，表示编译期常量的值
// 2.含有成员类型::value_type，为::value的真实类型

// 命名规范

// 别名类型/别名模板(使用using/typedef定义的类型)
    // 统一使用蛇形命名法(小写字母写单词，一个下划线作为单词之间的分隔符)
    // 作为模板参数列表的形参时使用一个下划线_作为开头
// 非别名类型/非别名模板
    // 统一使用大驼峰命名法(一个单词中只有首字母大写，该单词的其他字母小写)
    // 作为模板参数列表的形参时使用一个下划线_作为开头
// 变量
    // 统一使用蛇形命名法(小写字母写单词，一个下划线作为单词之间的分隔符)
    // 作为模板参数列表的形参时使用一个下划线_作为开头

// 概念的实现

// 元函数类
template<
    template<typename...>class _MetaFunction
>struct MetaFunctionClass{
    template<typename..._Arguments>
    using apply=_MetaFunction<_Arguments...>;
    using type=MetaFunctionClass<_MetaFunction>
        ::template apply<>::type;
};
template<
    template<typename...>class _MetaFunction
>using fn=MetaFunctionClass<_MetaFunction>;

// Bind
template<
    typename _MetaFunctionClass,
    typename..._Arguments
>struct Bind{
private:
    template<typename...__Arguments>
    struct Binder
    :_MetaFunctionClass::template apply<
        _Arguments...,
        __Arguments...
    >{};
public:
    using type=MetaFunctionClass<Binder>;
};
// bind_t
template<
    typename _MetaFunctionClass,
    typename..._Arguments
>using Bind_t=typename Bind<
    _MetaFunctionClass,
    _Arguments...
>::type;
// Identity
template<typename _Type>
struct Identity{
    using type=_Type;
};
// Constant
template<
    typename _ValueType,
    _ValueType _value
>
struct Constant
:Identity<
    Constant<
        _ValueType,
        _value
    >
>{
    using value_type=_ValueType;
    static constexpr value_type const value=_value;
};
//
template<bool _value>
using bool_c=Constant<bool,_value>;
using true_c=Constant<bool,true>;
using false_c=Constant<bool,true>;
template<auto _value>
using auto_c=Constant<decltype(_value),_value>;
//
template<
    typename _ConditionType, 
    typename _TrueReturnType,
    typename _FalseReturnType
>struct _IfThenElse;
template<
    typename _TrueReturnType,
    typename _FalseReturnType
>struct _IfThenElse<
    true_c,
    _TrueReturnType,
    _FalseReturnType
>{
    using type=_TrueReturnType;
};
template<
    typename _TrueReturnType,
    typename _FalseReturnType
>struct _IfThenElse<
    false_c,
    _TrueReturnType,
    _FalseReturnType
>{
    using type=_FalseReturnType;
};
// _Condition:MetaFunctionClass<>->BooleanConstant
// _Then:MetaFunction
template<
    typename _Condition, 
    typename _TrueReturn,
    typename _FalseReturn
>struct IfThenElse{
    
};
template<
    typename _Constant_1,
    typename _Constant_2
>struct BinaryOperatorAdd{
private:
    static constexpr auto value=
        _Constant_1::value+
        _Constant_2::value;
public:
    using type=Constant<
        decltype(value),
        value
    >;
};
template<
    typename _Constant_1,
    typename _Constant_2
>struct BinaryOperatorSub{
private:
    static constexpr auto value=
        _Constant_1::value-
        _Constant_2::value;
public:
    using type=Constant<
        decltype(value),
        value
    >;
};
template<
    typename _Constant_1,
    typename _Constant_2
>struct BinaryOperatorMul{
private:
    static constexpr auto value=
        _Constant_1::value*
        _Constant_2::value;
public:
    using type=Constant<
        decltype(value),
        value
    >;
};
template<
    typename _Constant_1,
    typename _Constant_2
>struct BinaryOperatorDiv{
private:
    static constexpr auto value=
        _Constant_1::value/
        _Constant_2::value;
public:
    using type=Constant<
        decltype(value),
        value
    >;
};
template<
    typename _Constant_1,
    typename _Constant_2
>struct BinaryOperatorMod{
private:
    static constexpr auto value=
        _Constant_1::value%
        _Constant_2::value;
public:
    using type=Constant<
        decltype(value),
        value
    >;
};

#define __BINARY_OPERATOR(__OPERATOR__,__OPERATOR_NAME__) \
template< \
    typename _Constant_1, \
    typename _Constant_2 \
>struct BinaryOperator_##__OPERATOR_NAME__{ \
private: \
    static constexpr auto value= \
        (_Constant_1::value) __OPERATOR__ \
        (_Constant_2::value); \
public: \
    using type=Constant<
        decltype(value), \
        value \
    >; \
};

#define __UNARY_OPERATOR(__OPERATOR__,__OPERATOR_NAME__) \
template<typename _Constant> \
struct Operator_##__OPERATOR_NAME__{ \
private: \
    static constexpr decltype(auto) value= \
        __OPERATOR__ (_Constant::value); \
public: \
    using Type=Auto<value>; \
};

__META_OPERATOR_BINARY(+,Plus      )
__META_OPERATOR_BINARY(-,Minus     )
__META_OPERATOR_BINARY(*,Multiplies)
__META_OPERATOR_BINARY(/,Divides   )
__META_OPERATOR_BINARY(%,Modulus   )
__META_OPERATOR_UNARY (-,Negate    )

__META_OPERATOR_BINARY(==,EqualTo     )
__META_OPERATOR_BINARY(!=,NotEqualTo  )
__META_OPERATOR_BINARY(> ,Greater     )
__META_OPERATOR_BINARY(< ,Less        )
__META_OPERATOR_BINARY(>=,GreaterEqual)
__META_OPERATOR_BINARY(<=,LessEqual   )

__META_OPERATOR_BINARY(&&,LogicalAnd)
__META_OPERATOR_BINARY(||,LogicalOr )
__META_OPERATOR_UNARY (! ,LogicalNot)

__META_OPERATOR_BINARY(&,BitAnd)
__META_OPERATOR_BINARY(|,BitOr )
__META_OPERATOR_BINARY(^,BitXor)
__META_OPERATOR_UNARY (!,BitNot)

__META_OPERATOR_BINARY(<<,LeftShift )
__META_OPERATOR_BINARY(>>,RightShift)

#undef __META_OPERATOR_UNARY
#undef __META_OPERATOR_BINARY
template<
template<
    typename _binary_operator, // function
    typename _argument_1,
    typename _argument_2,
    typename..._arguments
>struct _operator;
{
    
};