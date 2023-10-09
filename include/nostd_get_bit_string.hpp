#pragma once
#include<deque>
#include<string>
namespace nostd{
template<typename _Type>
static constexpr ::std::string getBitString(_Type const& value)noexcept{
    constexpr ::std::size_t byte_bit_size=8;
    constexpr ::std::size_t value_byte_size=sizeof(value);
    using byte_t=unsigned char;
    auto byte_array=(byte_t*)(void*)(&value);
    ::std::deque<char> deque;
    for(::std::size_t byte_index=0;byte_index<value_byte_size;++byte_index){
        for(::std::size_t bit_index=0;bit_index<byte_bit_size;++bit_index){
            deque.push_back(
                static_cast<byte_t>(
                    byte_array[byte_index]&
                    (byte_t{1}<<static_cast<byte_t>(byte_bit_size-1-bit_index))
                )!=byte_t{0}?'1':'0'
            );
        }
        deque.push_back(' ');
    }
    if(!deque.empty()){
        deque.pop_back();
    }
    return ::std::string(deque.cbegin(),deque.cend());
}
}// namespace nostd
