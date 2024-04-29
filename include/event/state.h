#pragma once
class State{
public:
    virtual ~State()noexcept
    {}
    //只有在进入该状态的时候执行一次
    virtual void on_entry(void)noexcept
    {}
    //每次事件轮询时执行一次
    virtual void on_execute(void)noexcept
    {}
    //只有在退出该状态的时候执行一次
    virtual void on_exit(void)noexcept
    {}
};
