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
	struct node *lchild, *rchild,*parent;
}Threadnode,*ThreadTree;

ThreadTree Create_BTree();//创建一个二叉树（便于线索化的二叉树）

//声明函数（递归线索化）
void PreThread_1(ThreadTree t,ThreadTree pre);//先序线索化
void InThread_1(ThreadTree t,ThreadTree pre);//中序线索化
void PosThread_1(ThreadTree t,ThreadTree pre);//后续线索化
//线索化算法（非递归）
void PreThread_2(ThreadTree t,ThreadTree pre);//先序线索化
void InThread_2(ThreadTree t, ThreadTree pre);//中序线索化
void PostThread_2(ThreadTree t,ThreadTree pre);//后续线索化
//遍历线索二叉树的操作
void PreThreadOrder(ThreadTree t);//先序遍历
void InThreadOrder(ThreadTree t);//中序遍历
void PostThreadOrder(ThreadTree t);//后续遍历
//处理函数
void Visit(DataType t);//访问函数

//声明全局变量指针，便于操作
ThreadTree pre;

//主函数入口
int main()
{
	ThreadTree t;
	Threadnode *parent = NULL;
	t = Create_BTree(parent);	//	创建一颗二叉树
	pre = NULL;
	//后续操作

	return 0;
}

//创建二叉树（递归算法）
ThreadTree Create_BTree(Threadnode *parent)
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
		t->parent = parent;
		t->data = ch;
		t->ltag = t->rtag = 0;	//全部初始化为0，在线索化时减少修改
		t->lchild = Create_BTree(parent);
		t->rchild = Create_BTree(parent);
	}
	return t;
}

//线索化算法（递归）
//先序线索化
void PreThread_1(Threadnode *t, Threadnode *pre)//pre为全局指针变量
{
	if (t != NULL)
	{
		if (t->lchild == NULL)
		{
			t->ltag = 1;
			t->lchild = pre;
		}
		if (pre != NULL && pre->rchild == NULL)
		{
			t->rtag = 1;
			pre->rchild = t;
		}
		pre = t;
		PreThread_1(t->lchild,pre);
		PreThread_1(t->rchild,pre);
	}
}

//中序线索化
void InThread_1(Threadnode *t, Threadnode *pre)//指针变量pre指向t结点的前驱，函数调用前pre为空
{
	if (t != NULL)
	{
		InThread_1(t->lchild, pre);
		if (t->lchild == NULL)
		{
			t->ltag = 1;
			t->lchild = pre;
		}
		if (pre != NULL && pre->rchild == NULL)
		{
			t->rtag = 1;
			pre->rchild = t;
		}
		pre = t;
		InThread_1(t->rchild, pre);
	}
}

void PosThread_1(Threadnode *t, Threadnode *pre)//后续线索化
{
	if (t != NULL)
	{
		PosThread_1(t->lchild, pre);
		PosThread_1(t->rchild, pre);
		if (t->lchild == NULL)
		{
			t->ltag = 1;
			t->lchild = pre;
		}
		if (pre != NULL && pre->rchild == NULL)
		{
			t->rtag = 1;
			pre->rchild = t;
		}
		pre = t;
	}
}

//线索化算法（非递归）
void PreThread_2(Threadnode *t, Threadnode * pre)//先序线索化
{
	stack<ThreadTree> S;
	ThreadTree p = t;
	if (p != NULL || S.empty() != true)
	{
		if (p)
		{
			if (p->lchild == NULL)
			{
				p->ltag = 1;
				p->lchild = pre;
			}
			if (pre != NULL && pre->rchild == NULL)
			{
				p->rtag = 1;
				pre->rchild = p;
			}
			pre = p;
			S.push(p);
			p = p->lchild;
		}
		else
		{
			p = S.top();
			S.pop();
			p = p->rchild;
		}
	}
}

void InThread_2(Threadnode *t, Threadnode *pre)//中序线索化
{
	stack<ThreadTree> S;
	ThreadTree p = t;
	if (p != NULL || S.empty() != true)
	{
		if (p)
		{
			S.push(p);
			p = p->lchild;
		}
		else
		{
			p = S.top();
			S.pop();
			if (t->lchild == NULL)
			{
				t->ltag = 1;
				t->lchild = pre;
			}
			if (pre != NULL && pre->rchild == NULL)
			{
				t->rtag = 1;
				pre->rchild = t;
			}
			pre = t;
			p = p->rchild;
		}
	}
}

void PostThread_2(Threadnode *t, Threadnode *pre)//后续线索化
{
	//待完成
}

//遍历线索二叉树的操作
void PreThreadOrder(ThreadTree t)//先序遍历
{
	if (t != NULL)
	{
		ThreadTree pCur = t;
		while ( pCur != NULL)
		{
			while ( pCur->lchild != NULL && pCur->ltag == 0)//遇到左结点就访问
			{
				Visit(pCur->data);
				pCur = pCur->lchild;
			}
			//到此处还有一个结点未访问
			Visit(pCur->data);
			if (pCur->ltag == 1)//遇到线索就访问右结点
			{
				pCur = pCur->rchild;
			}
			while (pCur != NULL)
			{
				if (pCur->lchild != NULL && pCur->ltag == 0)//遇到左结点就访问
				{
					break;
				}
				Visit(pCur->data);
				pCur = pCur->rchild;
			}
		}
	}
}

void InThreadOrder(ThreadTree t)//中序遍历
{
	if (t != NULL)
	{
		ThreadTree pCur = t;
		while (pCur != NULL)
		{
			while (pCur->ltag == 0)	//找最近的左结点
			{
				pCur = pCur->lchild;
			}
			Visit(pCur->data);
			while (pCur != NULL && pCur->rtag == 1)//找中序后续结点
			{
				pCur = pCur->rchild;
				Visit(pCur->data);
			}
			//没有后继，即为右子树
			pCur = pCur->rchild;
		}
	}
}

void PostThreadOrder(ThreadTree t)//后续遍历
{
	if (t != NULL)
	{
		Threadnode *pCur = t;
		pre = NULL;
		while (pCur != NULL)
		{
			//第一步：找树最左边的节点  
			while (pCur->lchild != pre && pCur->ltag == 0) //左子树  
			{
				pCur = pCur->lchild;
			}
			//循环结束后 pCur== Root 或者为空  

			//第二步：访问后继  
			while (pCur && pCur->rtag == 1)
			{
				Visit(pCur->data);
				pre = pCur;
				pCur = pCur->rchild;
			}
			//判断此时pCur是不是指向了根节点  
			if (pCur == t)
			{
				Visit(pCur->data);
				return;
			}
			while (pCur && pCur->rchild == pre)
			{
				Visit(pCur->data);
				pre = pCur;
				pCur = pCur->parent;  //往上一级走  
			}
			//这里不能用NULL判断，而是用Rtag  
			if (pCur && pCur->rtag == 0)
			{
				pCur = pCur->rchild;
			}
		}
		//end-while  
	}
}

//访问函数
void Visit(DataType t)
{
	printf("%c ",t);
}