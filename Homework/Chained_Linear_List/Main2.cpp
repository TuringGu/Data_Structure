#include<windows.h>
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h> 

//函数结果状态代码 
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

//链式线性表的储存结构
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

//初始化链式线性表
void InitList_L(LNode *&L)
{
	L= (LinkList)malloc(sizeof(LinkList));
	L->next = NULL;
}

//逆向构建一个链式线性表,具有n个元素
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

//输出链式线性表
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

//令链式线性表逆置(不开辟新空间)
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

//令链式线性表实现值非递减排列
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

//实现
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

////实现2
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