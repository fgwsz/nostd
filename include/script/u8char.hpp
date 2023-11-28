#pragma once
extern "C"{
#include<stdint.h>
} // extern "C"
namespace script{
constexpr unsigned char const u8_1byte_head_byte_begin     =0b00000000;
constexpr unsigned char const u8_1byte_head_byte_finish    =0b01111111;
constexpr unsigned char const u8_2byte_head_byte_begin     =0b11000000;
constexpr unsigned char const u8_2byte_head_byte_finish    =0b11011111;
constexpr unsigned char const u8_3byte_head_byte_begin     =0b11100000;
constexpr unsigned char const u8_3byte_head_byte_finish    =0b11101111;
constexpr unsigned char const u8_4byte_head_byte_begin     =0b11110000;
constexpr unsigned char const u8_4byte_head_byte_finish    =0b11110111;
constexpr unsigned char const u8_multibyte_tail_byte_begin =0b10000000;
constexpr unsigned char const u8_multibyte_tail_byte_finish=0b10111111;
class U8Char final{
public:
    static constexpr unsigned char const max_byte_size_=4;
    using data_type=unsigned char[U8Char::max_byte_size_];
private:
    union{
        data_type data_;
        uint32_t data_number_;
    };
    unsigned char byte_size_;
public:
    constexpr U8Char()noexcept{
        for(auto& byte:this->data_){
            byte=0;
        }
        this->byte_size_=1;
    }
    constexpr U8Char(char const* value)noexcept
        :U8Char(){
        (*this)=value;
    }
    constexpr U8Char(U8Char const& u8char)noexcept
        :U8Char(){
        (*this)=u8char;
    }
    constexpr U8Char& operator=(char const* value)noexcept{
        if(!value){
            return *this;
        }
        unsigned char head_byte=(unsigned char)(value[0]);
        unsigned char byte_size=0;
        if(head_byte>=u8_1byte_head_byte_begin&&
           head_byte<=u8_1byte_head_byte_finish){
            byte_size=1;
        }else if(head_byte>=u8_2byte_head_byte_begin&&
                 head_byte<=u8_2byte_head_byte_finish){
            byte_size=2;
        }else if(head_byte>=u8_3byte_head_byte_begin&&
                 head_byte<=u8_3byte_head_byte_finish){
            byte_size=3;
        }else if(head_byte>=u8_4byte_head_byte_begin&&
                 head_byte<=u8_4byte_head_byte_finish){
            byte_size=4;
        }
        if(!byte_size){
            return *this;
        }
        if(byte_size>1){
            unsigned char tail_byte=0;
            for(unsigned char index=1;index<byte_size;++index){
                tail_byte=(unsigned char)(value[index]);
                if(!(tail_byte>=u8_multibyte_tail_byte_begin&&
                     tail_byte<=u8_multibyte_tail_byte_finish)){
                    return *this;
                }
            }
        }
        for(unsigned char index=0;index<byte_size;++index){
            this->data_[index]=(unsigned char)(value[index]);
        }
        for(unsigned char index=byte_size;index<U8Char::max_byte_size_;++index){
            this->data_[index]=0;
        }
        this->byte_size_=byte_size;
        return *this;
    }
    constexpr U8Char& operator=(U8Char const& u8char)noexcept{
        return (*this)=(char const*)(void*)(u8char.data_);
    }
    constexpr unsigned char byte_size()const noexcept{
        return this->byte_size_;
    }
    constexpr unsigned char max_byte_size()const noexcept{
        return U8Char::max_byte_size_;
    }
    constexpr typename U8Char::data_type& data()noexcept{
        return this->data_;
    }
    constexpr typename U8Char::data_type const& const_data()const noexcept{
        return this->data_;
    }
    constexpr bool operator==(U8Char const& u8char)const noexcept{
        return this->data_number_==u8char.data_number_;
    }
    constexpr bool operator!=(U8Char const& u8char)const noexcept{
        return this->data_number_!=u8char.data_number_;
    }
    constexpr bool operator<(U8Char const& u8char)const noexcept{
        return this->data_number_<u8char.data_number_;
    }
    constexpr bool operator>(U8Char const& u8char)const noexcept{
        return this->data_number_>u8char.data_number_;
    }
    constexpr bool operator<=(U8Char const& u8char)const noexcept{
        return this->data_number_<=u8char.data_number_;
    }
    constexpr bool operator>=(U8Char const& u8char)const noexcept{
        return this->data_number_>=u8char.data_number_;
    }
    template<typename OutputStream>
    friend constexpr OutputStream& operator<<(OutputStream& os,U8Char const& u8char)noexcept{
        for(unsigned char index=0;index<u8char.byte_size();++index){
            os<<u8char.const_data()[index];
        }
        return os;
    }
}; // class U8Char
} // namespace script
