#include<iostream>
#include<type_traits>
#include"type_name.hpp"
#include"function_traits.hpp"
#include"meta_function.hpp"
//
template<typename _Type>
void testFunctionTraitsT(){
    using function_tt=::nostd::function_traits_t<_Type>;
    ::std::cout<<__func__<<"<"<<::nostd::type_name<_Type>()<<">()\n";
    ::std::cout<<"is_function               :"<<::nostd::type_name<typename function_tt::is_function               >()<<"\n";
    ::std::cout<<"is_member_function_pointer:"<<::nostd::type_name<typename function_tt::is_member_function_pointer>()<<"\n";
    ::std::cout<<"result_type               :"<<::nostd::type_name<typename function_tt::result_type               >()<<"\n";
    ::std::cout<<"class_type                :"<<::nostd::type_name<typename function_tt::class_type                >()<<"\n";
    ::std::cout<<"argument_list             :"<<::nostd::type_name<typename function_tt::argument_list             >()<<"\n";
    ::std::cout<<"has_c_style_va_list       :"<<::nostd::type_name<typename function_tt::has_c_style_va_list       >()<<"\n";
    ::std::cout<<"has_const                 :"<<::nostd::type_name<typename function_tt::has_const                 >()<<"\n";
    ::std::cout<<"has_volatile              :"<<::nostd::type_name<typename function_tt::has_volatile              >()<<"\n";
    ::std::cout<<"has_left_value_reference  :"<<::nostd::type_name<typename function_tt::has_left_value_reference  >()<<"\n";
    ::std::cout<<"has_right_value_reference :"<<::nostd::type_name<typename function_tt::has_right_value_reference >()<<"\n";
    ::std::cout<<"has_noexcept              :"<<::nostd::type_name<typename function_tt::has_noexcept              >()<<"\n";
    ::std::cout<<"function_base_type        :"<<::nostd::type_name<typename function_tt::function_base_type        >()<<"\n";
}
template<auto _function>
void testFunctionTraitsOf(){
    ::std::cout<<__func__<<"<"<<::nostd::type_name<decltype(_function)>()<<">()\n";
    ::testFunctionTraitsT<decltype(_function)>();
}
//
int main(void){
    struct Foo{};
    testFunctionTraitsT<int(*)(...)noexcept>();
    testFunctionTraitsT<int(...)noexcept>();
    testFunctionTraitsT<int(Foo::*)(...)const volatile&&noexcept>();
    testFunctionTraitsOf<[](...)noexcept->int{return 0;}>();
    return 0;
}
