#pragma once
#include<string>//::std::string
#include<queue>//::std::queue
#include<vector>//::std::vector
#include<functional>//::std::function

using message_t=::std::string;
using callback_t=::std::function<void(message_t const&)>;
static ::std::queue<message_t> message_queue;
static ::std::queue<message_t> message_publish_queue;
static ::std::vector<callback_t> callback_list;
static ::std::vector<callback_t> callback_regist_list;
void execute_callbacks(message_t const& message)noexcept{
    for(auto const& callback:callback_list){
        callback(message);
    }
}
void update_callback_list()noexcept{
    if(!callback_regist_list.empty()){
        callback_list.insert(
            callback_list.cend(),
            callback_regist_list.cbegin(),
            callback_regist_list.cend()
        );
        callback_regist_list.clear();
    }
}
void update_message_queue()noexcept{
    while(!message_publish_queue.empty()){
        message_queue.push(message_publish_queue.front());
        message_publish_queue.pop();
    }
}
void event_loop(void)noexcept{
    while(true){
        update_message_queue();
        if(message_queue.empty()){
            break;
        }
        update_callback_list();
        execute_callbacks(message_queue.front());
        message_queue.pop();
    }
}
void message_publish(message_t const& message)noexcept{
    message_publish_queue.push(message);
}
void callback_regist(callback_t const& callback)noexcept{
    callback_regist_list.push_back(callback);
}
