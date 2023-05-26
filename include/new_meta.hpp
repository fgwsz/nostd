#pragma once
namespace nostd{
// 命名规范：
// 类型别名/别名模板使用蛇形命名法
// 类型名(非别名)使用大驼峰命名法
// 变量名使用蛇形命名法
// 函数名使用蛇形命名法
// 模板参数 首字母统一使用一个下划线开头
// _t/_v惯用法

// 将编译期常量转化为类型
template<typename _Type,_Type _value>
struct Constant final{
    using type=Constant;
    using value_type=_Type;
    static constexpr value_type value=_value;
    constexpr value_type operator()()const noexcept{
        return this->value;
    }
    constexpr operator value_type()const noexcept{
        return this->value;
    }
};
using size_t=unsigned long long;
// 此类型的实例对象可以直接作为非类型模板参数传入模板参数列表
template<typename _ElementType,size_t _size>
struct Array final{
    using type=Array;
    using element_type=_ElementType;
    static constexpr size_t size=_size;
    using value_type=element_type[size];
    value_type value{};
    using reference_type=element_type const(&)[size];
    // 可以直接传入c风格的字符串字面量来实例化一个类对象
    // C++20新特性类模板推断
    // 使用Array("hello")语句
    // 等效于Array<char,6>{"hello"}
    consteval Array(_ElementType const(&c_array)[_size])noexcept{
    // 注意此处使用_ElementType const(&)[_size]而不使用reference_type
    // 在gcc中使用类型别名reference_type会导致编译不通过
    // 猜测可能的原因：类还没推断完成，类型别名未定义
        for(size_t index=0;index<size;++index){
            this->value[index]=c_array[index];
        }
    }
    consteval Array()noexcept=default;
    constexpr reference_type operator()()const noexcept{
        return this->value;
    }
    constexpr operator reference_type()const noexcept{
        return this->value;
    }
};
// _c 后缀表示这是一个Constant
template<bool _value>
using bool_c=Constant<bool,_value>;
using true_t=bool_c<true>;
using false_t=bool_c<false>;
template<size_t _value>
using size_c=Constant<size_t,_value>;
// C++20新语法类模板隐式类型转换构造推断
// 可以直接传入一个字符数组字面量
// 例如array_c<"hello">
// 它会被推断为array_c<Array<char,5>{"hello"}>
template<Array _value>
using array_c=Constant<decltype(_value),_value>;

#define META_FUNC_CLASS(__NAME__,...) \
    struct __NAME__ final{__VA_ARGS__}; \
//

#define META_FUNC_APPLY(...) \
    static consteval auto apply(__VA_ARGS__)noexcept \
//

META_FUNC_CLASS(Invoke,
    template<typename _MetaFuncClass,typename..._Types>
    META_FUNC_APPLY(
        _MetaFuncClass meta_func_class_obj,
        _Types...args
    ){
        return meta_func_class_obj.apply(args...);
    }
)

template<typename _MetaFuncClass,typename..._Types>
static consteval auto invoke(
    _MetaFuncClass meta_func_class_obj,
    _Types...args
)noexcept{
    return Invoke::apply<_MetaFuncClass,_Types...>(
        meta_func_class_obj,
        args...
    );
}

template<typename _Type>
static consteval auto create()noexcept{
    return _Type{};
}

template<typename _MetaFuncClass,typename..._Types>
using invoke_t=
decltype(
    invoke(
        create<_MetaFuncClass>(),
        create<_Types>()...
    )
);

template<typename _MetaFuncClass,typename..._Types>
static constexpr auto invoke_v=
invoke(
    create<_MetaFuncClass>(),
    create<_Types>()...
).value;

META_FUNC_CLASS(If,
    template<typename _Then,typename _Else>
    META_FUNC_APPLY(
        true_t condition,
        _Then true_ret,
        _Else false_ret
    ){
        return true_ret;
    }
    template<typename _Then,typename _Else>
    META_FUNC_APPLY(
        false_t condition,
        _Then true_ret,
        _Else false_ret
    ){
        return false_ret;
    }
)

template<
    typename _ElementType,
    size_t size_1,
    size_t size_2
>
static consteval auto operator+(
    Array<_ElementType,size_1> array_1,
    Array<_ElementType,size_2> array_2
)noexcept{
    constexpr auto size=size_1+size_2;
    Array<_ElementType,size> ret;
    for(size_t index=0;index<size_1;++index){
        ret.value[index]=array_1.value[index];
    }
    for(size_t index=0;index<size_2;++index){
        ret.value[index+size_1]=array_2.value[index];
    }
    return ret;
}

template<typename _CharType,size_t _size>
struct String final{
    using type=String;
    using char_type=_CharType;
    static constexpr size_t size=_size;
    using value_type=char_type[size];
    value_type value{};
    using reference_type=char_type const(&)[size];
    consteval String(_CharType const(&c_str)[_size])noexcept{
        for(size_t index=0;index<size;++index){
            this->value[index]=c_str[index];
        }
    }
    consteval String()noexcept=default;
    constexpr reference_type operator()()const noexcept{
        return this->value;
    }
    constexpr operator reference_type()const noexcept{
        return this->value;
    }
};

template<String _value>
using string_c=Constant<decltype(_value),_value>;

template<
    typename _ElementType,
    size_t size_1,
    size_t size_2
>
static consteval auto operator+(
    String<_ElementType,size_1> string_1,
    String<_ElementType,size_2> string_2
)noexcept{
    constexpr auto size=size_1+size_2-1;
    String<_ElementType,size> ret;
    for(size_t index=0;index<size_1-1;++index){
        ret.value[index]=string_1.value[index];
    }
    for(size_t index=0;index<size_2;++index){
        ret.value[index+size_1-1]=string_2.value[index];
    }
    return ret;
}

} // namespace nostd
