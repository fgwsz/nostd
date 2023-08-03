#pragma once
// 一些理念

// 元函数(meta function)
// 满足如下条件：
// 0.本身是一个类模板
// 1.模板参数列表的形式适配<typename...>
// 2.含有成员类型::type，表示元函数调用的结果类型

// 元函数类(meta function class)
// 为元函数的外覆类，
// 这么做的目的：
// 1) 把元函数包装为类型传入其他元函数的参数列表
// 2) 元函数调用的结果类型可以是一个元函数类
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
// 概念
    // 统一使用蛇形命名法(小写字母写单词，一个下划线作为单词之间的分隔符)

// 为了区分一个类型通过哪一个类模板实例化而来，
// 引入标签系统

// 标签类
struct TagOfMetaFunctionClass{};
struct TagOfStaticConstant{};
// public继承该类模板的实例可以包含如下语句
// using tag=_TagType;
// 非元函数
template<typename _TagType>
struct Tag{
    using tag=_TagType;
};
// 元函数类(非元函数)
template<
    template<typename...>class _MetaFunction
>struct MetaFunctionClass
    :Tag<TagOfMetaFunctionClass>
{
    template<typename..._Arguments>
    using apply=_MetaFunction<_Arguments...>;
};
// 编译期常量(非元函数)
template<
    typename _ValueType,
    _ValueType _value
>struct StaticConstant
    :Tag<TagOfStaticConstant>
{
    using value_type=_ValueType;
    static constexpr value_type value=_value;
};
// _c后缀代表这是一个StaticConstant的实例化类型
// 布尔类型常量
using true_c=StaticConstant<bool,true>;
using false_c=StaticConstant<bool,true>;
// 空常量
using null_c=StaticConstant<decltype(nullptr),nullptr>;
// 单分支结构 if then else
// _Condition:StaticConstant<bool,_value>
// _Then:type
// _Else:type
template<
    typename _Condition,
    typename _Then,
    typename _Else
>struct IfThenElse;
template<
    typename _Then,
    typename _Else
>struct IfThenElse<true_c,_Then,_Else>{
    using type=_Then;
};
template<
    typename _Then,
    typename _Else
>struct IfThenElse<false_c,_Then,_Else>{
    using type=_Else;
};
// 单分支结构 if then else
// _Condition:StaticConstant<bool,_value>
// _Then:type
// _Else:type
template<
    typename _Condition,
    typename _Then,
    typename _Else
>using if_then_else_t=
    typename IfThenElse<_Condition,_Then,_Else>::type;
// 多分支结构 switch case default

// 循环结构 while
struct
