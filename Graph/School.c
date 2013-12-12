/*************************************************************************
    * File Name: School.c
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Created Time: Tue 10 Dec 2013 10:24:32 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#define MAX_NAME 20
#define MAX_INFO 20
#define MAX_VERTEX_NUM 30   //最大顶点个数
typedef char InfoType;
typedef char VertexType[MAX_NAME];

//邻接多重表存储
struct EdgeTyle //边的类型
{
    int ivex, jvex;//该边依附的两个顶点的位置
    struct EdgeTyle *ilink, *jlink;//分别指向依附这两个顶点的下一条边
    InfoType *info; //该边的信息
    int length; //边的权值，边的长度
};

struct VertexType   //顶点的类型
{
    char name[MAX_NAME];
    InfoType *info;
};
struct VexNode
{
    struct VertexType data;
    struct EdgeTyle *firstedge;//指向第一条依附该顶点的边
};

struct Graph
{
    struct VexNode adjmulist[30];
    int vexnum, edgenum;//顶点数,边数
};

//确定e在G中的位置
int LocateVex (struct Graph * G, struct VertexType e)
{
    int i;
    for (i =0; i < G->vexnum; i++)
    {
        if (strcmp(e.name, G->adjmulist[i].data.name) == 0)
            return i;
    }
    return -1;
}

//利用邻接多重表存储结构，构造无向图G
void CreateGraph (struct Graph *G)
{
    int VertexInfo;//是否含顶点信息
    int EdgeInfo;//是否含边信息
    int i, j, k;
    char s[MAX_INFO];
    struct VertexType a, b;
    struct EdgeTyle *p;

    prinf("请输入无向图G的顶点个数，顶点是否含其他信息（是：1，否：0）：");
    scanf("%d%d",G->vexnum, &VertexInfo);
    printf("请输入%d个顶点的值\n",G->vexnum);
    for (i = 0; i < G->vexnum; i++)
    {
        scanf("%s", &G->adjmulist[i].data.name);
        G->adjmulist[i].firstedge = NULL;
        //顶点其他信息
        if (VertexInfo)
        {
            printf("输入该顶点其他信息：\n");
            scanf("%s",s);
            int length = strlen(s);
            if (length)
            {
                G->adjmulist[i].data.info = (char *) malloc ((length + 1) * sizeof (char));
                strcpy(G->adjmulist[i].data.info, s);
            }//end if
        }//end if
    }//end for
    printf("请输入边的条数，边是否含其他信息（是：1，否0）：");
    scanf("%d%d",G->edgenum, &EdgeInfo);
    printf("输入每条边的两个端点以及该边的长度，空格分割\n");
    for (k = 0; k < G->edgenum; k++)
    {
        scanf("%s%s",a.name, b.name);
        i = LocateVex(&G, a);
        j = LocateVex(&G, b);
        p = (struct EdgeTyle *) malloc (sizeof(struct EdgeTyle));
        p->ivex = i;
        p->jvex = j;
        p->info = NULL;
        p->ilink = G->adjmulist[i].firstedge;//插在表头
        G->adjmulist[i].firstedge = p;
        p->jlink = G->adjmulist[j].firstedge;//插在表头
        G->adjmulist[j].firstedge = p;
        scanf("%d",&p->length);
        if (EdgeInfo)
        {
            printf("输该边其他信息：\n");
            scanf("%s",s);
            int length = strlen(s);
            if (length)
            {
                p->info = (char *) malloc ((length + 1) * sizeof (char));
                strcpy(p->info, s);
            }
        }//end if
    }//end for
}

void GetShortestPath (struct Graph *G, struct VertexType start, struct VertexType end)
{
    //求start到end的一条最短路径及其长度
    int v = LocateVex(&G, start);
    int w = LocateVex(&G, end);
    int u;
    int DistVtoU, DistUtoW, DistVtoW;
    int path[MAX_VERTEX_NUM];//路径
    int i = 0;
    path[i++] = v;

    for (u = 0; u < G->vexnum; u++)
    {
        if (v != w && DistVtoU + DistUtoW < DistVtoW)   //从v经u到w的一条路径更短
        {
            DistVtoW = DistVtoU + DistUtoW;
            path[i++] = u;
        }
    }
    path[i] = w;
}

int main()
{
    return 0;
}
