#pragma once
#include<string_view>//::std::string_view
#include"state.h"//State

class StateManger{
public:
    using state_name_t=::std::string_view;
    static bool regist(
        state_name_t const& state_name,
        State const& state
    )noexcept;
    static bool unregist(
        state_name_t const& state_name
    )noexcept;
    static state_name_t get_current_state_name()noexcept;
    static bool set_current_state(
        state_name_t const& state_name
    )noexcept;
};
