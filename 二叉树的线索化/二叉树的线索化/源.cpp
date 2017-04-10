#include<stdio.h>
#include<stdlib.h>

//声明数据类型
typedef int DataType;

//线索化的二叉树数据类型声明
typedef struct node {
	int ltag, rtag;
	DataType data;
	struct node *lchild, *rchild;
}Threadnode,*ThreadTree;

//声明函数
void InThreah();//中序线索化

//主函数入口
int main()
{
	return 0;

}
//中序线索化
void InThread(ThreadTree t, ThreadTree pre)
{

}