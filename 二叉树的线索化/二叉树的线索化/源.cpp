//期待你的加入
//在此调用库堆栈和队列
#include<iostream>
#include<stdlib.h>
#include<stack>
#include<queue>
using namespace std;

//声明数据类型
typedef char DataType;

//线索化的二叉树数据类型声明
typedef struct node {
	int ltag;				//ltag = 0表示该结点指向该结点的左孩子，为 1 时表示指向前驱结点
	int rtag;				//rtag = 0表示该结点指向该结点的右孩子，为 1 时表示指向后继结点
	DataType data;
	struct node *lchild, *rchild;
}Threadnode,*ThreadTree;

//声明函数（递归线索化）
void PerThread();//先序线索化
void InThread(ThreadTree t,ThreadTree pre);//中序线索化
void PosThread();//后续线索化
ThreadTree Create_BTree();//创建一个二叉树（便于线索化的二叉树）

//主函数入口
int main()
{
	ThreadTree t;
	t = Create_BTree();	//	创建一颗二叉树
	
	//后续操作

	return 0;
}

//创建二叉树（递归算法）
ThreadTree Create_BTree()
{
	ThreadTree t;
	DataType ch;
	ch = getchar();
	if (ch == '#')
	{
		t = NULL;
	}
	else
	{
		t = (Threadnode *)malloc(sizeof(Threadnode));
		t->data = ch;
		t->lchild = Create_BTree();
		t->rchild = Create_BTree();
	}
	return t;
}

//线索化算法（递归）
//先序线索化
void PerThread()
{

}

//中序线索化
void InThread(ThreadTree t, ThreadTree pre)//指针变量pre指向t结点的前驱，函数调用前pre为空
{
	if (t != NULL)
	{
		InThread(t->lchild, pre);
		if (t->lchild != NULL)
		{
			t->ltag = 1;
			t->lchild = pre;
		}
		if (t->rchild != NULL)
		{
			t->rtag = 1;
		}
		if (pre != NULL && pre->rtag == 1)
		{
			pre->rchild = t;
		}
		pre = t;
		InThread(t->rchild, pre);
	}
}

void PosThread()//后续线索化
{

}