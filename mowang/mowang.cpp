#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#define STACK_INIT_SIZE 100;

typedef struct Node
{
    char data;
    Node *next;
} Node, *QueuePrt;

typedef struct  //队列
{
    QueuePrt front;//队头指针
    QueuePrt rear;  //队尾指针
}SqQueue;

typedef struct  //栈
{
    char *base;//栈低指针
    char *top;//栈顶指针
} SqStack;

//栈的基本操作
void InitStack(SqStack &S)  //构造空栈
{
    S.base = (char*) malloc ( 100 * sizeof(char));
    if (!S.base)
    {
        cout << "分配内存失败！" << endl;
        return;
    }
    S.top = S.base;
}

void push(SqStack &S, char e)   //压入栈
{
    *S.top++ = e;
}

void pop(SqStack &S, char &e)   //弹出栈顶元素
{
    if (S.top == S.base)
    {
        cout << "栈为空" << endl;
        return;
    }
    e = *--S.top;
}

//队列基本操作
void InitSqQueue (SqQueue &Q)
{
    Q.front = Q.rear = (QueuePrt) malloc (sizeof(Node));
    if (!Q.front)
    {
        cout << "分配内存失败" << endl;
        return;
    }
    Q.front->next = NULL;
}

void EnQueue(SqQueue &Q, char e)    //入队列
{
    QueuePrt p;
    p = (QueuePrt) malloc (sizeof(Node));
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
}

void DeQueue(SqQueue &Q, char &e)   //出队列
{
    if (Q.rear == Q.front)
    {
        cout << "空队列" << endl;
        return;
    }
    QueuePrt p;
    p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)
        Q.rear = Q.front;
    free(p);
}

bool readLanguage(SqStack &S)//将魔王语言压入栈
{
    string s;
    int n, i, left=0, right=0;
	cout<<"请输入魔王语言:"<<endl;
    cin >> s;
    n = s.length();//字符串长度
    //判断括号是否匹配
    for (i=0;i<n;i++)
    {
        if (s[i] == '(')
            left++;
        else if (s[i] == ')')
            right++;
    }
    if (left != right)
        return false;
    //压入栈
    for (i = n-1;i>=0;i--)
        push(S,s[i]);
    return true;
}

/*********************************
 *这个函数修改了，基本重写了
 *********************************/
void push_and_pop(SqQueue &Q, SqStack &S2)//处理规则2
{
    char e, ch;
    if (Q.front == Q.rear)
        return;
    ch = Q.rear->data;
    //DeQueue(Q,e);//')'
    while (Q.front->next != Q.rear)
    {
        push(S2,ch);
        DeQueue(Q,e);
        push(S2,e);
    }
    push(S2,ch);
    DeQueue(Q,e);//Q中最后一个弹出,也就是那个特殊的
}

void EnQueue_A(SqQueue &Q)
{
    EnQueue(Q,'s');
    EnQueue(Q,'a');
    EnQueue(Q,'e');
}

void EnQueue_B(SqQueue &Q)
{
    EnQueue(Q, 't');
    EnQueue_A(Q);
    EnQueue(Q, 'd');
    EnQueue_A(Q);
}

//打印
void print(char c)
{
    switch (c)
    {
    case 't':
        cout << "天";
        break;
    case 'd':
        cout << "地";
        break;
    case 's':
        cout << "上";
        break;
    case 'a':
        cout << "一只";
        break;
    case 'e':
        cout << "鹅";
        break;
    case 'z':
        cout << "追";
        break;
    case 'g':
        cout << "赶";
        break;
    case 'x':
        cout << "下";
        break;
    case 'n':
        cout << "蛋";
        break;
    case 'h':
        cout << "恨";
        break;
    }
}

void OutQueue(SqQueue &Q)
{
    for (Node *p = Q.front->next; p!= NULL;p=p->next)
    {
        cout << p->data;
        //print(p->data);
    }
    cout << endl;
}

void DestoryQueue(SqQueue &Q)
{
    while (Q.front)
    {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
}

int main()
{
    SqStack S, S1, S2;
    InitStack(S);
    InitStack(S1);
    InitStack(S2);
    SqQueue Q;
    InitSqQueue(Q);
    char e;
    bool flag = readLanguage(S);
    if (flag == false)
    {
		cout<<"括号不匹配，无法解释！"<<endl;
		return 0;
    }
    while (S.top != S.base)
    {
        pop(S,e);
        if (e ==')')
        {
            //这里有修改
            //EnQueue(Q,e);
            pop(S2,e);
            while (e != '(')
            {
                EnQueue(Q,e);
                pop(S2,e);
            }
            //这里有修改
            //if (e == '(')
                //EnQueue(Q,e);
            push_and_pop(Q,S2);
        }
        else
            push(S2,e);
    }
    while (S2.top != S2.base)
    {
        pop(S2,e);
        push(S,e);
    }
    DestoryQueue(Q);
    InitSqQueue(Q);
    //对规则1操作
    while (S.top != S.base)
    {
        pop(S,e);
        if (e == 'A')
        {
            EnQueue_A(Q);
        }
        else if (e == 'B')
        {
            EnQueue_B(Q);
        }
        else
        {
            EnQueue(Q, e);
        }
    }
	cout<<"魔王语言可以解释为:"<<endl;
    OutQueue(Q);
    DestoryQueue(Q);
    free(S.base);
    free(S1.base);
    free(S2.base);
    return 0;
}
