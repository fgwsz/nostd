#pragma once
#include<type_traits>//::std::is_same_v ::std::decay_t
#include<list>//::std::list
#include<unordered_map>//::std::unordered_map
#include<utility>//::std::move
#include<stdexcept>//::std::runtime_error
#include<cstddef>//::std::size_t
#include<functional>//::std::function

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
    using list_iterator=typename ::std::list<pair_t>::iterator;
    ::std::unordered_map<_KeyType,list_iterator> map_;
    ::std::list<pair_t> list_;
public:
    constexpr OrderedMap(void)noexcept
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
        rhs->foreach(
            [this](_KeyType const& key,_ValueType const& value){
                this->insert(key,value);
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
    constexpr bool contains(_KeyType const& key)const noexcept{
        return this->map_.count(key)!=0;
    }
    constexpr OrderedMap& insert(
        _KeyType const& key,
        _ValueType const& value
    ){
        if(this->contains(key)){
            throw ::std::runtime_error(
                "OrderedMap::insert():"
                "This key already exists."
            );
        }
        this->map_[key]=this->list_.insert(
            this->list_.cend(),
            pair_t{key,value}
        );
        return *this;
    }
    constexpr OrderedMap& erase(_KeyType const& key){
        if(!this->contains(key)){
            throw ::std::runtime_error(
                "OrderedMap::erase():"
                "Can't find this key."
            );
        }
        this->list_.erase(this->map_[key]);
        this->map_.erase(key);
        return *this;
    }
    constexpr OrderedMap& clear(void)noexcept{
        this->list_.clear();
        this->map_.clear();
        return *this;
    }
    constexpr _ValueType const& get(_KeyType const& key)const{
        if(!this->contains(key)){
            throw ::std::runtime_error(
                "OrderedMap::get():"
                "Can't find this key."
            );
        }
        return this->map_[key]->value_;
    }
    constexpr OrderedMap& update(
        _KeyType const& key,
        _ValueType const& value
    ){
        if(!this->contains(key)){
            throw ::std::runtime_error(
                "OrderedMap::update():"
                "Can't find this key."
            );
        }
        this->map_[key]->value_=value;
        return *this;
    }
    constexpr OrderedMap& set(
        _KeyType const& key,
        _ValueType const& value
    )noexcept{
        if(!this->contains(key)){
            this->insert(key,value);
        }else{
            this->update(key,value);
        }
        return *this;
    }
    constexpr ::std::size_t size(void)const noexcept{
        return this->map_.size();
    }
    constexpr bool empty(void)const noexcept{
        return this->size()==0;
    }
    constexpr OrderedMap& foreach(
        ::std::function<void(_KeyType const&,_ValueType&)>const& func
    )noexcept{
        for(auto& pair:this->list_){
            func(pair.key_,pair.value_);
        }
        return *this;
    }
    constexpr OrderedMap const& foreach(
        ::std::function<void(_KeyType const&,_ValueType const&)>const& func
    )const noexcept{
        for(auto const& pair:this->list_){
            func(pair.key_,pair.value_);
        }
        return *this;
    }
};
