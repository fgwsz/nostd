#pragma once
namespace script{
class Boolean final{
public:
    using data_type=bool;
private:
    data_type data_;
public:
    constexpr Boolean()noexcept{
        this->data_=false;
    }
    constexpr Boolean(bool value)noexcept
        :Boolean(){
        (*this)=value;
    }
    constexpr Boolean(Boolean const& boolean)noexcept
        :Boolean(){
        (*this)=boolean;
    }
    constexpr Boolean& operator=(bool value)noexcept{
        this->data_=static_cast<typename Boolean::data_type>(value);
        return *this;
    }
    constexpr Boolean& operator=(Boolean const& boolean)noexcept{
        return (*this)=boolean.data_;
    }
    constexpr typename Boolean::data_type& data()noexcept{
        return this->data_;
    }
    constexpr typename Boolean::data_type const& const_data()const noexcept{
        return this->data_;
    }
    explicit constexpr operator bool()const noexcept{
        return static_cast<bool>(this->data_);
    }
    constexpr bool to_bool()const noexcept{
        return static_cast<bool>(*this);
    }
    constexpr Boolean operator==(Boolean const& boolean)const noexcept{
        return this->data_==boolean.data_;
    }
    constexpr Boolean operator!=(Boolean const& boolean)const noexcept{
        return this->data_!=boolean.data_;
    }
    constexpr Boolean operator&&(Boolean const& boolean)const noexcept{
        return this->data_&&boolean.data_;
    }
    constexpr Boolean operator||(Boolean const& boolean)const noexcept{
        return this->data_||boolean.data_;
    }
    constexpr Boolean operator!()const noexcept{
        return !(this->data_);
    }
    template<typename OutputStream>
    friend constexpr OutputStream& operator<<(OutputStream& os,Boolean const& boolean) noexcept{
        return os<<(boolean.const_data()
            ?"True"
            :"False");
    }
}; // class Boolean
constexpr Boolean const True (true );
constexpr Boolean const False(false);
} // namespace script
