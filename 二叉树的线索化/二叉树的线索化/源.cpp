//�ڴ���ļ���
//�ڴ˵��ÿ��ջ�Ͷ���
#include<iostream>
#include<stdlib.h>
#include<stack>
#include<queue>
using namespace std;

//������������
typedef int DataType;

//�������Ķ�����������������
typedef struct node {
	int ltag, rtag;
	DataType data;
	struct node *lchild, *rchild;
}Threadnode,*ThreadTree;

//��������
void InThread();//����������

//���������
int main()
{
	return 0;

}
//����������
void InThread(ThreadTree t, ThreadTree pre)
{
	//�����
}