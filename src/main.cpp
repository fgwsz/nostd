﻿#include<string>//::std::string
#include<iostream>//::std::cout
#include"nostd_type_name.hpp"
#include"container/ordered_map.hpp"
template<typename _OutputStreamType,typename _KeyType,typename _ValueType>
_OutputStreamType& operator<<(
    _OutputStreamType& os,
    OrderedMap<_KeyType,_ValueType> const& map
)noexcept{
    os<<"OrderedMap<"
        <<::nostd::type_name<_KeyType>()<<","
        <<::nostd::type_name<_ValueType>()<<">\n";
    map.foreach(
        [&os](_KeyType const& key,_ValueType const& value){
            os<<"\t<"<<key<<":"<<value<<">\n";
        }
    );
    return os;
}
int main(void){
    OrderedMap<::std::string,int> map;
    map
        .set("age",100)
        .set("name",666);
    ::std::cout<<map;
    return 0;
}
