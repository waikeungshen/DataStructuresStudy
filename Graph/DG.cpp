/*************************************************************************
    * File Name: DG.cpp
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Created Time: 2013年12月05日 星期四 07时28分43秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

#define MAX_VERTEX_NUM 20
#define MAX_NAME 20

struct ArcNode
{
    int adjvex;
    ArcNode *nextarc;
    char *info;
};

struct VNode
{
    char data[MAX_NAME];
    ArcNode *firstarc;
};

struct DGraph
{
    VNode vertices[MAX_VERTEX_NUM];
    int vexnum, arcnum;//顶点数和弧数
};

int LocateVex(DGraph G, char v[])
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (strcmp(v, G.vertices[i].data) == 0)
            return i;
    }
    return -1;
}

void CreateDG(DGraph &G)
{
    int i, j, k, flag;
    ArcNode *p;
    char v1[MAX_NAME], v2[MAX_NAME];
    char s[30];
    cout << "输入有向图的顶点数和弧数,及是否含有弧的信息（是：1，否：0）：";
    cin >> G.vexnum >> G.arcnum >> flag;
    cout << "输入个顶点的信息：" << endl;
    for (i = 0; i < G.vexnum ; i++)
    {
        cin >> G.vertices[i].data;
        G.vertices[i].firstarc = NULL;
    }
    cout << "输入弧的两个端点，空格分割:" << endl;
    for (k = 0; k < G.arcnum; k++)
    {
        cin >> v1 >> v2;
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        p = (ArcNode *) malloc (sizeof(ArcNode));
        p->adjvex = j;
        p->info = NULL;
        p->nextarc = G.vertices[i].firstarc;//插在表头
        G.vertices[i].firstarc = p;
        if (flag)
        {
            cout << "输入该弧的相关信息：";
            cin >> s;
            int length = strlen(s);
            if (length)
            {
                p->info = (char *) malloc ((length + 1) * sizeof (char));
                strcpy(p->info, s);
            }//end if
        }//end if 
    }//end for
}

void Print(DGraph G)
{
    int i;
    ArcNode *p;
    for (i = 0; i < G.vexnum; i++)
    {
        cout << i << " ";
        p = G.vertices[i].firstarc;
        while (p != NULL)
        {
            cout << p->adjvex << " ";
            p = p->nextarc;
        }
        cout << endl;
    }
}

int main()
{
    DGraph G;
    CreateDG(G);
    Print(G);
}
