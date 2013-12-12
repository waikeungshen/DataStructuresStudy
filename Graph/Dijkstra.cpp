#include<iostream>  
#include<string>  
using namespace std;  
  
const int MAX=99999;  
const int MAX_VEX_NUM=20;  
class MGraph  
{  
private:  
    string vexs[MAX_VEX_NUM];//顶点数组  
    int arcs[MAX_VEX_NUM][MAX_VEX_NUM];//邻接矩阵  
    int vexnum;//顶点数  
    int arcnum;//边数  
public:  
    void Create_MG()  
    {  
        int i,j,k;  
        cout<<"输入图的顶点数和边数：";  
        cin>>vexnum>>arcnum;  
        cout<<"输入各个顶点的民称：";  
        for(i=0;i<vexnum;i++)  
            cin>>vexs[i];  
          
        for(i=0;i<vexnum;i++)  
            for(int j=0;j<vexnum;j++)  
                arcs[i][j]=MAX;  
        //上面是初始化邻接矩阵  
          
        for(k=0;k<arcnum;k++)  
        {  
            cout<<"输入每条边对应的始点和终点以及该边的权值：";  
            string v1,v2;  
            int w;  
            cin>>v1>>v2>>w;  
            i=Locate_Vex(v1);  
            j=Locate_Vex(v2);             
          
            while(i<0|| i>vexnum-1 || j<0 || j>vexnum-1)  
            {  
                cout<<"结点位置输入错误,重新输入: ";  
                cin>>v1>>v2>>w;  
                i=Locate_Vex(v1);  
                j=Locate_Vex(v2);     
            }  
              
            arcs[i][j]=w;  
        }  
        cout<<"图构造完成"<<endl;  
    }  
  
    int Locate_Vex(string x)  //用于确定顶点在顶点数组中的位置  
    {  
        for(int k=0;vexs[k]!=x;k++);  
        return k;  
    }  
      
    /*--------------------------------------------------------- 
    / 用迪杰斯特拉(Dijkstra)算法求源点到其他各个顶点的最短路径 
    / 用数组Dist[i]表示当前所找到的从源点v到每个终点vi的最短路径 
    / 长度,初始化时，如果v到vi有弧直接连接，那么Dist[i]为权值，否 
    / 则就为一个很大的值(99999...)。下面介绍下算法的过程： 
    / 集合Final[]为已找到的从v出发的最短路径的终点的集合，初始 
    / 状态只有源点一个顶点。 
    / (1)初始化Dist[]数组，然后在Dist[]中选择最小的一个， 
    / 将其终点并入Final[]中。(2)修改从v出发到集合V-Final上任一顶点Vk 
    / 可达的最短路径长度，如果Dist[j]+arcs[j][k]<Dist[k], 
    / 则修改Dist[k]=Dist[j]+arcs[j][k]。重复(1)、(2)直到 
    / Final[]包含全部V中顶点为止。 
    / path[]记录终点的上一个顶点的位置. 
    /--------------------------------------------------------*/  
      
    void Dijks_Short_Path(int v,int path[],int Dist[])  
    {  
        int min,u;  
        bool Final[MAX_VEX_NUM];  
        for(int i=0;i<vexnum;i++)  
        {  
            Final[i]=false;  
            Dist[i]=arcs[v][i];  
            if(i!=v && arcs[v][i]<MAX)  
                path[i]=v;  
            else  
                path[i]=-1;  
        }  
        Final[v]=true; //Final[]中初始状态只有V  
  
        for(i=1;i<vexnum;i++)  
        {  
            min=MAX;//当前所知离v顶点最近的距离  
            for(int w=0;w<vexnum;w++)  
                if(!Final[w])  
                    if(Dist[w]<min)  
                    {  
                        u=w;  
                        min=Dist[w];  
                    }  
            if(min==MAX)  
                return;  
            Final[u]=true; //找到离v最近的点，并加入Final  
            for(w=0;w<vexnum;w++)  
                if(!Final[w] && (min+arcs[u][w]<Dist[w]))  
                {  
                    //修改Dist[w]和path[w]  
                    Dist[w]=min+arcs[u][w];  
                    path[w]=u;  
                }  
        }  
    }  
  
    void Print(int Dist[],int path[],int v)  
    {  
        int a[10],c,j;  
        cout<<"从源点"<<vexs[v]<<"到其他各个顶点的最短路径长度如下："<<endl;  
        for(int i=1;i<vexnum;i++)  
        {  
            if(Dist[i]<MAX)  
                cout<<vexs[v]<<"->"<<vexs[i]<<"  "<<Dist[i]<<endl;  
            else  
                cout<<vexs[v]<<"和"<<vexs[i]<<"之间不存在路径连通"<<endl;  
        }  
  
        //利用path[]数组的特点，依次回溯找到源点，将其输出就是路径的过程了  
        for(i=1;i<vexnum;i++)  
            if(Dist[i]<MAX)  
            {  
                cout<<"从源点到"<<vexs[v]<<"到顶点"<<vexs[i]<<"的最短路径为：";  
                j=i;  
                c=0;  
                while(path[j]!=-1)  
                {  
                    a[c]=path[j];  
                    j=path[j];  
                    c++;  
                }  
                for(j=c-1;j>=0;j--)  
                    cout<<vexs[a[j]]<<"->";  
                cout<<vexs[i]<<endl;  
            }  
  
    }  
};  

int main()  
{  
    MGraph G;  
    G.Create_MG();  
  
    int Dist[20];  
    int path[20];  
  
    cout<<"输入源点：";  
    int v;  
    cin>>v;  
    cout<<"_____求源点到其他顶点的最短路径____"<<endl;  
    G.Dijks_Short_Path(v,path,Dist);  
    cout<<endl;  
    G.Print(Dist,path,v);  
    return 0;  
}  
//http://blog.csdn.net/jkay_wong/article/details/6692572
