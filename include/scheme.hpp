#pragma once
#include<string>
#include<functional>
#include<vector>
#include<map>
#include<variant>
namespace scheme{
// 数据类型
using boolean_t=bool const;
using number_t=double const;
using string_t=::std::string const;
using data_t=::std::variant<boolean_t,number_t,string_t>const;

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
    boolean,
    number,
    string,
    function,
    list
};
using type_t=Type const;

using object_name_t=string_t;
using object_data_t=data_t;

struct Object{
    object_name_t name;
    object_data_t data;
};
using object_t=Object;

using object_map_t=::std::map<object_name_t,object_t>;
static object_map_t object_map{};

using list_t=::std::vector<object_t>;

struct Data{
    type_t     type_value    ;
    boolean_t  boolean_value ;
    number_t   number_value  ;
    string_t   string_value  ;
    function_t function_value;
    list_t     list_value    ;
};
static constexpr void define_function(function_name_t name,function_data_t data){
    if(function_map.count(name)!=0){
        return;
    }
    function_map.emplace(name,data);
}
static constexpr void define_object(object_name_t name,object_data_t data){
    if(object_map.count(name)!=0){
        return;
    }
    object_map.emplace(name,data);
}
};
}
