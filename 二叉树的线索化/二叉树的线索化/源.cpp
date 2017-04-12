//�ڴ���ļ���
//�ڴ˵��ÿ��ջ�Ͷ���
#include<iostream>
#include<stdlib.h>
#include<stack>
#include<queue>
using namespace std;

//������������
typedef char DataType;

//�������Ķ�����������������
typedef struct node {
	int ltag;				//ltag = 0��ʾ�ý��ָ��ý������ӣ�Ϊ 1 ʱ��ʾָ��ǰ�����
	int rtag;				//rtag = 0��ʾ�ý��ָ��ý����Һ��ӣ�Ϊ 1 ʱ��ʾָ���̽��
	DataType data;
	struct node *lchild, *rchild;
}Threadnode,*ThreadTree;

ThreadTree Create_BTree();//����һ���������������������Ķ�������

//�����������ݹ���������
void PreThread_1(ThreadTree t,ThreadTree pre);//����������
void InThread_1(ThreadTree t,ThreadTree pre);//����������
void PosThread_1(ThreadTree t,ThreadTree pre);//����������
//�������㷨���ǵݹ飩
void PreThread_2(ThreadTree t,ThreadTree pre);//����������
void InThread_2(ThreadTree t, ThreadTree pre);//����������
void PostThread_2(ThreadTree t,ThreadTree pre);//����������
//���������������Ĳ���
void PreThreadOrder(ThreadTree t);//�������
void InThreadOrder(ThreadTree t);//�������
void PostThreadOrder(ThreadTree t);//��������
//������
void Visit(DataType t);//���ʺ���

//����ȫ�ֱ���ָ�룬���ڲ���
ThreadTree pre;

//���������
int main()
{
	ThreadTree t;
	t = Create_BTree();	//	����һ�Ŷ�����
	pre = NULL;
	//��������

	return 0;
}

//�������������ݹ��㷨��
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
		t->ltag = t->rtag = 0;	//ȫ����ʼ��Ϊ0����������ʱ�����޸�
		t->lchild = Create_BTree();
		t->rchild = Create_BTree();
	}
	return t;
}

//�������㷨���ݹ飩
//����������
void PreThread_1(ThreadTree t,ThreadTree pre)//preΪȫ��ָ�����
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

//����������
void InThread_1(ThreadTree t, ThreadTree pre)//ָ�����preָ��t����ǰ������������ǰpreΪ��
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

void PosThread_1(ThreadTree t,ThreadTree pre)//����������
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

//�������㷨���ǵݹ飩
void PreThread_2(ThreadTree t, ThreadTree pre)//����������
{
	stack<ThreadTree> S;
	ThreadTree p = t;
	if (p != NULL || S.empty() != true)
	{
		if (p)
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
void InThread_2(ThreadTree t, ThreadTree pre)//����������
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
void PostThread_2(ThreadTree t, ThreadTree pre)//����������
{
	//�����
}

//���������������Ĳ���
void PreThreadOrder(ThreadTree t)//�������
{
	if (t != NULL)
	{
		ThreadTree pCur = t;
		while ( pCur != NULL)
		{
			while ( pCur->lchild != NULL && pCur->ltag == 0)//��������ͷ���
			{
				Visit(pCur->data);
				pCur = pCur->lchild;
			}
			//���˴�����һ�����δ����
			Visit(pCur->data);
			if (pCur->ltag == 1)//���������ͷ����ҽ��
			{
				pCur = pCur->rchild;
			}
			while (pCur != NULL)
			{
				if (pCur->lchild != NULL && pCur->ltag == 0)//��������ͷ���
				{
					break;
				}
				Visit(pCur->data);
				pCur = pCur->rchild;
			}
		}
	}
}

void InThreadOrder(ThreadTree t)//�������
{
	if (t != NULL)
	{
		ThreadTree pCur = t;
		while (pCur != NULL)
		{
			while (pCur->ltag == 0)	//�����������
			{
				pCur = pCur->lchild;
			}
			Visit(pCur->data);
			while (pCur != NULL && pCur->rtag == 1)//������������
			{
				pCur = pCur->rchild;
				Visit(pCur->data);
			}
			//û�к�̣���Ϊ������
			pCur = pCur->rchild;
		}
	}
}

void PostThreadOrder(ThreadTree t)//��������
{

}

//���ʺ���
void Visit(DataType t)
{
	printf("%c ",t);
}