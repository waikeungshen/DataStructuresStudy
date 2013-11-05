#include <iostream>
#include <cstdlib>
using namespace std;
/*---------------存储结构的定义---------------*/
//车的定义
typedef struct
{
    int licensePlate;//牌照
    int time;//进入停车场时间
    int number;//位置编号
}car;

//栈的定义
typedef struct
{
    car *base;//栈低指针
    car *top;//栈顶指针
    int stacksize;//当前以分配的存储空间
}SqStack;

//队列的定义
typedef struct QNode
{
    car data;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
    QueuePtr front;//队头指针
    QueuePtr rear;//队尾指针
}LinkQueue;

/*---------------基本操作---------------------*/
//创建一个空栈
void InitStack(SqStack &S, int n)
{
    S.base = (car *) malloc (n * sizeof(car));
    S.top = S.base;
    S.stacksize = n;
}

//入栈
void Push(SqStack &S, car e)
{
    if (S.top - S.base <= S.stacksize)
        *S.top++ = e;
    else
        cout << "停车场停车位已满" << endl;
}

//出栈
void Pop(SqStack &S, car &e)
{
    if (S.top != S.base)
    {
        e = *--S.top;
    }
    else
        cout << "停车场未停车" << endl;
}

//判断栈是否为空
bool StackEmpty(SqStack &S)
{
    if (S.base == S.top)
        return true;
    else
        return false;
}

//创建一个空队列
void InitQueue(LinkQueue &Q)
{
    Q.front = Q.rear = (QueuePtr) malloc (sizeof(QNode));
    Q.front->next = NULL;
}

//入队
void EnQueue (LinkQueue &Q, car e)
{
    QueuePtr p = (QueuePtr) malloc (sizeof(QNode));
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
}

//出队
void DeQueue (LinkQueue &Q, car &e)
{
    QueuePtr p;
    if (Q.front != Q.rear)
    {
        p = Q.front->next;
        e = p->data;
        Q.front->next = p->next;
        if (Q.rear == p)
            Q.rear = Q.front;
        free(p);
    }
    else
        cout << "通道为空" << endl;
}

//将队列元素中的number减1
void QueueNum(LinkQueue &Q)
{
    if (Q.front == Q.rear)
        return;
    QueuePtr p;
    p = Q.front->next;
    while (p != Q.rear)
    {
        p->data.number--;
        p = p->next;
    }
    p->data.number--;
}
//统计队列中的元素个数
/*int QueueNumber(LinkQueue &Q)
{
    QueuePtr p = Q.front->next;
    int num = 0;
    if (Q.front == Q.rear)
        return 0;
    while (p != Q.rear)
    {
        num++;
        p = p->next;
    }
    num++;
    return num;

}*/

/*---------------开始操作--------------------*/
SqStack Into;//停车场栈
SqStack Temp;//临时停车栈
LinkQueue Gallery;//通道队列
int QueueNumber = 0;

void IntoPark(int licensePlate, int time)
{
    car e;
    e.licensePlate = licensePlate;
    e.time = time;
    if (Into.top - Into.base < Into.stacksize)//如果停车位未满
    {
        e.number = Into.top - Into.base + 1;
        Push(Into, e);//压入停车场栈
        cout << "车牌号：" << e.licensePlate << endl;
        cout << "停在停车场的位置：" << e.number<<  endl;
    }
    else
    {
        e.number = ++QueueNumber;
        EnQueue(Gallery, e);//进入队列
        cout << "车牌号：" << e.licensePlate << endl;
        cout << "停在通道的位置：" << e.number << endl;
    }
}

void OutPark(int licensePlate, int time)
{
   car e;
   do
   {
       Pop (Into, e);
       if (e.licensePlate != licensePlate)//不是要出停车场的车
       {
           Push(Temp, e);//压入临时停车栈
       }
       if (StackEmpty(Into) == true)
           break;
   } while (e.licensePlate != licensePlate);
   if (e.licensePlate == licensePlate)
   {
       cout << "车牌号:" << e.licensePlate << endl;
       cout << "进入停车场时间:" << e.time << endl;
       cout << "开出停车场时间:" << time << endl;
       cout << "费用：" << (time - e.time) * 10 << endl;
   }
   while (Temp.top != Temp.base)//将临时停车栈的车开回停车场
   {
       Pop(Temp, e);//弹出临时停车栈的车
       e.number = Into.top - Into.base + 1;
       Push(Into, e);//压入停车场栈
   }
   if (Gallery.front != Gallery.rear)//通道中还有车
   {
       DeQueue(Gallery, e);
       QueueNumber--;
       QueueNum(Gallery);//编号减1
       e.number = Into.top - Into.base + 1;
       e.time = time;
       Push(Into, e);

   }
}

void start(int n)
{
    char AorD;
    int licensePlate;//牌照
    int time;
    InitStack(Into, n);
    InitStack(Temp, n);
    InitQueue(Gallery);
    do
    {
        cin >> AorD;
        cin >> licensePlate;
        cin >> time;
        if (AorD == 'A')
        {
            IntoPark(licensePlate, time);
        }
        else if (AorD == 'D')
        {
            OutPark(licensePlate, time);
        }
    }while(AorD != 'E');
}

int main()
{
    int n;
    cout << "输入停车场可停放车的数量n:";
    cin >> n;
    start(n);
    return 0;
}
