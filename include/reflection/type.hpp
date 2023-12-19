#pragma once
#include<typeinfo>
#include"nostd_type_name.hpp"
template<typename _Type>
struct TypeHelper{};
class Type{
    ::std::string_view name_;
    ::std::type_info const* info_;
public:
    template<typename _Type>
    inline constexpr Type(TypeHelper<_Type>)noexcept{
        this->name_=::nostd::type_name<_Type>();
        this->info_=&typeid(_Type);
    }
    inline constexpr Type()noexcept
        :Type(TypeHelper<void>())
    {}
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
};
template<typename _Type>
inline constexpr Type make_type()noexcept{
    return Type(TypeHelper<_Type>());
}