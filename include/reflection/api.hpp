#include<string_view>
#include<vector>
#include<any>
namespace reflection{
using string=::std::string_view;
template<typename _Type>
using vector=::std::vector<_Type>;
using any=::std::any;
class Method;
class Field;
class Constructor;
class Class {
public:
    string get_name() const;
    vector<Method> get_methods() const;
    vector<Field> get_fields() const;
    vector<Constructor> get_constructors() const;
    Method get_method(string method_name)const;
    Field get_field(string field_name)const;
    Constructor get_constructor(string constructor_name)const;
};
class Type{
public:
    string get_name() const;
    void set_name(string name);
};
class Object{
public:
    Object();
    template<typename _Type>
    Object(_Type&&);
    Object(Object const&);
    Object& operator=(Object const&);
};
class Method {
public:
    string get_class_name() const;
    string get_name() const;
    Type get_return_type() const;
    vector<Type> get_parameter_types() const;
    Object invoke(Object self, vector<Object> args);
};
class Field {
public:
    string get_class_name() const;
    string get_name() const;
    Type get_type() const;
    void set_value(Object self, Object value);
    Object get_value(Object self);
};
class Constructor {
public:
    string get_class_name() const;
    string get_name() const;
    string get_return_type() const;
    vector<Type> get_parameter_types() const;
    Object invoke(vector<Object> args);
};
class Manger{
public:
    static Class get_class(string class_name);
    static Method get_method(string class_name,string method_name);
    static Field get_field(string class_name,string field_name);
    static Constructor get_constructor(string class_name,string constructor_name);
};
class Register{
public:
    static void regist_class(string class_name,Type type);
    static void regist_method(string class_name,string method_name,Type type);
    static void regist_field(string class_name,string field_name,Type type);
    static void regist_constructor(string class_name,string constructor_name,Type type);
};
void test_api(){
    Class my_class = Manger::get_class("MyClass"); // 获取类信息
    vector<Method> methods = my_class.get_methods(); // 获取类的方法名列表
    Method my_method = Manger::get_method("MyClass", "my_method"); // 获取方法信息
    Constructor my_ctor = Manger::get_constructor("MyClass", "my_ctor(int,double)"); // 获取方法信息
    Object my_object=my_ctor.invoke({0,3.14});
    Object arg1,arg2;
    my_method.invoke(my_object,{arg1, arg2}); // 调用方法
    Field my_field = Manger::get_field("MyClass", "my_field"); // 获取属性信息
    my_field.set_value(my_object, {}); // 设置属性值
}
} // namespace reflection end
// 一个非常实际的问题：就是如何存储元信息呢？
// 元信息怎么组织，又使用什么数据结构来存储，什么数据结构来优化查询效率。
// 首先就是一个类，要有类型
// 通过类型到类元信息的单向映射，可以得到类元信息的内容。
// map<Type,ClassMetaInfo> 存储Type->ClassMetaInfo的映射关系
// 其次我们要关注一下ClassMetaInfo包含哪些内容？
// 最简单最直接的就是类成员变量/函数。
// 其中类成员变量可能需要记录一下类型信息和类成员变量偏移地址。
// FieldMetaInof{Type type_;size_t offset_;};
// 接下来就是类成员函数需要记录的元信息。
// MethodMetaInfo{Type return_type_;Type[] parameter_list_;size_t offset_;}
// 接下俩就是构造函数需要记录的元信息。
// ConstructorMetaInfo{Type[] parameter_list_;size_t}