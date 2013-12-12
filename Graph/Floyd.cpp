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
        int k;
        for(k=0;vexs[k]!=x;k++);  
        return k;  
    }  
  
    /*------------------------------------------------------------------ 
    / 
    / 弗洛伊德(Floyd)算法：求有向网中每两个顶点之间的距离 
    / 第一次，判别(Vi,Vo)和(Vo,Vj),即判断vi->vo->vj路径是否存在,若存在 
    / 则比较vi->vj 和 vi->vo->vj的长度，短的作为vi到vj的之间顶点的序号 
    / 不大于0的最短路径。第二次，再增加一个顶点v1,也就是说，如果(vi,..,v1)  
    / 和(v1,..,vj)分别是当前找到的中间顶点序号不大于0的最短路径，那么 
    / (vi,...,v1,...,vj)就有可能是从vi到vj的中间顶点 不大于1的最短路径。将 
    / 它和已经得到的从vi到vj的中间顶点不大于0的最短路径比较，短的为从vi 
    / 到vj的中间顶点不大于1的最短路径。第三次，在增加一个顶点v2,继续比较。 
    / 依此类推，在经过n次这样的比较之后，最后求得的就是vi到vj的最短路径。 
    / 
    /------------------------------------------------------------------*/  
  
    void Floyd_Short_Path(int path[20][20],int Dist[20][20])  
    {  
        //Dist[v][w]保存从顶点v到w的最短路径长度  
        //path[v][w]保存到达w的前一个顶点  
  
        for(int v=0;v<vexnum;v++)  
            for(int w=0;w<vexnum;w++)  
            {  
                Dist[v][w]=arcs[v][w];  
                if(Dist[v][w]<MAX) //从v到w有直接路径 by waikeung 
                    path[v][w]=v;  
                else  
                    path[v][w]=-1;  
            }  
        for(int u=0;u<vexnum;u++)  
            for(int v=0;v<vexnum;v++)  
                for(int w=0;w<vexnum;w++)  
                    if(v!=w && Dist[v][u]+Dist[u][w]<Dist[v][w]) //从v经u到w的一条路径更短 by waikeung
                    {  
                        Dist[v][w]=Dist[v][u]+Dist[u][w];  
                        path[v][w]=path[u][w];  
                    }  
    }  
  
    //下面输出两顶点间最短路径的过程的算法，是利用了path[][]数组的特点，进行逆序输出  
    void Print(int path[20][20],int Dist[20][20])  
    {  
        cout<<"___输出每两个顶点之间的最短路径和经过的顶点___"<<endl;  
        int j,a[10],c;  
        for(int v=0;v<vexnum;v++)  
            for(int w=0;w<vexnum;w++)      
                if(Dist[v][w]<MAX)  
                {  
                    cout<<"顶点"<<vexs[v]<<"到顶点"<<vexs[w]<<"的最短路径长为"<<Dist[v][w]<<endl;  
                    cout<<"经过的顶点为：";  
                    j=w;  
                    c=0;  
                    while(path[v][j]!=-1)  
                    {  
                        a[c]=path[v][j];  
                        j=path[v][j];  
                        c++;  
                    }  
                    for(j=c-1;j>=0;j--)  
                        cout<<vexs[a[j]]<<"->";  
                    cout<<vexs[w]<<endl;  
                }  
    }  
};  

int main()  
{  
    MGraph G;  
    G.Create_MG();  
  
    int Dist[20][20];  
    int path[20][20];  
  
    cout<<"求有向网中没两个顶点之间的最短路径"<<endl;  
    G.Floyd_Short_Path(path,Dist);  
    cout<<endl;  
  
    G.Print(path,Dist);  
    cout<<endl;  
  
    return 0;  
}  
//http://blog.csdn.net/jkay_wong/article/details/6693447
