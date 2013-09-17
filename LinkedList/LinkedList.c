/*************************************************************************
    * File Name: LinkedList.c
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Created Time: 2013年09月16日 星期一 16时37分22秒
 ************************************************************************/

#include<stdio.h>

struct student
{
    char name[10];
    float score;
    struct student *next;
};

/*定义创建链表函数create*/
struct student *create(int n)
{
    struct student *head, *pnew, *ptail;
    int i;
    pnew = (struct student*) malloc (sizeof(struct student));
    scanf("%s%f",pnew->name, &pnew->score);
    head = pnew;
    ptail = pnew;//建立头节点
    for (i = 1; i < n; i++)//建立其他n-1个节点
    {
        pnew = (struct student *) malloc (sizeof(struct student));
        scanf("%s%f", pnew->name, &pnew->score);
        ptail->next = pnew;
        ptail = pnew;
    }
    ptail->next = NULL;
    return head;
}

/*遍历链表*/
void print(struct student *head)
{
    struct student *p = head;
    while (p != NULL)
    {
        printf("%s %.1f\n",p->name, p->score);
        p = p->next;
    }
}

/*定义在有序链表中插入一个节点，使链表按score成员从大到小排列节点*/
struct student *insert(struct student *head)
{
    struct student *p, *pnew, *pold;
    pnew = (struct student *) malloc (sizeof(struct student));
    scanf("%s%f",pnew->name,&pnew->score);
    p = head;
    if (pnew->score > head->score)//插入在头节点前
    {
        pnew->next = head;
        head = pnew;
    }
    else
    {
        while(p != NULL && pnew->score < p->score)//确定插入位置
        {
            pold = p;
            p = p->next;
        }
        pnew->next = p;
        pold->next = pnew;
    }
    return head;
}

/*定义在列表中删除所有成员score值大于等于grade值的节点*/
struct student *pdelete(struct student *head, int grade)
{
    struct student *p, *pold;
    //删除满足指定条件的链表头部的连续若干节点
    p = head;
    while (head != NULL && head->score >= grade)
    {
        head = head->next;
        free(p);
        p = head;
    }
    if(head == NULL) 
        return head;
    //删除满足指定条件的链表中的若干节点
    p = head->next;
    pold = head;
    while(p != NULL)
    {
        if(p->score >= grade)
        {
            pold->next = p->next;
            free(p);
            p = pold->next;
        }
        else
        {
            pold = p;
            p = p->next;
        }
    }
    return head;
}

int main()
{
    int n;
    struct student *head;
    printf("Input the number of nodes:\n");
    scanf("%d",&n);
    printf("Input nodes:\n");
    head = create(n);
    printf("Output:\n");
    print(head);
    return 0;
}
