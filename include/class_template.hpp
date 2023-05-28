#pragma once
#include"type_traits.hpp"
// 注意类模板元函数类名称全部使用蛇形命名法
// 数据外覆类类名称全部使用大驼峰命名法
// 模板参数中类型名统一使用大驼峰，变量名统一使用蛇形，但是全部要使用一个下划线作为开头
namespace tmp{
/**********************************************************************************************/
// 标签类
/**********************************************************************************************/
struct ConstantTag{};
struct SequenceTag{};
struct TypeListTag{};
struct ClassTemplateTag{};
struct MetaFunctionTag{};
/**********************************************************************************************/
// 辅助类型
/**********************************************************************************************/
using usize_t=unsigned long long int;
struct NullType{};
template<typename _Type,_Type _value>
struct Constant;
using true_type=Constant<bool,true>;
using false_type=Constant<bool,false>;
/**********************************************************************************************/
// 数据外覆类接口
/**********************************************************************************************/
template<typename _Type,_Type _value>
struct Constant;
template<typename _Type,_Type..._values>
struct Sequence;
template<typename..._Types>
struct TypeList;
template<template<typename...> class _ClassTemplate>
struct ClassTemplate;
/**********************************************************************************************/
// 概念实现
/**********************************************************************************************/
template<typename _Type>
concept has_tag=requires{
    typename _Type::tag;
};

template<typename _Type,typename _Tag>
concept check_tag=has_tag<_Type>&&
    is_same_v<_Tag,typename _Type::tag>;

template<typename _Type,typename _ValueType>
concept constant_of=check_tag<_Type,ConstantTag>&&
    is_same_v<typename _Type::value_type,_ValueType>;
/**********************************************************************************************/
// 元函数接口
/**********************************************************************************************/
template<typename _ClassTemplateInstance>
struct class_template_of;

template<
    constant_of<bool> _Condition,
    typename _Then,
    typename _Else
>
struct if_then_else;

template<typename _Type>
struct return_self;

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    typename _Type_1st
>
struct bind_1st;

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    typename _Type_2nd
>
struct bind_2nd;

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    typename _Type_1st,
    typename _Type_2nd
>
struct bind_1st_and_2nd;

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    typename..._Types
>
struct bind;

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    typename..._Types
>
struct invoke;

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    check_tag<TypeListTag> _TypeList
>
struct invoke_by_typelist;

// _LoopBody(_HasNext,_Ret,_Types)->TypeList(_HasNext,_Ret,_Types)
template<
    check_tag<ClassTemplateTag> _LoopBody,
    constant_of<bool> _HasNext,
    typename _Ret,
    typename..._Types
>
struct while_loop;

// 失败返回NullType
template<check_tag<TypeListTag> _TypeList,constant_of<usize_t> _Index>
struct typelist_at;

template<
    check_tag<TypeListTag> _TypeList_1,
    check_tag<TypeListTag> _TypeList_2,
    check_tag<TypeListTag>..._TypeLists
>
struct typelist_concat;

template<
    check_tag<TypeListTag> _TypeList,
    constant_of<usize_t> _BeginIndex,
    constant_of<usize_t> _EndIndex
>
struct typelist_sublist;
/**********************************************************************************************/
// 别名模板接口
/**********************************************************************************************/
template<typename _ClassTemplateInstance>
using class_template_of_t=typename class_template_of<_ClassTemplateInstance>::type;

template<
    constant_of<bool> _Condition,
    typename _Then,
    typename _Else
>
using if_then_else_t=typename if_then_else<_Condition,_Then,_Else>::type;

template<bool _value>
using bool_constant=Constant<bool,_value>;

template<usize_t _value>
using usize_constant=Constant<usize_t,_value>;

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    typename _Type_1st
>
using bind_1st_t=typename bind_1st<_ClassTemplate,_Type_1st>::type;

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    typename _Type_2nd
>
using bind_2nd_t=typename bind_2nd<_ClassTemplate,_Type_2nd>::type;

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    typename _Type_1st,
    typename _Type_2nd
>
using bind_1st_and_2nd_t=typename bind_1st_and_2nd<_ClassTemplate,_Type_1st,_Type_2nd>::type;

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    typename..._Types
>
using bind_t=typename bind<_ClassTemplate,_Types...>::type;

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    typename..._Types
>
using invoke_t=typename invoke<_ClassTemplate,_Types...>::type;

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    check_tag<TypeListTag> _TypeList
>
using invoke_by_typelist_t=typename invoke_by_typelist<_ClassTemplate,_TypeList>::type;

template<
    check_tag<ClassTemplateTag> _LoopBody,
    constant_of<bool> _HasNext,
    typename _Ret,
    typename..._Types
>
using while_loop_t=typename while_loop<_LoopBody,_HasNext,_Ret,_Types...>::type;

template<
    check_tag<TypeListTag> _TypeList,
    constant_of<usize_t> _Index
>
using typelist_at_t=typename typelist_at<_TypeList,_Index>::type;

template<
    check_tag<TypeListTag> _TypeList_1,
    check_tag<TypeListTag> _TypeList_2,
    check_tag<TypeListTag>..._TypeLists
>
using typelist_concat_t=typename typelist_concat<_TypeList_1,_TypeList_2,_TypeLists...>::type;

template<
    check_tag<TypeListTag> _TypeList,
    constant_of<usize_t> _BeginIndex,
    constant_of<usize_t> _EndIndex
>
using typelist_sublist_t=typename typelist_sublist<_TypeList,_BeginIndex,_EndIndex>::type;
/**********************************************************************************************/
// 数据外覆类实现
/**********************************************************************************************/
// 将单个编译期常量转换为类型
template<typename _Type,_Type _value>
struct Constant{
    using type=Constant;
    using value_type=_Type;
    static constexpr value_type value=_value;
    using tag=ConstantTag;
    value_type operator()()const noexcept{
        return this->value;
    }
    operator value_type()const noexcept{
        return this->value;
    }
};
// 将多个编译期常量转换为类型
template<typename _Type>
struct Sequence<_Type>{
    using type=Sequence;
    using value_type=_Type;
    static constexpr usize_t size=0;
    // size==0的时候，没有::value
    using tag=SequenceTag;
};
template<typename _Type,_Type _value,_Type..._values>
struct Sequence<_Type,_value,_values...>{
    using type=Sequence;
    using value_type=_Type;
    static constexpr usize_t size=sizeof...(_values);
    static constexpr value_type value[size]={_values...};
    using tag=SequenceTag;
    using reference_type=value_type(&)[size];
    reference_type operator()()const noexcept{
        return this->value;
    }
    operator reference_type()const noexcept{
        return this->value;
    }
};
// 可变参数类型外覆类
template<>
struct TypeList<>{
    using type=TypeList;
    using head=NullType;
    using tail=TypeList<>;
    static constexpr usize_t size=0;
    using tag=TypeListTag;
};
template<typename _HeadType,typename..._Types>
struct TypeList<_HeadType,_Types...>{
    using type=TypeList;
    using head=_HeadType;
    using tail=TypeList<_Types...>;
    static constexpr usize_t size=1+sizeof...(_Types);
    using tag=TypeListTag;
};
// 类模板外覆盖类
template<template<typename...> class _ClassTemplate>
struct ClassTemplate{
    using type=ClassTemplate;
    template<typename..._Types>
    using apply=_ClassTemplate<_Types...>;
    using tag=ClassTemplateTag;
};
/**********************************************************************************************/
// 元函数实现
/**********************************************************************************************/
template<template<typename...>class _ClassTemplate,typename..._Types>
struct class_template_of<_ClassTemplate<_Types...>>{
    using type=ClassTemplate<_ClassTemplate>;
    using tag=MetaFunctionTag;
};
// 分支结构
template<typename _Then,typename _Else>
struct if_then_else<true_type,_Then,_Else>{
    using type=_Then;
    using tag=MetaFunctionTag;
};
template<typename _Then,typename _Else>
struct if_then_else<false_type,_Then,_Else>{
    using type=_Else;
    using tag=MetaFunctionTag;
};

template<typename _Type>
struct return_self{
    using type=_Type;
    using tag=MetaFunctionTag;
};

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    typename _Type_1st
>
struct bind_1st{
    template<typename..._Types>
    struct binder
        :public _ClassTemplate::template apply<_Type_1st,_Types...>{};
    using type=ClassTemplate<binder>;
    using tag=MetaFunctionTag;
};

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    typename _Type_2nd
>
struct bind_2nd{
    template<typename _Type_1st,typename..._Types>
    struct binder
        :public _ClassTemplate::template apply<_Type_1st,_Type_2nd,_Types...>{};
    using type=ClassTemplate<binder>;
    using tag=MetaFunctionTag;
};

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    typename _Type_1st,
    typename _Type_2nd
>
struct bind_1st_and_2nd{
    template<typename..._Types>
    struct binder
        :public _ClassTemplate::template apply<_Type_1st,_Type_2nd,_Types...>{};
    using type=ClassTemplate<binder>;
    using tag=MetaFunctionTag;
};

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    typename..._Types
>
struct bind{
    template<typename..._Ts>
    struct binder
        :public _ClassTemplate::template apply<_Types...,_Ts...>{};
    using type=ClassTemplate<binder>;
    using tag=MetaFunctionTag;
};

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    typename..._Types
>
struct invoke{
    using type=typename _ClassTemplate::template apply<_Types...>::type;
    using tag=MetaFunctionTag;
};

template<
    check_tag<ClassTemplateTag> _ClassTemplate,
    typename..._Types
>
struct invoke_by_typelist<_ClassTemplate,TypeList<_Types...>>{
    using type=typename _ClassTemplate::template apply<_Types...>::type;
};

template<check_tag<TypeListTag> _TypeList,constant_of<usize_t> _Index>
struct typelist_at{
    /*
    * if(index>=typelist.size){ return null; }
    * if(index==0){ return head; }
    * else{ return typelist_at(index-1); }
    */
    static constexpr auto case_0=_Index::value>=_TypeList::size;
    static constexpr auto case_1=_Index::value==0;
    using type=
    if_then_else_t<bool_constant<case_0>,
        bind_t<ClassTemplate<return_self>,NullType>,
    // else
        if_then_else_t<bool_constant<case_1>,
            bind_t<ClassTemplate<return_self>,typename _TypeList::head>,
        // else
            bind_t<ClassTemplate<typelist_at>,
                typename _TypeList::tail,
                usize_constant<_Index::value-1>
            >
        >
    >::template apply<>::type;
    using tag=MetaFunctionTag;
};

template<
    check_tag<ClassTemplateTag> _LoopBody,
    typename _Ret,
    typename..._Types
>
struct while_loop<
    _LoopBody,
    false_type,
    _Ret,
    _Types...
>{
    using type=_Ret;
    using tag=MetaFunctionTag;
};

template<
    check_tag<ClassTemplateTag> _LoopBody,
    typename _Ret,
    typename..._Types
>
struct while_loop<
    _LoopBody,
    true_type,
    _Ret,
    _Types...
>{
    using loop_result=typename _LoopBody::template apply<
        true_type,
        _Ret,
        _Types...
    >::type;
    using type=invoke_by_typelist_t<
        bind_t<ClassTemplate<while_loop>,_LoopBody>,
        loop_result
    >;
    using tag=MetaFunctionTag;
};


template<
    check_tag<TypeListTag> _TypeList_1,
    check_tag<TypeListTag> _TypeList_2
>
struct __typelist_concat_helper;
template<
    typename..._Types_1,
    typename..._Types_2
>
struct __typelist_concat_helper<
    TypeList<_Types_1...>,
    TypeList<_Types_2...>
>{
    using type=TypeList<_Types_1...,_Types_2...>;
};
template<
    check_tag<TypeListTag> _TypeList_1,
    check_tag<TypeListTag> _TypeList_2,
    check_tag<TypeListTag>..._TypeLists
>
struct typelist_concat{
    /*
    * if(sizeof...(_TypeLists)==0){ return concat(1,2); }
    * else{ return typelist_concat(concat(1,2),_Typelists); }
    */
private:
    using concat_1_2=typename __typelist_concat_helper<
        _TypeList_1,
        _TypeList_2
    >::type;
public:
    using type=
    if_then_else_t<bool_constant<sizeof...(_TypeLists)==0>,
        bind_t<ClassTemplate<return_self>,concat_1_2>,
    // else
        bind_t<ClassTemplate<typelist_concat>,concat_1_2,_TypeLists...>
    >::template apply<>::type;
    using tag=MetaFunctionTag;
};

template<
    constant_of<bool>      _HasNext,
    check_tag<TypeListTag> _Ret,
    check_tag<TypeListTag> _TypeList,
    constant_of<usize_t>   _BeginIndex,
    constant_of<usize_t>   _EndIndex,
    constant_of<usize_t>   _CurrentIndex
>
struct __typelist_sublist_loop_body{
    static constexpr auto case_0=
        _CurrentIndex::value<_EndIndex::value;
    using has_next=bool_constant<case_0>;
    static constexpr auto case_1=
        _CurrentIndex::value>=_BeginIndex::value;
    using ret=
    if_then_else_t<bool_constant<case_0&&case_1>,
        bind_t<ClassTemplate<typelist_concat>,_Ret,TypeList<typename _TypeList::head>>,
    // else
        bind_t<ClassTemplate<return_self>,_Ret>
    >::template apply<>::type;
    using next_list=typename _TypeList::tail;
    using next_index=usize_constant<_CurrentIndex::value+1>;
    using type=TypeList<
        has_next,
        ret,
        next_list,
        _BeginIndex,
        _EndIndex,
        next_index
    >;
};

template<
    check_tag<TypeListTag> _TypeList,
    constant_of<usize_t> _BeginIndex,
    constant_of<usize_t> _EndIndex
>
struct typelist_sublist{
    static constexpr auto case_0=
        _BeginIndex::value>=_TypeList::size||
        _BeginIndex::value>=_EndIndex::value||
        _TypeList::size==0;
    static constexpr auto end_index=_EndIndex::value<_TypeList::size
        ?_EndIndex::value
        :_TypeList::size;
    using type=
    if_then_else_t<bool_constant<case_0>,
        bind_t<ClassTemplate<return_self>,TypeList<>>,
    // else while loop
        bind_t<ClassTemplate<while_loop>,
            ClassTemplate<__typelist_sublist_loop_body>,
            true_type,
            TypeList<>,
            _TypeList,
            _BeginIndex,
            usize_constant<end_index>,
            usize_constant<0>
        >
    >::template apply<>::type;
    using tag=MetaFunctionTag;
};

} // namespace end