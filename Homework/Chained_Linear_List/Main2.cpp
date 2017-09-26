#include<windows.h>
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h> 

//�������״̬���� 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE 1000 
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int  ElemType;
typedef char Status;

//��ʽ���Ա�Ĵ���ṹ
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

//��ʼ����ʽ���Ա�
void InitList_L(LNode *&L)
{
	L= (LinkList)malloc(sizeof(LinkList));
	L->next = NULL;
}

//���򹹽�һ����ʽ���Ա�,����n��Ԫ��
void CreatList_L(LNode *&L, int n)
{
	LinkList p; int i;
	L = (LinkList)malloc(sizeof(LinkList));
	L->next = NULL;
	for (i = n; i >0; --i)
	{
		p = (LinkList)malloc(sizeof(LinkList));
		scanf_s("%d", &p->data);
		p->next = L->next;
		L->next = p;
	}
}

//�����ʽ���Ա�
void DispList_L(LinkList L)
{
	L = L->next;
	while (L->next != NULL)
	{
		printf("%d ", L->data);
		L = L->next;
	}
	printf("%d ", L->data);
	printf("\n");
}

//����ʽ���Ա�����(�������¿ռ�)
void InverseList_L(LinkList &L)
{
	LinkList p, q;
	p = L->next;
	L->next = NULL;
	q = p->next;
	while (q != NULL)
	{
		p->next = L->next;
		L->next = p;
		p = q; q = q->next;
	}
	p->next = L->next;
	L->next = p;
}

//����ʽ���Ա�ʵ��ֵ�ǵݼ�����
void NondecList_L(LinkList &L)
{
	LinkList p, q, k;
	p = L; q = p->next; k = p->next;
	while ((p->next) != NULL)
	{
		while (q->next != NULL)
		{
			if ((p->next->data)>(q->next->data))
			{
				p->next = q->next;
				q->next = p->next->next;
				p->next->next = k;
				k = p->next;
			}
			else q = q->next;
		}
		p = p->next;
		k = k->next;
		q = p->next;
	}
}

//ʵ��
int main()
{
	LinkList L1;
	printf("Reverse input 7 numbers:\n");
	CreatList_L(L1,7);
	printf("The LinkList you have built is:\n");
	DispList_L(L1);
	printf("Inverse the LinkList.\n");
	InverseList_L(L1);
	DispList_L(L1);
	Sleep(10000);
}

////ʵ��2
//int main()
//{
//	LinkList L1;
//	printf("Reverse input 5 numbers:\n");
//	CreatList_L(L1, 5);
//	printf("The LinkList you have built is:\n");
//	DispList_L(L1);
//	printf("Making the list non decreasing.\n");
//	NondecList_L(L1);
//	DispList_L(L1);
//	Sleep(8000);
//}