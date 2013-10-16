#include <stdio.h>
#define LIST_INIT_SIZE 100  //线性表存储空间的初始分配量
#define LISTINCREMENT 10    //线性表存储空间的分配增量

#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2
typedef int Status;

typedef struct SqList
{
    ElemType *elem; //存储空间的基址
    int length;     //当前长度
    int listsize;   //当前分配的存储容量（以sizeof(ElemType)为单位）
};

//构建一个空的线性表L
Status InitList_Sq(SqList &L)
{
    L.elem = (ElemType *) malloc (LIST_INIT_SIZE * sizeof(ElemType));
    if (! L.elem) 
        exit(OVERFLOW);//存储分配失败
    L.length = 0;//空表长度为0
    L.listsize = LIST_INIT_SIZE;//初始存储容量
    return OK;
}

//在顺序线性表L中第i个位置之前插入新的元素e
Status ListInsetr_Sq(SqList &L, int i, ElemType e)
{
    if (i < 1 || i > L.length + 1)
        return ERROR;//i的值不合法
    if (L.length >= L.listsize)
    {
        SqList *newbase = (ElemType *) realloc (L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            exit(ERROR);
        L.elem = newbase;//新基址
        L.listsize += LISTINCREMENT;//增加存储容量
    }
    ElemType *q = &(L.elem[i - 1]);
    for (p = &(L.elem[L.length - 1]); p >= q; --p)
        *(p+1) = *p;//插入位置之后的元素右移
    *q = e;
    ++L.length;
    return OK;
}

//在顺序线性表L中删除第i个元素，并用e返回其值
Status ListDelete_Sq(SqList &L, int i, ElemType &e)
{
    if (i < 1 || i > L.length)
        return ERROR;
    ElemType *p = L.elem[i-1];//p为被删除元素的位置
    e = *p;
    ElemType *q = L.elem + L.length - 1;//表尾元素的位置
    for (++p; p <= q; ++p)
        *(p-1) = *p;//被删除元素之后的元素左移
    --L.length;
    return OK;
}

//在顺序线性表L中查找第1个值与e满足compare()的元素的位序
int LocateElem_Sq(SqList L, ElemType e, compare(ElemType, ElemType))
{
    int i = 1;
    ElemType *p = L.elem;
    while (i <= L.length && ! (*compare)(*p++, e)
            ++i;
    if (i <= L.length)
        return i;
    else
        return 0;
}

//销毁线性表L
void DestroyList(SqList &L)
{

}

//将线性表重置为空表
Status ClearList(SqList &L)
{
    L.length = 0;
    return OK;
}

//判断线性表是否为空
Status ListEmpty(SqList L)
{
    if (L.length == 0)
        return TRUE;
    else
        return FALSE;
}

//返回顺序线性表L中第i个元素的数据
Status GetElem(SqList L, int i, ElemType &e)
{
    if (i < 1 || i > L.length)
        return ERROR;
    e = L.elem[i-1];
    return OK;
}

int main()
{

    return 0;
}
