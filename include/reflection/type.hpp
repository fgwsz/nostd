#pragma once
#include<cstddef>
#include<typeinfo>
#include<type_traits>
#include"nostd_type_name.hpp"
template<typename _Type>
struct TypeHelper{};
class Type{
    ::std::string_view name_;
    ::std::type_info const* info_;
    size_t byte_size_;
public:
    inline constexpr Type()noexcept{
        this->name_=::nostd::type_name<void>();
        this->info_=&typeid(void);
        this->byte_size_=0; // sizeof(void) is UB,这里暂定sizeof(void)=0
    }
    template<typename _Type>
    inline constexpr Type(TypeHelper<_Type>)noexcept
        :Type(){
        if constexpr(!::std::is_void_v<_Type>){
            this->name_=::nostd::type_name<_Type>();
            this->info_=&typeid(_Type);
            this->byte_size_=sizeof(::std::conditional_t<
                ::std::is_function_v<_Type>,
                ::std::decay_t<_Type>,
                _Type
            >); // 对函数类型取sizeof,msvc会编译报错,退化成函数指针类型就可以编译通过了
        }
    }
    inline constexpr ::std::string_view const& name()const noexcept{
        return this->name_;
    }
    inline constexpr ::std::type_info const& info()const noexcept{
        return *(this->info_);
    }
    inline constexpr bool operator==(Type const& type)const noexcept{
        return (this->name_==type.name_)&&(this->info_==type.info_);
    }
    inline constexpr bool operator!=(Type const& type)const noexcept{
        return !((*this)==type);
    }
    inline constexpr size_t byte_size()const noexcept{
        return this->byte_size_;
    }
};
template<typename _Type>
inline constexpr Type make_type()noexcept{
    return Type(TypeHelper<_Type>());
}