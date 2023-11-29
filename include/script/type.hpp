#pragma once
namespace script{
enum class Type:unsigned char{
    typeid_of_boolean ,
    typeid_of_number  ,
    typeid_of_u8string,
    typeid_of_array   ,
    typeid_of_object
};
}// namespace script
