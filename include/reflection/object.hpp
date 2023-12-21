#pragma once
#include<type_traits>
#include<functional>
#include<stdexcept>
#include"value.hpp"
#include"reference.hpp"

// 在构造时可选四种不同的底层存储类型:
// T/T const/T&/T const&
// 支持用值类型存储右值T&&，但会退化为值类型T进行存储
// 不支持volatile
// T/T const值类型不支持函数类型ret(arg...)和数组类型type[n]
// T/T const值类型支持函数指针类型ret(*)(arg...)和数组指针类型type(*)[n]
// T&/T const&引用类型支持函数引用类型ret(&)(arg...)和数组引用类型type(&)[n]
// 运行时（构造后非空时）底层存储类型不可变的强类型
class Object{
    template<typename _BaseType>
    static void mval_assign_from_mval(Value& to,Value const& from){
        to.get<_BaseType&>()=from.get<_BaseType const&>();
    }
    template<typename _BaseType>
    static void mval_assign_from_cval(Value& to,Value const& from){
        to.get<_BaseType&>()=from.get<_BaseType const&>();
    }
    template<typename _BaseType>
    static void mval_assign_from_mref(Value& to,Value const& from){
        to.get<_BaseType&>()=from.get<Reference<_BaseType>const&>().get();
    }
    template<typename _BaseType>
    static void mval_assign_from_cref(Value& to,Value const& from){
        to.get<_BaseType&>()=from.get<Reference<_BaseType const>const&>().get();
    }
    template<typename _BaseType>
    static void mref_assign_from_mval(Value& to,Value const& from){
        to.get<Reference<_BaseType>&>().get()=from.get<_BaseType const&>();
    }
    template<typename _BaseType>
    static void mref_assign_from_cval(Value& to,Value const& from){
        to.get<Reference<_BaseType>&>().get()=from.get<_BaseType const&>();
    }
    template<typename _BaseType>
    static void mref_assign_from_mref(Value& to,Value const& from){
        to.get<Reference<_BaseType>&>().get()=from.get<Reference<_BaseType>const&>().get();
    }
    template<typename _BaseType>
    static void mref_assign_from_cref(Value& to,Value const& from){
        to.get<Reference<_BaseType>&>().get()=from.get<Reference<_BaseType const>const&>().get();
    }
    Value data_;
    Type type_;
    Type base_type_;
    void(*mval_assign_from_mval_)(Value&,Value const&);
    void(*mval_assign_from_cval_)(Value&,Value const&);
    void(*mval_assign_from_mref_)(Value&,Value const&);
    void(*mval_assign_from_cref_)(Value&,Value const&);
    void(*mref_assign_from_mval_)(Value&,Value const&);
    void(*mref_assign_from_cval_)(Value&,Value const&);
    void(*mref_assign_from_mref_)(Value&,Value const&);
    void(*mref_assign_from_cref_)(Value&,Value const&);
    enum class Info{
        NIL,
        MVAL,
        CVAL,
        MREF,
        CREF
    } info_;
public:
    inline Object()noexcept
        :data_()
        ,type_()
        ,base_type_()
        ,mval_assign_from_mval_(nullptr)
        ,mval_assign_from_cval_(nullptr)
        ,mval_assign_from_mref_(nullptr)
        ,mval_assign_from_cref_(nullptr)
        ,mref_assign_from_mval_(nullptr)
        ,mref_assign_from_cval_(nullptr)
        ,mref_assign_from_mref_(nullptr)
        ,mref_assign_from_cref_(nullptr)
        ,info_(Info::NIL)
    {}
    // T        -> decay_t<T>
    // T const  -> decay_t<T const>
    // T&       -> remove_cvref_t<T&>
    // T const& -> remove_cvref_t<T const&>
    // T&&      -> remove_cvref_t<T&&>
    template<typename _Type>
    using get_base_type_t=::std::conditional_t<
        ::std::is_reference_v<_Type>,
        ::std::remove_cvref_t<_Type>,
        ::std::decay_t<_Type>
    >;
    template<typename _Type,
        ::std::enable_if_t<!::std::is_const_v<_Type>,int> _=0>
    inline Object(TypeHelper<_Type> place_holder,_Type arg)noexcept
        :Object(){
        // 值类型不支持函数类型ret(arg...)和数组类型type[n]
        using base_type=get_base_type_t<_Type>;
        this->data_=Value(arg);
        this->type_=make_type<base_type>();
        this->base_type_=make_type<base_type>();
        this->mval_assign_from_mval_=this->mval_assign_from_mval<base_type>;
        this->mval_assign_from_cval_=this->mval_assign_from_cval<base_type>;
        this->mval_assign_from_mref_=this->mval_assign_from_mref<base_type>;
        this->mval_assign_from_cref_=this->mval_assign_from_cref<base_type>;
        this->mref_assign_from_mval_=this->mref_assign_from_mval<base_type>;
        this->mref_assign_from_cval_=this->mref_assign_from_cval<base_type>;
        this->mref_assign_from_mref_=this->mref_assign_from_mref<base_type>;
        this->mref_assign_from_cref_=this->mref_assign_from_cref<base_type>;
        this->info_=Info::MVAL;
    }
    template<typename _Type>
    inline Object(TypeHelper<_Type const> place_holder,_Type const arg)noexcept
        :Object(){
        // 值类型不支持函数类型ret(arg...)和数组类型type[n]
        using base_type=get_base_type_t<_Type const>;
        this->data_=Value(arg);
        this->type_=make_type<base_type const>();
        this->base_type_=make_type<base_type>();
        this->mval_assign_from_mval_=this->mval_assign_from_mval<base_type>;
        this->mval_assign_from_cval_=this->mval_assign_from_cval<base_type>;
        this->mval_assign_from_mref_=this->mval_assign_from_mref<base_type>;
        this->mval_assign_from_cref_=this->mval_assign_from_cref<base_type>;
        this->mref_assign_from_mval_=this->mref_assign_from_mval<base_type>;
        this->mref_assign_from_cval_=this->mref_assign_from_cval<base_type>;
        this->mref_assign_from_mref_=this->mref_assign_from_mref<base_type>;
        this->mref_assign_from_cref_=this->mref_assign_from_cref<base_type>;
        this->info_=Info::CVAL;
    }
    template<typename _Type,
        ::std::enable_if_t<!::std::is_const_v<_Type>,int> _=0>
    inline Object(TypeHelper<_Type&> place_holder,_Type& arg)noexcept
        :Object(){
        // 引用类型支持函数引用类型ret(&)(arg...)和数组引用类型type(&)[n]
        using base_type=get_base_type_t<_Type&>;
        this->data_=Value(Reference<base_type>(arg));
        this->type_=make_type<base_type&>();
        this->base_type_=make_type<base_type>();
        this->mval_assign_from_mval_=this->mval_assign_from_mval<base_type>;
        this->mval_assign_from_cval_=this->mval_assign_from_cval<base_type>;
        this->mval_assign_from_mref_=this->mval_assign_from_mref<base_type>;
        this->mval_assign_from_cref_=this->mval_assign_from_cref<base_type>;
        this->mref_assign_from_mval_=this->mref_assign_from_mval<base_type>;
        this->mref_assign_from_cval_=this->mref_assign_from_cval<base_type>;
        this->mref_assign_from_mref_=this->mref_assign_from_mref<base_type>;
        this->mref_assign_from_cref_=this->mref_assign_from_cref<base_type>;
        this->info_=Info::MREF;
    }
    template<typename _Type>
    inline Object(TypeHelper<_Type const&> place_holder,_Type const& arg)noexcept
        :Object(){
        // 常量引用类型支持函数引用类型ret(const&)(arg...)和数组引用类型type(const&)[n]
        using base_type=get_base_type_t<_Type const&>;
        this->data_=Value(Reference<base_type const>(arg));
        this->type_=make_type<base_type const&>();
        this->base_type_=make_type<base_type>();
        this->mval_assign_from_mval_=this->mval_assign_from_mval<base_type>;
        this->mval_assign_from_cval_=this->mval_assign_from_cval<base_type>;
        this->mval_assign_from_mref_=this->mval_assign_from_mref<base_type>;
        this->mval_assign_from_cref_=this->mval_assign_from_cref<base_type>;
        this->mref_assign_from_mval_=this->mref_assign_from_mval<base_type>;
        this->mref_assign_from_cval_=this->mref_assign_from_cval<base_type>;
        this->mref_assign_from_mref_=this->mref_assign_from_mref<base_type>;
        this->mref_assign_from_cref_=this->mref_assign_from_cref<base_type>;
        this->info_=Info::CREF;
    }
    inline constexpr Type const& type()const noexcept{
        return this->type_;
    }
    inline constexpr bool empty()const noexcept{
        return this->info_==Info::NIL;
    }
    inline Object(Object const& obj)noexcept
        :Object(){
        (*this)=obj;
    }
    // from\to |T      |T const |T&      |T const&
    // T       |O      |X       |O       |X        
    // T const |O      |X       |O       |X        
    // T&      |O      |X       |O       |X        
    // T const&|O      |X       |O       |X        
    inline Object& operator=(Object const& obj){
        if(this!=&obj){
            if(this->empty()&&!obj.empty()){
                this->data_=obj.data_;
                this->type_=obj.type_;
                this->base_type_=obj.base_type_;
                this->mval_assign_from_mval_=obj.mval_assign_from_mval_;
                this->mval_assign_from_cval_=obj.mval_assign_from_cval_;
                this->mval_assign_from_mref_=obj.mval_assign_from_mref_;
                this->mval_assign_from_cref_=obj.mval_assign_from_cref_;
                this->mref_assign_from_mval_=obj.mref_assign_from_mval_;
                this->mref_assign_from_cval_=obj.mref_assign_from_cval_;
                this->mref_assign_from_mref_=obj.mref_assign_from_mref_;
                this->mref_assign_from_cref_=obj.mref_assign_from_cref_;
                this->info_=obj.info_;
            }else if(!this->empty()&&obj.empty()){
                throw ::std::runtime_error("Object Assign Error:Object(Not Empty) Assign by Nil");
            }else if(this->base_type_!=obj.base_type_){
                throw ::std::runtime_error("Object Assign Error:Object Base Type Not Equal");
            }else if(this->info_==Info::CVAL||this->info_==Info::CREF){
                throw ::std::runtime_error("Object Assign Error:Object(CVal/CRef) Can't be Assign");
            }else if(this->info_==Info::MVAL&&obj.info_==Info::MVAL){
                this->mval_assign_from_mval_(this->data_,obj.data_);
            }else if(this->info_==Info::MVAL&&obj.info_==Info::CVAL){
                this->mval_assign_from_cval_(this->data_,obj.data_);
            }else if(this->info_==Info::MVAL&&obj.info_==Info::MREF){
                this->mval_assign_from_mref_(this->data_,obj.data_);
            }else if(this->info_==Info::MVAL&&obj.info_==Info::CREF){
                this->mval_assign_from_cref_(this->data_,obj.data_);
            }else if(this->info_==Info::MREF&&obj.info_==Info::MVAL){
                this->mref_assign_from_mval_(this->data_,obj.data_);
            }else if(this->info_==Info::MREF&&obj.info_==Info::CVAL){
                this->mref_assign_from_cval_(this->data_,obj.data_);
            }else if(this->info_==Info::MREF&&obj.info_==Info::MREF){
                this->mref_assign_from_mref_(this->data_,obj.data_);
            }else if(this->info_==Info::MREF&&obj.info_==Info::CREF){
                this->mref_assign_from_cref_(this->data_,obj.data_);
            }
        }
        return *this;
    }
    // from\to |T      |T const |T&      |T const&
    // T       |O      |O       |X       |O        
    // T const |O      |O       |X       |O        
    // T&      |O      |O       |O       |O        
    // T const&|O      |O       |X       |O        
    template<typename _Type>
    inline _Type safe_cast()const{
        if constexpr(::std::is_void_v<_Type>){
            if(this->empty()){
                return;
            }else{
                throw ::std::runtime_error("Value Cast Error:Value Is Not Empty,Can't Cast To Void");
            }
        }
        using base_type=get_base_type_t<_Type>;
        if(make_type<base_type>()!=this->base_type_){
            throw ::std::runtime_error("Object Cast Error:Object Base Type Not Equal");
        }
        if constexpr( // to T
            !::std::is_reference_v<_Type>&&
            ::std::is_convertible_v<base_type,_Type>
        ){
            if(this->info_==Info::MVAL){
                return this->data_.get<base_type const&>();
            }else if(this->info_==Info::CVAL){
                return this->data_.get<base_type const&>();
            }else if(this->info_==Info::MREF){
                return this->data_.get<Reference<base_type>const&>().get();
            }else if(this->info_==Info::CREF){
                return this->data_.get<Reference<base_type const>const&>().get();
            }
        }else if constexpr( // to T const
            !::std::is_reference_v<_Type>&&
            ::std::is_convertible_v<base_type const,_Type>
        ){
            if(this->info_==Info::MVAL){
                return this->data_.get<base_type const&>();
            }else if(this->info_==Info::CVAL){
                return this->data_.get<base_type const&>();
            }else if(this->info_==Info::MREF){
                return this->data_.get<Reference<base_type>const&>().get();
            }else if(this->info_==Info::CREF){
                return this->data_.get<Reference<base_type const>const&>().get();
            }
        }else if constexpr( // to T&
            ::std::is_reference_v<_Type>&&
            !::std::is_const_v<::std::remove_reference_t<_Type>>&&
            ::std::is_convertible_v<base_type&,_Type>
        ){
            if(this->info_==Info::MVAL){
                throw ::std::runtime_error("Object Cast Error:T =X=> T&");
            }else if(this->info_==Info::CVAL){
                throw ::std::runtime_error("Object Cast Error:T const =X=> T&");
            }else if(this->info_==Info::MREF){
                return this->data_.get<Reference<base_type>const&>().get();
            }else if(this->info_==Info::CREF){
                throw ::std::runtime_error("Object Cast Error:T const& =X=> T&");
            }
        }else if constexpr( // to T const&
            ::std::is_reference_v<_Type>&&
            ::std::is_const_v<::std::remove_reference_t<_Type>>&&
            ::std::is_convertible_v<base_type const&,_Type>
        ){
            if(this->info_==Info::MVAL){
                return this->data_.get<base_type const&>();
            }else if(this->info_==Info::CVAL){
                return this->data_.get<base_type const&>();
            }else if(this->info_==Info::MREF){
                return this->data_.get<Reference<base_type>const&>().get();
            }else if(this->info_==Info::CREF){
                return this->data_.get<Reference<base_type const>const&>().get();
            }
        }
        throw ::std::runtime_error("Object Cast Error:_Type Not Match");
    }
    using void_t=void;
    // 空Object对象作为函数返回值返回void时使用
    inline operator void_t()const{
        if(this->empty()){
            return;
        }else{
            throw ::std::runtime_error("Value Cast Error:Value Is Not Empty,Can't Cast To Void");
        }
    }
    // 如下的类型转换函数；
    // 用于Ojbect隐式类型转换到函数参数，请谨慎使用。
    // 安全的类型转换请使用safe_cast函数代替
    // 为什么使用operator _Type&()，而不是operator _Type()?
    // 原因如下：
    // operator _Type(内部处理T/T const/T&/T const&转换)实现的时候，
    // Object obj;
    // foo_1(obj);// foo_1(int num)
        //隐式类型转换调用正常，
        // 类型转换路线是 Object->operator int()->int
    // foo_2(obj);// foo_2(int const num)
        // 隐式类型转换调用正常，
        // 类型转换路线是 Object->operator int()->int->形参赋值->int const
    // foo_3(obj);// foo_3(int& num)
        // 隐式类型转换调用错误，直接是编译错误
        // 类型转换路线是 Object->operator int()->int->形参赋值->int& 编译错误
        // 解决思路是显式调用类型转换函数:foo_3(obj.operator int&());
    // foo_4(obj);
        // foo_4(int const& num)隐式类型转换调用正常
        // 类型转换路线是 Object->operator int()->int->形参赋值->int const&
    // 总结来说，隐式类型转换会根据operator()的函数定义方式来进行模式匹配
        // 只写一个operator _Type()，隐式转换的时候会直接看作 值类型匹配
        // 要隐式转换到的类型(目标类型)被退化成了值类型的类型转换
        // 目标类型从 int        ->int
        // 目标类型从 int const  ->int
        // 目标类型从 int &      ->int
        // 目标类型从 int const& ->int
        // 此时会直接调用operator int()
        // 而不会选择合适的复合类型(int cons/int&/int const&)去调用
        // 然后发生了尝试用int -> int/int const/int&/int const&的二次类型转换
        // 其中int->int&引发了编译错误。
    // 那么此时会有另外一种声音出现：为什么不多写几种不同的类型转换函数来做到精准匹配呢？
    // 原因如下：多写几种不同类型的类型转换，虽然会提高隐式类型转换的匹配度，
    // 但是，会造成一个类型到另一个类型的多路径转换问题，直接引发编译错误。
    // 例如：定义operator _Type()/operator _Type const()/operator _Type&()/operator _Type const&()
        // static_cast<int>(obj);// 编译报错：匹配多个函数模板
    // 那么此时如果想要将Object转换到int类型
    // 编译器有4条路径可走：
        // 1.Object->operator int()->int
        // 2.Object->operator int const()->int const->赋值->int
        // 3.Object->operator int&()->int&->赋值->int
        // 3.Object->operator int const&()->int const&->赋值->int
        // 此时编译器直接编译报错，因为存在多条类型转换路径，编译器无法抉择。
    // 总结：隐式类型转换必须只有一条路径可走，即为只能选择一种形式的函数模板，
    // 那么选择什么形式的operator好呢？
        // C++默认的类型可转换图如下：
        // from\to |T      |T const |T&      |T const&
        // T       |O      |O       |X       |O        
        // T const |O      |O       |X       |O        
        // T&      |O      |O       |O       |O        
        // T const&|O      |O       |X       |O        
    // 不难发现，其中的万金油形式是T&，它可以转换到T/T const/T&/T const&
    // 而其他的三种形式(T/T const/T const&)都无法做到这一点。
    // 因此我们只提供了唯一一种泛型转换函数operator _Type&()。
    // 并实现了Object到X/X const/X&/X const&路径唯一的类型转换策略:
        // Object->T&(T=X)      ->assign->X
        // Object->T&(T=X)      ->assign->X const
        // Object->T&(T=X)      ->X&
        // Object->T&(T=X const)->X const&
    // 其余的疑问：为什么不使用operator _Type&&()这一形式？
        // 因为这一形式在隐式类型转换的时候，不是万能引用，而且只能匹配右值类型。
        // 它和值类型/引用类型的转换路径是完全割裂的。
        // 如果要Object支持转换到右值类型，
        // 可以额外定义一个operator _Type&&()来进行右值类型的转换，
        // 但是如果要将Object转换到右值，会面临Object底层存储对象的失效，
        // 让Object的生命周期难以管理，因此没有提供这一形式的类型转换函数。
    template<typename _Type>
    inline operator _Type&()const{
        using base_type=get_base_type_t<_Type&>;
        if(make_type<base_type>()!=this->base_type_){
            throw ::std::runtime_error("Object Cast Error:Object Base Type Not Equal");
        }
        if constexpr( // to T&->assign->T/T const
            !::std::is_const_v<_Type>&&
            ::std::is_convertible_v<base_type&,_Type&>
        ){
            if(this->info_==Info::MVAL){
                return this->data_.get<base_type&>();
            }else if(this->info_==Info::CVAL){
                return this->data_.get<base_type&>();
            }else if(this->info_==Info::MREF){
                return this->data_.get<Reference<base_type>const&>().get();
            }else if(this->info_==Info::CREF){
                return const_cast<base_type&>(
                    this->data_.get<Reference<base_type const>const&>().get()
                );
            }
        }else if constexpr( // to T const&
            ::std::is_const_v<_Type>&&
            ::std::is_convertible_v<base_type const&,_Type&>
        ){
            if(this->info_==Info::MVAL){
                return this->data_.get<base_type const&>();
            }else if(this->info_==Info::CVAL){
                return this->data_.get<base_type const&>();
            }else if(this->info_==Info::MREF){
                return this->data_.get<Reference<base_type>const&>().get();
            }else if(this->info_==Info::CREF){
                return this->data_.get<Reference<base_type const>const&>().get();
            }
        }
        throw ::std::runtime_error("Object Cast Error:_Type& Not Match");
    }
    template<typename _Type>
    inline _Type get()const{
        return this->safe_cast<_Type>();
    }
    inline constexpr Type const& base_type()const noexcept{
        return this->base_type_;
    }
    inline constexpr bool is_mval()const noexcept{
        return this->info_==Info::MVAL;
    }
    inline constexpr bool is_cval()const noexcept{
        return this->info_==Info::CVAL;
    }
    inline constexpr bool is_mref()const noexcept{
        return this->info_==Info::MREF;
    }
    inline constexpr bool is_cref()const noexcept{
        return this->info_==Info::CREF;
    }
};
// 此宏用于Object类构造函数中传入非Object类的参数时使用
// 使用示例如下：
// int arg;
// Object obj(OBJECT_CTOR_ARG(arg));
// 构建此宏的用意：
// 依据输入参数__arg__的实际类型来选择Object对应的构造函数
// T         -> Object(TypeHelper<T>        ,T         __arg__)
// T const   -> Object(TypeHelper<T const>  ,T const   __arg__)
// T &       -> Object(TypeHelper<T &>      ,T &       __arg__)
// T const & -> Object(TypeHelper<T const &>,T const & __arg__)
// T &&      -> Object(TypeHelper<T>        ,T         __arg__)
#define OBJECT_CTOR_ARG(...) \
    TypeHelper< \
        ::std::conditional_t< \
            ::std::is_rvalue_reference_v<decltype(__VA_ARGS__)>, \
            ::std::remove_cvref_t<decltype(__VA_ARGS__)>, \
            decltype(__VA_ARGS__) \
        > \
    >(),(__VA_ARGS__) \
