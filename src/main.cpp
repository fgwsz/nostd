#include<iostream>
#include<type_traits>
#include"type_name.hpp"
#include"function_traits.hpp"
struct foo{void show(...)const volatile&&{}};
template<typename _Type>
_Type declval()noexcept;
//
//
int main(void){
    std::cout<<nostd::type_name<
        nostd::function_traits_t<int(...)const volatile&&>::has_c_style_va_list
    >()<<std::endl;
    std::cout<<nostd::type_name<
        nostd::function_traits_of<declval<void>>::has_noexcept
    >()<<std::endl;
    return 0;
}
