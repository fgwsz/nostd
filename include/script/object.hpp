#pragma once
extern "C"{
#include<stddef.h>
#include<stdlib.h>
} // extern "C"
namespace script{
template<typename _Type>
class _List{
public:
    struct _Node{
        _Node* prev_;
        _Node* next_;
        _Type* data_;
    };
private:
    _Node* head_;
    size_t size_;
public:
    constexpr _List<_Type>()noexcept{
        this->head_=(typename _List<_Type>::_Node*)::malloc(sizeof(typename _List<_Type>::_Node));
        this->head_->prev_=this->head_;
        this->head_->next_=this->head_;
        this->head_->data_=nullptr;
        this->size_=0;
    }
    constexpr ~_List()noexcept{
        this->clear();
        ::free(this->head_);
    }
    constexpr _List<_Type>(_List<_Type> const& list)noexcept
        :_List<_Type>(){
        (*this)=list;
    }
    constexpr _List<_Type>& operator=(_List<_Type> const& list)noexcept
        // TODO
        return *this;
    }
    constexpr void clear() noexcept{
        // TODO
    }
    constexpr bool empty()const noexcept{
        // TODO
    }
    constexpr size_t size()const noexcept{
        // TODO
    }
    constexpr bool insert_element(typename _List<_Type>::_Node* position,_Type const& value)noexcept{
        // TODO
    }
    constexpr bool erase_element(typename _List<_Type>::_Node* position)noexcept{
        // TODO
    }
    constexpr bool set_element(typename _List<_Type>::_Node* position,_Type const& value)noexcept{
        // TODO
    }
    constexpr bool get_element(typename _List<_Type>::_Node* position,_Type& value)noexcept{
        // TODO
    }
    constexpr void push_front(_Type const& value)noexcept{
        // TODO
    }
    constexpr void push_back(_Type const& value)noexcept{
        // TODO
    }
    constexpr void pop_front()noexcept{
        // TODO
    }
    constexpr void pop_back()noexcept{
        // TODO
    }
    constexpr typename _List<_Type>::_Node* begin_position()noexcept{
        // TODO
    }
    constexpr typename _List<_Type>::_Node* end_position()noexcept{
        // TODO
    }
    constexpr typename _List<_Type>::_Node* get_position(size_t index)noexcept{
        // TODO
    }
}; // class _List
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