//

// 放入OBJECT_CTOR_OF宏的第一个参数来选择Object对应的构造函数
// OBJECT_CTOR_FLAG_MVAL -> Object(TypeHelper<T>        ,T         __arg__)
#define OBJECT_CTOR_FLAG_MVAL 
// 放入OBJECT_CTOR_OF宏的第一个参数来选择Object对应的构造函数
// OBJECT_CTOR_FLAG_CVAL -> Object(TypeHelper<T const>  ,T const   __arg__)
#define OBJECT_CTOR_FLAG_CVAL const
// 放入OBJECT_CTOR_OF宏的第一个参数来选择Object对应的构造函数
// OBJECT_CTOR_FLAG_MREF -> Object(TypeHelper<T &>      ,T &       __arg__)
#define OBJECT_CTOR_FLAG_MREF &
// 放入OBJECT_CTOR_OF宏的第一个参数来选择Object对应的构造函数
// OBJECT_CTOR_FLAG_CREF -> Object(TypeHelper<T const &>,T const & __arg__)
#define OBJECT_CTOR_FLAG_CREF const&

// 此宏用于Object类构造函数中传入非Object类的参数时使用
// 使用示例如下：
// int arg_1=100;
// Object obj_1(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_MVAL,arg_1));
// int const arg_2=200;
// Object obj_2(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_CVAL,arg_2));
// int& arg_3=arg_1;
// Object obj_3(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_MREF,arg_3));
// int const& arg_4=arg_2;
// Object obj_4(OBJECT_CTOR_OF(OBJECT_CTOR_FLAG_CREF,arg_4));
// 构建此宏的用意：
// 依据 __object_ctor_flag__ 来选择Object对应的构造函数
// OBJECT_CTOR_FLAG_MVAL -> Object(TypeHelper<T>        ,T         __arg__)
// OBJECT_CTOR_FLAG_CVAL -> Object(TypeHelper<T const>  ,T const   __arg__)
// OBJECT_CTOR_FLAG_MREF -> Object(TypeHelper<T &>      ,T &       __arg__)
// OBJECT_CTOR_FLAG_CREF -> Object(TypeHelper<T const &>,T const & __arg__)
#define OBJECT_CTOR_OF(__object_ctor_flag__,...) \
    TypeHelper< \
        Object::get_base_type_t<decltype(__VA_ARGS__)>__object_ctor_flag__ \
    >(),(__VA_ARGS__) \
//
