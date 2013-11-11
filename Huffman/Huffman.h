/*************************************************************************
    * File Name: Huffman.h
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Created Time: 2013年11月06日 星期三 11时00分49秒
 ************************************************************************/

#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
typedef struct HTNode
{
    unsigned int weight;//权值
    unsigned int parent, lchild, rchild;
} HTNode, *HuffmanTree;//动态分配数组存储赫夫曼树

typedef char **HuffmanCode;//动态分配数组存储赫夫曼编码表

HuffmanTree HT;//哈夫曼树
HuffmanCode HC;//哈夫曼编码表
int n;//字符集大小
char *character;//字符集
int *weight;//权值

void Initialization();//初始化
void Encoding();//编码
void Decoding();//译码
void Print();//印代码文件
void TreePrinting();//印哈夫曼树
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n);//哈夫曼编码
