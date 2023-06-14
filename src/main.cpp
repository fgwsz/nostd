#include"type_name.hpp"
#include"c_str_view.hpp"
#include"person.hpp"
#include<unordered_map>
#include<any>
#include<functional>
using person_name_t=
nostd::Field<
    ::nostd::CStrView<"Person">,
    ::nostd::CStrView<"name">,
    &Person::name
>;
struct FieldInfo{
    ::std::string class_name;
    ::std::string field_name;
    ::std::string_view class_type;
    ::std::string_view field_type;
    ::std::any field_pointer;
};
struct ClassInfo{
    ::std::string class_name;
    ::std::string_view class_type;
    ::std::unordered_map<::std::string,FieldInfo> field_info;
    ::std::function<::std::any(::std::vector<::std::any>)> ctor;
    ::std::function<void(::std::any&)> dtor;
    ::std::function<::std::any(::std::any const&)> clone;
    ::std::function<void(::std::any&,::std::any const&)> assign;
    ::std::function<void(::std::any&,::std::any&)> swap;
    ::std::function<int(::std::any const&,::std::any const&)> compare;
};
::std::unordered_map<::std::string,ClassInfo> class_info;

int main(void){
    NOSTD_STATIC_REFLECT_TYPE(::nostd::CStrView<"Person">) person;
    NOSTD_LOG_TYPE_NAME_OF(person);
    return 0;
}
