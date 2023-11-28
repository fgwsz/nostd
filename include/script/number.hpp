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
        *this=value;
    }
    Number(unsigned short int value)
        :Number(){
        *this=value;
    }
    Number(signed int value)
        :Number(){
        *this=value;
    }
    Number(unsigned int value)
        :Number(){
        *this=value;
    }
    Number(signed long int value)
        :Number(){
        *this=value;
    }
    Number(unsigned long int value)
        :Number(){
        *this=value;
    }
    Number(signed long long int value)
        :Number(){
        *this=value;
    }
    Number(unsigned long long int value)
        :Number(){
        *this=value;
    }
    Number(float value)
        :Number(){
        *this=value;
    }
    Number(double value)
        :Number(){
        *this=value;
    }
    Number(Number const& number)
        :Number(){
        *this=number;
    }
    Number& operator=(signed short int value){
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    Number& operator=(unsigned short int value){
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    Number& operator=(signed int value){
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    Number& operator=(unsigned int value){
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    Number& operator=(signed long int value){
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    Number& operator=(unsigned long int value){
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    Number& operator=(signed long long int value){
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    Number& operator=(unsigned long long int value){
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    Number& operator=(float value){
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    Number& operator=(double value){
        this->data_=static_cast<typename Number::data_type>(value);
        return *this;
    }
    Number& operator=(Number const& number){
        *this=number.data_;
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
        return ::fmod(this->data_,number.data_);
    }
    Number operator^(Number const& number) const{
        return ::pow(this->data_,number.data_);
    }
    Number operator+() const{
        return +(this->data_);
    }
    Number operator-() const{
        return -(this->data_);
    }
    Number& operator+=(Number const& number){
        return (*this)=(*this)+number;
    }
    Number& operator-=(Number const& number){
        return (*this)=(*this)-number;
    }
    Number& operator*=(Number const& number){
        return (*this)=(*this)*number;
    }
    Number& operator/=(Number const& number){
        return (*this)=(*this)/number;
    }
    Number& operator%=(Number const& number){
        return (*this)=(*this)%number;
    }
    Number& operator^=(Number const& number){
        return (*this)=(*this)^number;
    }
    Number& operator++(){
        return (*this)+=1;
    }
    Number& operator--(){
        return (*this)-=1;
    }
    Number operator++(int){
        Number ret=*this;
        ++(*this);
        return ret;
    }
    Number operator--(int){
        Number ret=*this;
        --(*this);
        return ret;
    }
    typename Number::data_type& data(){
        return this->data_;
    }
    typename Number::data_type const& const_data() const{
        return this->data_;
    }
    static Number min_value(){
        return DBL_MIN;
    }
    static Number max_value(){
        return DBL_MAX;
    }
    static Number floor(Number const& number){
        return ::floor(number.data_);
    }
    static Number ceil(Number const& number){
        return ::ceil(number.data_);
    }
    static Number integer(Number const& number){
        return number>=0
            ?Number::floor(number)
            :Number::ceil(number);
    }
    static Number min(Number const& number_1,Number const& number_2){
        return ::fmin(number_1.const_data(),number_2.const_data());
    }
    static Number max(Number const& number_1,Number const& number_2){
        return ::fmax(number_1.const_data(),number_2.const_data());
    }
    static Number abs(Number const& number){
        return ::fabs(number.const_data());
    }
    static Number difference(Number const& number_1,Number const& number_2){
        return Number::abs(number_1-number_2);
    }
    bool is_integer() const{
        return (*this)==Number::integer(*this);
    }
    bool is_signed_short_int() const{
        return this->is_integer()&&(*this)>=SHRT_MIN&&(*this)<=SHRT_MAX;
    }
    bool is_unsigned_short_int() const{
        return this->is_integer()&&(*this)>=0&&(*this)<=USHRT_MAX;
    }
    bool is_signed_int() const{
        return this->is_integer()&&(*this)>=INT_MIN&&(*this)<=INT_MAX;
    }
    bool is_unsigned_int() const{
        return this->is_integer()&&(*this)>=0&&(*this)<=UINT_MAX;
    }
    bool is_signed_long_int() const{
        return this->is_integer()&&(*this)>=LONG_MIN&&(*this)<=LONG_MAX;
    }
    bool is_unsigned_long_int() const{
        return this->is_integer()&&(*this)>=0&&(*this)<=ULONG_MAX;
    }
    bool is_signed_long_long_int() const{
        return this->is_integer()&&(*this)>=LLONG_MIN&&(*this)<=LLONG_MAX;
    }
    bool is_unsigned_long_long_int() const{
        return this->is_integer()&&(*this)>=0&&(*this)<=ULLONG_MAX;
    }
    bool is_float() const{
        return (*this)>=FLT_MIN&&(*this)<=FLT_MAX;
    }
    bool is_double() const{
        return (*this)>=DBL_MIN&&(*this)<=DBL_MAX;
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
    template<typename OutputStream>
    friend OutputStream& operator<<(OutputStream& os,Number const& number){
        return os<<number.const_data();
    }
}; // class Number
} // namespace script
