/*************************************************************************
    * File Name: List.h
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Created Time: 2013年09月25日 星期三 08时22分02秒
 ************************************************************************/

/*存储结构*/
#define LIST_INTI_SIZE 100
#define LISTINCREMENT 10
typedef struct
{
    ElemType *elem;//存储空间基址
    int length;//当前长度
    int listsize;//当前分配的存储容量
}SqList;//顺序表类型

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;//线性链表类型
