#pragma once
#include<utility>
#include<array>
#include<stdexcept>
#include<functional>
#include"object.hpp"
#include"nostd_function_traits.hpp"
class Function{
    size_t args_count_;
    void* args_ptr_;
    ::std::function<Object()> func_;
    ::std::function<void(void*)> args_destory_;
public:
    template<typename _FuncType>
    requires requires{
        ::nostd::FunctionTraits<_FuncType>::is_functor::value&&
        ::nostd::FunctionTraits<_FuncType>::is_unmember_function::value&&
        ::nostd::FunctionTraits<_FuncType>::is_unmember_function_pointer::value&&// 成员函数的情况呢？
        !::nostd::FunctionTraits<_FuncType>::has_c_style_va_list&&// 包含C可变参数的情况呢？
        ::nostd::FunctionTraits<_FuncType>::parameter_list::size!=0;// 参数为0的情况呢？
    }
    inline Function(_FuncType&& func)noexcept{
        constexpr size_t args_count=
            ::nostd::FunctionTraits<_FuncType>::parameter_list::size;
        this->args_count_=args_count;
        using args_array_t=::std::array<Object,args_count>;
        this->args_ptr_=new(::std::nothrow_t)args_array_t;
        this->func_=[&](){
            auto& args=*static_cast<args_array_t*>(this->args_ptr_);
            return make_object(func(/*TODO*/));// 有没有返回值/以及返回值是不是右值
        };
        this->args_destory_=[&](void* args_ptr){
            auto ptr=static_cast<args_array_t*>(args_ptr);
            delete(::std::nothrow_t)ptr;
        };
    }
    inline ~Function()noexcept{
        this->args_destory_(this->args_ptr_);
    }
    template<typename..._ArgTypes>
    inline Object operator()(_ArgTypes&&...args)const{
        if(sizeof...(args)!=this->args_count_){
            throw ::std::runtime_error("Function::operator() Error:Args Count Not Equal");
        }else{
            using args_array_t=::std::array<Object,sizeof...(args)>;
            auto& args=*static_cast<args_array_t*>(this->args_ptr_);
            args={make_object(::std::forward<_ArgType>(args))...};
            return this->func_();
        }
    }
};