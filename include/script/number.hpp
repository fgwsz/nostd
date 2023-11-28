#pragma once
extern "C"{
#include<limits.h>
#include<float.h>
#include<math.h>
} // extern "C"
namespace script{
class Number{
public:
    using data_type=double;
private:
    data_type data_;
public:
    Number(){
        this->data_=0;
    }
    Number(signed short int value)
        :Number(){
        (*this)=value;
    }
    Number(unsigned short int value)
        :Number(){
        (*this)=value;
    }
    Number(signed int value)
        :Number(){
        (*this)=value;
    }
    Number(unsigned int value)
        :Number(){
        (*this)=value;
    }
    Number(signed long int value)
        :Number(){
        (*this)=value;
    }
    Number(unsigned long int value)
        :Number(){
        (*this)=value;
    }
    Number(signed long long int value)
        :Number(){
        (*this)=value;
    }
    Number(unsigned long long int value)
        :Number(){
        (*this)=value;
    }
    Number(float value)
        :Number(){
        (*this)=value;
    }
    Number(double value)
        :Number(){
        (*this)=value;
    }
    Number(Number const& value)
        :Number(){
        (*this)=value;
    }
    Number& operator=(signed short int value){
        this->data_=static_cast<data_type>(value);
        return *this;
    }
    Number& operator=(unsigned short int value){
        this->data_=static_cast<data_type>(value);
        return *this;
    }
    Number& operator=(signed int value){
        this->data_=static_cast<data_type>(value);
        return *this;
    }
    Number& operator=(unsigned int value){
        this->data_=static_cast<data_type>(value);
        return *this;
    }
    Number& operator=(signed long int value){
        this->data_=static_cast<data_type>(value);
        return *this;
    }
    Number& operator=(unsigned long int value){
        this->data_=static_cast<data_type>(value);
        return *this;
    }
    Number& operator=(signed long long int value){
        this->data_=static_cast<data_type>(value);
        return *this;
    }
    Number& operator=(unsigned long long int value){
        this->data_=static_cast<data_type>(value);
        return *this;
    }
    Number& operator=(float value){
        this->data_=static_cast<data_type>(value);
        return *this;
    }
    Number& operator=(double value){
        this->data_=static_cast<data_type>(value);
        return *this;
    }
    Number& operator=(Number const& value){
        (*this)=value->data_;
        return *this;
    }
    explicit operator signed short int() const{
        return static_cast<signed short int>(this->data_);
    }
    explicit operator unsigned short int() const{
        return static_cast<unsigned short int>(this->data_);
    }
    explicit operator signed int() const{
        return static_cast<signed int>(this->data_);
    }
    explicit operator unsigned int() const{
        return static_cast<unsigned int>(this->data_);
    }
    explicit operator signed long int() const{
        return static_cast<signed long int>(this->data_);
    }
    explicit operator unsigned long int() const{
        return static_cast<unsigned long int>(this->data_);
    }
    explicit operator signed long long int() const{
        return static_cast<signed long long int>(this->data_);
    }
    explicit operator unsigned long long int() const{
        return static_cast<unsigned long long int>(this->data_);
    }
    explicit operator float() const{
        return static_cast<float>(this->data_);
    }
    explicit operator double() const{
        return static_cast<double>(this->data_);
    }
    data_type& data(){
        return this->data_;
    }
    static data_type min_value(){
        return DBL_MIN;
    }
    static data_type max_value(){
        return DBL_MAX;
    }
    bool is_integer() const{
        return this->data_==this->data_>=0
            ?::floor(this->data_)
            :::ceil(this->data_);
    }
    bool is_signed_short_int() const{
        return this->is_integer()&&this->data_>=SHRT_MIN&&this->data_<=SHRT_MAX;
    }
    bool is_unsigned_short_int() const{
        return this->is_integer()&&this->data_>=0&&this->data_<=USHRT_MAX;
    }
    bool is_signed_int() const{
        return this->is_integer()&&this->data_>=INT_MIN&&this->data_<=INT_MAX;
    }
    bool is_unsigned_int() const{
        return this->is_integer()&&this->data_>=0&&this->data_<=UINT_MAX;
    }
    bool is_signed_long_int() const{
        return this->is_integer()&&this->data_>=LONG_MIN&&this->data_<=LONG_MAX;
    }
    bool is_unsigned_long_int() const{
        return this->is_integer()&&this->data_>=0&&this->data_<=ULONG_MAX;
    }
    bool is_signed_long_long_int() const{
        return this->is_integer()&&this->data_>=LLONG_MIN&&this->data_<=LLONG_MAX;
    }
    bool is_unsigned_long_long_int() const{
        return this->is_integer()&&this->data_>=0&&this->data_<=ULLONG_MAX;
    }
    bool is_float() const{
        return this->data_>=FLT_MIN&&this->data_<=FLT_MAX;
    }
    bool is_double() const{
        return this->data_>=DBL_MIN&&this->data_<=DBL_MAX;
    }
    bool to_signed_short_int(signed short int& reference) const{
        if(this->is_signed_short_int()){
            reference=static_cast<signed short int>(*this);
            return true;
        }
        return false;
    }
    bool to_unsigned_short_int(unsigned short int& reference) const{
        if(this->is_unsigned_short_int()){
            reference=static_cast<unsigned short int>(*this);
            return true;
        }
        return false;
    }
    bool to_signed_int(signed int& reference) const{
        if(this->is_signed_int()){
            reference=static_cast<signed int>(*this);
            return true;
        }
        return false;
    }
    bool to_unsigned_int(unsigned int& reference) const{
        if(this->is_unsigned_int()){
            reference=static_cast<unsigned int>(*this);
            return true;
        }
        return false;
    }
    bool to_signed_long_int(signed long int& reference) const{
        if(this->is_signed_long_int()){
            reference=static_cast<signed long int>(*this);
            return true;
        }
        return false;
    }
    bool to_unsigned_long_int(unsigned long int& reference) const{
        if(this->is_unsigned_long_int()){
            reference=static_cast<unsigned long int>(*this);
            return true;
        }
        return false;
    }
    bool to_signed_long_long_int(signed long long int& reference) const{
        if(this->is_signed_long_long_int()){
            reference=static_cast<signed long long int>(*this);
            return true;
        }
        return false;
    }
    bool to_unsigned_long_long_int(unsigned long long int& reference) const{
        if(this->is_unsigned_long_long_int()){
            reference=static_cast<unsigned long long int>(*this);
            return true;
        }
        return false;
    }
    bool to_float(float& reference) const{
        if(this->is_float()){
            reference=static_cast<float>(*this);
            return true;
        }
        return false;
    }
    bool to_double(double& reference) const{
        if(this->is_double()){
            reference=static_cast<double>(*this);
            return true;
        }
        return false;
    }
    signed short int to_signed_short_int() const{
        return this->is_signed_short_int()
            ?static_cast<signed short int>(*this)
            :0;
    }
    unsigned short int to_unsigned_short_int() const{
        return this->is_unsigned_short_int()
            ?static_cast<unsigned short int>(*this)
            :0;
    }
    signed int to_signed_int() const{
        return this->is_signed_int()
            ?static_cast<signed int>(*this)
            :0;
    }
    unsigned int to_unsigned_int() const{
        return this->is_unsigned_int()
            ?static_cast<unsigned int>(*this)
            :0;
    }
    signed long int to_signed_long_int() const{
        return this->is_signed_long_int()
            ?static_cast<signed long int>(*this)
            :0;
    }
    unsigned long int to_unsigned_long_int() const{
        return this->is_unsigned_long_int()
            ?static_cast<unsigned long int>(*this)
            :0;
    }
    signed long long int to_signed_long_long_int() const{
        return this->is_signed_long_long_int()
            ?static_cast<signed long long int>(*this)
            :0;
    }
    unsigned long long int to_unsigned_long_long_int() const{
        return this->is_unsigned_long_long_int()
            ?static_cast<unsigned long long int>(*this)
            :0;
    }
    float to_float() const{
        return this->is_float()
            ?static_cast<float>(*this)
            :0;
    }
    double to_double() const{
        return this->is_double()
            ?static_cast<double>(*this)
            :0;
    }
    bool operator==(Number const& number) const{
        return this->data_==number.data_;
    }
    bool operator!=(Number const& number) const{
        return this->data_!=number.data_;
    }
    bool operator<(Number const& number) const{
        return this->data_<number.data_;
    }
    bool operator>(Number const& number) const{
        return this->data_>number.data_;
    }
    bool operator<=(Number const& number) const{
        return this->data_<=number.data_;
    }
    bool operator>=(Number const& number) const{
        return this->data_>=number.data_;
    }
    Number operator+(Number const& number) const{
        return this->data_+number.data_;
    }
    Number operator-(Number const& number) const{
        return this->data_-number.data_;
    }
    Number operator*(Number const& number) const{
        return this->data_*number.data_;
    }
    Number operator/(Number const& number) const{
        return this->data_/number.data_;
    }
    Number operator%(Number const& number) const{
        if(this->is_unsigned_long_long_int()&&number.is_unsigned_long_long_int()){
            return this->to_unsigned_long_long_int()%number.to_unsigned_long_long_int();
        }
        return ::fmod(this->data_,number.data_);
    }
}; // class Number
} // namespace script
