#pragma once
#include<utility>
#include<array>
#include<stdexcept>
#include<functional>
#include<vector>
#include"object.hpp"
#include"nostd_function_traits.hpp"

template<typename _MetaFuncType,typename _Type>
struct MetaFuncPushFront;
template<typename _Type,template<typename...>class _MetaFunc,typename..._Args>
struct MetaFuncPushFront<_MetaFunc<_Args...>,_Type>{
    using type=_MetaFunc<_Type,_Args...>;
};
template<typename _MetaFuncType,typename _Type>
using meta_func_bind_front_t=typename MetaFuncPushFront<_MetaFuncType,_Type>::type;

template<typename _Result,typename _MetaFuncType>
struct MetaFuncTypeToUnMemberFunc;
template<typename _Result,template<typename...>class _MetaFunc,typename..._Args>
struct MetaFuncTypeToUnMemberFunc<_Result,_MetaFunc<_Args...>>{
    using type=_Result(_Args...);
};
template<typename _Result,typename _MetaFuncType>
using meta_func_type_to_unmember_func_t=typename MetaFuncTypeToUnMemberFunc<_Result,_MetaFuncType>::type;

template<typename _MemFunc,typename _Object=
    typename ::nostd::FunctionTraits<_MemFunc>::class_type&>
using member_func_to_unmember_func_t=
    meta_func_type_to_unmember_func_t<
        typename ::nostd::FunctionTraits<_MemFunc>::result_type,
        meta_func_bind_front_t<
            typename ::nostd::FunctionTraits<_MemFunc>::parameter_list,
            _Object
        >
    >;

class Function{
    void* func_ptr_;
    void* args_ptr_;
    size_t args_count_;
    Object(*invoker_)(void* func_ptr,void* args_ptr);
    void(*destory_)(void*& func_ptr,void*& args_ptr);
    void (*copy_)(
        void*& to_func_ptr,
        void*& to_args_ptr,
        void(*destory_fn)(void*&,void*&),
        void* from_func_ptr,
        void* from_args_ptr
    );
    Type type_;
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
        return Function::invoke_impl(
            ::std::forward<_FuncType>(func),
            args,
            ::std::make_index_sequence<
                sizeof(args)/sizeof(Object)
            >()
        );
    }
    template<typename _Func,typename _Args>
    inline static Object invoker_11(void* func_ptr,void* args_ptr){
        auto& func=*static_cast<_Func*>(func_ptr);
        auto& args=*static_cast<_Args*>(args_ptr);
        return ::make_object(Function::invoke(func,args));
    }
    template<typename _Func,typename _Args>
    inline static Object invoker_10(void* func_ptr,void* args_ptr){
        auto& func=*static_cast<_Func*>(func_ptr);
        auto& args=*static_cast<_Args*>(args_ptr);
        Function::invoke(func,args);
        return {};
    }
    template<typename _Func,typename _Args>
    inline static Object invoker_01(void* func_ptr,void* args_ptr){
        auto& func=*static_cast<_Func*>(func_ptr);
        return ::make_object(func());
    }
    template<typename _Func,typename _Args>
    inline static Object invoker_00(void* func_ptr,void* args_ptr){
        auto& func=*static_cast<_Func*>(func_ptr);
        func();
        return {};
    }
    template<typename _Func,typename _Args>
    inline static void destory(void*& func_ptr,void*& args_ptr){
        if(func_ptr){
            delete static_cast<_Func*>(func_ptr);
            func_ptr=nullptr;
        }
        if(args_ptr){
            delete static_cast<_Args*>(args_ptr);
            args_ptr=nullptr;
        }
    };
    template<typename _Func,typename _Args>
    inline static void copy(
        void*& to_func_ptr,
        void*& to_args_ptr,
        void(*destory_fn)(void*&,void*&),
        void* from_func_ptr,
        void* from_args_ptr
    ){
        if(to_func_ptr&&to_args_ptr&&destory_fn){
            destory_fn(to_func_ptr,to_args_ptr);
        }
        if(from_func_ptr){
            to_func_ptr=new(::std::nothrow)_Func(*static_cast<_Func*>(from_func_ptr));
        }
        if(from_args_ptr){
            to_args_ptr=new(::std::nothrow)_Args;
        }
    }
