#pragma once
#include<new>
#include<string_view>
#include<unordered_map>
#include<iostream>
void* _malloc_wrapper(size_t size){
    return ::operator new(size,::std::nothrow);
}
void _free_wrapper(void* data){
    ::operator delete(data,::std::nothrow);
}
template<typename _ValueType>
void _ctor_wrapper(void* data){
    new(data)_ValueType{};
}
template<typename _ValueType>
void _dtor_wrapper(void* data){
    ((_ValueType*)data)->~_ValueType();
}
template<typename _ValueType>
void _copy_wrapper(void const* from,void* to){
    *((_ValueType*)to)=*((_ValueType const*)from);
}
struct TypeMetaInfo{
    ::std::string_view type_name_;
    size_t size_;
    void* (*malloc_func_)(size_t);
    void (*free_func_)(void*);
    void (*ctor_func_)(void*);
    void (*dtor_func_)(void*);
    void (*copy_func_)(void const*,void*);
    void* new_func(){
        void* ret=malloc_func_(size_);
        ctor_func_(ret);
        return ret;
    }
    void delete_func(void* data){
        dtor_func_(data);
        free_func_(data);
    }
};
template<typename _ValueType>
TypeMetaInfo make_type_meta_info(::std::string_view const& type_name){
    return {
        .type_name_=type_name,
        .size_=sizeof(_ValueType),
        .malloc_func_=&_malloc_wrapper,
        .free_func_=&_free_wrapper,
        .ctor_func_=&_ctor_wrapper<_ValueType>,
        .dtor_func_=&_dtor_wrapper<_ValueType>,
        .copy_func_=&_copy_wrapper<_ValueType>
    };
}
struct FieldMetaInfo{
    ::std::string_view class_name_;
    ::std::string_view field_name_;
    long long offset_;
    TypeMetaInfo type_;
};
struct ClassMetaInfo{
    TypeMetaInfo type_;
    ::std::unordered_map<::std::string_view,FieldMetaInfo> fields_;
    ClassMetaInfo& add_field(
        ::std::string_view const& field_name,
        long long field_offset,
        TypeMetaInfo const& field_type
    ){
        fields_.emplace(
            field_name,
            FieldMetaInfo{
                .class_name_=type_.type_name_,
                .field_name_=field_name,
                .offset_=field_offset,
                .type_=field_type
            }
        );
        return *this;
    }
};
static ::std::unordered_map<::std::string_view,ClassMetaInfo> _class_meta_info_map;
template<typename _ClassType,typename _FieldType>
long long get_offset(_ClassType const& self,_FieldType _ClassType::* field_ptr){
    return (long long)((char*)&(self.*field_ptr)-(char*)&self);
}
void* get_field(void* object,long long offset){
    return (void*)(((char*)(void*)object)+offset);
}
// for test
struct Person{
    ::std::string_view name_;
    size_t age_;
};
static bool const regist_class_of_person=[]{
    ClassMetaInfo class_meta_info;
    class_meta_info.type_=make_type_meta_info<Person>("::Person");
    class_meta_info.add_field(
        "name_",
        get_offset(*(Person*)(nullptr),&Person::name_),
        make_type_meta_info<::std::string_view>("::std::string_view")
    )
    .add_field(
        "age_",
        get_offset(*(Person*)(nullptr),&Person::age_),
        make_type_meta_info<size_t>("size_t")
    );
    _class_meta_info_map.emplace(
        class_meta_info.type_.type_name_,
        class_meta_info
    );
    return true;
}();
void test_refl(){
    ClassMetaInfo person_meta_info=_class_meta_info_map.at("::Person");
    void* person=person_meta_info.type_.new_func();
    FieldMetaInfo name_meta_info=person_meta_info.fields_.at("name_");
    void* person_name=get_field(person,name_meta_info.offset_);
    FieldMetaInfo age_meta_info=person_meta_info.fields_.at("age_");
    void* person_age=get_field(person,age_meta_info.offset_);
    ::std::string_view name="Tom";
    size_t age=100;
    name_meta_info.type_.copy_func_(&name,person_name);
    age_meta_info.type_.copy_func_(&age,person_age);
    auto& person_ref=*(Person*)person;
    ::std::cout<<"Person{name:"<<person_ref.name_<<",age:"<<person_ref.age_<<"}\n";
    person_meta_info.type_.delete_func(person);
}