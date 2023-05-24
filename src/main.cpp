#include<iostream>
#include"meta.hpp"
#include"meta_name.hpp"
#include<type_traits>
#include<cassert>

template<typename _Type>
void foo(_Type&& arg){
    ::std::cout<<"foo -> "<<META_FUNCTION_NAME<<::std::endl;
    ::std::cout<<"_Type -> "<<meta::type_name<_Type>()<<::std::endl;
    ::std::cout<<"_Type&& -> "<<meta::type_name<_Type&&>()<<::std::endl;
    ::std::cout<<"arg -> "<<meta::type_name<decltype(arg)>()<<::std::endl;
}

void test_universal_ref(){
    int num_value=100;
    int const num_const=num_value;
    int & num_ref=num_value;
    int const& num_cref=num_const;
    int&& num_rvalue=::std::move(200);
    int temp=num_value;
    int&& num_rref=::std::move(temp);
    ::std::cout<<"num_value"<<::std::endl;
    foo(num_value);
    ::std::cout<<"num_const"<<::std::endl;
    foo(num_const);
    ::std::cout<<"num_ref"<<::std::endl;
    foo(num_ref);
    ::std::cout<<"num_cref"<<::std::endl;
    foo(num_cref);
    ::std::cout<<"num_rvalue"<<::std::endl;
    foo(num_rvalue);
    ::std::cout<<"num_rref"<<::std::endl;
    foo(num_rref);
    ::std::cout<<"num_literal"<<::std::endl;
    foo(decltype(num_value)(100));
}

template<intmax_t _length>
constexpr intmax_t static_string_size(char const(&)[_length]){
    return _length-1;
}

template<intmax_t _length>
constexpr char static_string_at(char const(&static_string)[_length],size_t index){
    return static_string[index];
}

template<intmax_t _length>
constexpr intmax_t static_string_find_first_of(char const(&static_string)[_length],char char_value){
    for(intmax_t index=0;index<static_string_size(static_string);++index){
        if(static_string[index]==char_value){
            return index;
        }
    }
    return -1;
}

template<intmax_t _length>
constexpr intmax_t static_string_find_last_of(char const(&static_string)[_length],char char_value){
    for(intmax_t index=static_string_size(static_string)-1;index>=0;--index){
        if(static_string[index]==char_value){
            return index;
        }
    }
    return -1;
}

template<::std::size_t _value>
static constexpr char temp_c_str[_value];
template<::std::size_t _value>
constexpr ::std::size_t integer_bit_num(){
    ::std::size_t value=_value;
    ::std::size_t ret=0;
    while(value!=0){
        value/=10;
        ++ret;
    }
    return ret;
}
template<::std::size_t _value>
constexpr char const* integer_to_string(){
    ::std::size_t value=_value;
    while(value!=0){
        stack.push_back(static_cast<char>(value%10)+'0');
        value/=10;
    }
    ::std::string ret{};
    while(!stack.empty()){
        ret.push_back(stack.back());
        stack.pop_back();
    }
    return ret;
}

template<char..._values>
struct StaticString{
    static constexpr char const value[sizeof...(_values)+1]={_values...,'\0'};
    using Type=StaticString;
};

void test_static_string(){
    constexpr auto&& static_string=META_FUNCTION_NAME;
    constexpr auto string_size=static_string_size(static_string);
    constexpr auto string_element_of_index_2=static_string_at(static_string,2);
    constexpr auto first_index=static_string_find_first_of(static_string,'_');
    constexpr auto last_index=static_string_find_last_of(static_string,'_');
    constexpr::std::string number=integer_to_string<1000>();
    ::std::cout<<number<<::std::endl;
    //assert(::std::stoi(number)==1000);
}
meta::Enable<meta::True,int> main(void){
    ::std::cout<<META_FUNCTION_NAME<<::std::endl;
    test_static_string();
    typename meta::Invoke<
        typename meta::Invoke<
            meta::Template<meta::IF>,
            meta::True,
            meta::Template<meta::IF>,
            meta::Template<meta::Return>
        >::Type,
        meta::True,
        int,
        double
    >::Type a;
    ::std::cout<<"typeof(a)="<<meta::type_name<decltype(a)>()<<::std::endl;
    meta::Operator_LeftShift<meta::Auto<(int)true>,meta::Auto<4>>::Type b;
    ::std::cout<<"typeof(b)="<<meta::type_name<decltype(b)>()<<::std::endl;
    meta::test_compiler_name();
    meta::test_function_name<::std::string>();
    meta::test_type_name<::std::string const volatile* const volatile(*const volatile&&)[2][1]>();
    test_universal_ref();
    return 0;
}
