#pragma once
#include"type.hpp"
#include"object.hpp"
class Field{
    template<typename _ClassType,typename _FieldType>
    static inline Object _get(Object const& object,Object const& field_ptr){
        return make_object(
            object.safe_cast<_ClassType const&>().*(
                field_ptr.safe_cast<_FieldType _ClassType::*>()
            )
        );
    }
    template<typename _ClassType,typename _FieldType>
    static inline void _set(Object& object,Object const& field_ptr,Object const& value){
        object.safe_cast<_ClassType&>().*(
            field_ptr.safe_cast<_FieldType _ClassType::*>()
        )=value.safe_cast<::std::remove_cvref_t<_FieldType> const&>();
    }
    Object data_;
    Object(*get_)(Object const& object,Object const& field_ptr);
    void(*set_)(Object& object,Object const& field_ptr,Object const& value);
    Type class_type_;
    Type field_type_;
public:
    inline Field()
        :data_()
        ,get_(nullptr)
        ,set_(nullptr)
        ,class_type_()
        ,field_type_()
    {}
    template<typename _ClassType,typename _FieldType>
    inline Field(_FieldType _ClassType::* field_ptr)
        :Field(){
        this->data_=Object(OBJECT_CTOR_ARG(field_ptr));
        this->get_=this->_get<_ClassType,_FieldType>;
        this->set_=this->_set<_ClassType,_FieldType>;
        this->class_type_=::make_type<_ClassType>();
        this->field_type_=::make_type<_FieldType>();
    }
    inline Object get(Object const& object)const{
        return this->get_(object,this->data_);
    }
    inline void set(Object& object,Object const& value){
        this->set_(object,this->data_,value);
    }
    inline Type const& class_type()const noexcept{
        return this->class_type_;
    }
    inline Type const& field_type()const noexcept{
        return this->field_type_;
    }
};