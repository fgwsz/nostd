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
    nostd::string_c<
        nostd::String("hello")+
        nostd::String(" world!")+
        nostd::String(" haha")
    > str;
    ::std::cout<<meta::type_name<
       decltype(str) 
    >()<<::std::endl;
    ::std::cout<<
        nostd::String_SubStr::apply(
            nostd::String("0123456789"),
            nostd::usize_c<3>{},
            nostd::usize_c<8>{}
        )
    <<::std::endl;
    ::std::cout<<nostd::TestClassTmp::apply(
        nostd::String("hello"),nostd::Array(" world")
    ).value<<::std::endl;
    return 0;
}
