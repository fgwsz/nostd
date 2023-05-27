#pragma once
namespace nostd{
// 命名规范：
// 类型别名/别名模板使用蛇形命名法
// 类型名(非别名)使用大驼峰命名法
// 变量名使用蛇形命名法
// 函数名使用蛇形命名法
// 模板参数 首字母统一使用一个下划线开头
// _t/_v惯用法
// 书写元函数的实现时要注意：
// 函数模板的模板参数列表里面的东西只是用来进行类型检查的，
// 在函数体实现的时候能不用模板参数列表里面的东西就尽量不要用
struct ConstantTag final{};
// 将编译期常量转化为类型
template<typename _ValueType,_ValueType _value>
struct Constant final{
    using type=Constant;
    using value_type=_ValueType;
    static constexpr value_type value=_value;
    constexpr value_type operator()()const noexcept{
        return this->value;
    }
    constexpr operator value_type()const noexcept{
        return this->value;
    }
    using tag=ConstantTag;
};
using ssize_t=signed long long int;
using usize_t=unsigned long long int;
// _c 后缀表示这是一个Constant
template<bool _value>
using bool_c=Constant<bool,_value>;
using true_t=bool_c<true>;
using false_t=bool_c<false>;
template<usize_t _value>
using usize_c=Constant<usize_t,_value>;
template<ssize_t _value>
using ssize_c=Constant<ssize_t,_value>;

struct ArrayTag final{};
// 此类型的实例对象可以直接作为非类型模板参数传入模板参数列表
template<typename _ElementType,usize_t _size>
struct Array final{
    using type=Array;
    using element_type=_ElementType;
    static constexpr usize_t size=_size;
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
        for(usize_t index=0;index<size;++index){
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
    using tag=ArrayTag;
};
// C++20新语法类模板隐式类型转换构造推断
// 可以直接传入一个字符数组字面量
// 例如array_c<"hello">
// 它会被推断为array_c<Array<char,5>{"hello"}>
template<Array _value>
using array_c=Constant<decltype(_value),_value>;

struct StringTag final{};
template<typename _CharType,usize_t _size>
struct String final{
    using type=String;
    using char_type=_CharType;
    static constexpr usize_t size=_size;
    static constexpr usize_t length=size-1;
    using value_type=char_type[size];
    value_type value{};
    using reference_type=char_type const(&)[size];
    consteval String(_CharType const(&c_str)[_size])noexcept{
        for(usize_t index=0;index<size;++index){
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
    using tag=StringTag;
};

template<String _value>
using string_c=Constant<decltype(_value),_value>;

#define META_FUNC_CLASS_BEGIN(__NAME__) \
    struct __NAME__ final{ \
    public: \
        consteval __NAME__()=default; \
//

#define META_FUNC_CLASS_END \
    }; \
//

#define META_FUNC_ARGS_BEGIN \
    static consteval auto apply( \
//

#define META_FUNC_ARGS_END \
    )noexcept \
//

META_FUNC_CLASS_BEGIN(Invoke)
    template<typename _MetaFuncClass,typename..._Types>
    META_FUNC_ARGS_BEGIN
        _MetaFuncClass meta_func_class_obj,
        _Types...args
    META_FUNC_ARGS_END
    {
        return meta_func_class_obj.apply(args...);
    }
META_FUNC_CLASS_END

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

META_FUNC_CLASS_BEGIN(If)
    template<typename _Then,typename _Else>
    META_FUNC_ARGS_BEGIN
        true_t condition,
        _Then true_ret,
        _Else false_ret
    META_FUNC_ARGS_END
    {
        return true_ret;
    }
    template<typename _Then,typename _Else>
    META_FUNC_ARGS_BEGIN
        false_t condition,
        _Then true_ret,
        _Else false_ret
    META_FUNC_ARGS_END
    {
        return false_ret;
    }
META_FUNC_CLASS_END

template<
    typename _ElementType,
    usize_t _usize_1,
    usize_t _usize_2
>
static consteval auto operator+(
    Array<_ElementType,_usize_1> array_1,
    Array<_ElementType,_usize_2> array_2
)noexcept{
    constexpr auto size=array_1.size+array_2.size;
    using element_type=typename decltype(array_1)::element_type;
    Array<element_type,size> ret;
    usize_t ret_index=0;
    for(usize_t index=0;index<array_1.size;++index){
        ret.value[ret_index]=array_1.value[index];
        ++ret_index;
    }
    for(usize_t index=0;index<array_2.size;++index){
        ret.value[ret_index]=array_2.value[index];
        ++ret_index;
    }
    return ret;
}

template<
    typename _CharType,
    usize_t _usize_1,
    usize_t _usize_2
>
static consteval auto operator+(
    String<_CharType,_usize_1> string_1,
    String<_CharType,_usize_2> string_2
)noexcept{
    constexpr auto length=string_1.length+string_2.length;
    constexpr auto size=length+1;
    using char_type=typename decltype(string_1)::char_type;
    String<char_type,size> ret;
    usize_t ret_index=0;
    for(usize_t index=0;index<string_1.length;++index){
        ret.value[ret_index]=string_1.value[index];
        ++ret_index;
    }
    for(usize_t index=0;index<string_2.length;++index){
        ret.value[ret_index]=string_2.value[index];
        ++ret_index;
    }
    ret.value[ret_index]='\0';
    return ret;
}

META_FUNC_CLASS_BEGIN(Constant_Max)
    template<
        typename _ValueType_1,
        typename _ValueType_2,
        _ValueType_1 _value_1,
        _ValueType_2 _value_2
    >
    META_FUNC_ARGS_BEGIN
        Constant<_ValueType_1,_value_1> constant_1,
        Constant<_ValueType_2,_value_2> constant_2
    META_FUNC_ARGS_END
    {
        constexpr auto const condition=
            constant_1.value>constant_2.value;
        return If::apply(
            bool_c<condition>{},
            constant_1,
            constant_2
        );
    }
META_FUNC_CLASS_END

META_FUNC_CLASS_BEGIN(Constant_Min)
    template<
        typename _ValueType_1,
        typename _ValueType_2,
        _ValueType_1 _value_1,
        _ValueType_2 _value_2
    >
    META_FUNC_ARGS_BEGIN
        Constant<_ValueType_1,_value_1> constant_1,
        Constant<_ValueType_2,_value_2> constant_2
    META_FUNC_ARGS_END
    {
        constexpr auto const condition=
            constant_1.value<constant_2.value;
        return If::apply(
            bool_c<condition>{},
            constant_1,
            constant_2
        );
    }
META_FUNC_CLASS_END

META_FUNC_CLASS_BEGIN(String_SubStr)
    template<
        typename _CharType,
        usize_t _string_size,
        usize_t _begin_index,
        usize_t _end_index
    >
    META_FUNC_ARGS_BEGIN
        String<_CharType,_string_size> string,
        Constant<usize_t,_begin_index> begin_index,
        Constant<usize_t,_end_index> end_index
    META_FUNC_ARGS_END
    {
        static_assert(begin_index.value<end_index.value,
            "begin_index must be less than end_index");
        static_assert(begin_index.value<(string.length),
            "begin_index must be less than end_index");
        constexpr auto end=Constant_Min::apply(
            end_index,
            usize_c<string.length>{}
        ).value;
        constexpr auto length=end-begin_index.value;
        constexpr auto size=length+1;
        using char_type=typename decltype(string)::char_type;
        String<char_type,size> ret;
        usize_t ret_index=0;
        for(usize_t string_index=begin_index;string_index<end;++string_index){
            ret.value[ret_index]=string.value[string_index];
            ++ret_index;
        }
        ret.value[ret_index]='\0';
        return ret;
    }
META_FUNC_CLASS_END


template<typename _Type_1,typename _Type_2>
struct IsSame{
    static constexpr auto value=false;
};
template<typename _Type>
struct IsSame<_Type,_Type>{
    static constexpr auto value=true;
};
template<typename _Type_1,typename _Type_2>
static constexpr auto is_same_v=IsSame<_Type_1,_Type_2>::value;
template<typename _Type>
concept constant_instance=is_same_v<typename _Type::tag,ConstantTag>;
template<typename _Type>
concept array_instance=is_same_v<typename _Type::tag,ArrayTag>;
template<typename _Type>
concept string_instance=is_same_v<typename _Type::tag,StringTag>;

META_FUNC_CLASS_BEGIN(TestClassTmp)
    template<
        String _string,
        Array _array
    >
    META_FUNC_ARGS_BEGIN
    META_FUNC_ARGS_END
    {
        return string_c<"ok!">{};
    }
    template<
        string_instance _str,
        array_instance _arr
    >
    META_FUNC_ARGS_BEGIN
        _str _string,
        _arr _array
    META_FUNC_ARGS_END
    {
        return string_c<"ok!">{};
    }
META_FUNC_CLASS_END

} // namespace nostd
