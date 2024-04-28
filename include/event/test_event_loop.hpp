#pragma once
#include<iostream>
#include"event_loop.hpp"
//-message_0->callback_0-message_1->callback_1-message_2->callback_2
static void callback_0(message_t const& msg){
    if(msg=="message_0"){
        ::std::cout<<"Execute callback_0.\n";
        message_publish("message_1");
        ::std::cout<<"Publish message_1.\n";
    }
}
static void callback_1(message_t const& msg){
    if(msg=="message_1"){
        ::std::cout<<"Execute callback_1.\n";
        message_publish("message_2");
        ::std::cout<<"Publish message_2.\n";
    }
}
static void callback_2(message_t const& msg){
    if(msg=="message_2"){
        ::std::cout<<"Execute callback_2.\n";
    }
}
void test_event_loop(void)noexcept{
    callback_regist(callback_0);
    callback_regist(callback_1);
    callback_regist(callback_2);
    message_publish("message_0");
    ::std::cout<<"Publish message_0.\n";
    event_loop();
}
