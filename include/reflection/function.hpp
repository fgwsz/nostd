#pragma once
#include<utility>
#include<array>
#include<stdexcept>
#include<functional>
#include<vector>
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
    void* func_ptr_;
    void* args_ptr_;
    size_t args_count_;
    ::std::function<Object(void* func_ptr,void* args_ptr)> invoker_;
    ::std::function<void(void*& func_ptr,void*& args_ptr)> destory_;
public:
    inline Function()noexcept
        :func_ptr_(nullptr)
        ,args_ptr_(nullptr)
        ,args_count_(0)
        ,invoker_(nullptr)
        ,destory_(nullptr)
    {}
    template<typename _FuncType>
    requires requires{
        (::nostd::FunctionTraits<_FuncType>::is_functor::value||
        ::nostd::FunctionTraits<_FuncType>::is_unmember_function::value||
        ::nostd::FunctionTraits<_FuncType>::is_unmember_function_pointer::value)&&// 成员函数的情况呢？
        !::nostd::FunctionTraits<_FuncType>::has_c_style_va_list::value;// 包含C可变参数的情况呢？
    }
    inline Function(_FuncType&& _function)noexcept
        :Function(){
        using func_t=::std::function<
            typename ::nostd::FunctionTraits<_FuncType>::function_base_type
        >;
        constexpr size_t args_count=
            ::nostd::FunctionTraits<_FuncType>::parameter_list::size;
        using args_t=::std::array<Object,args_count>;
        constexpr bool result_is_void=
            ::std::is_void_v<typename ::nostd::FunctionTraits<_FuncType>::result_type>;

        this->func_ptr_=new(::std::nothrow)func_t(::std::forward<_FuncType>(_function));

        if constexpr(args_count!=0&&!result_is_void){
            this->args_ptr_=new(::std::nothrow)args_t;
            this->invoker_=[](void* func_ptr,void* args_ptr){
                auto& func=*static_cast<func_t*>(func_ptr);
                auto& args=*static_cast<args_t*>(args_ptr);
                return make_object(invoke(func,args));
            };
        }else if constexpr(args_count!=0&&result_is_void){
            this->args_ptr_=new(::std::nothrow)args_t;
            this->invoker_=[](void* func_ptr,void* args_ptr){
                auto& func=*static_cast<func_t*>(func_ptr);
                auto& args=*static_cast<args_t*>(args_ptr);
                invoke(func,args);
                return make_object();
            };
        }else if constexpr(args_count==0&&!result_is_void){
            this->invoker_=[](void* func_ptr,void* args_ptr){
                auto& func=*static_cast<func_t*>(func_ptr);
                return make_object(func());
            };
        }else{
            this->invoker_=[](void* func_ptr,void* args_ptr){
                auto& func=*static_cast<func_t*>(func_ptr);
                func();
                return make_object();
            };
        }
        this->args_count_=args_count;
        this->destory_=[](void*& func_ptr,void*& args_ptr){
            if(func_ptr){
                delete static_cast<func_t*>(func_ptr);
                func_ptr=nullptr;
            }
            if(args_ptr){
                delete static_cast<args_t*>(args_ptr);
                args_ptr=nullptr;
            }
        };
    }
    inline ~Function()noexcept{
        if(this->destory_){
            this->destory_(this->func_ptr_,this->args_ptr_);
        }
    }
    inline Object invoke_by_objects(::std::vector<Object>const& objects)const{
        if(objects.size()!=this->args_count_){
            throw ::std::runtime_error("Function::operator() Error:Args Count Not Equal");
        }else if(this->args_count_!=0){
            auto* args=static_cast<Object*>(this->args_ptr_);
            for(size_t index=0;index<this->args_count_;++index){
                args[index]=objects[index];
            }
        }
        return this->invoker_(this->func_ptr_,this->args_ptr_);
    }
    template<typename..._ArgTypes>
    inline Object operator()(_ArgTypes&&...args)const{
        return this->invoke_by_objects({make_object(::std::forward<_ArgTypes>(args))...});
    }
    template<typename..._ArgTypes>
    inline Object invoke_by_args(_ArgTypes&&...args)const{
        return (*this)(::std::forward<_ArgTypes>(args)...);
    }
    //inline Function(Function const& func)noexcept
    //    :Function(){
    //    (*this)=func;
    //}
    //inline Function operator=(Function const& func)noexcept{
    //}
};