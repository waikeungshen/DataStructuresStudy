/*************************************************************************
    * File Name: Huffman.cpp
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Created Time: 2013年11月05日 星期二 10时46分42秒
************************************************************************/

/*
 *history:
 *Decoding函数未写
 *Print函数未写
 */

#include <iostream>
#include "Huffman.h"
using namespace std;

//功能选择菜单
void menu()
{
    cout << "============================" << endl;
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
    char ch[256];
    int weight[256];
    cout << "输入字符集大小:";
    cin >> n;
    cout << "输入每个字符以及它的权值：" << endl;
    for (i = 0; i < n; i++)
    {
        cin >> ch[i] >> weight[i];
    }
    HuffmanCoding(HT, n, ch, weight);//建立哈夫曼树
    CreatBook();//建立哈夫曼编码表
    WriteHT();//写入文件hfmTree
}

//编码
void Encoding()
{
    ifstream inFile;
    inFile.open("ToBeTran.txt", ios::in);
    if (inFile.fail())
    {
        cout << "ERROR" << endl;
        exit(1);
    }
    ofstream outFile;
    outFile.open("CodeFile.txt", ios::out);
    if (outFile.fail())
    {
        cout << "ERROR!" << endl;
        exit(1);
    }
    char ch;
    char *code;
    int j;
    ch = inFile.get();//从文件中读取一个字符
    while (!inFile.eof())
    {
        for (j = 0; j < n; j++)
        {
            if (character[j].ch == ch)
            {
                code = (char *) malloc (strlen(character[j].pstring) * sizeof(char));
                strcpy(code, character[j].pstring);
                break;
            }
        }
        //将编码结果写入文件CodeFile
        outFile << code;
        if (ch != '\n')
            free(code);
        ch = inFile.get();
    }
    inFile.close();
    outFile.close();
    cout << "编码完毕！" << endl;
}

//译码
void Decoding()
{
    ifstream inFile;
    ofstream outFile;
    inFile.open("CodeFile.txt", ios::in);
    if (inFile.fail())
    {
        cout << "ERROR" << endl;
        return;
    }
    outFile.open("TextFile.txt", ios::out);
    if (outFile.fail())
    {
        cout << "ERROR!" << endl;
        exit(1);
    }
    char codeString[256];
    int i = 0;
    while (codeString[i++] = inFile.get()) {}   //读取需译码的01串到codeString中
    codeString[i] = '\0';
    cout << "需译码的01串是：" << endl;
    cout << codeString << endl;
    cout << "译码的结果为：" << endl;
    int root = 2 * n - 2;   //根
    int res = -1;   //结果
    i = 0;
    int p = root;
    while (i < strlen(codeString))
    {
        while (p != -1)
        {
            if (codeString[i] == '0')
            {
                res = p;
                p = HT[p].lchild;
            }
            else
            {
                res = p;
                p = HT[p].rchild;
            }
            i++;
        }
        cout << HT[res].ch;
        outFile << HT[res].ch;
        i--;
        res = -1;
        p = root;
    }
    cout << "译码完毕！" << endl;
    inFile.close();
    outFile.close();
}

//印代码文件
void Print()
{
    ofstream outFile;
    outFile.open("CodePrin.txt", ios::out);
    if (outFile.fail())
    {
        cout << "ERROR!" << endl;
        exit(1);
    }
    ifstream inFile;
    inFile.open("CodeFile.txt", ios::in);
    if (inFile.fail())
    {
        cout << "ERROR" << endl;
        return;
    }
    char ch;
    int i;//计数
    i = 1;
    ch = inFile.get();
    while (!inFile.eof())
    {
        if (i == 50)
        {
            cout << ch << endl;
            outFile << ch << endl;
            i = 0;
        }
        else
        {
            cout << ch;
            outFile << ch;
        }
        i++;
        ch = inFile.get();
    }
    cout << endl;
    inFile.close();
    outFile.close();
}

//印哈夫曼树
void TreePrinting(int n)
{
    int i;
    int HTsize;//哈夫曼树节点数
    HTsize = 2 * n - 1;
    cout << "打印哈夫曼树如下:" << endl;
    for (i = 0; i < n ; i++)
    {
        cout << i << " "
            << HT[i].ch << " "
            << HT[i].weight << " "
            << HT[i].parent << " "
            << HT[i].lchild << " "
            << HT[i].rchild << " "
            << endl;
    }
    for (; i < HTsize; i++)
    {
        cout << i << " "
            << "-" << " "
            << HT[i].weight << " "
            << HT[i].parent << " "
            << HT[i].lchild << " "
            << HT[i].rchild << " "
            << endl;
    }

}

