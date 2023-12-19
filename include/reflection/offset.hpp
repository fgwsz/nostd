#pragma once
#include<cstddef>
template<typename _ClassType,typename _MemberType>
ptrdiff_t _get_member_offset(
    _ClassType& object,
    _MemberType _ClassType::* member_pointer
){
    return reinterpret_cast<char*>(&(object.*member_pointer))
        -reinterpret_cast<char*>(&object);
}
template<typename _ClassType,typename _MemberType>
ptrdiff_t _get_member_offset_by_nullptr(_MemberType _ClassType::* member_pointer){
    return ::_get_member_offset(
        *reinterpret_cast<_ClassType*>(nullptr),
        member_pointer
    );
}
void* _get_member_ptr(
    void* object_ptr,
    ptrdiff_t member_offset
){
    return reinterpret_cast<void*>(
        reinterpret_cast<char*>(object_ptr)+member_offset
    );
}
template<typename _MemberType,typename _ClassType>
_MemberType& _get_member_ref(
    _ClassType& object,
    ptrdiff_t member_offset
){
    return *reinterpret_cast<_MemberType*>(
        ::_get_member_ptr(reinterpret_cast<void*>(&object),member_offset);
    );
}