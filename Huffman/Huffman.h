/*************************************************************************
    * File Name: Huffman.h
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Created Time: 2013年11月06日 星期三 11时00分49秒
 ************************************************************************/

#include <cstdlib>
typedef struct HTNode
{
    unsigned int weight;//权值
    unsigned int parent, lchild, rchild;
} HTNode, *HuffmanTree;//动态分配数组存储赫夫曼树

typedef char **HuffmanCode;//动态分配数组存储赫夫曼编码表