int min(HuffmanTree t,int i)
{
    int j,flag;
    int k=100; /* 取k为不小于可能的值 */
    for(j = 0; j <= i; j++)
    {
        if(t[j].weight < k && t[j].parent == -1)
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

//建立哈夫曼树
void HuffmanCoding(HuffmanTree &HT, int n, char *ch, int *weight)//哈夫曼编码
{
    int i, s1, s2;
    int HTsize;//哈夫曼树节点数
    if (n <= 1)
        return;
    HTsize = 2 * n - 1;
    HT = (HuffmanTree) malloc (HTsize * sizeof(HTNode));
    for (i = 0; i < n; i++)
    {
        HT[i].ch = ch[i];
        HT[i].weight = weight[i];
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
    }
    for (; i < HTsize; i++)
    {
        Select(HT, i-1, s1, s2);//选择在HT[0...i-1]中parent=-1且weight最小的两个节点
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
        HT[i].parent = -1;
    }
    cout << "哈夫曼树建立完毕" << endl;
}

//建立哈夫曼编码表
void CreatBook()
{
    int i, start, c, f, j;
    character = (HCnode *) malloc (n * sizeof(HCnode));
    char *cd = (char *) malloc (n * sizeof(char));
    cd[n - 1] = '\0';
    //逐个字符求哈夫曼编码
    for (i =0 ;i < n; i++)
    {
        start = n - 1;
        character[i].ch = HT[i].ch;
        for (c = i, f = HT[i].parent; f != -1; c = f , f = HT[f].parent)//从叶子到根逆向求编码
        {
            if (HT[f].lchild == c)
                cd [--start] = '0';
            else
                cd [--start] = '1';
        }
        character[i].pstring = (char *) malloc ((n - start) * sizeof (char));
        //单个字符的编码
        strcpy(character[i].pstring, &cd[start]);
    }
    free(cd);
    //打印
   // cout << "打印哈夫曼编码表" << endl;
   // for (i = 0; i < n; i++)
   // {
   //     cout << character[i].ch << " " << character[i].pstring << endl;
   // }
   // cout << "打印完毕" << endl;
}

//将哈夫曼树存于文件hfmTree
void WriteHT()
{
    ofstream outFile;
    outFile.open("hfmTree.dat", ios::out);
    if (outFile.fail())
    {
        cout << "ERROR!" << endl;
        exit(1);
    }
    int i;
    int HTsize;//哈夫曼树节点数
    HTsize = 2 * n - 1;
    outFile << n << endl;
    for (i = 0; i < n ;i++)
    {
        outFile << i << " "
            << HT[i].ch << " "
            << HT[i].weight << " "
            << HT[i].parent << " "
            << HT[i].lchild << " "
            << HT[i].rchild << " "
            << endl;
    }
    for (; i < HTsize; i++)
    {
        outFile << i << " "
            << "-" << " "
            << HT[i].weight << " "
            << HT[i].parent << " "
            << HT[i].lchild << " "
            << HT[i].rchild << " "
            << endl;
    }
    outFile.close();
}

//读取文件hfmTree中的哈夫曼树
void ReadHT()
{
    ifstream inFile;
    inFile.open("hfmTree.dat", ios::in);
    if (inFile.fail())//不存在hfmTree文件
    {
        cout << "不存在hfmTree文件，请进行初始化" << endl;
        return;
    }
    int HTsize, i, tmp;
    inFile >> n;
    HTsize = 2 * n - 1; 
    HT = (HuffmanTree) malloc (HTsize * sizeof(HTNode));
    //读取哈夫曼树到内存
    for (i = 0; i < HTsize; i++)
    {
        inFile >> tmp
            >> HT[i].ch
            >> HT[i].weight
            >> HT[i].parent
            >> HT[i].lchild
            >> HT[i].rchild;
    }
    inFile.close();
    CreatBook();
}

int main()
{
    ReadHT();
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
            TreePrinting(n);
            break;
        case 'Q':
            break;
        default:
            cout << "参数错误，重新输入:" << endl;
        }
    } while (select != 'Q');
    cout << "System Close !" << endl;
    return 0;
}
