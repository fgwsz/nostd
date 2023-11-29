#pragma once
extern "C"{
#include<stddef.h>
#include<stdlib.h>
#include<string.h>
} // extern "C"
namespace script{
template<typename _Type>
struct _Element{
    _Type* pointer_;
};
template<typename _Type>
class _Array final{
private:
    _Element<_Type>* data_;
    size_t capacity_;
    size_t size_;
    static constexpr size_t const default_capacity_=10;
public:
    constexpr _Array<_Type>()noexcept{
        this->data_=(_Element<_Type>*)::malloc(sizeof(_Element<_Type>)*_Array::default_capacity_);
        this->capacity_=_Array::default_capacity_;
        this->size_=0;
    }
    constexpr size_t capacity()const noexcept{
        return this->capacity_;
    }
    constexpr size_t size()const noexcept{
        return this->size_;
    }
private:
    constexpr void auto_expand_capacity()const noexcept{
        if(this->size_<this->capacity_){
            return;
        }
        size_t new_capacity=this->capacity_*2;
        _Element<_Type>* new_data=(_Element<_Type>*)::malloc(sizeof(_Element<_Type>)*new_capacity);
        ::memmove(new_data,this->data_,this->size_*sizeof(_Element<_Type>));
        ::free(this->data_);
        this->data_=new_data;
        this->capacity_=new_capacity;
    }
public:
    constexpr bool insert_element(size_t index,_Type const& value)noexcept{
        if(index>this->size_){
            return false;
        }
        this->auto_expand_capacity();
        ::memmove(this->data_+index+1,this->data_+index,(this->size_-index)*sizeof(_Element<_Type>));
        (this->data_[index]).pointer_=(_Type*)::malloc(sizeof(_Type));
        new((this->data_[index]).pointer_)_Type(value);
        ++(this->size_);
        return true;
    }
    constexpr bool erase_element(size_t index)noexcept{
        if(index>=this->size_){
            return false;
        }
        ((this->data_[index]).pointer_)->~_Type();
        ::free((this->data_[index]).pointer_);
        ::memmove(this->data_+index,this->data_+index+1,(this->size_-index-1)*sizeof(_Element<_Type>));
        --(this->size_);
        return true;
    }
    constexpr bool get_element(size_t index,_Type& value)const noexcept{
        if(index>=this->size_){
            return false;
        }
        value=*((this->data_[index]).pointer_);
        return true;
    }
    constexpr bool set_element(size_t index,_Type const& value)noexcept{
        if(index>this->size_){
            return false;
        }
        if(index==this->size_){
            return this->insert_element(index,value);
        }
        *((this->data_[index]).pointer_)=value;
        return true;
    }
    constexpr _Type& operator[](size_t index)noexcept{
        return *((this->data_[index]).pointer_);
    }
    constexpr _Type const& operator[](size_t index)const noexcept{
        return *((this->data_[index]).pointer_);
    }
    constexpr _Array<_Type>(_Array<_Type> const& array)noexcept
        :_Array<_Type>(){
        (*this)=array;
    }
    constexpr bool empty()const noexcept{
        return this->size_==0;
    }
    constexpr void push_back(_Type const& value)noexcept{
        this->insert_element(this->size_,value);
    }
    constexpr void pop_back()noexcept{
        if(!this->empty()){
            this->erase_element(this->size_-1);
        }
    }
    constexpr _Array<_Type>& operator=(_Array<_Type> const& array)noexcept{
        if(this!=&array){
            while(this->size_>array.size_){
                this->pop_back();
            }
            for(size_t index=0;index<array.size_;++index){
                this->set_element(index,array[index]);
            }
        }
        return *this;
    }
    constexpr void clear()noexcept{
        while(!this->empty()){
            this->pop_back();
        }
    }
    constexpr ~_Array()noexcept{
        this->clear();
        ::free(this->data_);
    }
}; // class Array
} // namespace script
