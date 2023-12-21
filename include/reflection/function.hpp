#pragma once
#include<utility>
#include<vector>
#include<functional>
#include"object.hpp"
#include"nostd_function_traits.hpp"
class Function{
    ::std::function<Object(::std::vector<Object> const&)> data_;
public:
    template<typename _FuncType>
    requires requires{
        ::nostd::FunctionTraits<_FuncType>::is_functor::value&&
        ::nostd::FunctionTraits<_FuncType>::is_unmember_function::value&&
        ::nostd::FunctionTraits<_FuncType>::is_unmember_function_pointer::value;
    }
    inline constexpr Function(_FuncType&& func)noexcept{
        auto invoker=[&]<typename..._ArgTypes>(_ArgTypes&&...args){
            decltype(auto) ret=::std::forward<_FuncType>(func)(::std::forward<_ArgTypes>(arg)...);
            return Object(OBJECT_CTOR_ARG(ret));
        };
    }
    template<typename..._ArgTypes>
    inline Object operator()(_ArgTypes&&...args)const{
        return {};
    }
};