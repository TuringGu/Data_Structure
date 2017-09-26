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


#include <stdio.h> 
#define MaxSize 100 

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int ElemType; 
typedef struct 
{ ElemType data[MaxSize]; /*存放顺序表元素*/ 
int length; /*存放顺序表的长度*/ 
int listsize; 
}SqList; 


//初始化顺序表 
void InitList(SqList &L) 
{ 
L.length=0;
L.listsize=LIST_INIT_SIZE; 
} 


//创建n个元素的顺序表 
void CreateList(SqList &L,int n) 
{ 
int i; 
printf("输入%d个元素：\n",n); 
for(i=0;i<n;i++) 
scanf("%d",&L.data[i]); 
printf("\n"); 
L.length=n; 
} 


//判断空表 
int ListEmpty(SqList L) 
{ 
return(L.length==0); 
} 


//求顺序表长度 
int ListLength(SqList L) 
{ 
return(L.length); 
} 


//输出顺序表 
void DispList(SqList L) 
{ 
int i; 
if (L.length==0) return; 
for(i=0;i<L.length;i++) 
printf("%d ",L.data[i]); 
printf("\n"); 
} 



//在顺序表中查找值为e的元素位置 
int LocateElem(SqList L,ElemType e) 
{ 
int i=1; 
while(i<=L.length && L.data[i-1]!=e) i++; 
if (i<=L.length) 
return i; 
else 
return 0; 
} 


//构造一个空的线性表L
ElemType InitList_Sq(SqList &L)
{
	if(!L.data) exit(OVERFLOW);
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	return OK; 
} 




//在顺序线性表L中第i个位置前插入新元素e 
int ListInsert(SqList &L, int i,ElemType e) 
{ 
	int j; 
	if (i<1 || i>L.length+1) return 0; 
	for(j=L.length-1;j>=i-1;j--) /*将data[i‐1]及后面元素后移一个位置*/ 
	L.data[j+1]=L.data[j]; 
	L.data[i-1]=e; /*插入元素e*/ 
	++L.length; /*顺序表长度增1*/ 
	return 1; 
} 


//删除第i个元素，并用e返回其值
int ListDelete(SqList &L,int i,ElemType e) 
{ 
	int j; 
	if (i<1 || i>L.length) return 0; 
	e=L.data[i-1]; 
	for(j=i-1;j<L.length-1;j++) /*将data[i]及后面元素前移一个位置*/ 
	L.data[j]=L.data[j+1]; 
	--L.length; /*顺序表长度减1*/ 
	return 1; 
} 


//取顺序表位置i的元素值 
int GetElem(SqList L,int i,ElemType &e) 
{ 
	if (i<1 || i>L.length) return 0; 
	e=L.data[i-1]; 
	return 1; 
} 


//返回L中第一个与e满足关系Equal的数据位序，若不存在，返回值为0
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

//算法2.3 构造一个空的线性表L
ElemType InitList_Sq(SqList &L)
{
	//L.data=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if (!L.data) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}


//算法2.4 在顺序线性表L中第i个位置前插入新元素e 
int ListInsert(SqList &L, int i, ElemType e)
{
	int j;
	if (i<1 || i>L.length + 1) return 0;
	for (j = L.length - 1; j >= i - 1; j--) /*将data[i‐1]及后面元素后移一个位置*/
		L.data[j + 1] = L.data[j];
	L.data[i - 1] = e; /*插入元素e*/
	++L.length; /*顺序表长度增1*/
	return 1;
}


//算法2.5 删除第i个元素，并用e返回其值
int ListDelete(SqList &L, int i, ElemType e)
{
	int j;
	if (i<1 || i>L.length) return 0;
	e = L.data[i - 1];
	for (j = i - 1; j<L.length - 1; j++) /*将data[i]及后面元素前移一个位置*/
		L.data[j] = L.data[j + 1];
	--L.length; /*顺序表长度减1*/
	return 1;
}



//实验题3 归并L1，L2 成为L1；
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


//实验题3  L1,L2合并为l3,L3中的数据元素按值非递减有序排列。
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



//编程实现
int main()
{
	SqList L1,L2,L3,L4,L5;
	printf("建立4个空表\n");
	printf("创建4个5个元素的顺序表\n");
	CreateList(L1,5);CreateList(L2,5);CreateList(L3,5);CreateList(L4,5);
	printf("合并L1，L2为L1\n");
	Union(L1,L2);
	DispList(L1);
	printf("L3,L4合并为L5,L5中的数据元素按值非递减有序排列。\n");
	MergeList(L3,L4,L5);
	DispList(L5);
} 


////算法的实现2
//int main()
//{
//	int a, b, c, d;
//	SqList L;
//	printf("建立一个空表\n");
//	InitList_Sq(L);
//	DispList(L);
//	printf("创建10个元素的顺序表\n");
//	CreateList(L, 10);
//	printf("写出删除元素位置，和返回值\n");
//	scanf("%d%d", &a, &b);
//	printf("删除第%d个元素，并用%d返回其值\n", a, b);
//	ListDelete(L, a, b);
//	DispList(L);
//	printf("创建10个元素的顺序表\n");
//	CreateList(L, 10);
//	printf("写出插入新元素位置，数值\n");
//	scanf("%d%d", &c, &d);
//	printf("顺序线性表L中第%d个位置前插入新元素%d\n", c, d);
//	ListInsert(L, c, d);
//	DispList(L);
//
//}