public:
    inline Function()noexcept
        :func_ptr_(nullptr)
        ,args_ptr_(nullptr)
        ,args_count_(0)
        ,invoker_(nullptr)
        ,destory_(nullptr)
        ,copy_(nullptr)
        ,type_(::make_type<void(*)(void)>())
    {}
    template<typename _FuncType,::std::enable_if_t<
        !::std::is_same_v<::std::remove_cvref_t<_FuncType>,Function>&& // 优先匹配拷贝构造
        (
            ::nostd::FunctionTraits<_FuncType>::is_functor::value||
            ::nostd::FunctionTraits<_FuncType>::is_unmember_function::value||
            ::nostd::FunctionTraits<_FuncType>::is_unmember_function_pointer::value
        )&&
        !::nostd::FunctionTraits<_FuncType>::has_c_style_va_list::value // 不支持C可变参数
    ,int>_=0>
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
            this->invoker_=this->invoker_11<func_t,args_t>;
        }else if constexpr(args_count!=0&&result_is_void){
            this->args_ptr_=new(::std::nothrow)args_t;
            this->invoker_=this->invoker_10<func_t,args_t>;
        }else if constexpr(args_count==0&&!result_is_void){
            this->invoker_=this->invoker_01<func_t,args_t>;
        }else{
            this->invoker_=this->invoker_00<func_t,args_t>;
        }
        this->args_count_=args_count;
        this->destory_=this->destory<func_t,args_t>;
        this->copy_=this->copy<func_t,args_t>;
        this->type_=::make_type<
            typename ::nostd::FunctionTraits<_FuncType>::function_base_type*
        >();
    }
    template<typename _MemFuncType,::std::enable_if_t<
        !::std::is_same_v<::std::remove_cvref_t<_MemFuncType>,Function>&& // 优先匹配拷贝构造
        ::nostd::FunctionTraits<_MemFuncType>::is_member_function_pointer::value&&
        !::nostd::FunctionTraits<_MemFuncType>::has_c_style_va_list::value // 不支持C可变参数
    ,int>_=0>
    inline Function(_MemFuncType&& _member_function)noexcept
        :Function(
            ::std::function<
                member_func_to_unmember_func_t<
                    decltype(_member_function)
                >
            >(::std::mem_fn(::std::forward<_MemFuncType>(_member_function)))
        )
    {}
    inline bool empty()const noexcept{
        return this->func_ptr_==nullptr;
    }
    inline void reset()noexcept{
        if(!this->empty()){
            this->destory_(this->func_ptr_,this->args_ptr_);
            this->args_count_=0;
            this->invoker_=nullptr;
            this->destory_=nullptr;
            this->copy_=nullptr;
            this->type_=::make_type<void(*)(void)>();
        }
    }
    inline ~Function()noexcept{
        this->reset();
    }
    inline Object invoke_by_objects()const{
        if(this->empty()){
            return {};
        }
        if(0!=this->args_count_){
            throw ::std::runtime_error("Function::operator() Error:Args Count Not Equal");
        }else{
            return this->invoker_(this->func_ptr_,this->args_ptr_);
        }
    }
    inline Object invoke_by_objects(::std::vector<Object>const& objects)const{
        if(this->empty()){
            return {};
        }
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
    inline Object operator()()const{
        return this->invoke_by_objects();
    }
    template<typename..._ArgTypes,
        ::std::enable_if_t<sizeof...(_ArgTypes)!=0,int>_=0>
    inline Object operator()(_ArgTypes&&...args)const{
        return this->invoke_by_objects({make_object(::std::forward<_ArgTypes>(args))...});
    }
    template<typename..._ArgTypes>
    inline Object invoke_by_args(_ArgTypes&&...args)const{
        return (*this)(::std::forward<_ArgTypes>(args)...);
    }
    inline explicit operator bool()const noexcept{
        return this->empty();
    }
    inline Function(Function const& func)noexcept
        :Function(){
        (*this)=func;
    }
    inline Function& operator=(Function const& func)noexcept{
        if(this!=&func){
            if(!func.empty()){
                func.copy_(
                    this->func_ptr_,
                    this->args_ptr_,
                    this->destory_,
                    func.func_ptr_,
                    func.args_ptr_
                );
                this->args_count_=func.args_count_;
                this->invoker_=func.invoker_;
                this->destory_=func.destory_;
                this->copy_=func.copy_;
                this->type_=func.type_;
            }else{
                this->reset();
            }
        }
        return *this;
    }
    inline Type const& type()const noexcept{
        return this->type_;
    }
};