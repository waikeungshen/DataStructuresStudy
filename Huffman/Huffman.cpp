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
}

//编码
void Encoding()
{
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

int main()
{
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
    return 0;
}
