#include <iostream>
#include <cstring>
#include <cstdlib>
#include <queue>
using namespace std;

#define MAX_NAME 20
#define MAX_INFO 20
typedef char InfoType;
typedef char VertexType[MAX_NAME];
/************************************
 *图的邻接多重表存储表示
 ************************************/
#define MAX_VERTEX_NUM 30   //最大顶点个数
typedef enum {unvisited, visited} VisitIf;

struct EBox
{
    VisitIf mark; // 访问标记
    int ivex, jvex; // 该边依附的两个顶点的位置
    EBox *ilink, *jlink; // 分别指向依附这两个顶点的下一条边
    InfoType *info; // 该边信息指针
};
struct VexBox
{
    VertexType data;
    EBox *firstedge; // 指向第一条依附该顶点的边
};

struct AMLGraph
{
    VexBox adjmulist[MAX_VERTEX_NUM];
    int vexnum, edgenum; // 无向图的当前顶点数和边数
};

//确定点e在G中的位置
int LocateVex (AMLGraph *G, VertexType e)
{
    int i;
    for (i =0 ;i < G->vexnum; i++)
    {
        if (strcmp(e, G->adjmulist[i].data) == 0)
            return i;
    }
    return -1;
}

//采用邻接多重表存储结构，构造无向图G
int CreateGraph(AMLGraph *G)
{
    int IncInfo;//是否含边信息
    int i,j,k;
    char s[MAX_INFO];
    VertexType a, b;
    EBox *p;
    cout << "请输入无向图G的顶点个数，边数，边是否含其他信息（是：1，否：0）：";
    cin >> G->vexnum >> G->edgenum >> IncInfo;
    cout << "请输入" << G->vexnum << "个顶点的值" << endl;
    for (i = 0; i < G->vexnum; i++)//构造顶点向量
    {
        cin >> G->adjmulist[i].data;
        G->adjmulist[i].firstedge = NULL;
    }
    cout << "输入每条边的两个端点，空格分割：" << endl;
    for (k = 0; k < G->edgenum; k++)
    {
        cin >> a >> b;
        i = LocateVex(G, a);//确定a在G中的位置
        j = LocateVex(G, b);//确定b在G中的位置
        p = (EBox *) malloc (sizeof(EBox));
        p->mark = unvisited;
        p->ivex = i;
        p->jvex = j;
        p->info = NULL;
        p->ilink = G->adjmulist[i].firstedge;//插在表头
        G->adjmulist[i].firstedge = p;
        p->jlink = G->adjmulist[j].firstedge;//插在表头
        G->adjmulist[j].firstedge = p;
        if (IncInfo)//边有关信息
        {
            cout << "输入该边相关的信息:";
            cin >> s;
            int length = strlen(s);
            if (length)
            {
                p->info = (char *) malloc ((length + 1) * sizeof (char));
                strcpy(p->info, s);
            }
        }
    }
}

int visite[MAX_VERTEX_NUM];//访问标记数组

void DFS (AMLGraph G, int v)
{
    int i;
    EBox *p;

    visite[v] = 1;
    cout << G.adjmulist[v].data << " ";
    p = G.adjmulist[v].firstedge;
    while (p)
    {
        i = p->ivex==v?p->jvex:p->ivex;
        if (!visite[i])
        {
            cout << G.adjmulist[v].data << "->" << G.adjmulist[i].data << endl; //边集
            DFS(G,i);
        }
        p = p->ivex==v?p->ilink:p->jlink;
    }
}

void DFSTraverse(AMLGraph G)
{
    int v;
    for (v = 0; v < G.vexnum; v++)
        visite[v] = 0;
    //for (v = 0; v < G.vexnum; v++)
    //    if (!visite[v])
    cout << "输入开始遍历的第一个顶点编号：";
    cin >> v;
            DFS(G, v);
    cout << endl;
}

//返回u的第一个邻接点,若顶点在G中无邻接点，则返回-1
int FirstAdjVex(AMLGraph G, int u)
{
    if (u < 0)
        return -1;
    if (G.adjmulist[u].firstedge)   //u有邻接点
        if (G.adjmulist[u].firstedge->ivex == u)
            return G.adjmulist[u].firstedge->jvex;
        else
            return G.adjmulist[u].firstedge->ivex;
    else
        return -1;
}

//返回u（相对于w）的下一个邻接点，若w为最后一个邻接点，则返回-1
int NextAdjVex(AMLGraph G, int u, int w)
{
    if (u < 0 || w < 0)
        return -1;
    EBox *p;
    p = G.adjmulist[u].firstedge;
    while (p)
    {
        if (p->ivex == u && p->jvex != w)
            p = p->ilink;
        else if (p->jvex == u && p->ivex != w)
            p = p->jlink;
        else
            break;
    }
    if (p && p->ivex == u && p->jvex == w)
    {
        p = p->ilink;
        if (p && p->ivex == u)
            return p->jvex;
        else if (p && p->jvex == u)
            return p->ivex;
    }
    if (p && p->jvex == u && p->ivex == w)
    {
        p = p->jlink;
        if (p && p->jvex == u)
            return p->ivex;
        else if (p && p->ivex == u)
            return p->jvex;
    }
    return -1;
}

void BFSTraverse(AMLGraph G)
{
    int v,u,w;
    queue<int> Q;
    //Q.queue(MAX_VERTEX_NUM);
    for (v = 0; v < G.vexnum; v++)
        visite[v] = 0;
    //for (v = 0; v < G.vexnum; v++)
    //{
        cout << "输入要遍历的第一个顶点编号：";
        cin >> v;
        if (!visite[v])//v尚为被访问
        {
            visite[v] = 1;
            cout << G.adjmulist[v].data << " ";
            Q.push(v);//进入队列
            while (!Q.empty())//队列不空
            {
                u = Q.front();//返回队头元素
                Q.pop();//删除队头元素
                for (w = FirstAdjVex(G,u); w >= 0; w = NextAdjVex(G,u,w))
                    if (!visite[w])
                    {
                        visite[w] = 1;
                        cout << G.adjmulist[w].data << " ";
                        cout << G.adjmulist[u].data << "->" << G.adjmulist[w].data << endl;//边集
                        Q.push(w);
                    }
            }
        }
    //}
}

int main ()
{
    AMLGraph G;
    CreateGraph(&G);
    cout << "深度优先搜索的结果：" << endl;
    DFSTraverse(G);
    cout << "广度优先搜索的结果：" << endl;
    BFSTraverse(G);
    return 0;
}
