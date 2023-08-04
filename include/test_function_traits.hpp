#pragma once
#include<iostream>
#include"type_name.hpp"
#include"function_traits.hpp"
template<typename _Type>
static void testFunctionTraitsT(void)noexcept{
    using function_tt=::nostd::FunctionTraits<_Type>;
    ::std::cout<<__func__<<"<"<<::nostd::type_name<_Type>()<<">()\n";
    ::std::cout<<"is_function                 :"<<::nostd::type_name<typename function_tt::is_function                 >()<<"\n";
    ::std::cout<<"is_unmember_function        :"<<::nostd::type_name<typename function_tt::is_unmember_function        >()<<"\n";
    ::std::cout<<"is_unmember_function_pointer:"<<::nostd::type_name<typename function_tt::is_unmember_function_pointer>()<<"\n";
    ::std::cout<<"is_member_function_pointer  :"<<::nostd::type_name<typename function_tt::is_member_function_pointer  >()<<"\n";
    ::std::cout<<"is_functor                  :"<<::nostd::type_name<typename function_tt::is_functor                  >()<<"\n";
    ::std::cout<<"result_type                 :"<<::nostd::type_name<typename function_tt::result_type                 >()<<"\n";
    ::std::cout<<"class_type                  :"<<::nostd::type_name<typename function_tt::class_type                  >()<<"\n";
    ::std::cout<<"parameter_list              :"<<::nostd::type_name<typename function_tt::parameter_list               >()<<"\n";
    ::std::cout<<"has_c_style_va_list         :"<<::nostd::type_name<typename function_tt::has_c_style_va_list         >()<<"\n";
    ::std::cout<<"has_const                   :"<<::nostd::type_name<typename function_tt::has_const                   >()<<"\n";
    ::std::cout<<"has_volatile                :"<<::nostd::type_name<typename function_tt::has_volatile                >()<<"\n";
    ::std::cout<<"has_left_value_reference    :"<<::nostd::type_name<typename function_tt::has_left_value_reference    >()<<"\n";
    ::std::cout<<"has_right_value_reference   :"<<::nostd::type_name<typename function_tt::has_right_value_reference   >()<<"\n";
    ::std::cout<<"has_noexcept                :"<<::nostd::type_name<typename function_tt::has_noexcept                >()<<"\n";
    ::std::cout<<"function_base_type          :"<<::nostd::type_name<typename function_tt::function_base_type          >()<<"\n";
    ::std::cout<<"function_type               :"<<::nostd::type_name<typename function_tt::function_type               >()<<"\n";
    ::std::cout<<"raw_type                    :"<<::nostd::type_name<typename function_tt::raw_type                    >()<<"\n";
}
template<typename _Type>
static void testFunctionTraitsOf(_Type&& value)noexcept{
    ::std::cout<<__func__<<"<"<<::nostd::type_name<decltype(value)>()<<">()\n";
    using function_tt=decltype(::nostd::function_traits_of(::std::forward<_Type>(value)));
    ::std::cout<<"is_function                 :"<<::nostd::type_name<typename function_tt::is_function                 >()<<"\n";
    ::std::cout<<"is_unmember_function        :"<<::nostd::type_name<typename function_tt::is_unmember_function        >()<<"\n";
    ::std::cout<<"is_unmember_function_pointer:"<<::nostd::type_name<typename function_tt::is_unmember_function_pointer>()<<"\n";
    ::std::cout<<"is_member_function_pointer  :"<<::nostd::type_name<typename function_tt::is_member_function_pointer  >()<<"\n";
    ::std::cout<<"is_functor                  :"<<::nostd::type_name<typename function_tt::is_functor                  >()<<"\n";
    ::std::cout<<"result_type                 :"<<::nostd::type_name<typename function_tt::result_type                 >()<<"\n";
    ::std::cout<<"class_type                  :"<<::nostd::type_name<typename function_tt::class_type                  >()<<"\n";
    ::std::cout<<"parameter_list              :"<<::nostd::type_name<typename function_tt::parameter_list               >()<<"\n";
    ::std::cout<<"has_c_style_va_list         :"<<::nostd::type_name<typename function_tt::has_c_style_va_list         >()<<"\n";
    ::std::cout<<"has_const                   :"<<::nostd::type_name<typename function_tt::has_const                   >()<<"\n";
    ::std::cout<<"has_volatile                :"<<::nostd::type_name<typename function_tt::has_volatile                >()<<"\n";
    ::std::cout<<"has_left_value_reference    :"<<::nostd::type_name<typename function_tt::has_left_value_reference    >()<<"\n";
    ::std::cout<<"has_right_value_reference   :"<<::nostd::type_name<typename function_tt::has_right_value_reference   >()<<"\n";
    ::std::cout<<"has_noexcept                :"<<::nostd::type_name<typename function_tt::has_noexcept                >()<<"\n";
    ::std::cout<<"function_base_type          :"<<::nostd::type_name<typename function_tt::function_base_type          >()<<"\n";
    ::std::cout<<"function_type               :"<<::nostd::type_name<typename function_tt::function_type               >()<<"\n";
    ::std::cout<<"raw_type                    :"<<::nostd::type_name<typename function_tt::raw_type                    >()<<"\n";
}
static void testFunctionTraits(void){
    struct Foo{};
    ::testFunctionTraitsT<int(*const volatile&&)(int const volatile&&,...)noexcept>();
    ::testFunctionTraitsT<int(&)(int const volatile&&,...)>();
    ::testFunctionTraitsT<int const volatile&&(int const volatile&&,...)const volatile&&noexcept>();
    ::testFunctionTraitsT<int const volatile&&(&)(int const volatile&&,...)noexcept>();
    ::testFunctionTraitsT<int(Foo::*const volatile&&)(int const volatile&&,...)const volatile&&noexcept>();
    ::testFunctionTraitsOf([](int const volatile&&,...)noexcept->int{return 0;});
}
