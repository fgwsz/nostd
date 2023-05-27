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
// 调用函数模板的时候必须使用全命名空间名称，防止发生调用歧义
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

struct MetaFuncClassTag final{};

template<typename _Type>
struct IsConst{
    static constexpr auto value=false;
};
template<typename _Type>
struct IsConst<_Type const>{
    static constexpr auto value=true;
};
template<typename _Type>
static constexpr auto is_const_v=IsConst<_Type>::value;

template<typename _Type>
struct IsVolatile{
    static constexpr auto value=false;
};
template<typename _Type>
struct IsVolatile<_Type volatile>{
    static constexpr auto value=true;
};
template<typename _Type>
static constexpr auto is_volatile_v=IsVolatile<_Type>::value;

template<typename _Type>
struct IsLeftValueReference{
    static constexpr auto value=false;
};
template<typename _Type>
struct IsLeftValueReference<_Type&>{
    static constexpr auto value=true;
};
template<typename _Type>
static constexpr auto is_left_value_reference_v=IsLeftValueReference<_Type>::value;

template<typename _Type>
struct IsRightValueReference{
    static constexpr auto value=false;
};
template<typename _Type>
struct IsRightValueReference<_Type&&>{
    static constexpr auto value=true;
};
template<typename _Type>
static constexpr auto is_right_value_reference_v=IsRightValueReference<_Type>::value;

template<typename _Type>
struct RemoveConst{
    using type=_Type;
};
template<typename _Type>
struct RemoveConst<_Type const>{
    using type=_Type;
};
template<typename _Type>
using remove_const_t=typename RemoveConst<_Type>::type;

template<typename _Type>
struct RemoveVolatile{
    using type=_Type;
};
template<typename _Type>
struct RemoveVolatile<_Type volatile>{
    using type=_Type;
};
template<typename _Type>
using remove_volatile_t=typename RemoveVolatile<_Type>::type;

template<typename _Type>
struct RemoveLeftValueReference{
    using type=_Type;
};
template<typename _Type>
struct RemoveLeftValueReference<_Type&>{
    using type=_Type;
};
template<typename _Type>
using remove_left_value_reference_t=typename RemoveLeftValueReference<_Type>::type;

template<typename _Type>
struct RemoveRightValueReference{
    using type=_Type;
};
template<typename _Type>
struct RemoveRightValueReference<_Type&&>{
    using type=_Type;
};
template<typename _Type>
using remove_right_value_reference_t=typename RemoveRightValueReference<_Type>::type;

template<typename _Type>
using remove_reference_t=
remove_right_value_reference_t<
    remove_left_value_reference_t<_Type>
>;

template<typename _Type>
using remove_cv_t=remove_volatile_t<remove_const_t<_Type>>;

template<typename _Type>
using remove_cvref_t=remove_cv_t<remove_reference_t<_Type>>;

template<typename _Type_1,typename _Type_2>
struct IsSame{
    static constexpr auto value=false;
};
template<typename _Type>
struct IsSame<_Type,_Type>{
    static constexpr auto value=true;
};
template<typename _Type_1,typename _Type_2>
static constexpr auto is_same_v=
IsSame<
    remove_cvref_t<_Type_1>,
    remove_cvref_t<_Type_2>
>::value;

template<typename _Type>
concept has_tag=requires{
    typename _Type::tag;
};

template<typename _Type>
concept constant_instance=
    has_tag<_Type>&&
    is_same_v<typename _Type::tag,ConstantTag>;

template<typename _Type,typename _ValueType>
concept constant_instance_of=
    constant_instance<_Type>&&
    is_same_v<typename _Type::value_type,_ValueType>;

template<typename _Type>
concept array_instance=
    has_tag<_Type>&&
    is_same_v<typename _Type::tag,ArrayTag>;

template<typename _Type,typename _ElementType>
concept array_instance_of=
    array_instance<_Type>&&
    is_same_v<typename _Type::element_type,_ElementType>;

template<typename _Type>
concept string_instance=
    has_tag<_Type>&&
    is_same_v<typename _Type::tag,StringTag>;

template<typename _Type,typename _CharType>
concept string_instance_of=
    string_instance<_Type>&&
    is_same_v<typename _Type::char_type,_CharType>;

template<typename _Type>
concept meta_func_class_instance=
    has_tag<_Type>&&
    is_same_v<typename _Type::tag,MetaFuncClassTag>;

template<typename _Type>
concept array_constant_instance=
    constant_instance<_Type>&&
    array_instance<typename _Type::value_type>;

template<typename _Type,typename _ElementType>
concept array_constant_instanct_of=
    array_constant_instance<_Type>&&
    array_instance_of<typename _Type::value_type,_ElementType>;

template<typename _Type>
concept string_constant_instance=
    constant_instance<_Type>&&
    string_instance<typename _Type::value_type>;

