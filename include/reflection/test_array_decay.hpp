#pragma once
#include<utility>
int _num;
int _arr_0[]={_num};
int _arr_1[1]={_num};
// int&  _arr_2[] ={_num};
// int&  _arr_3[1]={_num};
// int&& _arr_4[] ={::std::move(_num)};
// int&& _arr_5[1]={::std::move(_num)};
// 描述一下自己遇到的问题：
// 如何把一个函数类型把参数列表转化为::std::tuple的模板参数