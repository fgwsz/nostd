#pragma once
#include<memory>
#include<stdexcept>
#include<type_traits>
template<typename _Type>
class Reference{
    _Type* data_;
public:
    inline constexpr Reference()noexcept{
        this->data_=nullptr;
    }
    inline explicit constexpr Reference(_Type& lval_ref)noexcept{
        this->data_=::std::addressof(lval_ref);
    }
    inline constexpr bool empty()const noexcept{
        return this->data_==nullptr;
    }
    inline constexpr Reference(Reference<_Type> const& ref)noexcept{
        this->data_=ref.data_;
    }
    using reference_type=_Type&;
    inline constexpr operator reference_type()const noexcept{
        return *(this->data_);
    }
    inline constexpr _Type& get()const noexcept{
        return *(this->data_);
    }
    inline constexpr void reset()noexcept{
        this->data_=nullptr;
    }
    inline constexpr ~Reference()noexcept{
        this->reset();
    }
    inline constexpr Reference& operator=(Reference<_Type> const& ref){
        if(this!=&ref){
            if(!this->data_&&!ref.data_){ // 11
                if constexpr(::std::is_const_v<_Type>){
                    throw ::std::runtime_error("Reference Assign Error:Const Ref Can't Be Assign");
                }else{
                    if(this->data_!=ref.data_){
                        *(this->data_)=*(ref.data_);
                    }
                }
            }else{ // 00 10 01
                this->data_=ref.data_;
            }
        }
        return *this;
    }
};