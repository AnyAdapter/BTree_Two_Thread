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
	struct node *lchild, *rchild,*parent;
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
	Threadnode *parent = NULL;
	t = Create_BTree(parent);	//	����һ�Ŷ�����
	pre = NULL;
	//��������

	return 0;
}

//�������������ݹ��㷨��
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
		t->ltag = t->rtag = 0;	//ȫ����ʼ��Ϊ0����������ʱ�����޸�
		t->lchild = Create_BTree(parent);
		t->rchild = Create_BTree(parent);
	}
	return t;
}

//�������㷨���ݹ飩
//����������
void PreThread_1(Threadnode *t, Threadnode *pre)//preΪȫ��ָ�����
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
void InThread_1(Threadnode *t, Threadnode *pre)//ָ�����preָ��t����ǰ������������ǰpreΪ��
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

void PosThread_1(Threadnode *t, Threadnode *pre)//����������
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
void PreThread_2(Threadnode *t, Threadnode * pre)//����������
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

void InThread_2(Threadnode *t, Threadnode *pre)//����������
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

void PostThread_2(Threadnode *t, Threadnode *pre)//����������
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
	if (t != NULL)
	{
		Threadnode *pCur = t;
		pre = NULL;
		while (pCur != NULL)
		{
			//��һ������������ߵĽڵ�  
			while (pCur->lchild != pre && pCur->ltag == 0) //������  
			{
				pCur = pCur->lchild;
			}
			//ѭ�������� pCur== Root ����Ϊ��  

			//�ڶ��������ʺ��  
			while (pCur && pCur->rtag == 1)
			{
				Visit(pCur->data);
				pre = pCur;
				pCur = pCur->rchild;
			}
			//�жϴ�ʱpCur�ǲ���ָ���˸��ڵ�  
			if (pCur == t)
			{
				Visit(pCur->data);
				return;
			}
			while (pCur && pCur->rchild == pre)
			{
				Visit(pCur->data);
				pre = pCur;
				pCur = pCur->parent;  //����һ����  
			}
			//���ﲻ����NULL�жϣ�������Rtag  
			if (pCur && pCur->rtag == 0)
			{
				pCur = pCur->rchild;
			}
		}
		//end-while  
	}
}

//���ʺ���
void Visit(DataType t)
{
	printf("%c ",t);
}