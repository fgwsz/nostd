#pragma once
#include<string>
#include<functional>
#include<vector>
#include<map>
namespace scheme{

using string_t=::std::string const;
using number_t=double const;
struct Data;
using data_t=Data const;

using function_name_t=string_t;
using function_data_t=::std::function<data_t(data_t)>const;
struct Function{
    function_name_t name;
    function_data_t data;
};
using function_t=Function const;

using function_map_t=::std::map<function_name_t,function_t>;
static function_map_t function_map{};

enum class Type{
    number,
    string,
    function,
    list
};
using type_t=Type const;

using object_name_t=string_t;
using object_type_t=type_t;
using object_data_t=data_t;

struct Object{
    object_name_t name;
    object_type_t type;
    object_data_t data;
};
using object_t=Object;

using object_map_t=::std::map<object_name_t,object_t>;
static object_map_t object_map{};

using list_t=::std::vector<object_t>;

struct Data{
    number_t   number_value  ;
    string_t   string_value  ;
    function_t function_value;
    list_t     list_value    ;
};
static constexpr void define_function(function_name_t name,function_data_t data){

};
}
