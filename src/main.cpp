#include<iostream>
#include<type_traits>
#include"type_name.hpp"
template<typename _Type>
void test(_Type&& arg){
    ::std::cout<<"_Type:"<<::nostd::type_name<_Type>()<<::std::endl;
    ::std::cout<<"_Type&&:"<<::nostd::type_name<_Type&&>()<<::std::endl;
    ::std::cout<<"decltype(arg):"<<::nostd::type_name<decltype(arg)>()<<::std::endl;
    ::std::cout<<"decltype(::std::forward<_Type>(arg)):"<<::nostd::type_name<decltype(::std::forward<_Type>(arg))>()<<::std::endl;
}
#define name(...) #__VA_ARGS__
int main(void){
    int v=10;
    int const v_c=10;
    int& v_mr=v;
    int const& v_cr=v_c;
    int v_temp_1=10;
    int&& v_rr=::std::move(v_temp_1);
    ::std::cout<<name(v    )<<::std::endl;test(v    );
    ::std::cout<<name(v_c  )<<::std::endl;test(v_c  );
    ::std::cout<<name(v_mr )<<::std::endl;test(v_mr );
    ::std::cout<<name(v_cr )<<::std::endl;test(v_cr );
    ::std::cout<<name(v_rr )<<::std::endl;test(::std::move(v_rr));
    return 0;
}
