#pragma once
#include<cstddef>
#include<typeinfo>
#include"nostd_type_name.hpp"
template<typename _Type>
struct TypeHelper{};
class Type{
    ::std::string_view name_;
    ::std::type_info const* info_;
    size_t byte_size_;
public:
    template<typename _Type>
    inline constexpr Type(TypeHelper<_Type>)noexcept{
        this->name_=::nostd::type_name<_Type>();
        this->info_=&typeid(_Type);
        this->byte_size_=sizeof(_Type);
    }
    inline constexpr Type()noexcept{
        this->name_=::nostd::type_name<void>();
        this->info_=&typeid(void);
        this->byte_size_=0; // sizeof(void) is UB
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