#include"type_name.hpp"
#include"c_str_view.hpp"
#include"meta_name.hpp"
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
    NOSTD_LOG_TYPE_NAME(::nostd::c_str_view_concat_t<
        ::nostd::CStrView<"hello">,
        ::nostd::CStrView<" world">,
        ::nostd::CStrView<" !!!">
    >);
    return 0;
}
