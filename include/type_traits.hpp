#pragma once
template<typename _Type>
struct IsConst{
    static constexpr auto value=false;
};
template<typename _Type>
struct IsConst<_Type const>{
    static constexpr auto value=true;
};
template<typename _Type>
static constexpr auto is_const_v=IsConst<_Type>::value;

template<typename _Type>
struct IsVolatile{
    static constexpr auto value=false;
};
template<typename _Type>
struct IsVolatile<_Type volatile>{
    static constexpr auto value=true;
};
template<typename _Type>
static constexpr auto is_volatile_v=IsVolatile<_Type>::value;

template<typename _Type>
struct IsLeftValueReference{
    static constexpr auto value=false;
};
template<typename _Type>
struct IsLeftValueReference<_Type&>{
    static constexpr auto value=true;
};
template<typename _Type>
static constexpr auto is_left_value_reference_v=IsLeftValueReference<_Type>::value;

template<typename _Type>
struct IsRightValueReference{
    static constexpr auto value=false;
};
template<typename _Type>
struct IsRightValueReference<_Type&&>{
    static constexpr auto value=true;
};
template<typename _Type>
static constexpr auto is_right_value_reference_v=IsRightValueReference<_Type>::value;

template<typename _Type>
struct RemoveConst{
    using type=_Type;
};
template<typename _Type>
struct RemoveConst<_Type const>{
    using type=_Type;
};
template<typename _Type>
using remove_const_t=typename RemoveConst<_Type>::type;

template<typename _Type>
struct RemoveVolatile{
    using type=_Type;
};
template<typename _Type>
struct RemoveVolatile<_Type volatile>{
    using type=_Type;
};
template<typename _Type>
using remove_volatile_t=typename RemoveVolatile<_Type>::type;

template<typename _Type>
struct RemoveLeftValueReference{
    using type=_Type;
};
template<typename _Type>
struct RemoveLeftValueReference<_Type&>{
    using type=_Type;
};
template<typename _Type>
using remove_left_value_reference_t=typename RemoveLeftValueReference<_Type>::type;

template<typename _Type>
struct RemoveRightValueReference{
    using type=_Type;
};
template<typename _Type>
struct RemoveRightValueReference<_Type&&>{
    using type=_Type;
};
template<typename _Type>
using remove_right_value_reference_t=typename RemoveRightValueReference<_Type>::type;

template<typename _Type>
using remove_reference_t=
remove_right_value_reference_t<
    remove_left_value_reference_t<_Type>
>;

template<typename _Type>
using remove_cv_t=remove_volatile_t<remove_const_t<_Type>>;

template<typename _Type>
using remove_cvref_t=remove_cv_t<remove_reference_t<_Type>>;

template<typename _Type_1,typename _Type_2>
struct IsSame{
    static constexpr auto value=false;
};
template<typename _Type>
struct IsSame<_Type,_Type>{
    static constexpr auto value=true;
};
template<typename _Type_1,typename _Type_2>
static constexpr auto is_same_v=
IsSame<
    remove_cvref_t<_Type_1>,
    remove_cvref_t<_Type_2>
>::value;
