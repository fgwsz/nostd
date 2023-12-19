#pragma once
#include"nostd_type_name.hpp"
template<typename _Type>
struct TypeHelper{};
class Type{
    ::std::string_view name_;
public:
    Type(){
        this->name_=::nostd::type_name<void>();
    }
    template<typename _Type>
    inline constexpr Type(TypeHelper<_Type>)noexcept{
        this->name_=::nostd::type_name<_Type>();
    }
    inline constexpr ::std::string_view name() const noexcept{
        return this->name_;
    }
};
template<typename _Type>
inline constexpr auto make_type()noexcept{
    return Type(TypeHelper<_Type>());
}