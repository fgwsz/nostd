#pragma once
enum class TypeCheckID{
    TYPE,
    TYPE_CONST,
    TYPE_VOLATILE,
    TYPE_CONST_VOLATILE,
    TYPE_LVALUE_REFERENCE,
    TYPE_CONST_LVALUE_REFERENCE,
    TYPE_VOLATILE_LVALUE_REFERENCE,
    TYPE_CONST_VOLATILE_LVALUE_REFERENCE,
    TYPE_RVALUE_REFERENCE,
    TYPE_CONST_RVALUE_REFERENCE,
    TYPE_VOLATILE_RVALUE_REFERENCE,
    TYPE_CONST_VOLATILE_RVALUE_REFERENCE
};
template<typename _Type>
struct TypeCheck{
    static constexpr auto id=TypeCheckID::TYPE;
};
template<typename _Type>
struct TypeCheck<_Type const>{
    static constexpr auto id=TypeCheckID::TYPE_CONST;
};
template<typename _Type>
struct TypeCheck<_Type volatile>{
    static constexpr auto id=TypeCheckID::TYPE_VOLATILE;
};
template<typename _Type>
struct TypeCheck<_Type const volatile>{
    static constexpr auto id=TypeCheckID::TYPE_CONST_VOLATILE;
};
template<typename _Type>
struct TypeCheck<_Type&>{
    static constexpr auto id=TypeCheckID::TYPE_LVALUE_REFERENCE;
};
template<typename _Type>
struct TypeCheck<_Type const&>{
    static constexpr auto id=TypeCheckID::TYPE_CONST_LVALUE_REFERENCE;
};
template<typename _Type>
struct TypeCheck<_Type volatile&>{
    static constexpr auto id=TypeCheckID::TYPE_VOLATILE_LVALUE_REFERENCE;
};
template<typename _Type>
struct TypeCheck<_Type const volatile&>{
    static constexpr auto id=TypeCheckID::TYPE_CONST_VOLATILE_LVALUE_REFERENCE;
};
template<typename _Type>
struct TypeCheck<_Type&&>{
    static constexpr auto id=TypeCheckID::TYPE_RVALUE_REFERENCE;
};
template<typename _Type>
struct TypeCheck<_Type const&&>{
    static constexpr auto id=TypeCheckID::TYPE_CONST_RVALUE_REFERENCE;
};
template<typename _Type>
struct TypeCheck<_Type volatile&&>{
    static constexpr auto id=TypeCheckID::TYPE_VOLATILE_RVALUE_REFERENCE;
};
template<typename _Type>
struct TypeCheck<_Type const volatile&&>{
    static constexpr auto id=TypeCheckID::TYPE_CONST_VOLATILE_RVALUE_REFERENCE;
};
template<bool _condition,typename _ResultType>
struct EnableIf;
template<typename _ResultType>
struct EnableIf<true,_ResultType>{
    using type=_ResultType;
};
template<typename _ResultType>
struct EnableIf<false,_ResultType>{
    //using type=void;
};
template<bool _condition,typename _ResultType>
using enable_if_t=typename EnableIf<_condition,_ResultType>::type;
template<typename _Type,TypeCheckID _id>
struct TypeCheckIsSameID{
    static constexpr auto value=TypeCheck<_Type>::id==_id;
};
template<typename _Type,TypeCheckID _id>
static constexpr auto type_check_is_same_id_v=TypeCheckIsSameID<_Type,_id>::value;