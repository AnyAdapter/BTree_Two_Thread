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
	struct node *lchild, *rchild, *parent;
}Threadnode, *ThreadTree;

ThreadTree pre = NULL;
ThreadTree Create_BTree(Threadnode *parent);//创建一个二叉树（便于线索化的二叉树）

											//声明函数（递归线索化）
void PreThread_1(ThreadTree t);//先序线索化
void InThread_1(ThreadTree t);//中序线索化
void PostThread_1(ThreadTree t);//后续线索化
								//线索化算法（非递归）
void PreThread_2(ThreadTree t);//先序线索化
void InThread_2(ThreadTree t);//中序线索化
void PostThread_2(ThreadTree t);//后续线索化
								//遍历线索二叉树的操作
void PreThreadOrder(ThreadTree t);//先序遍历
void InThreadOrder(ThreadTree t);//中序遍历
void PostThreadOrder(ThreadTree t);//后续遍历
								   //处理函数
void Visit(DataType t);//访问函数

void InOrder_1(ThreadTree t)//先序遍历
{
	if (t != NULL)
	{

		InOrder_1(t->lchild);
		Visit(t->data);
		printf("%d\t%d\n", t->ltag, t->rtag);
		InOrder_1(t->rchild);
	}
}
//主函数入口
int main()
{
	ThreadTree t;
	Threadnode *parent = NULL;
	pre = NULL;
	t = Create_BTree(parent);	//	创建一颗二叉树
	InOrder_1(t);
	InThread_1(t);
	InThreadOrder(t);
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
		parent = t;
		t->data = ch;
		t->ltag = t->rtag = 0;	//全部初始化为0，在线索化时减少修改
		t->lchild = Create_BTree(parent);
		t->rchild = Create_BTree(parent);
	}
	return t;
}

//线索化算法（递归）
//先序线索化
void PreThread_1(ThreadTree t)//pre为全局指针变量
{
	if (t != NULL)
	{
		if (t->lchild == NULL)
		{
			t->ltag = 1;
			t->lchild = pre;
		}
		if (t->rchild == NULL) t->rtag = 1;
		if (pre != NULL && pre->rtag == 1)
		{
			pre->rchild = t;
		}
		pre = t;
		PreThread_1(t->lchild);
		PreThread_1(t->rchild);
	}
}

//中序线索化
void InThread_1(ThreadTree t)//指针变量pre指向t结点的前驱，函数调用前pre为空
{
	if (t != NULL)
	{
		InThread_1(t->lchild);
		if (t->lchild == NULL)
		{
			t->ltag = 1;
			t->lchild = pre;
		}
		if (t->rchild == NULL) t->rtag = 1;
		if (pre != NULL && pre->rtag == 1)
		{
			pre->rchild = t;
		}
		pre = t;
		InThread_1(t->rchild);
	}
}

void PostThread_1(ThreadTree t)//后续线索化
{
	if (t != NULL)
	{
		PostThread_1(t->lchild);
		PostThread_1(t->rchild);
		if (t->lchild == NULL)
		{
			t->ltag = 1;
			t->lchild = pre;
		}
		if (t->rchild == NULL) t->rtag = 1;
		if (pre != NULL && pre->rtag == 1)
		{
			pre->rchild = t;
		}
		pre = t;
	}
}

//线索化算法（非递归）
void PreThread_2(Threadnode *t)//先序线索化
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
			if (pre != NULL && p->rchild == NULL)
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

void InThread_2(Threadnode *t)//中序线索化
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
			if (pre != NULL && p->rchild == NULL)
			{
				t->rtag = 1;
				pre->rchild = t;
			}
			pre = t;
			p = p->rchild;
		}
	}
}

void PostThread_2(Threadnode *t)//后续线索化
{
	//待完成
}

//遍历线索二叉树的操作
void PreThreadOrder(ThreadTree t)//先序遍历
{
	if (t != NULL)
	{
		Threadnode * pCur = t;
		while (pCur != NULL)
		{
			while (pCur->lchild != NULL && pCur->ltag == 0)//遇到左结点就访问
			{
				if (pCur != NULL)
					Visit(pCur->data);
				pCur = pCur->lchild;
			}
			//到此处还有一个结点未访问
			if (pCur != NULL)
				Visit(pCur->data);
			if (pCur->ltag == 1)//遇到线索就访问右结点
			{
				if (pCur != NULL)
					pCur = pCur->rchild;
			}
			while (pCur != NULL)
			{
				if (pCur->lchild != NULL && pCur->ltag == 0)//遇到左结点就访问
				{
					break;
				}
				if (pCur != NULL)
					Visit(pCur->data);
				pCur = pCur->rchild;
			}
		}
	}
}

void InThreadOrder(ThreadTree t)//中序线索化遍历
{
	if (t == NULL)
	{
		return;
	}
	Threadnode * pCur = t;
	while (pCur != NULL)
	{
		while (pCur != NULL && pCur->ltag == 0)	//找最近的左结点
		{
			pCur = pCur->lchild;
		}
		if (pCur != NULL) Visit(pCur->data);
		while (pCur != NULL && pCur->rtag == 1)//找中序后续结点
		{
			pCur = pCur->rchild;
			if (pCur != NULL)
				Visit(pCur->data);
		}
		if (pCur != NULL)
			//没有后继，即为右子树
			pCur = pCur->rchild;
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
				if (pCur != NULL)
					Visit(pCur->data);
				pre = pCur;
				pCur = pCur->rchild;
			}
			//判断此时pCur是不是指向了根节点  
			if (pCur == t)
			{
				if (pCur != NULL)
					Visit(pCur->data);
				return;
			}
			while (pCur && pCur->rchild == pre)
			{
				if (pCur != NULL)
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
void Visit(DataType data)
{
	printf("%c ", data);
}
