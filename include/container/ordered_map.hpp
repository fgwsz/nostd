#pragma once
#include<type_traits>//::std::is_same_v ::std::decay_t
#include<list>//::std::list
#include<unordered_map>//::std::unordered_map
#include<utility>//::std::move
#include<stdexcept>//::std::runtime_error
#include<cstddef>//::std::size_t
#include<functional>//::std::function
#include<vector>//::std::vector

template<typename _KeyType,typename _ValueType>
requires
    ::std::is_same_v<::std::decay_t<_KeyType>,_KeyType>&&
    ::std::is_same_v<::std::decay_t<_ValueType>,_ValueType>
class OrderedMap final{
    struct Pair{
        _KeyType const key_;
        _ValueType value_;
    };
    using pair_t=Pair;
    using list_iterator=typename ::std::list<pair_t>::const_iterator;
    ::std::unordered_map<_KeyType,list_iterator> map_;
    ::std::list<pair_t> list_;
public:
    constexpr OrderedMap()noexcept
        :map_({})
        ,list_({})
    {}
    constexpr OrderedMap(OrderedMap const& rhs)noexcept
        :OrderedMap(){
        *this=rhs;
    }
    constexpr OrderedMap(OrderedMap&& rhs)noexcept
        :OrderedMap(){
        *this=::std::move(rhs);
    }
    constexpr OrderedMap& operator=(OrderedMap const& rhs)noexcept{
        if(this==&rhs){
            return *this;
        }
        this->clear();
        rhs->for_each(
            [this](_KeyType const& key,_ValueType const& value){
                this->add_key(key,value);
            }
        );
        return *this;
    }
    constexpr OrderedMap& operator=(OrderedMap&& rhs)noexcept{
        if(this==&rhs){
            return *this;
        }
        this->list_=::std::move(rhs.list_);
        this->map_=::std::move(rhs.map_);
        return *this;
    }
    constexpr OrderedMap& swap(OrderedMap& rhs)noexcept{
        this->list_.swap(rhs.list_);
        this->map_.swap(rhs.map_);
        return *this;
    }
    constexpr bool has_key(_KeyType const& key)const noexcept{
        return this->map_.count(key)!=0;
    }
    constexpr OrderedMap& add_key(
        _KeyType const& key,
        _ValueType const& value
    ){
        if(this->has_key(key)){
            throw ::std::runtime_error(
                "OrderedMap::add_key():"
                "This key already exists."
            );
        }
        this->map_[key]=this->list_.insert(
            this->list_.cend(),
            pair_t{key,value}
        );
        return *this;
    }
    constexpr OrderedMap& delete_key(_KeyType const& key){
        if(!this->has_key(key)){
            throw ::std::runtime_error(
                "OrderedMap::delete_key():"
                "Can't find this key."
            );
        }
        this->list_.erase(this->map_[key]);
        this->map_.erase(key);
        return *this;
    }
    constexpr OrderedMap& clear(){
        this->list_.clear();
        this->map_.clear();
        return *this;
    }
    constexpr _ValueType const& value_of(_KeyType const& key)const{
        if(!this->has_key(key)){
            throw ::std::runtime_error(
                "OrderedMap::value_of():"
                "Can't find this key."
            );
        }
        return *(this->map_[key]);
    }
    constexpr ::std::size_t size()const noexcept{
        return this->map_.size();
    }
    constexpr OrderedMap& for_each(
        ::std::function<void(_KeyType const&,_ValueType&)>const& func
    )noexcept{
        for(auto& pair:this->list_){
            func(pair.key_,pair.value_);
        }
        return *this;
    }
    constexpr OrderedMap const& for_each(
        ::std::function<void(_KeyType const&,_ValueType const&)>const& func
    )const noexcept{
        for(auto const& pair:this->list_){
            func(pair.key_,pair.value_);
        }
        return *this;
    }
    constexpr ::std::vector<_KeyType> keys_of(
        _ValueType const& value
    )const noexcept{
        ::std::vector<_KeyType> ret={};
        this->for_each(
            [&value,&ret](_KeyType const& _key,_ValueType const& _value){
                if(value==_value){
                    ret->push_back(_key);
                }
            }
        );
        return ret;
    }
};
