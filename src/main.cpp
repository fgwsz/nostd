#include<iostream>
#include"reflection/argument.hpp"
int main(void){
    int num=10;
    Argument arg=num;
    ::std::cout<<arg.is_val()<<::std::endl;
    arg=*(&num);
    ::std::cout<<arg.is_lval_ref()<<::std::endl;
    arg=::std::move(num);
    ::std::cout<<arg.is_rval_ref()<<::std::endl;
    return 0;
}
