#ifndef _Huffman_
#define _Huffman_
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
//哈夫曼树节点
typedef struct HTNode
{
    char ch;//字符
    int weight;//权值
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;//动态分配数组存储赫夫曼树

//哈夫曼编码表结构
typedef struct HCnode
{
    char ch;//字符
    char *pstring;//编码
} HCnode;

HuffmanTree HT;//哈夫曼树
int n;//字符集大小
HCnode *character = NULL;//哈夫曼编码表

void Initialization();//初始化
void Encoding();//编码
void Decoding();//译码
void Print();//印代码文件
void TreePrinting();//印哈夫曼树
void HuffmanCoding(HuffmanTree &HT, int n, char *ch, int *weight);//建立哈夫曼树
void CreatBook();//建立哈夫曼编码表
void menu();
int min(HuffmanTree y, int i);
void Select(HuffmanTree t, int i, int &s1, int &s2);
void WriteHT();//将哈夫曼树存于文件hfmTree
void ReadHT(); //读取文件hfmTree中的哈夫曼树
#endif
