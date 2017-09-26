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
#define MaxSize 100 
typedef int  ElemType;
typedef char Status;

typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LinkList;


//��ʼ�����Ա�
void InitList_L(LinkList *&L)
{
	L = (LinkList *)malloc(sizeof(LinkList));
	L->next = NULL;
}



//������Ա�ĳ��ȣ���������
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


//�����ʽ���Ա�
void DispList_L(LinkList *L)   //������Ա�
{
	LinkList *p = L->next;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}


//���L�д��ڵ�һ��������Ҫ��e��ͬ��Ԫ�أ�����������ͬ�ĸ�����
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

//���L�д��ڵ�һ��������Ҫ��e��ͬ��Ԫ�أ�����������ͬ�ĸ���-1��
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


//�㷨2.8 ��e����L�е�i��Ԫ�ص�ֵ
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

//2.9 ��i��λ�ò���e
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



//2.10ɾ����i��Ԫ�أ� ��e������ֵ
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

//�㷨2.11 ����һ����ʽ���Ա�����n�����(β�巨)
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



//La��Lb�ϳ��µ���������Lc��Lc�е�����Ԫ��Ҳ��ֵ�ǵݼ��������С�(La,Lb�ǵݼ�)
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


//La,Lb�鲢Ϊ�µ����Ա�Lc.
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
	printf("La��Lb�ϳ�Ϊ�µ���������Lc�ҷǵݼ�\n");
	MergeList_L(La, Lb, Lc);
	DispList_L(Lc);
	printf("Please reverse input 5 numbers.\n");
	CreatList_L(La1, 5);
	printf("Please reverse input 6 numbers.\n");
	CreatList_L(Lb1, 6);
	DispList_L(La1);
	DispList_L(Lb1);
	printf("La1��Lb1�鲢��Ϊ�µ�����Lc1(�󲢼�)\n");
	Union(La1, Lb1, Lc1); DispList_L(Lb1);
	Sleep(8000);
}


////����ʵ��2
//int main()
//{
//	LinkList *L1;
//	int i, e;
//	printf("Please reverse input 5 numbers.\n");
//	CreatList_L(L1, 5);
//	printf("The LinkList you have built is:\n");
//	DispList_L(L1);
//	printf("���صڼ���Ԫ�ص�ֵ\n");
//	scanf_s("%d", &i);
//	GetElem_L(L1, i, e);
//	printf("�ڼ���λ�ò��뼸\n");
//	scanf_s("%d%d", &i, &e);
//	ListInsert_L(L1, i, e);
//	DispList_L(L1);
//	printf("ɾ���ڼ���Ԫ��\n");
//	scanf_s("%d", &i);
//	ListDelete_L(L1, i, e);
//	DispList_L(L1);
//	Sleep(2000);
//}