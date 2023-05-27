#include<iostream>
#include"meta.hpp"
#include"meta_string.hpp"
#include"meta_name.hpp"
#include"new_meta.hpp"
int main(void){
    using type=nostd::invoke_t<
        nostd::If,
        nostd::false_t,
        double,
        nostd::array_c<"show time!">
    >;
    ::std::cout<<meta::type_name<
        type
    >()<<::std::endl;
    ::std::cout<<meta::type_name<
        meta::Auto<meta::CStr("show time!")>
    >()<<::std::endl;
    ::std::cout<<nostd::invoke_v< 
        nostd::If,
        nostd::false_t,
        double,
        nostd::array_c<"show time!">
    ><<::std::endl;
    ::std::cout<<nostd::invoke( 
        nostd::If{},
        nostd::false_t{},
        double{},
        nostd::array_c<"show time!">{}
    ).value<<::std::endl;
    nostd::array_c<
        nostd::Array("hello")+
        nostd::Array(" world!")+
        nostd::Array(" haha")
    > str;
    ::std::cout<<meta::type_name<
       decltype(str) 
    >()<<::std::endl;
    ::std::cout<<nostd::string_c<
        nostd::String_SubStr::apply(
            nostd::string_c<"0123456789">{},
            nostd::usize_c<3>{},
            nostd::usize_c<8>{}
    )>{}.value
    <<::std::endl;
    constexpr auto a_st=nostd::String("hello");
    ::std::cout<<nostd::ssize_c<
        nostd::String_FindFirstOf::apply(
            nostd::string_c<a_st>{},
            nostd::Constant<char,'e'>{}
    )>{}<<::std::endl;
    return 0;
}
