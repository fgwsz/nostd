#pragma once
namespace script{
template<typename _KeyType,typename _ValueType>
struct _Pair{
    _KeyType*   key_;  // maybe big object
    _ValueType* value_;// linked list of value
};
template<typename _DataType>
struct _Node{
    _Node*     prev_;
    _Node*     next_;
    _DataType* data_;
};
// hash (key)->(node)
// list [head]<->[node]<->[...]->null
//                 |
//                 v
//              [pair:key;value_list_head]->[...]->null
// insert O(1)
//    list push_front(pair)->get node
//    hash insert(key,node)
// erase  O(1)
//    hash find(key)->get node
//    list_node_erase(node)
// find   O(1)
//    hash find(key)->get node
//    list_node_data(node)->value
} // namespace script
