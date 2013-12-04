#include<iostream>  
#include<string>  
#include<queue>  
using namespace std;  
  
const int MAX_VEX_NUM=20;  
  
class ArcNode //表结点  
{  
public:  
    int adjvex;  
    ArcNode *nextarc;  
};  
  
class VNode //头结点  
{  
public:  
    string data;  
    int indegree;  
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
        //构造有向图       
        string v1,v2;  
        int i,j;  
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
            cout<<"按照尾->头的顺序输入每条边对应的两个顶点：";  
            cin>>v1>>v2;  
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
            p->nextarc=vertices[i].firstarc;  
            vertices[i].firstarc=p;  
            vertices[j].indegree+=1; //作为有向弧的头的顶点入度加1  
        }  
  
        cout<<"图构造完成"<<endl;  
    }  
  
    int Locate_Vex(string v)  
    {  
        for(int k=0;k<vexnum && vertices[k].data!=v;k++);  
        if(k<vexnum)  
            return k;  
        else  
            return -1;  
    }  
  
                        /*拓扑排序*/  
    /*------------------------------------------------ 
    / 对AOV网进行拓扑排序的方法是： 
    / (1)在有向图中选取一个没有前驱的顶点，将其输出 
    / (2)从图中删除该顶点和所有以他为尾的弧 
    / 重复上述2个步骤，若有向图中全部顶点都被输出，则 
    / 該图不存在环，否则，該图存在有向环路。 
    / 为了实现以上操作，可增加一个记录顶点入度的数据成员， 
    / 每个顶点的入度随着顶点的输出动态变化，入度为0即 
    / 该顶点没有前驱，删除以该顶点为尾的弧也可以通过将 
    / 与之相连的顶点的入度都减少1即可。为了减少重复检测 
    / 入度为0的结点，这里借助队列来装入度为0的顶点，在队列 
    / 非空时进行入度为0的顶点的出入队和输出,详细操作看代码 
    /------------------------------------------------*/  
  
    void Topo_Sort()  
    {  
        queue<int> s;  
        ArcNode *p=NULL;  
        for(int i=0;i<vexnum;i++)  
            if(!vertices[i].indegree)  
                s.push(i);  
        int count=0;  
        while(!s.empty())  
        {  
            int k=s.front();  
            s.pop();  
            cout<<vertices[k].data<<"  ";  
            count++;  
            for(p=vertices[k].firstarc;p;p=p->nextarc)  
            {  
                int w=p->adjvex;  
                if(vertices[w].indegree)  
                    vertices[w].indegree--;  
                if(!vertices[w].indegree)  
                    s.push(w);  
            }  
        }  
        if(count<vexnum)  
            cout<<"图中含有有向环"<<endl;  
    }  
};  

int main()  
{  
    ALGraph G;  
    G.Create_ALG();  
    cout<<"拓扑排序为：";  
    G.Topo_Sort();  
    cout<<endl;  
    return 0;  
}  
//http://blog.csdn.net/jkay_wong/article/details/6695929
