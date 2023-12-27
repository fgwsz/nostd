#pragma once
#include<cstddef>
template<typename _ClassType,typename _FieldType>
ptrdiff_t _get_field_offset(
    _ClassType& object,
    _FieldType _ClassType::* field_ptr
){
    return reinterpret_cast<char*>(&(object.*field_ptr))
        -reinterpret_cast<char*>(&object);
}
template<typename _ClassType,typename _FieldType>
ptrdiff_t _get_field_offset_by_nullptr(_FieldType _ClassType::* field_ptr){
    return ::_get_field_offset(
        *reinterpret_cast<_ClassType*>(nullptr),
        field_ptr
    );
}
void* _get_field_ptr(
    void* object_ptr,
    ptrdiff_t field_offset
){
    return reinterpret_cast<void*>(
        reinterpret_cast<char*>(object_ptr)+field_offset
    );
}
template<typename _FieldType,typename _ClassType>
_FieldType& _get_field_ref(
    _ClassType& object,
    ptrdiff_t field_offset
){
    return *reinterpret_cast<_FieldType*>(
        ::_get_field_ptr(reinterpret_cast<void*>(&object),field_offset);
    );
}