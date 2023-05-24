#include<iostream>
#include"meta.hpp"
#include"meta_name.hpp"
meta::Enable<meta::True,int> main(void){
    typename meta::Invoke<
        typename meta::Invoke<
            meta::Template<meta::IF>,
            meta::True,
            meta::Template<meta::IF>,
            meta::Template<meta::Return>
        >::Type,
        meta::True,
        int,
        double
    >::Type a;
    ::std::cout<<"typeof(a)="<<meta::type_name<decltype(a)>()<<::std::endl;
    meta::Operator_LeftShift<meta::Auto<(int)true>,meta::Auto<4>>::Type b;
    ::std::cout<<"typeof(b)="<<meta::type_name<decltype(b)>()<<::std::endl;
    meta::test_compiler_name();
    meta::test_function_name<::std::string>();
    meta::test_type_name<::std::string const volatile* const volatile(*const volatile&&)[2][1]>();
    ::std::system("pause");
    return 0;
}
