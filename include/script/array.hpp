#pragma once
extern "C"{
#include<stddef.h>
#include<stdlib.h>
#include<string.h>
} // extern "C"
#include<initializer_list>
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
    constexpr void auto_expand_capacity()noexcept{
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
    template<typename OutputStream>
    friend constexpr OutputStream& operator<<(OutputStream& os,_Array<_Type>const& array)noexcept{
        os<<'[';
        for(size_t index=0;index<array.size();++index){
            os<<array[index]<<(index+1!=array.size()?",":"");
        }
        return os<<']';
    }
    template<typename OutputStream>
    constexpr OutputStream& debug_print(OutputStream& os)const noexcept{
        os<<"+++++ARRAY BEGIN+++++\n"
          <<"data_:"<<this->data_<<'\n'
          <<"size_:"<<this->size_<<'\n'
          <<"capacity_:"<<this->capacity_<<'\n'
          <<"elemnts:\n";
        for(size_t index=0;index<this->size_;++index){
            os<<"-----ELEMENT "<<index<<" BEGIN-----\n"
              <<"pointer_:"<<(this->data_[index]).pointer_<<'\n'
              <<"value:"<<*((this->data_[index]).pointer_)<<'\n'
              <<"-----ELEMENT "<<index<<" END-----\n";
        }
        return os<<"+++++ARRAY END+++++\n";
    }
    constexpr bool operator==(_Array<_Type> const& array)const noexcept{
        if(this==&array){
            return true;
        }
        if(this->size_!=array.size_){
            return false;
        }
        for(size_t index=0;index<array.size_;++index){
            if((*this)[index]!=array[index]){
                return false;
            }
        }
        return true;
    }
    constexpr bool operator!=(_Array<_Type> const& array)const noexcept{
        return !((*this)==array);
    }
    constexpr _Array<_Type>(::std::initializer_list<_Type> const& list)noexcept
        :_Array<_Type>(){
        (*this)=list;
    }
    constexpr _Array<_Type>& operator=(::std::initializer_list<_Type> const& list)noexcept{
        while(this->size_>list.size()){
            this->pop_back();
        }
        for(size_t index=0;index<list.size();++index){
            this->set_element(index,*(list.begin()+index));
        }
        return *this;
    }
    template<size_t _size>
    constexpr _Array<_Type>(_Type const(&array)[_size])noexcept
        :_Array<_Type>(){
        (*this)=array;
    }
    template<size_t _size>
    constexpr _Array<_Type>& operator=(_Type const(&array)[_size])noexcept{
        while(this->size_>_size){
            this->pop_back();
        }
        for(size_t index=0;index<_size;++index){
            this->set_element(index,array[index]);
        }
        return *this;
    }
    constexpr void reserve_capacity(size_t capacity)noexcept{
        if(capacity>this->capacity_){
            _Element<_Type>* new_data=(_Element<_Type>*)::malloc(sizeof(_Element<_Type>)*capacity);
            ::memmove(new_data,this->data_,this->size_*sizeof(_Element<_Type>));
            ::free(this->data_);
            this->data_=new_data;
            this->capacity_=capacity;
        }
    }
    constexpr void shrink_to_fit()noexcept{
        if(this->capacity_>this->size_){
            _Element<_Type>* new_data=(_Element<_Type>*)::malloc(sizeof(_Element<_Type>)*this->size_);
            ::memmove(new_data,this->data_,this->size_*sizeof(_Element<_Type>));
            ::free(this->data_);
            this->data_=new_data;
            this->capacity_=this->size_;
        }
    }
    constexpr size_t max_size()const noexcept{
        return ((size_t)-1);
    }
    constexpr void swap(_Array<_Type>& array)noexcept{
        if(this!=&array){
            _Element<_Type>* temp_data=this->data_;
            size_t temp_size=this->size_;
            size_t temp_capacity=this->capacity_;
            this->data_=array.data_;
            this->size_=array.size_;
            this->capacity_=array.capacity_;
            array.data_=temp_data;
            array.size_=temp_size;
            array.capacity_=temp_capacity;
        }
    }
    constexpr bool insert_element_n(size_t index,_Type const& value,size_t count)noexcept{
        if(index>this->size_){
            return false;
        }
        this->reserve_capacity(this->size_+count);
        ::memmove(this->data_+index+count,this->data_+index,(this->size_-index)*sizeof(_Element<_Type>));
        for(size_t n=0;n<count;++n){
            (this->data_[index+n]).pointer_=(_Type*)::malloc(sizeof(_Type));
            new((this->data_[index+n]).pointer_)_Type(value);
        }
        this->size_+=count;
        return true;
    }
    constexpr bool erase_element_n(size_t index,size_t count)noexcept{
        if(index>=this->size_){
            return false;
        }
        size_t real_count=count>(this->size_-index)?(this->size_-index):count;
        for(size_t n=0;n<count;++n){
            ((this->data_[index+n]).pointer_)->~_Type();
            ::free((this->data_[index+n]).pointer_);
        }
        ::memmove(this->data_+index,this->data_+index+real_count,(this->size_-index-real_count)*sizeof(_Element<_Type>));
        this->size_-=real_count;
        return true;
    }
    constexpr bool insert_array(size_t index,_Array<_Type> const& array)noexcept{
        if(index>this->size_){
            return false;
        }
        this->reserve_capacity(this->size_+array.size_);
        if(this!=&array){
            ::memmove(this->data_+index+array.size_,this->data_+index,(this->size_-index)*sizeof(_Element<_Type>));
            for(size_t n=0;n<array.size_;++n){
                (this->data_[index+n]).pointer_=(_Type*)::malloc(sizeof(_Type));
                new((this->data_[index+n]).pointer_)_Type(array[n]);
            }
        }else{
            _Array<_Type>array_value=array;
            ::memmove(this->data_+index+array_value.size_,this->data_+index,(this->size_-index)*sizeof(_Element<_Type>));
            for(size_t n=0;n<array_value.size_;++n){
                (this->data_[index+n]).pointer_=(_Type*)::malloc(sizeof(_Type));
                new((this->data_[index+n]).pointer_)_Type(array_value[n]);
            }
        }
        this->size_+=array.size_;
        return true;
    }
    constexpr _Array<_Type>& operator+=(_Array<_Type> const& array)noexcept{
        this->insert_array(this->size_,array);
        return *this;
    }
    constexpr _Array<_Type> operator+(_Array<_Type> const& array)const noexcept{
        _Array<_Type> ret(*this);
        return ret+=array;
    }
}; // class Array
} // namespace script
