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
    script::U8Char u8char("你好世界");
    ::std::cout<<"u8char.data()="<<u8char<<::std::endl;
    ::std::cout<<"u8char.byte_size()="<<number_t(u8char.byte_size())<<::std::endl;
    using array_t=script::_Array<int>;
    array_t array;
    for(auto count=0;count<30;++count){
        array.set_element(count,2*count);
    }
    ::std::cout<<array<<::std::endl;
    array={1,2,3};
    ::std::cout<<array<<::std::endl;
    int carr[6]{4,5,6,7,8,9};
    array=carr;
    ::std::cout<<array<<::std::endl;
    array.insert_element(3,0);
    ::std::cout<<array<<::std::endl;
    array.erase_element(3);
    ::std::cout<<array<<::std::endl;
    return 0;
}
