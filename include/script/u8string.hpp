#pragma once
#include"u8char.hpp"
#include"array.hpp"
namespace script{
class U8String{
private:
    _Array<U8Char> data_;
public:
    constexpr U8String()noexcept{
        this->data_=_Array<U8Char>();
    }
    constexpr U8String(char const* value)noexcept
        :U8String(){
        (*this)=value;
    }
    constexpr U8String(U8String const& u8string)noexcept
        :U8String(){
        (*this)=u8string;
    }
    constexpr U8String& operator=(char const* value)noexcept{
        char const* str=value;
        U8Char u8char;
        while((*str)!='\0'){
            u8char=str;
            if(u8char.empty()){
                break;
            }
            this->data_.push_back(u8char);
            str+=u8char.byte_size();
        }
        return *this;
    }
    constexpr U8String& operator=(U8String const& u8string)noexcept{
        if(this!=&u8string){
            this->data_=u8string.data_;
        }
        return *this;
    }
    constexpr size_t size()const noexcept{
        return this->data_.size();
    }
    constexpr U8Char& operator[](size_t index)noexcept{
        return this->data_[index];
    }
    constexpr U8Char const& operator[](size_t index)const noexcept{
        return this->data_[index];
    }
    template<typename OutputStream>
    friend constexpr OutputStream& operator<<(OutputStream& os,U8String const& u8string)noexcept{
        for(size_t index=0;index<u8string.size();++index){
            os<<u8string[index];
        }
        return os;
    }
    constexpr U8String operator+(U8String const& u8string)const noexcept{
        U8String ret(*this);
        for(size_t index=0;index<u8string.size();++index){
            ret.data_.push_back(u8string[index]);
        }
        return ret;
    }
    constexpr U8String& operator+=(U8String const& u8string)noexcept{
        return (*this)=(*this)+u8string;
    }
    constexpr bool insert(size_t index,U8Char const& u8char)noexcept{
        return this->data_.insert_element(u8char);
    }
    constexpr bool erase(size_t index)noexcept{
        return this->data_.erase_element(index);
    }
}; // class U8String
}// namespace script
