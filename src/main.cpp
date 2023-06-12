#include<iostream>
#include"class_template.hpp"
#include"meta_name.hpp"
#include"meta_string.hpp"
#include"static_typename.hpp"
template<typename _Type>
consteval auto foo(){
    if constexpr(sizeof(_Type)==0){
        return int{};
    }else{
        return double{};
    }
}
int main(void){
    using namespace tmp;
    using typelist=TypeList<
        Constant<int,0>,
        Constant<int,1>,
        Constant<int,2>,
        Constant<int,3>,
        Constant<int,4>,
        Constant<int,5>,
        Constant<int,6>,
        Constant<int,7>,
        Constant<int,8>,
        Constant<int,9>
    >;
    using type_2=typelist_sublist_t<
        typelist,
        usize_constant<4>,
        usize_constant<10000>
    >;
    ::std::cout<<meta::type_name<
        type_2
    >()<<std::endl;
    auto a=::meta::type_name<decltype((int*)(0)==0)>();
    foo<int>();
    constexpr auto str=::nostd::static_typename<void>();
    ::std::cout<<str<<::std::endl;
    return 0;
}
