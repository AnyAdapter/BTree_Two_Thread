#include<stdio.h>
#include<stdlib.h>

//������������
typedef int DataType;

//�������Ķ�����������������
typedef struct node {
	int ltag, rtag;
	DataType data;
	struct node *lchild, *rchild;
}Threadnode,*ThreadTree;

//��������
void InThreah();//����������

//���������
int main()
{
	return 0;

}
//����������
void InThread(ThreadTree t, ThreadTree pre)
{

}