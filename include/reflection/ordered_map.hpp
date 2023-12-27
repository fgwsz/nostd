#pragma once
#include<cstddef>
#include<unordered_map>
#include<list>
#include<utility>
#include<type_traits>
#include<stdexcept>
#include<initializer_list>
template<typename _KeyType,typename _ValueType>
requires 
    ::std::is_same_v<::std::decay_t<_KeyType>,_KeyType>&&
    ::std::is_same_v<::std::decay_t<_ValueType>,_ValueType>
class OrderedMap{
public:
    struct Pair{
        _KeyType const key;
        _ValueType value;
    };
private:
    using pair_t=Pair;
    using list_iterator=typename ::std::list<pair_t>::iterator;
    ::std::unordered_map<_KeyType,list_iterator> map_;
    ::std::list<pair_t> list_;
public:
    inline constexpr bool has(_KeyType const& key)const noexcept{
        return this->map_.count(key)!=0;
    }
    inline constexpr OrderedMap& insert(Pair const& pair)noexcept{
        if(!this->has(pair.key)){
            this->map_[key]=this->list_.insert(this->list_.cend(),pair);
        }
        return *this;
    }
    inline constexpr OrderedMap& insert(_KeyType const& key,_ValueType const& value)noexcept{
        return this->insert(pair_t{key,value});
    }
    inline constexpr OrderedMap& erase(_KeyType const& key)noexcept{
        if(this->has(key)){
            this->list_.erase(this->map_[key]);
            this->map_.erase(key);
        }
        return *this;
    }
    template<typename _Func>
    inline constexpr OrderedMap& for_each(_Func&& func)noexcept{
        for(auto& element:this->list_){
            ::std::forward<_Func>(func)(element);
        }
    }
    template<typename _Func>
    inline constexpr OrderedMap const& for_each(_Func&& func)const noexcept{
        for(auto const& element:this->list_){
            ::std::forward<_Func>(func)(element);
        }
    }
    inline constexpr _ValueType& operator[](_KeyType const& key)noexcept{
        if(this->has(key)){
            return this->map_[key];
        }else{
            this->insert(key,_ValueType{});
            return this->map_[key];
        }
    }
    inline constexpr _ValueType const& operator[](_KeyType const& key)const{
        if(this->has(key)){
            return this->map_[key];
        }
        throw ::std::runtime_error("OrderedMap operator()const:has not the key");
    }
    inline OrderedMap()noexcept=default;
    inline constexpr OrderedMap(::std::initializer_list<pair_t> const& list)noexcept
        :OrderedMap(){
        for(auto const& element:list){
            this->insert(element);
        }
    }
    inline constexpr size_t size()const noexcept{
        return this->map_.size();
    }
};