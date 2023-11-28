#pragma once
extern "C"{
#include<limits.h>
#include<float.h>
#include<math.h>
} // extern "C"
namespace script{
class Number final{
public:
    using data_type=double;
private:
    data_type data_;
public:
    constexpr Number()noexcept{
        this->data_=0;
    }
    constexpr Number(signed short int value)noexcept
        :Number(){
        *this=value;
    }
    constexpr Number(unsigned short int value)noexcept
        :Number(){
        *this=value;
    }
    constexpr Number(signed int value)noexcept
        :Number(){
        *this=value;
    }
    constexpr Number(unsigned int value)noexcept
        :Number(){
        *this=value;
    }
    constexpr Number(signed long int value)noexcept
        :Number(){
        *this=value;
    }
    constexpr Number(unsigned long int value)noexcept
        :Number(){
        *this=value;
    }
    constexpr Number(signed long long int value)noexcept
        :Number(){
        *this=value;
    }
    constexpr Number(unsigned long long int value)noexcept
        :Number(){
        *this=value;
    }
    constexpr Number(float value)noexcept
        :Number(){
        *this=value;
    }
    constexpr Number(double value)noexcept
        :Number(){
        *this=value;
    }
    constexpr Number(Number const& number)noexcept
        :Number(){
        *this=number;
    }
    constexpr Number& operator=(signed short int value)noexcept{
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    constexpr Number& operator=(unsigned short int value)noexcept{
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    constexpr Number& operator=(signed int value)noexcept{
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    constexpr Number& operator=(unsigned int value)noexcept{
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    constexpr Number& operator=(signed long int value)noexcept{
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    constexpr Number& operator=(unsigned long int value)noexcept{
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    constexpr Number& operator=(signed long long int value)noexcept{
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    constexpr Number& operator=(unsigned long long int value)noexcept{
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    constexpr Number& operator=(float value)noexcept{
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    constexpr Number& operator=(double value)noexcept{
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    constexpr Number& operator=(Number const& number)noexcept{
        *this=number.data_;
        return *this;
    }
    explicit constexpr operator signed short int()const noexcept{
        return static_cast<signed short int>(this->data_);
    }
    explicit constexpr operator unsigned short int()const noexcept{
        return static_cast<unsigned short int>(this->data_);
    }
    explicit constexpr operator signed int()const noexcept{
        return static_cast<signed int>(this->data_);
    }
    explicit constexpr operator unsigned int()const noexcept{
        return static_cast<unsigned int>(this->data_);
    }
    explicit constexpr operator signed long int()const noexcept{
        return static_cast<signed long int>(this->data_);
    }
    explicit constexpr operator unsigned long int()const noexcept{
        return static_cast<unsigned long int>(this->data_);
    }
    explicit constexpr operator signed long long int()const noexcept{
        return static_cast<signed long long int>(this->data_);
    }
    explicit constexpr operator unsigned long long int()const noexcept{
        return static_cast<unsigned long long int>(this->data_);
    }
    explicit constexpr operator float()const noexcept{
        return static_cast<float>(this->data_);
    }
    explicit constexpr operator double()const noexcept{
        return static_cast<double>(this->data_);
    }
    constexpr bool operator==(Number const& number)const noexcept{
        return this->data_==number.data_;
    }
    constexpr bool operator!=(Number const& number)const noexcept{
        return this->data_!=number.data_;
    }
    constexpr bool operator<(Number const& number)const noexcept{
        return this->data_<number.data_;
    }
    constexpr bool operator>(Number const& number)const noexcept{
        return this->data_>number.data_;
    }
    constexpr bool operator<=(Number const& number)const noexcept{
        return this->data_<=number.data_;
    }
    constexpr bool operator>=(Number const& number)const noexcept{
        return this->data_>=number.data_;
    }
    constexpr Number operator+(Number const& number)const noexcept{
        return this->data_+number.data_;
    }
    constexpr Number operator-(Number const& number)const noexcept{
        return this->data_-number.data_;
    }
    constexpr Number operator*(Number const& number)const noexcept{
        return this->data_*number.data_;
    }
    constexpr Number operator/(Number const& number)const noexcept{
        return this->data_/number.data_;
    }
    constexpr Number operator%(Number const& number)const noexcept{
        return ::fmod(this->data_,number.data_);
    }
    constexpr Number operator^(Number const& number)const noexcept{
        return ::pow(this->data_,number.data_);
    }
    constexpr Number operator+()const noexcept{
        return +(this->data_);
    }
    constexpr Number operator-()const noexcept{
        return -(this->data_);
    }
    constexpr Number& operator+=(Number const& number)noexcept{
        return (*this)=(*this)+number;
    }
    constexpr Number& operator-=(Number const& number)noexcept{
        return (*this)=(*this)-number;
    }
    constexpr Number& operator*=(Number const& number)noexcept{
        return (*this)=(*this)*number;
    }
    constexpr Number& operator/=(Number const& number)noexcept{
        return (*this)=(*this)/number;
    }
    constexpr Number& operator%=(Number const& number)noexcept{
        return (*this)=(*this)%number;
    }
    constexpr Number& operator^=(Number const& number)noexcept{
        return (*this)=(*this)^number;
    }
    constexpr Number& operator++()noexcept{
        return (*this)+=1;
    }
    constexpr Number& operator--()noexcept{
        return (*this)-=1;
    }
    constexpr Number operator++(int)noexcept{
        Number ret=*this;
        ++(*this);
        return ret;
    }
    constexpr Number operator--(int)noexcept{
        Number ret=*this;
        --(*this);
        return ret;
    }
    constexpr typename Number::data_type& data()noexcept{
        return this->data_;
    }
    constexpr typename Number::data_type const& const_data()const noexcept{
        return this->data_;
    }
    static constexpr Number min_value()noexcept{
        return DBL_MIN;
    }
    static constexpr Number max_value()noexcept{
        return DBL_MAX;
    }
    static constexpr Number floor(Number const& number){
        return ::floor(number.data_);
    }
    static constexpr Number ceil(Number const& number){
        return ::ceil(number.data_);
    }
    static constexpr Number integer(Number const& number){
        return number>=0
            ?Number::floor(number)
            :Number::ceil(number);
    }
    static constexpr Number min(Number const& number_1,Number const& number_2)noexcept{
        return ::fmin(number_1.const_data(),number_2.const_data());
    }
    static constexpr Number max(Number const& number_1,Number const& number_2)noexcept{
        return ::fmax(number_1.const_data(),number_2.const_data());
    }
    static constexpr Number abs(Number const& number)noexcept{
        return ::fabs(number.const_data());
    }
    static constexpr Number difference(Number const& number_1,Number const& number_2)noexcept{
        return Number::abs(number_1-number_2);
    }
    constexpr bool is_integer()const noexcept{
        return (*this)==Number::integer(*this);
    }
    constexpr bool is_signed_short_int()const noexcept{
        return this->is_integer()&&(*this)>=SHRT_MIN&&(*this)<=SHRT_MAX;
    }
    constexpr bool is_unsigned_short_int()const noexcept{
        return this->is_integer()&&(*this)>=0&&(*this)<=USHRT_MAX;
    }
    constexpr bool is_signed_int()const noexcept{
        return this->is_integer()&&(*this)>=INT_MIN&&(*this)<=INT_MAX;
    }
    constexpr bool is_unsigned_int()const noexcept{
        return this->is_integer()&&(*this)>=0&&(*this)<=UINT_MAX;
    }
    constexpr bool is_signed_long_int()const noexcept{
        return this->is_integer()&&(*this)>=LONG_MIN&&(*this)<=LONG_MAX;
    }
    constexpr bool is_unsigned_long_int()const noexcept{
        return this->is_integer()&&(*this)>=0&&(*this)<=ULONG_MAX;
    }
    constexpr bool is_signed_long_long_int()const noexcept{
        return this->is_integer()&&(*this)>=LLONG_MIN&&(*this)<=LLONG_MAX;
    }
    constexpr bool is_unsigned_long_long_int()const noexcept{
        return this->is_integer()&&(*this)>=0&&(*this)<=ULLONG_MAX;
    }
    constexpr bool is_float()const noexcept{
        return (*this)>=FLT_MIN&&(*this)<=FLT_MAX;
    }
    constexpr bool is_double()const noexcept{
        return (*this)>=DBL_MIN&&(*this)<=DBL_MAX;
    }
    constexpr bool to_signed_short_int(signed short int& reference)const noexcept{
        if(this->is_signed_short_int()){
            reference=static_cast<signed short int>(*this);
            return true;
        }
        return false;
    }
    constexpr bool to_unsigned_short_int(unsigned short int& reference)const noexcept{
        if(this->is_unsigned_short_int()){
            reference=static_cast<unsigned short int>(*this);
            return true;
        }
        return false;
    }
    constexpr bool to_signed_int(signed int& reference)const noexcept{
        if(this->is_signed_int()){
            reference=static_cast<signed int>(*this);
            return true;
        }
        return false;
    }
    constexpr bool to_unsigned_int(unsigned int& reference)const noexcept{
        if(this->is_unsigned_int()){
            reference=static_cast<unsigned int>(*this);
            return true;
        }
        return false;
    }
    constexpr bool to_signed_long_int(signed long int& reference)const noexcept{
        if(this->is_signed_long_int()){
            reference=static_cast<signed long int>(*this);
            return true;
        }
        return false;
    }
    constexpr bool to_unsigned_long_int(unsigned long int& reference)const noexcept{
        if(this->is_unsigned_long_int()){
            reference=static_cast<unsigned long int>(*this);
            return true;
        }
        return false;
    }
    constexpr bool to_signed_long_long_int(signed long long int& reference)const noexcept{
        if(this->is_signed_long_long_int()){
            reference=static_cast<signed long long int>(*this);
            return true;
        }
        return false;
    }
    constexpr bool to_unsigned_long_long_int(unsigned long long int& reference)const noexcept{
        if(this->is_unsigned_long_long_int()){
            reference=static_cast<unsigned long long int>(*this);
            return true;
        }
        return false;
    }
    constexpr bool to_float(float& reference)const noexcept{
        if(this->is_float()){
            reference=static_cast<float>(*this);
            return true;
        }
        return false;
    }
    constexpr bool to_double(double& reference)const noexcept{
        if(this->is_double()){
            reference=static_cast<double>(*this);
            return true;
        }
        return false;
    }
    constexpr signed short int to_signed_short_int()const noexcept{
        return this->is_signed_short_int()
            ?static_cast<signed short int>(*this)
            :0;
    }
    constexpr unsigned short int to_unsigned_short_int()const noexcept{
        return this->is_unsigned_short_int()
            ?static_cast<unsigned short int>(*this)
            :0;
    }
    constexpr signed int to_signed_int()const noexcept{
        return this->is_signed_int()
            ?static_cast<signed int>(*this)
            :0;
    }
    constexpr unsigned int to_unsigned_int()const noexcept{
        return this->is_unsigned_int()
            ?static_cast<unsigned int>(*this)
            :0;
    }
    constexpr signed long int to_signed_long_int()const noexcept{
        return this->is_signed_long_int()
            ?static_cast<signed long int>(*this)
            :0;
    }
    constexpr unsigned long int to_unsigned_long_int()const noexcept{
        return this->is_unsigned_long_int()
            ?static_cast<unsigned long int>(*this)
            :0;
    }
    constexpr signed long long int to_signed_long_long_int()const noexcept{
        return this->is_signed_long_long_int()
            ?static_cast<signed long long int>(*this)
            :0;
    }
    constexpr unsigned long long int to_unsigned_long_long_int()const noexcept{
        return this->is_unsigned_long_long_int()
            ?static_cast<unsigned long long int>(*this)
            :0;
    }
    constexpr float to_float()const noexcept{
        return this->is_float()
            ?static_cast<float>(*this)
            :0;
    }
    constexpr double to_double()const noexcept{
        return this->is_double()
            ?static_cast<double>(*this)
            :0;
    }
    template<typename OutputStream>
    friend constexpr OutputStream& operator<<(OutputStream& os,Number const& number)noexcept{
        return os<<number.const_data();
    }
}; // class Number
} // namespace script
