#include<iostream>
#include"meta.hpp"
#include"meta_name.hpp"
#include<type_traits>
#include<cassert>
template<meta::SizeType _length>
struct CStr{
    char value[_length]{};
    constexpr CStr(char const(&c_str)[_length]){
        for(meta::SizeType index=0;index<_length;++index){
            this->value[index]=c_str[index];
        }
    }
};
template<meta::SizeType _length,CStr<_length> _value>
struct String{
    static constexpr auto value=_value;
    static constexpr auto length=_length;
};


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
        String<sizeof(META_FUNCTION_NAME),META_FUNCTION_NAME>
    >()<<::std::endl;
    return 0;
}
