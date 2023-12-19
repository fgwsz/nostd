#pragma once
#include<cstddef>
#include<new>
#include<utility>
#include<type_traits>
#include<stdexcept>
#include"type.hpp"
// 构造时可选任何类型的值类型（不包括C风格数组）进行存储
// 运行时底层存储类型可变的弱类型
class Value{
    static constexpr size_t small_data_max_size=sizeof(void*);
    union Data{
        void* big_data_ptr_;
        char small_data_[small_data_max_size];
    };
    Data data_;
    Type type_;
    void (*copy_ctor_func_)(void*,void const*);
    void (*dtor_func_)(void*);
    bool is_small_;
    bool is_empty_;
    template<typename _ValueType>
    static inline constexpr bool is_small()noexcept{
        return sizeof(_ValueType)<=Value::small_data_max_size;
    }
    template<typename _ValueType>
    static inline void copy_ctor_func(void* to,void const* from)noexcept{
        new (to)_ValueType(*reinterpret_cast<_ValueType const*>(from));
    }
    template<typename _ValueType>
    static inline void dtor_func(void* ptr)noexcept{
        reinterpret_cast<_ValueType*>(ptr)->~_ValueType();
    }
    inline void* malloc_func(size_t size)noexcept{
        return ::operator new(size,::std::nothrow);
    }
    inline void free_func(void* ptr)noexcept{
        ::operator delete(ptr,::std::nothrow);
    }
public:
    inline constexpr Value()noexcept
        :data_()
        ,type_()
        ,copy_ctor_func_(nullptr)
        ,dtor_func_(nullptr)
        ,is_small_(true)
        ,is_empty_(true)
    {}
    template<typename _Type>
    inline explicit Value(_Type const& value)noexcept
        :Value(){
        using value_type=::std::decay_t<::std::remove_cvref_t<_Type>>;
        this->copy_ctor_func_=&(this->copy_ctor_func<value_type>);
        this->dtor_func_=&(this->dtor_func<value_type>);
        this->type_=make_type<value_type>();
        if(this->is_small<value_type>()){
            this->copy_ctor_func_(this->data_.small_data_,&value);
            this->is_small_=true;
        }else{
            this->data_.big_data_ptr_=this->malloc_func(this->type_.byte_size());
            this->copy_ctor_func_(this->data_.big_data_ptr_,&value);
            this->is_small_=false;
        }
        this->is_empty_=false;
    }
    inline constexpr bool empty()const noexcept{
        return this->is_empty_;
    }
    inline void reset()noexcept{
        if(!this->is_empty_){
            if(this->is_small_){
                this->dtor_func_(this->data_.small_data_);
            }else{
                this->dtor_func_(this->data_.big_data_ptr_);
                this->free_func(this->data_.big_data_ptr_);
                this->data_.big_data_ptr_=nullptr;
            }
            this->type_=Type();
            this->copy_ctor_func_=nullptr;
            this->dtor_func_=nullptr;
            this->is_small_=true;
            this->is_empty_=true;
        }
    }
    inline ~Value()noexcept{
        this->reset();
    }
    inline Value(Value const& value)noexcept
        :Value(){
        (*this)=value;
    }
    inline Value& operator=(Value const& value)noexcept{
        if(this!=&value){
            this->reset();
            if(value.is_small_){
                value.copy_ctor_func_(this->data_.small_data_,value.data_.small_data_);
            }else{
                this->data_.big_data_ptr_=this->malloc_func(value.type_.byte_size());
                value.copy_ctor_func_(this->data_.big_data_ptr_,value.data_.big_data_ptr_);
            }
            this->type_=value.type_;
            this->copy_ctor_func_=value.copy_ctor_func_;
            this->dtor_func_=value.dtor_func_;
            this->is_small_=value.is_small_;
            this->is_empty_=value.is_empty_;
        }
        return *this;
    }
    inline constexpr Type const& type()const noexcept{
        return this->type_;
    }
    template<typename _Type>
    inline operator _Type()const{
        using value_type=::std::decay_t<::std::remove_cvref_t<_Type>>;
        static_assert(
            !::std::is_void_v<_Type>&&
            ::std::is_convertible_v<value_type&,_Type>
        );
        if(this->empty()){
            throw ::std::runtime_error("Value Cast Error:Value Is Empyt"); 
        }
        else if(make_type<value_type>()!=this->type_){
            throw ::std::runtime_error("Value Cast Error:Type Not Equal");
        }else{
            if(this->is_small_){
                return *reinterpret_cast<value_type*>(
                    const_cast<char*>(this->data_.small_data_)
                );
            }else{
                return *reinterpret_cast<value_type*>(this->data_.big_data_ptr_);
            }
        }
    }
    template<typename _Type>
    inline _Type get()const{
        return this->operator _Type();
    }
};