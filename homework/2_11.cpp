/*************************************************************************
    * File Name: 2_11.cpp
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Created Time: 2013年09月25日 星期三 08时31分02秒
 ************************************************************************/

#include<iostream>
#include "List.h"
#include "Head.h"
using namespace std;
/*顺序表va中的数据元素递增有序,将x插入到顺序表的适当位置，以保持该表的有序性*/
Status InsertX (SqList &va, ElemType x)
{
    if (va.length >= va.listsize)//当前存储空间已满，增加分配内存
    {
        SqList *newbase = (ElemType *) realloc (va.elem, (va.listsize + LISTINCREMENT) * sizeof (ElemType));
        if (! newbase)
            exit(OVERFLOW);//存储空间分配失败
        va.elem = newbase;
        va.listsize += LISTINCREMENT;
    }
    int i;
    for (i = 0; i < length; i++)
    {
        if (va.elem[i] <= x && va.elem[i+1] > x)//找到要插入的位置
            break;
    }
    ElemType *q = &va.elem[i+1];//记录要插入的位置
    ElemType *p = &va.elem[va.length-1];
    for (p; p >= q; --p)
        *(p+1) = *p;//插入位置及之后的元素右移
    *q = x;//插入x
    ++va.length;//表长加1
    return OK;
}
