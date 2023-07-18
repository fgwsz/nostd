#pragma once
// public继承该类获得type域
template<typename _Type>
struct Type{
    using type=_Type;
};
// public继承该类获得value域
template<typename _Type,_Type _value>
struct Value{
    static constexpr _Type value=_value;
};
// is const
template<typename _Type>
struct IsConst:Value<bool,false>{};
template<typename _Type>
struct IsConst<_Type const>:Value<bool,true>{};
template<typename _Type>
static constexpr auto is_const_v=IsConst<_Type>::value;
// is volatile
template<typename _Type>
struct IsVolatile:Value<bool,false>{};
template<typename _Type>
struct IsVolatile<_Type volatile>:Value<bool,true>{};
template<typename _Type>
static constexpr auto is_volatile_v=IsVolatile<_Type>::value;
// is left value reference
template<typename _Type>
struct IsLeftValueReference:Value<bool,false>{};
template<typename _Type>
struct IsLeftValueReference<_Type&>:Value<bool,true>{};
template<typename _Type>
static constexpr auto is_left_value_reference_v=IsLeftValueReference<_Type>::value;
// is right value reference
template<typename _Type>
struct IsRightValueReference:Value<bool,false>{};
template<typename _Type>
struct IsRightValueReference<_Type&&>:Value<bool,true>{};
template<typename _Type>
static constexpr auto is_right_value_reference_v=IsRightValueReference<_Type>::value;
// is unbounded array
template<typename _Type>
struct IsUnboundedArray:Value<bool,false>{};
template<typename _Type>
struct IsUnboundedArray<_Type[]>:Value<bool,true>{};
template<typename _Type>
static constexpr auto is_unbounded_array_v=IsUnboundedArray<_Type>::value;
// is bounded array
template<typename _Type>
struct IsBoundedArray:Value<bool,false>{};
template<typename _Type,unsigned long long _n>
struct IsBoundedArray<_Type[_n]>:Value<bool,true>{};
template<typename _Type>
static constexpr auto is_bounded_array_v=IsBoundedArray<_Type>::value;
// is pointer
template<typename _Type>
struct IsPointer:Value<bool,false>{};
template<typename _Type>
struct IsPointer<_Type*>:Value<bool,true>{};
template<typename _Type>
static constexpr auto is_pointer_v=IsPointer<_Type>::value;
// is member pointer
template<typename _Type>
struct IsMemberPointer:Value<bool,false>{};
template<typename _Type,typename _Class>
struct IsMemberPointer<_Type _Class::*>:Value<bool,true>{};
template<typename _Type>
static constexpr auto is_member_pointer_v=IsMemberPointer<_Type>::value;
// is function
template<typename _Type>
struct IsFunction:Value<bool,false>{};
// result(args...)
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)const>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)volatile>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)const volatile>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)&>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)const&>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)volatile&>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)const volatile&>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)&&>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)const&&>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)volatile&&>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)const volatile&&>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)const noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)volatile noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)const volatile noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)&noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)const&noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)volatile&noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)const volatile&noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)&&noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)const&&noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)volatile&&noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...)const volatile&&noexcept>:Value<bool,true>{};
// result(args...,...)
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)const>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)volatile>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)const volatile>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)&>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)const&>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)volatile&>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)const volatile&>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)&&>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)const&&>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)volatile&&>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)const volatile&&>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)const noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)volatile noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)const volatile noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)&noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)const&noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)volatile&noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)const volatile&noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)&&noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)const&&noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)volatile&&noexcept>:Value<bool,true>{};
template<typename _Ret,typename..._Args>
struct IsFunction<_Ret(_Args...,...)const volatile&&noexcept>:Value<bool,true>{};

template<typename _Type>
static constexpr auto is_function_v=IsFunction<_Type>::value;
// remove const
template<typename _Type>
struct RemoveConst:Type<_Type>{};
template<typename _Type>
struct RemoveConst<_Type const>:Type<_Type>{};
template<typename _Type>
using remove_const_t=typename RemoveConst<_Type>::type;
// remove volatile
template<typename _Type>
struct RemoveVolatile:Type<_Type>{};
template<typename _Type>
struct RemoveVolatile<_Type volatile>:Type<_Type>{};
template<typename _Type>
using remove_volatile_t=typename RemoveVolatile<_Type>::type;
// remove left value reference
template<typename _Type>
struct RemoveLeftValueReference:Type<_Type>{};
template<typename _Type>
struct RemoveLeftValueReference<_Type&>:Type<_Type>{};
template<typename _Type>
using remove_left_value_reference_t=typename RemoveLeftValueReference<_Type>::type;
// remove right value reference
template<typename _Type>
struct RemoveRightValueReference:Type<_Type>{};
template<typename _Type>
struct RemoveRightValueReference<_Type&&>:Type<_Type>{};
template<typename _Type>
using remove_right_value_reference_t=typename RemoveRightValueReference<_Type>::type;
// remove reference
template<typename _Type>
using remove_reference_t=
remove_right_value_reference_t<
    remove_left_value_reference_t<_Type>
>;
// remove const volatile
template<typename _Type>
using remove_cv_t=remove_volatile_t<remove_const_t<_Type>>;
// remove const volatile reference
template<typename _Type>
using remove_cvref_t=remove_cv_t<remove_reference_t<_Type>>;
// remove unbounded array
template<typename _Type>
struct RemoveUnboundedArray:Type<_Type>{};
template<typename _Type>
struct RemoveUnboundedArray<_Type[]>:Type<_Type>{};
template<typename _Type>
using remove_unbounded_array_t=typename RemoveUnboundedArray<_Type>::type;
// remove bounded array
template<typename _Type>
struct RemoveBoundedArray:Type<_Type>{};
template<typename _Type,unsigned long long _n>
struct RemoveBoundedArray<_Type[_n]>:Type<_Type>{};
template<typename _Type>
using remove_bounded_array_t=typename RemoveBoundedArray<_Type>::type;
// remove pointer
template<typename _Type>
struct RemovePointer:Type<_Type>{};
template<typename _Type>
struct RemovePointer<_Type*>:Type<_Type>{};
template<typename _Type>
using remove_pointer_t=typename RemovePointer<_Type>::type;
// remove member pointer
template<typename _Type>
struct RemoveMemberPointer:Type<_Type>{};
template<typename _Type,typename _Class>
struct RemoveMemberPointer<_Type _Class::*>:Type<_Type>{};
template<typename _Type>
using remove_member_pointer_t=typename RemoveMemberPointer<_Type>::type;
// is same
template<typename _Type_1,typename _Type_2>
struct _IsSame:Value<bool,false>{};
template<typename _Type>
struct _IsSame<_Type,_Type>:Value<bool,true>{};
template<typename _Type_1,typename _Type_2>
static constexpr auto is_same_v=
_IsSame<
    remove_cvref_t<_Type_1>,
    remove_cvref_t<_Type_2>
>::value;
