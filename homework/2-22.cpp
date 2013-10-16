/*************************************************************************
    * File Name: 2-22.cpp
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Created Time: 2013年09月25日 星期三 09时18分17秒
 ************************************************************************/

#include<iostream>
#include "head.h"
#include "List.h"
using namespace std;

Status ReserveLinkList(LinkList &L)
{
    if (L == NULL)
        return OK;
    if (L -> next == NULL)
        return OK;
    LNode *pre = NULL;
    LNode *cur = L;
    LNode *next = NULL;
    while (cur != NULL)
    {
        cur -> next = pre;
        pre = cur;
        cut = next;
        next = next -> next;
    }
    return OK;
}
