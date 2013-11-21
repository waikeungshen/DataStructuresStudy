#include "iostream"
#include "string"
using namespace std;

class SqStack    //使用链表实现栈类
{
private:
	struct Node
	{
		int content;
		char word;
		Node *next;
	}   ;
	Node *top,*base;
public:
	SqStack();
	virtual ~SqStack();
	bool push(char e);
	bool pop(char &e);
	bool StackEmpty();
};

//栈的基本操作
SqStack::SqStack()
{
	top=base=new Node;
}

SqStack::~SqStack()
{

}

bool SqStack::push(char e)    //压栈操作
{
	Node *p=new Node;
	if(p==NULL)
	{
		cout<<"Stack is overflow"<<endl;
		return false;
	}
	else
	{
		p->word=e;
		p->next=top;
		top=p;
		return true;
	}
}

bool SqStack::pop(char &e)    //出栈操作
{   
	if(top==NULL)
	{
		cout<<"Stack is empty"<<endl;
		return false;
	}
	else
	{
		if(top==base)
			return false;
		Node *p=top;
		top=top->next;
		e=p->word;
		delete p;
		return true;
	}
}

bool SqStack::StackEmpty()  //判断是否为空栈
{
	return top==base;
}

class SqQueue    //使用链表实现队列类
{
private:
	struct Node
	{
		int content;
		char word;
		Node *next;
	}   ;
	Node *head,*last;
public:
	SqQueue();
	virtual ~SqQueue();
	bool EnQueue(char e);
	bool DeQueue(char &e);
	bool QueueEmpty();
	void OutQueue();
	void EnQueue_A();
	void EnQueue_B();
};

//队列的基本操作
SqQueue::SqQueue()
{
	head=last=new Node;
}

SqQueue::~SqQueue()
{

}

bool SqQueue::EnQueue(char e)    //入队列
{
	Node *p=new Node;
	if(p==NULL)
	{
		cout<<"Queue is overflow"<<endl;
		return false; 
	}
	else
	{
		p->word=e;
		last->next=p;
		last=p;
		p->next=NULL;
		return true;
	}
}
bool SqQueue::DeQueue(char &e)    //出队列
{
	if(head==NULL)
	{
		cout<<"Queue is empty"<<endl;
		return false;
	}
	else
	{
		Node *p=head;
		head=head->next;
		e=p->word;
		delete p;
		return true;
	}
}

void SqQueue::OutQueue()    //输出队列中的数据
{
	for(Node *p=head->next;p!=NULL;p=p->next)
		cout<<p->word;
	cout<<endl;
}

bool SqQueue::QueueEmpty()
{
	return head==last;
}

void SqQueue::EnQueue_A()
{
	EnQueue('s');
	EnQueue('a');
	EnQueue('e');
}

void SqQueue::EnQueue_B()
{
	EnQueue('t');
	EnQueue_A();
	EnQueue('d');
	EnQueue_A();
}

bool read_language(SqStack &S)        //将魔王语言倒置压入栈中
{
	int i,n,left=0,right=0;
	string m; 
	cout<<"请输入魔王语言:"<<endl;
	cin>>m;
	n=m.length();      //求字符串长度
	for(i=0;i<n;i++)
	{
		if(m[i]=='(')
			left++;
		else if(m[i]==')')
			right++;
	}
	if(left!=right)
		return false;
	for(i=n-1;i>=0;i--)
	{
		S.push(m[i]);
	}
	return true;
}

void push_and_pop(SqStack &S1,SqStack &S2)      //处理规则2
{
	char e,e1;
	SqStack S3;    //栈S3作为进行转换的中间变量
	SqStack();
	while(!S1.StackEmpty())
	{
		S1.pop(e);
		if(e=='(')
		{
			S1.pop(e);
			e1=e;       //e1中保存的就是魔王语言中（右边的第一个字母，就是第二种规则中的θ
			if(e!=')')
				S1.pop(e);
            //将S1括号中的字符逆序存储在S3中
			while(e!=')')
			{
				S3.push(e);      
				S1.pop(e);
			} 
			while(!S3.StackEmpty())
			{
				S2.push(e1);    //根据第二种解释规则，将θ进行多次压栈操作
				S3.pop(e);
				S2.push(e);
			}
			S2.push(e1);
		}
	}
}


int main(void)
{
	char e;
	bool flag;
	SqStack S,S1,S2;
	SqQueue Q;
	SqStack();
	SqQueue();
	flag=read_language(S);     //读入魔王语言
	if(!flag)
	{
		cout<<"括号不匹配，无法解释！"<<endl;
		system("pause");
		return 0;
	}
	while(!S.StackEmpty())//S1为()内的，S2为()外的
	{
		S.pop(e);
		if(e==')')
		{
			S1.push(e);
			//S2.pop(e);
            S.pop(e);
			while(e!='(')
			{
				S1.push(e);
				//S2.pop(e);
                S.pop(e);
			}
			if(e=='(')
				S1.push(e);
			push_and_pop(S1,S2);
		}
		else
			S2.push(e);
	}
   //魔王语言的前面部分在栈S2的底部，后面部分在栈S2的顶部，需要转换一下
	while(!S2.StackEmpty())
	{
		S2.pop(e);
		S.push(e);    //魔王语言的后面部分在栈S的底部，前面部分在栈S的顶部
	}

	//上面的操作进行的是第二种解释规则
	//下面的操作进行的是第一种解释规则
	while(!S.StackEmpty())
	{
		S.pop(e);
		if(e=='A')
			Q.EnQueue_A();
		if(e=='B')
			Q.EnQueue_B();
		else
			Q.EnQueue(e);
	}
	cout<<"魔王语言可以解释为:"<<endl;
	Q.OutQueue();
	system("pause");
	return 0;
}
