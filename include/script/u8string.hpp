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
    constexpr U8String(U8Char const& u8char)noexcept
        :U8String(){
        (*this)=u8char;
    }
    constexpr U8String(_Array<U8Char> const& char_array)noexcept
        :U8String(){
        (*this)=char_array;
    }
    constexpr U8String& operator=(char const* value)noexcept{
        if(value){
            this->data_.clear();
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
        }
        return *this;
    }
    constexpr U8String& operator=(U8String const& u8string)noexcept{
        if(this!=&u8string){
            this->data_=u8string.data_;
        }
        return *this;
    }
    constexpr U8String& operator=(U8Char const& u8char)noexcept{
        this->data_.clear();
        if(!u8char.empty()){
            this->data_.push_back(u8char);
        }
        return *this;
    }
    constexpr U8String& operator=(_Array<U8Char> const& char_array)noexcept{
        this->data_=char_array;
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
    constexpr U8String& operator+=(U8String const& u8string)noexcept{
        this->data_+=u8string.data_;
        return *this;
    }
    constexpr U8String operator+(U8String const& u8string)const noexcept{
        U8String ret(*this);
        return ret+=u8string;
    }
    constexpr bool insert_char(size_t index,U8Char const& u8char)noexcept{
        return this->data_.insert_element(index,u8char);
    }
    constexpr bool insert_char_n(size_t index,U8Char const& u8char,size_t count)noexcept{
        return this->data_.insert_element_n(index,u8char,count);
    }
    constexpr bool insert_string(size_t index,U8String const& u8string)noexcept{
        return this->data_.insert_array(index,u8string.data_);
    }
    constexpr bool erase_char(size_t index)noexcept{
        return this->data_.erase_element(index);
    }
    constexpr bool erase_char_n(size_t index,size_t count)noexcept{
        return this->data_.erase_element_n(index,count);
    }
    constexpr U8String substring(size_t index,size_t count)const noexcept{
        U8String ret;
        if(index<this->size()){
            size_t real_count=count>(this->size()-index)?(this->size()-index):count;
            for(size_t n=0;n<real_count;++n){
                ret.data_.push_back(this->data_[index+n]);
            }
        }
        return ret;
    }
    constexpr void clear()noexcept{
        this->data_.clear();
    }
    constexpr void swap(U8String& u8string)noexcept{
        this->data_.swap(u8string.data_);
    }
    constexpr bool empty()const noexcept{
        this->data_.empty();
    }
    constexpr bool operator<(U8String const& u8string)const noexcept{
        if(this==&u8string){
            return false;
        }
        for(size_t index=0;
            index<(this->size()<=u8string.size()?this->size():u8string.size());
            ++index){
            if(this->data_[index]!=u8string[index]){
                return this->data_[index]<u8string[index];
            }
        }
        return this->size()<u8string.size();
    }
    constexpr bool operator>(U8String const& u8string)const noexcept{
        return u8string<(*this);
    }
    constexpr bool operator<=(U8String const& u8string)const noexcept{
        return !((*this)>u8string);
    }
    constexpr bool operator>=(U8String const& u8string)const noexcept{
        return !((*this)<u8string);
    }
    constexpr bool operator!=(U8String const& u8string)const noexcept{
        return (*this)>u8string||(*this)<u8string; 
    }
    constexpr bool operator==(U8String const& u8string)const noexcept{
        return !((*this)!=u8string);
    }
    constexpr _Array<unsigned char> to_byte_array()const noexcept{
        _Array<unsigned char> ret;
        for(size_t index=0;index<this->size();++index){
            for(size_t i=0;i<this->data_[index].byte_size();++i){
                ret.push_back(this->data_[index].const_data()[i]);
            }
        }
        return ret;
    }
    constexpr _Array<U8Char> to_char_array()const noexcept{
        return this->data_;
    }
}; // class U8String
}// namespace script
