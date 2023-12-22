#pragma once
#include<utility>
#include<array>
#include<stdexcept>
#include<functional>
#include"object.hpp"
#include"nostd_function_traits.hpp"
template<typename _StdArrayType>
struct ArraySize;
template<typename _Type,size_t _size>
struct ArraySize<::std::array<_Type,_size>>{
    static constexpr size_t value=_size;
};
template<typename _StdArrayType>
static constexpr size_t array_size_v=ArraySize<_StdArrayType>::value;
template<typename _FuncType,size_t _argc,size_t...index>
inline static decltype(auto) invoke_impl(
    _FuncType&& func,
    ::std::array<Object,_argc>const&args,
    ::std::index_sequence<index...>
){
    return ::std::forward<_FuncType>(func)(args[index]...);
}
template<typename _FuncType,size_t _argc>
inline static decltype(auto) invoke(
    _FuncType&& func,
    ::std::array<Object,_argc>const&args
){
    return ::invoke_impl(
        ::std::forward<_FuncType>(func),
        args,
        ::std::make_index_sequence<
            array_size_v<::std::remove_cvref_t<decltype(args)>>
        >()
    );
}
class Function{
    size_t args_count_;
    void* args_ptr_;
    ::std::function<Object()> func_;
    ::std::function<void(void*)> args_destory_;
public:
    inline Function()noexcept
        :args_count_(0)
        ,args_ptr_(nullptr)
        ,func_(nullptr)
        ,args_destory_(nullptr)
    {}
    template<typename _FuncType>
    requires requires{
        (::nostd::FunctionTraits<_FuncType>::is_functor::value||
        ::nostd::FunctionTraits<_FuncType>::is_unmember_function::value||
        ::nostd::FunctionTraits<_FuncType>::is_unmember_function_pointer::value)&&// 成员函数的情况呢？
        !::nostd::FunctionTraits<_FuncType>::has_c_style_va_list::value;// 包含C可变参数的情况呢？
    }
    inline Function(_FuncType&& func)noexcept
        :Function(){
        constexpr size_t args_count=
            ::nostd::FunctionTraits<_FuncType>::parameter_list::size;
        constexpr bool result_is_void=
            ::std::is_void_v<typename ::nostd::FunctionTraits<_FuncType>::result_type>;
        using args_array_t=::std::array<Object,args_count>;
        if constexpr(args_count!=0&&!result_is_void){
            this->args_ptr_=new(::std::nothrow)args_array_t;
            this->func_=[&](){
                auto& args=*static_cast<args_array_t*>(this->args_ptr_);
                return make_object(invoke(::std::forward<_FuncType>(func),args));
            };
        }else if constexpr(args_count!=0&&result_is_void){
            this->args_ptr_=new(::std::nothrow)args_array_t;
            this->func_=[&](){
                auto& args=*static_cast<args_array_t*>(this->args_ptr_);
                ::invoke(::std::forward<_FuncType>(func),args);
                return make_object();
            };
        }else if constexpr(args_count==0&&!result_is_void){
            this->func_=[&](){
                return make_object(::std::forward<_FuncType>(func)());
            };
        }else{
            this->func_=[&](){
                ::std::forward<_FuncType>(func)();
                return make_object();
            };
        }
        this->args_count_=args_count;
        this->args_destory_=[&](void* args_ptr){
            if(args_ptr){
                delete static_cast<args_array_t*>(args_ptr);
            }
        };
    }
    inline ~Function()noexcept{
        this->args_destory_(this->args_ptr_);
        this->args_ptr_=nullptr;
    }
    template<size_t _size>
    inline Object operator()(::std::array<Object,_size>const& args)const{
        if(args.size()!=this->args_count_){
            throw ::std::runtime_error("Function::operator() Error:Args Count Not Equal");
        }else{
            using args_array_t=::std::array<Object,_size>;
            auto& args_=*static_cast<args_array_t*>(this->args_ptr_);
            args_=args;
            return this->func_();
        }
    }
    inline Object operator()()const{
        if(this->args_count_!=0){
            throw ::std::runtime_error("Function::operator() Error:Args Count Not Equal");
        }else{
            return this->func_();
        }
    }
};