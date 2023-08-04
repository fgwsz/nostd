#pragma once
#include<string>
#include<functional>
#include<vector>
#include<map>
namespace scheme{

struct Data;
enum class Type;
struct Null;

using data_t    =Data;
using type_t    =Type;

using null_t    =Null;
using boolean_t =bool;
using number_t  =double;
using string_t  =::std::string;
using function_t=::std::function<data_t(data_t)>;
using list_t    =::std::vector<data_t>;

struct Null{};

enum class Type{
    null,
    boolean,
    number,
    string,
    function,
    list
};

struct Data{
    type_t     type_value    ;
    null_t     null_value    ;
    boolean_t  boolean_value ;
    number_t   number_value  ;
    string_t   string_value  ;
    function_t function_value;
    list_t     list_value    ;
    Data(null_t value={})
        :null_value(value)
        ,type_value(type_t::null)
    {}
    Data(boolean_t value)
        :boolean_value(value)
        ,type_value(type_t::boolean)
    {}
    Data(number_t value)
        :number_value(value)
        ,type_value(type_t::number)
    {}
    Data(string_t value)
        :string_value(value)
        ,type_value(type_t::string)
    {}
    Data(function_t value)
        :function_value(value)
        ,type_value(type_t::function)
    {}
    Data(list_t value)
        :list_value(value)
        ,type_value(type_t::list)
    {}
    Data(Data const&)=default;
    Data&opertor=(Data const&)=default;
    auto& as_null    (){ return null_value    ;}
    auto& as_boolean (){ return boolean_value ;}
    auto& as_number  (){ return number_value  ;}
    auto& as_string  (){ return string_value  ;}
    auto& as_function(){ return function_value;}
    auto& as_list    (){ return list_value    ;}
};
static function_t number_operator_add=[](data_t parameter_list){
    auto list=parameter_list.list_value;
    auto ret=number_t{0};
    for(auto const& element:list){
        ret+=element.number_value;
    }
    return ret;
};
}
