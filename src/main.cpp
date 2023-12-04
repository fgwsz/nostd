#include"nostd.hpp"
#include<iostream>
int main(void){
    using namespace script;
    _Array<U8Char> str;
    str=str+_Array<U8Char>{"你","好","世","界"};
    ::std::cout<<str<<"\n";
    U8String string{"你好世界"};
    ::std::cout<<string.to_char_array()<<"\n";

    return 0;
}
