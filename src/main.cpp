#include<iostream>
#include"meta.hpp"
#include"meta_name.hpp"
#include"meta_string.hpp"
#include<type_traits>
#include<cassert>
meta::Enable<meta::True,int> main(void){
    ::std::cout<<META_FUNCTION_NAME<<::std::endl;
    // test_static_string();
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
    // test_universal_ref();
    ::std::cout<<meta::type_name<typename meta::Sequence_Concat<
        meta::Sequence<int,0,1,2>,
        meta::Sequence<int,3,4,5>,
        meta::Sequence<int,6,7,8>,
        meta::Sequence<int,9,10,11>,
        meta::Sequence<int,12,13>
    >::Type>()<<::std::endl;
    ::std::cout<<meta::type_name<
        typename meta::Sequence_MakeIndexs<
            meta::Auto<meta::SizeType(10)>,
            meta::Auto<meta::SizeType(31)>
        >::Type
    >()<<::std::endl;
    ::std::cout<<meta::type_name<
        META_STRING(META_FUNCTION_NAME)
    >()<<::std::endl;
    using HelloType=::meta::Auto<::meta::CStr(META_STRING("hello")::value)>;
     ::std::cout<<meta::type_name<
        HelloType
    >()<<::std::endl;
    return 0;
}
