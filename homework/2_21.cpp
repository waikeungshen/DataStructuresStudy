/*************************************************************************
    * File Name: 2_21.cpp
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Created Time: 2013年09月25日 星期三 08时58分51秒
 ************************************************************************/

#include<iostream>
#include "head.h"
#include "List.h"
using namespace std;

/*将顺序表就地逆置*/
Status ReserveSqList(SqList &L)
{
    int begin, end;
    ElemType type;
    begin = 0;
    end = L.length - 1;
    while (begin < end)
    {
        type = L.elem[begin];
        L.elem[begin] = L.elem[end];
        L.elem[end] = type;
        begin++;
        end--;
    }
    return OK;
}
