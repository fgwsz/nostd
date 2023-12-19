#pragma once
template<typename _Type>
class Reference{
    _Type* data_;
public:
    inline constexpr Reference()noexcept{
        this->data_=nullptr;
    }
    inline explicit constexpr Reference(_Type& lval_ref)noexcept{
        this->data_=&lval_ref;
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
    inline constexpr Reference& operator=(Reference<_Type> const& ref)noexcept{
        if(this!=&ref){
            if(this->empty()&&!ref.empty()){
                this->data_=ref.data_;
            }else if(!this->empty()&&ref.empty()){
                this->reset();
            }else if(
                reinterpret_cast<char*>(this->data_)
                !=reinterpret_cast<char*>(ref.data_)
            ){
                this->get()=ref.get();
            }
        }
        return *this;
    }
};