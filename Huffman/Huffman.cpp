/*************************************************************************
    * File Name: Huffman.cpp
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Created Time: 2013年11月05日 星期二 10时46分42秒
************************************************************************/

#include<iostream>
#include 'Huffman.h'
using namespace std;

//功能选择菜单
void menu()
{
    cout << "Huffman 编/译码系统" << endl;
    cout << "I:初始化" << endl;
    cout << "E:编码" <<endl;
    cout << "D:译码" << endl;
    cout << "P:印代码文件" << endl;
    cout << "T:印哈夫曼树" << endl;
    cout << "Q:退出" << endl;
    cout << "请选择：";
}

//初始化
void Initialization()
{
    int i;
    cout << "输入字符集大小:";
    cin >> n;
    character = (char) malloc ((n + 1) * sizeof(char));
    weight = (int) malloc ((n + 1) * sizeof(int));
    cout << "输入每个字符以及它的权值：" << endl;
    for (i = 1; i <= n; i++)
    {
        cin >> character[i];
        cin >> weight[i];
    }
    HuffmanCoding(HT, HC, weight, n);//建立哈夫曼树及哈夫曼编码表
}

//编码
void Encoding()
{
    String s;//一行文字
    String code;//一个字符的编码
    char c;
    int i;
    for (i=0; c != '\0'; i++)
    {
        c = s[i];
        CharacterCode(c, code);//对单个字符进行编码
        cout << code << endl;
    }
}

//译码
void Decoding()
{

}

//印代码文件
void Print()
{

}

//印哈夫曼树
void TreePrinting()
{

}

int min(HuffmanTree t,int i)
{
    int j,flag;
    unsigned int k=0; /* 取k为不小于可能的值 */
    for(j = 1; j <= i; j++)
    {
        if(t[j].weight < k && t[j].parent == 0)
        {
            k = t[j].weight;
            flag = j;
        }
    }
    t[flag].parent = 1;
    return flag;
}

void Select(HuffmanTree t,int i,int &s1,int &s2)
{
    /* s1为最小的两个值中序号小的那个 */
    int j;
    s1 = min(t,i);
    s2 = min(t,i);
    if(s1>s2)
    {
        j = s1;
        s1 = s2;
        s2 = j;
    }
}

//哈夫曼编码
void HuffmanCoding (HuffmanTree &HT, HuffmanCode &HC, int *w, int n)//HT哈夫曼树，HC哈夫曼编码表
{
    /* w存放n个字符的权值(均>0),构造赫夫曼树HT,并求出n个字符的赫夫曼编码HC */
    int m,i,s1,s2,start;
    unsigned c,f;
    HuffmanTree p;
    char *cd;
    if (n <= 1) 
        return;
    m = 2 * n - 1;//节点个数
    HT = (HuffmanTree) malloc ((m + 1) * sizeof (HTNode));
    for( p= *HT + 1, i = 1; i <= n; ++i, ++p, ++w)
    {
        (*p).weight = *w;
        (*p).parent = 0;
        (*p).lchild = 0;
        (*p).rchild = 0;
    }
   for(;i <= m; ++i, ++p)
     (*p).parent = 0;
   //建立赫夫曼树
   for (i = n + 1; i <= m; i++)
   {
        /* 在HT[1~i-1]中选择parent为0且weight最小的两个结点,其序号分别为s1和s2 */
        Select(*HT, i-1, &s1, &s2);
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
   }
   /* 从叶子到根逆向求每个字符的赫夫曼编码 */
   *HC = (HuffmanCode) malloc ((n + 1) * sizeof(char*)); /* 分配n个字符编码的头指针向量([0]不用) */
   cd = (char*)malloc(n * sizeof(char)); /* 分配求编码的工作空间 */
   cd[n-1] = '\0'; /* 编码结束符 */
   for(i = 1; i <= n; i++)
   { 
       /* 逐个字符求赫夫曼编码 */
       start = n-1; /* 编码结束符位置 */
       for(c = i, f = (*HT)[i].parent; f != 0; c = f, f = (*HT)[f].parent)
       /* 从叶子到根逆向求编码 */
       if((*HT)[f].lchild == c)
         cd[--start] = '0';
       else
         cd[--start] = '1';
       (*HC)[i] = (char*) malloc ((n - start) * sizeof(char));
       /* 为第i个字符编码分配空间 */
       strcpy((*HC)[i],&cd[start]); /* 从cd复制编码(串)到HC */
   }
   free(cd); /* 释放工作空间 */
}

//单字符进行编码
void CharacterCode(char c, String &code)
{
    int i;
    i = 0;
    while (character[++i] != c) {}
    *HC[i];//c这个字符的编码

}

void WhichPrint(HuffmanCode &HC, int n)
{
    int i;
    for (i=0;i<n;i++)
    {
        cout << "HC[" << i << "]:" << character[i] << " " << HC[i] << end;
    }
}

int main()
{
    /*
    char select;
    do
    {
        menu();
        cin >> select;
        switch (select)
        {
        case 'I':
            Initialization();
            break;
        case 'E':
            Encoding();
            break;
        case 'D':
            Decoding();
            break;
        case 'P':
            Print();
            break;
        case 'T':
            TreePrinting();
            break;
        case 'Q':
            break;
        default:
            cout << "参数错误，重新输入:" << endl;
        }
    }while (select != 'Q');
    cout << "System Close !" << endl;
    */

    Initialization();
    WhichPrint(HC,n);
    return 0;
}
