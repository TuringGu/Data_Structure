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
#define MaxSize 100 
typedef int  ElemType;
typedef char Status;

typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LinkList;


//初始化线性表
void InitList_L(LinkList *&L)
{
	L = (LinkList *)malloc(sizeof(LinkList));
	L->next = NULL;
}



//输出线性表的长度（结点个数）
int LengthList_L(LinkList *L)
{
	LinkList *p = L;
	int i = 0;
	while (p->next != NULL)
	{
		p = p->next; i++;
	}
	return (i);
}


//输出链式线性表
void DispList_L(LinkList *L)   //输出线性表
{
	LinkList *p = L->next;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}


//如果L中存在第一个满足有要与e相同的元素，返回与其相同的个数。
int LocateList_L(LinkList *L, ElemType e)
{
	int i, j, len_L = LengthList_L(L); LinkList *p;
	p = L; j = 0;
	for (i = 0; i < len_L; i++)
	{
		p = p->next;
		if (p->data == e)
		{
			j++;
		}
	}
	return j;
}

//如果L中存在第一个满足有要与e相同的元素，返回与其相同的个数-1。
int LocateList_Ls(LinkList *L, ElemType e)
{
	int i, j, len_L = LengthList_L(L); LinkList *p;
	p = L; j = 0;
	for (i = 0; i < len_L; i++)
	{
		p = p->next;
		if (p->data == e)
		{
			j++;
		}
	}
	return j-1;
}


//算法2.8 用e返回L中的i个元素的值
ElemType GetElem_L(LinkList *L, int i, ElemType &e)
{
	int j; LinkList *p;
	p = L->next; j = 1;
	while (p&&j < i)
	{
		p = p->next; ++j;
	}
	if (!p || j>i)return ERROR;
	e = p->data;
	return e;
}

//2.9 第i个位置插入e
ElemType ListInsert_L(LinkList *&L, int i, ElemType e)
{
	LinkList *p, *s; int j;
	p = L; j = 0;
	while (p&&j < i - 1){ p = p->next; ++j; }
	if (!p || j>i - 1) return ERROR;
	s = (LinkList*)malloc(sizeof(LinkList));
	s->data = e; s->next = p->next;
	p->next = s;
	return OK;

}



//2.10删除第i个元素， 由e返回其值
ElemType ListDelete_L(LinkList *&L, int i, ElemType &e)
{
	LinkList *p, *q; int j;
	p = L; j = 0;
	while (p->next&&j < i - 1)
	{
		p = p->next; ++j;
	}
	if (!(p->next) || j>i - 1)return ERROR;
	q = p->next; p->next = q->next;
	e = q->data; free(q);
	return OK;

}

//算法2.11 建立一个链式线性表，具有n个结点(尾插法)
void CreatList_L(LinkList *&L, ElemType n)
{
	LinkList *s; ElemType  i;
	L = (LinkList*)malloc(sizeof(LinkList));
	L->next = NULL;
	for (i = n; i>0; --i)
	{
		s = (LinkList*)malloc(sizeof(LinkList));
		scanf_s("%d", &s->data);
		s->next = L->next;
		L->next = s;
	}
}



//La和Lb合成新的线性链表Lc，Lc中的数据元素也按值非递减有序排列。(La,Lb非递减)
void MergeList_L(LinkList *&La, LinkList *&Lb, LinkList *&Lc)
{
	LinkList *pa, *pb, *pc;
	pa = La->next; pb = Lb->next;
	Lc = pc = La;
	while (pa&&pb)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa; pc = pa; pa = pa->next;
		}
		else{ pc->next = pb; pc = pb; pb = pb->next; }

	}
	pc->next = pa ? pa : pb;
	free(Lb);
}


//La,Lb归并为新的线性表Lc.
void Union(LinkList *&La, LinkList *&Lb, LinkList *&Lc)
{
	int i, j, k, e1, e2, e3, e4, e5;
	int Len_La = LengthList_L(La);
	for (i = 1; i <= Len_La; i++)
	{
		e2 = GetElem_L(La, i, e1);
		if (!(LocateList_L(Lb, e2))) ListInsert_L(Lb, 1, e2);
	}
	for (j = 1; j <= LengthList_L(Lb); j++)
	{
		e4 = GetElem_L(Lb, j, e3);
		if (LocateList_Ls(Lb, e4))
		{
			ListDelete_L(Lb, j, e5);
			j--;
		}
	}
	Lc = Lb;
}


int main()
{
	LinkList *La, *Lb, *Lc, *La1, *Lb1, *Lc1;
	InitList_L(Lc1);
	printf("Please reverse input 5 numbers.\n");
	CreatList_L(La, 5);
	printf("Please reverse input 6 numbers.\n");
	CreatList_L(Lb, 6);
	DispList_L(La);
	DispList_L(Lb);
	printf("La和Lb合成为新的线性链表Lc且非递减\n");
	MergeList_L(La, Lb, Lc);
	DispList_L(Lc);
	printf("Please reverse input 5 numbers.\n");
	CreatList_L(La1, 5);
	printf("Please reverse input 6 numbers.\n");
	CreatList_L(Lb1, 6);
	DispList_L(La1);
	DispList_L(Lb1);
	printf("La1和Lb1归并成为新的链表Lc1(求并集)\n");
	Union(La1, Lb1, Lc1); DispList_L(Lb1);
	Sleep(8000);
}


////程序实现2
//int main()
//{
//	LinkList *L1;
//	int i, e;
//	printf("Please reverse input 5 numbers.\n");
//	CreatList_L(L1, 5);
//	printf("The LinkList you have built is:\n");
//	DispList_L(L1);
//	printf("返回第几个元素的值\n");
//	scanf_s("%d", &i);
//	GetElem_L(L1, i, e);
//	printf("第几个位置插入几\n");
//	scanf_s("%d%d", &i, &e);
//	ListInsert_L(L1, i, e);
//	DispList_L(L1);
//	printf("删除第几个元素\n");
//	scanf_s("%d", &i);
//	ListDelete_L(L1, i, e);
//	DispList_L(L1);
//	Sleep(2000);
//}