#pragma once
#include"Constant.hpp"
template<bool _value>
using bool_constant=Constant<bool,_value>;
using true_type=bool_constant<true>;
using false_type=bool_constant<false>;
