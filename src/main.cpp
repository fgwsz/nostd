#include"nostd.hpp"
#include<iostream>
int main(void){
    using number_t=::script::Number;
    ::std::cout<<(number_t(5)%3)<<::std::endl;
    ::std::cout<<(number_t(7)%-3)<<::std::endl;
    ::std::cout<<(number_t(100)^2)<<::std::endl;
    ::std::cout<<(number_t(4)^0.5)<<::std::endl;
    number_t num;
    ::std::cout<<num<<::std::endl;
    ::std::cout<<(num++)<<::std::endl;
    ::std::cout<<num<<::std::endl;
    ::std::cout<<(++num)<<::std::endl;
    ::std::cout<<num<<::std::endl;
    number_t num_2=100;
    num_2*=3;
    ::std::cout<<num_2<<::std::endl;
    ::std::cout<<number_t::difference(-300,-200)<<::std::endl;
    script::Boolean b;
    if(b)
        ::std::cout<<script::True<<::std::endl;
    else
        ::std::cout<<b<<::std::endl;
    return 0;
}
