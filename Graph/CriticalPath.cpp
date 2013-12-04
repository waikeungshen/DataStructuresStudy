/*************************************************************************
    * File Name: CriticalPath.cpp
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Created Time: 2013年12月03日 星期二 20时25分35秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<stack>
#include<iomanip>
using namespace std;

const int MAX_VEX_NUM=20;  
int ve[20];//全局变量,存放各个事件的最早发生时间  
  
class ArcNode //表结点  
{  
public:  
    int adjvex;  
    int info;//权值  
    ArcNode *nextarc;  
};  
  
class VNode //头结点  
{  
public:  
    string data;  
    int indegree; //顶点的入度  
    ArcNode *firstarc;  
};  
  
class ALGraph   
{  
private:  
    VNode vertices[MAX_VEX_NUM];  
    int arcnum;  
    int vexnum;  
public:  
    void Create_ALG()  
    {  
        //构造有向网,邻接表存储       
        string v1,v2;  
        int i,j,w;  
        ArcNode *p=NULL;  
  
        cout<<"输入顶点数和边数：";  
        cin>>vexnum>>arcnum;  
  
        cout<<"输入顶点名称：";  
        for(i=0;i<vexnum;i++)  
        {  
            cin>>vertices[i].data;  
            vertices[i].firstarc=NULL;  
            vertices[i].indegree=0;  
        }  
  
        for(int k=0;k<arcnum;k++)  
        {  
            cout<<"按照尾->头的顺序输入每条边对应的两个顶点和该边的权值：";  
            cin>>v1>>v2>>w;  
            i=Locate_Vex(v1);  
            j=Locate_Vex(v2);  
  
            while(i==-1 || j==-1)  
            {  
                cout<<"输入的顶点错误，重新输入：";  
                cin>>v1>>v2;  
                i=Locate_Vex(v1);  
                j=Locate_Vex(v2);  
            }  
  
            p=new ArcNode;  
            p->adjvex=j;  
            p->info=w;  
            p->nextarc=vertices[i].firstarc;  
            vertices[i].firstarc=p;  
            vertices[j].indegree+=1; //作为有向弧的头的顶点入度加1  
        }  
  
        cout<<"有向网构造完成"<<endl;  
    }  
  
    int Locate_Vex(string v) //求顶点在顶点数组中的位置  
    {  
        int k;
        for(k=0;k<vexnum && vertices[k].data!=v;k++);  
        if(k<vexnum)  
            return k;  
        else  
            return -1;  
    }  
                                /*关键路径求解思想*/  
            /*--------------------------------------------------------------- 
            / 辨别关键路径就是要找出l(i)=e(i)的活动，为了求AOE网中的e(i)和l(i) 
            / 首先应该求出每个事件的最早发生时间ve(j)和最晚发生时间vl(j),如果 
            / 活动ai用弧<j,k>表示,那么持续时间记为dut(<j,k>).则有如下关系： 
            / e(i)=ve(j),   l(i)=vl(k)-dut(<j,k>); 
            / 求事件的vj的最早发生时间ve(j)和最迟发生时间vl(j)要分两步进行： 
            / (1):从ve(0)=0(假设顶点0是开始点)开始，根据下面公式计算其它事件 
            / 的最早开始时间： ve(j)=Max{ve(i)+dut(<i,j>)} 其中i是j的所有直接前驱的集合 
            / (2)从vl(n-1)=ve(n-1)开始，根据下面公式计算其他事件的最晚开始时间： 
            / vl(i)=Min{vl(j)-dut(<i,j>)} 其中j是i的直接后继的集合 
            / 上述两个公式必须分别在拓扑有序和逆拓扑有序的前提下进行，也就是说ve(j-1) 
            / 必须在vj全部直接前驱的最早发生时间都求得以后才能确定。而vl(j-1)则必须在 
            / vj的所有直接后继的最晚发生时间求得之后才能确定，因此可以在拓扑排序的基础 
            / 上计算所有事件的ve(j-1)和vl(j-1). 
            / 为了能按逆拓扑有序序列的顺序计算各个顶点的vl值，需记下在拓扑排序的过程中 
            / 求得的拓扑有序序列，这只需要增加多一个栈，用来存储拓扑有序序列即可. 
            / 由于栈的结构特点，拓扑有序序列出栈就变成逆拓扑有序序列了. 
            /----------------------------------------------------------------*/  
  
    //求所有事件的最早发生时间  
    bool Topo_Order(stack<int> &T)  
    {  
        stack<int> s;  
        ArcNode *p=NULL;  
        //将入度不为0的事件压入栈,入度为0的点，最早发生时间就为0
        int i;
        for(i=0;i<vexnum;i++)  
            if(!vertices[i].indegree)  
                s.push(i);  
        int count=0;  
        for(i=0;i<vexnum;i++)  
            ve[i]=0; //设各顶点最早发生为0  
        while(!s.empty())  
        {  
            int k=s.top();  
            s.pop();  
            T.push(k);  
            count++;  
            for(p=vertices[k].firstarc;p;p=p->nextarc)  
            {  
                int w=p->adjvex;  
                if(vertices[w].indegree)  
                    vertices[w].indegree--;  
                if(!vertices[w].indegree)  
                    s.push(w);  
                if(ve[k]+p->info>ve[w]) //求ve[w]的最早发生时间  
                    ve[w]=ve[k]+p->info;  
            }  
        }  
        if(count<vexnum)  
            return 0;  
        else  
            return 1;  
    }  
      
    //求所有事件的最晚发生时间并求出关键活动和关键路径  
    void Critical_Path()  
    {  
        stack<int> T;  
        string cp[10];  
        int c=0;  
        if(!Topo_Order(T))  
        {  
            cout<<"该有向网有环！"<<endl;  
            return;  
        }  
        int vl[20];  
        for(int i=0;i<vexnum;i++)  
            vl[i]=ve[vexnum-1]; //初始化顶点事件最迟发生时间  
          
        while(!T.empty())  
        {  
            ArcNode *p=NULL;  
            int j=T.top();  
            T.pop();  
            for(p=vertices[j].firstarc;p;p=p->nextarc)  
            {  
                int k=p->adjvex;  
                int dut=p->info;  
                if(vl[k]-dut<vl[j])  
                    vl[j]=vl[k]-dut;  
            }  
        }  
        //下面是根据关键活动的特点(最早开始时间和最晚开始时间相等)求关键活动，做上标记  
        cout<<"tail  head  weight  earliest time  latest time  tag "<<endl;  
        for(int j=0;j<vexnum;j++)  
            for(ArcNode *p=vertices[j].firstarc;p;p=p->nextarc)  
            {  
                int k=p->adjvex;  
                int dut=p->info;  
                int ee=ve[j];  
                int el=vl[k]-dut;  
                char tag;  
                tag=(ee==el)?'*':' ';  
                cout<<setw(3)<<vertices[j].data<<setw(6)<<vertices[k].data<<setw(7)<<dut<<setw(9)<<ee<<setw(16)<<el<<setw(9)<<tag<<endl;  
                if(tag=='*' && j==0)  
                {  
                    cp[c]=vertices[j].data;  
                    c++;  
                    cp[c]=vertices[k].data;  
                    c++;  
                }  
                else if(tag=='*' && j!=0)  
                {  
                    cp[c]=vertices[k].data;  
                    c++;  
                }             
            }  
        cout<<"The critical activities are ended with * "<<endl;  
        cout<<"So the critical path is :";  
        int i;
        for(i=0;i<c-1;i++)  
            cout<<cp[i]<<"->";  
        cout<<cp[c-1]<<endl;  
    }  
  
};  


int main()  
{  
    ALGraph G;  
    G.Create_ALG();  
    G.Critical_Path();  
    cout<<endl;  
    return 0;  
}  
//http://blog.csdn.net/jkay_wong/article/details/6696701
