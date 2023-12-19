#pragma once
template<typename _Type>
class Reference{
    _Type* data_;
public:
    Reference(){
        this->data_=nullptr;
    }
    explicit Reference(_Type& lval_ref){
        this->data_=&lval_ref;
    }
    bool empty()const{
        return this->data_==nullptr;
    }
    Reference(Reference<_Type> const& ref){
        this->data_=ref->data_;
    }
    using reference_type=_Type&;
    operator reference_type()const{
        return *(this->data_);
    }
    void reset(){
        this->data_=nullptr;
    }
    ~Reference(){
        this->reset();
    }
    Reference& operator=(Reference<_Type> const& ref){
        if(this!=&ref){
            if(this->empty()&&!ref.empty()){
                this->data_=ref->data_;
            }else if(!this->empty()&&ref.empty()){
                this->reset();
            }else if(
                reinterpret_cast<char*>(this->data_)
                !=reinterpret_cast<char*>(ref.data_)
            ){
                static_cast<_Type&>(*this)=static_cast<_Type&>(ref);
            }
        }
        return *this;
    }
};