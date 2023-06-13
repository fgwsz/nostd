#include"type_name.hpp"
#include"static_string.hpp"
template<typename _Condition,typename _TrueRet,typename _FalseRet>
consteval auto if_then_else(){
    if constexpr(_Condition::value){
        return _TrueRet{};
    }else{
        return _FalseRet{};
    }
}
int main(void){
    NOSTD_LOG_TYPE_NAME_OF(if_then_else<::std::true_type,int,double>());
    NOSTD_LOG_TYPE_NAME_OF(if_then_else<::std::false_type,int,double>());
    NOSTD_LOG_TYPE_NAME(::nostd::CStrView<"hello string view">);
    return 0;
}
