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


#include <stdio.h> 
#define MaxSize 100 

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int ElemType; 
typedef struct 
{ ElemType data[MaxSize]; /*���˳���Ԫ��*/ 
int length; /*���˳���ĳ���*/ 
int listsize; 
}SqList; 


//��ʼ��˳��� 
void InitList(SqList &L) 
{ 
L.length=0;
L.listsize=LIST_INIT_SIZE; 
} 


//����n��Ԫ�ص�˳��� 
void CreateList(SqList &L,int n) 
{ 
int i; 
printf("����%d��Ԫ�أ�\n",n); 
for(i=0;i<n;i++) 
scanf("%d",&L.data[i]); 
printf("\n"); 
L.length=n; 
} 


//�жϿձ� 
int ListEmpty(SqList L) 
{ 
return(L.length==0); 
} 


//��˳����� 
int ListLength(SqList L) 
{ 
return(L.length); 
} 


//���˳��� 
void DispList(SqList L) 
{ 
int i; 
if (L.length==0) return; 
for(i=0;i<L.length;i++) 
printf("%d ",L.data[i]); 
printf("\n"); 
} 



//��˳����в���ֵΪe��Ԫ��λ�� 
int LocateElem(SqList L,ElemType e) 
{ 
int i=1; 
while(i<=L.length && L.data[i-1]!=e) i++; 
if (i<=L.length) 
return i; 
else 
return 0; 
} 


//����һ���յ����Ա�L
ElemType InitList_Sq(SqList &L)
{
	if(!L.data) exit(OVERFLOW);
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	return OK; 
} 




//��˳�����Ա�L�е�i��λ��ǰ������Ԫ��e 
int ListInsert(SqList &L, int i,ElemType e) 
{ 
	int j; 
	if (i<1 || i>L.length+1) return 0; 
	for(j=L.length-1;j>=i-1;j--) /*��data[i�\1]������Ԫ�غ���һ��λ��*/ 
	L.data[j+1]=L.data[j]; 
	L.data[i-1]=e; /*����Ԫ��e*/ 
	++L.length; /*˳�������1*/ 
	return 1; 
} 


//ɾ����i��Ԫ�أ�����e������ֵ
int ListDelete(SqList &L,int i,ElemType e) 
{ 
	int j; 
	if (i<1 || i>L.length) return 0; 
	e=L.data[i-1]; 
	for(j=i-1;j<L.length-1;j++) /*��data[i]������Ԫ��ǰ��һ��λ��*/ 
	L.data[j]=L.data[j+1]; 
	--L.length; /*˳����ȼ�1*/ 
	return 1; 
} 


//ȡ˳���λ��i��Ԫ��ֵ 
int GetElem(SqList L,int i,ElemType &e) 
{ 
	if (i<1 || i>L.length) return 0; 
	e=L.data[i-1]; 
	return 1; 
} 


//����L�е�һ����e�����ϵEqual������λ���������ڣ�����ֵΪ0
int EqualElem(SqList L,int e) 
{
	int i;
	for(i=0;i<=L.length;i++)
	{
		if(L.data[i]==e)
		{
			return 1;
		}
	}
	if(i>L.length)
	return 0;
}

//�㷨2.3 ����һ���յ����Ա�L
ElemType InitList_Sq(SqList &L)
{
	//L.data=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if (!L.data) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}


//�㷨2.4 ��˳�����Ա�L�е�i��λ��ǰ������Ԫ��e 
int ListInsert(SqList &L, int i, ElemType e)
{
	int j;
	if (i<1 || i>L.length + 1) return 0;
	for (j = L.length - 1; j >= i - 1; j--) /*��data[i�\1]������Ԫ�غ���һ��λ��*/
		L.data[j + 1] = L.data[j];
	L.data[i - 1] = e; /*����Ԫ��e*/
	++L.length; /*˳�������1*/
	return 1;
}


//�㷨2.5 ɾ����i��Ԫ�أ�����e������ֵ
int ListDelete(SqList &L, int i, ElemType e)
{
	int j;
	if (i<1 || i>L.length) return 0;
	e = L.data[i - 1];
	for (j = i - 1; j<L.length - 1; j++) /*��data[i]������Ԫ��ǰ��һ��λ��*/
		L.data[j] = L.data[j + 1];
	--L.length; /*˳����ȼ�1*/
	return 1;
}



//ʵ����3 �鲢L1��L2 ��ΪL1��
void Union(SqList &L1,SqList L2)
{
	int L1_len,L2_len,i;int e;
	L1_len=ListLength(L1); L2_len=ListLength(L2);
	for(i=1;i<=L2_len;i++)
	{
		GetElem(L2,i,e);
		if(!EqualElem(L1,e))ListInsert(L1,++L1_len,e);
	}
} 


//ʵ����3  L1,L2�ϲ�Ϊl3,L3�е�����Ԫ�ذ�ֵ�ǵݼ��������С�
void MergeList(SqList La,SqList Lb,SqList &Lc)
{
	InitList_Sq(Lc);
	int i,j,l; int k=0;int La_len,Lb_len;int ai,bj;
	i=j=l;
	La_len=ListLength(La);Lb_len=ListLength(Lb);
	while((i<=La_len)&&(j<=Lb_len))
	 GetElem(Lb,j,bj);GetElem(La,i,ai);
	if(ai<=bj)
	{
		ListInsert(Lc,++k,ai);++i; 
	}
	else
	{
		ListInsert(Lc,++k,bj);++j;
	}
	while(i<=La_len)
	{
		GetElem(La,i++,ai);ListInsert(Lc,++k,ai);
	}
	while(j<=Lb_len)
	{
		GetElem(Lb,j++,bj);ListInsert(Lc,++k,bj);
	}
}



//���ʵ��
int main()
{
	SqList L1,L2,L3,L4,L5;
	printf("����4���ձ�\n");
	printf("����4��5��Ԫ�ص�˳���\n");
	CreateList(L1,5);CreateList(L2,5);CreateList(L3,5);CreateList(L4,5);
	printf("�ϲ�L1��L2ΪL1\n");
	Union(L1,L2);
	DispList(L1);
	printf("L3,L4�ϲ�ΪL5,L5�е�����Ԫ�ذ�ֵ�ǵݼ��������С�\n");
	MergeList(L3,L4,L5);
	DispList(L5);
} 


////�㷨��ʵ��2
//int main()
//{
//	int a, b, c, d;
//	SqList L;
//	printf("����һ���ձ�\n");
//	InitList_Sq(L);
//	DispList(L);
//	printf("����10��Ԫ�ص�˳���\n");
//	CreateList(L, 10);
//	printf("д��ɾ��Ԫ��λ�ã��ͷ���ֵ\n");
//	scanf("%d%d", &a, &b);
//	printf("ɾ����%d��Ԫ�أ�����%d������ֵ\n", a, b);
//	ListDelete(L, a, b);
//	DispList(L);
//	printf("����10��Ԫ�ص�˳���\n");
//	CreateList(L, 10);
//	printf("д��������Ԫ��λ�ã���ֵ\n");
//	scanf("%d%d", &c, &d);
//	printf("˳�����Ա�L�е�%d��λ��ǰ������Ԫ��%d\n", c, d);
//	ListInsert(L, c, d);
//	DispList(L);
//
//}



