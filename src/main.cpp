#include<iostream>
#include"meta.hpp"
int main(void){
    typename meta::Invoke<
        typename meta::Invoke<
            meta::Template<meta::IF>,
            meta::True,
            meta::Template<meta::IF>,
            meta::Template<meta::DoNothing>
        >::Type,
        meta::True,
        int,
        double
    >::Type a;
    ::std::cout<<"typeof(a)="<<typeid(a).name()<<::std::endl;
    ::std::system("pause");
    return 0;
}