template<typename _Type,typename _CharType>
concept string_constant_instanct_of=
    string_constant_instance<_Type>&&
    string_instance_of<typename _Type::value_type,_CharType>;

#define META_FUNC_CLASS_BEGIN(__NAME__) \
    struct __NAME__ final{ \
    public: \
        consteval __NAME__()=default; \
        using tag=MetaFuncClassTag; \
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
    template<
        meta_func_class_instance _meta_func_class,
        typename..._Types
    >
    META_FUNC_ARGS_BEGIN
        _meta_func_class meta_func_class_obj,
        _Types...args
    META_FUNC_ARGS_END
    {
        return meta_func_class_obj.apply(args...);
    }
META_FUNC_CLASS_END

template<
    meta_func_class_instance _meta_func_class,
    typename..._Types
>
static consteval auto invoke(
    _meta_func_class meta_func_class_obj,
    _Types...args
)noexcept{
    return ::nostd::Invoke::apply(
        meta_func_class_obj,
        args...
    );
}

template<typename _Type>
concept has_default_ctor=requires{
    _Type{};
};

template<typename _Type> requires has_default_ctor<_Type>
static consteval auto create()noexcept{
    return _Type{};
}

template<
    meta_func_class_instance _meta_func_class,
    typename..._Types
>
using invoke_t=
decltype(
    ::nostd::invoke(
        ::nostd::create<_meta_func_class>(),
        ::nostd::create<_Types>()...
    )
);

template<
    meta_func_class_instance _meta_func_class,
    typename..._Types
>
static constexpr auto invoke_v=
::nostd::invoke(
    ::nostd::create<_meta_func_class>(),
    ::nostd::create<_Types>()...
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
    array_instance _array_1,
    array_instance _array_2
>
requires is_same_v<
    typename _array_1::element_type,
    typename _array_2::element_type
>
static consteval auto operator+(
    _array_1 array_1,
    _array_2 array_2
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
    string_instance _string_1,
    string_instance _string_2
>
requires is_same_v<
    typename _string_1::char_type,
    typename _string_2::char_type
>
static consteval auto operator+(
    _string_1 string_1,
    _string_2 string_2
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

template<typename _Type_1,typename _Type_2>
concept comparable=requires(_Type_1 value_1,_Type_2 value_2){
    value_1 <   value_2;
    value_1 <=  value_2;
    value_1 >   value_2;
    value_1 >=  value_2;
    value_1 ==  value_2;
    value_1 !=  value_2;
    value_1 <=> value_2;
};

META_FUNC_CLASS_BEGIN(Constant_Max)
    template<
        constant_instance _constant_1,
        constant_instance _constant_2
    >
    requires comparable<
        typename _constant_1::value_type,
        typename _constant_2::value_type
    >
    META_FUNC_ARGS_BEGIN
        _constant_1 constant_1,
        _constant_2 constant_2
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
        constant_instance _constant_1,
        constant_instance _constant_2
    >
    requires comparable<
        typename _constant_1::value_type,
        typename _constant_2::value_type
    >
    META_FUNC_ARGS_BEGIN
        _constant_1 constant_1,
        _constant_2 constant_2
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
        string_constant_instance _string,
        constant_instance_of<usize_t> _usize_c_1,
        constant_instance_of<usize_t> _usize_c_2
    >
    META_FUNC_ARGS_BEGIN
        _string string,
        _usize_c_1 begin_index,
        _usize_c_2 end_index
    META_FUNC_ARGS_END
    {
        static_assert(begin_index.value<end_index.value,
            "begin_index must be less than end_index");
        static_assert(begin_index.value<(string.value.length),
            "begin_index must be less than end_index");
        constexpr auto end=Constant_Min::apply(
            end_index,
            usize_c<string.value.length>{}
        ).value;
        constexpr auto length=end-begin_index.value;
        constexpr auto size=length+1;
        using char_type=typename decltype(string.value)::char_type;
        String<char_type,size> ret;
        usize_t ret_index=0;
        for(usize_t string_index=begin_index;string_index<end;++string_index){
            ret.value[ret_index]=string.value.value[string_index];
            ++ret_index;
        }
        ret.value[ret_index]='\0';
        return ret;
    }
META_FUNC_CLASS_END

template<typename _Type>
static consteval auto auto_c(_Type _value)noexcept{
    Constant<_Type,_Type{_value}> ret;
    return ret;
}

META_FUNC_CLASS_BEGIN(String_FindFirstOf)
    template<
        string_constant_instance _string,
        constant_instance_of<typename _string::value_type::char_type> _char
    >
    META_FUNC_ARGS_BEGIN
        _string string,
        _char ch
    META_FUNC_ARGS_END
    {
        ssize_t index=0;
        for(;index<string.value.length;++index){
            if(string.value.value[index]==ch.value){
                break;
            }
        }
        return index==string.value.length?-1:index;
    }
META_FUNC_CLASS_END

} // namespace nostd
