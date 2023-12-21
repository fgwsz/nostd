#pragma once
#include<utility>
#include<type_traits>
#include<iostream>
#include<source_location>
struct Any{
    int data_;
    // 不用多个Cast函数（SFINAE分发）的原因：因为类型隐式类型转换的时候可能会匹配多个版本，无法通过编译
    // template<typename _Type,::std::enable_if_t<
    //     !::std::is_reference_v<_Type>&&
    //     !::std::is_const_v<_Type>
    // ,int>_=0> // T
    // operator _Type()const noexcept{
    //     return *static_cast<_Type*>(nullptr);
    // }
    // template<typename _Type,::std::enable_if_t<
    //     !::std::is_reference_v<_Type>&&
    //     ::std::is_const_v<_Type>
    // ,int>_=1> // T const
    // operator _Type()const noexcept{
    //     return *static_cast<_Type*>(nullptr);
    // }
    // template<typename _Type,::std::enable_if_t<
    //     ::std::is_lvalue_reference_v<_Type&>&&
    //     !::std::is_const_v<_Type>
    // ,int>_=2> // T&
    // operator _Type&()const noexcept{
    //     return *static_cast<_Type*>(nullptr);
    // }
    // template<typename _Type,::std::enable_if_t<
    //     ::std::is_lvalue_reference_v<_Type&>&&
    //     ::std::is_const_v<_Type>
    // ,int>_=3> // T const&
    // operator _Type&()const noexcept{
    //     return *static_cast<_Type*>(nullptr);
    // }
    // template<typename _Type,::std::enable_if_t<
    //     ::std::is_rvalue_reference_v<_Type&&>
    // ,int>_=4> // T&&
    // operator _Type&&()const noexcept{
    //     return *static_cast<_Type*>(nullptr);
    // }

    // 使用万能引用(单个operator T&&)来转换任意的类型转换这个方式也失败了
    // T&&不给力，还是使用万金油的T&(T/T const/T&/T const&)+T&&(T&& only rvalue_ref)
    // operator T&:
    // T&->T
    // T&->T const
    // T&->T&
    // T const&->T const&
    // operator T&&:
    // T&&->T&&
    Any()=default;
    template<typename _Type>
    operator _Type&()const noexcept{
        ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
        if constexpr(!::std::is_const_v<_Type>){
            ::std::cout<<"Cast To _Type&\n";
        }else if constexpr(::std::is_const_v<_Type>){
            ::std::cout<<"Cast To _Type const&\n";
        }
        return *static_cast<_Type*>(
            const_cast<::std::remove_cvref_t<decltype(data_)>*>(&data_)
        );
    }
    template<typename _Type,
        ::std::enable_if_t<!::std::is_reference_v<_Type>,int>_=0>
    operator _Type&&()const noexcept{
        ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
        ::std::cout<<"Cast To _Type&&\n";
        return ::std::move(*static_cast<::std::remove_cvref_t<_Type>*>(
            const_cast<::std::remove_cvref_t<decltype(data_)>*>(&data_)
        ));
    }
};
void foo_0(int){
    ::std::cout<<"foo_0()\n";
}
void foo_1(int const){
    ::std::cout<<"foo_1()\n";
}
void foo_2(int&){
    ::std::cout<<"foo_2()\n";
}
void foo_3(int const&){
    ::std::cout<<"foo_3()\n";
}
void foo_4(int&&){
    ::std::cout<<"foo_4()\n";
}
void test_cast_1(){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    Any any;
    static_cast<int>(any);
    static_cast<int const>(any);
    static_cast<int&>(any);
    static_cast<int const&>(any);
    static_cast<int&&>(any);
}
void test_cast_2(){
    ::std::cout<<::std::source_location::current().function_name()<<::std::endl;
    Any any;
    foo_0(any);
    foo_1(any);
    foo_2(any);
    foo_3(any);
    foo_4(any);
}
void test(){
    test_cast_1();
    test_cast_2();
}