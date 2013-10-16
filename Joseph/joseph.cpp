#include <iostream>
#include <cstdlib>
#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2
using namespace std;
typedef int Status;
//Joseph环里的人的抽象类型
typedef struct LNode
{
    int num;
    int pwd;
    struct LNode *next;
}LNode, *LinkList;

//创建一个线性表
Status CreatList(LinkList &L, int n)
{
    LinkList p, temp;
    int i;
    cout << "intput the passwords:" << endl;
    L = (LinkList) malloc (sizeof(LNode));//创建第一个节点
    L->num = 1;
    cin >> L->pwd;//输入第一个密码
    temp = L;
    //创建剩下的节点
    for (i = 2; i <= n; i++)
    {
        p = (LinkList) malloc (sizeof(LNode));//创建一个新节点
        p->num = i;
        cin >> p->pwd;
        temp->next = p;
        temp = p;
    }
    temp->next = L;//形成循环链表
    L = temp;
    return OK;
}

//删除一个节点
Status DeletePerson(LNode *pre, LNode *del)
{
    pre->next = del->next;
    free(del);
    return OK;
}

Status Joseph(LinkList &L, int m)
{
    LinkList pre, del;
    del = NULL;//欲删除的节点
    pre = L;//L的前驱节点
    L = pre->next;
    //处理ｍ，知道最后一个节点
    while (pre != L)
    {
        while ((m--) != 1)
        {
            L = L->next;
            pre = pre->next;
        }
        del = L;
        m = del->pwd;
        cout << del->num << " ";
        L = L->next;
        DeletePerson(pre,del);
    }
    //最后一个节点
    cout << L->num << endl;
    free(L);
    return OK;
}

int main()
{
    LinkList L;
    int n, m;
    cout << "the number of person:";
    cin >> n;
    cout << "input m:";
    cin >> m;
    CreatList(L, n);
    cout << "出列顺序：" << endl;
    Joseph(L, m);
    return 0;
}
