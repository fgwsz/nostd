#pragma once
namespace nostd{
// 命名规范：
// 类型别名/别名模板使用蛇形命名法
// 类型名(非别名)使用大驼峰命名法
// 变量名使用蛇形命名法
// 函数名使用蛇形命名法
// 模板参数 首字母统一使用一个下划线开头
// _t/_v惯用法

// 将编译期变量转化为类型
template<typename _Type,_Type _value>
struct Constant final{
    using type=Constant;
    using value_type=_Type;
    static constexpr value_type value=_value;
    value_type operator()()const noexcept{
        return this->value;
    }
    operator value_type()const noexcept{
        return this->value;
    }
};
using size_t=unsigned long long;
// 此类型的实例对象可以作为非类型模板参数
template<typename _ElementType,size_t _size>
struct Array final{
    using type=Array;
    using element_type=_ElementType;
    static constexpr size_t size=_size;
    using value_type=element_type[size];
    value_type value{};
    using reference_type=element_type const(&)[size];
    // 可以直接传入c风格的字符串字面量来实例化一个类对象
    // Array("hello")
    consteval Array(reference_type c_array){
        for(size_t index=0;index<size;++index){
            this->value[index]=c_array[index];
        }
    }
    constexpr reference_type operator()()const noexcept{
        return this->value;
    }
    operator reference_type()const noexcept{
        return this->value;
    }
};
template<auto _value>
using auto_t=typename Constant<decltype(_value),_value>::type;
} // namespace nostd
