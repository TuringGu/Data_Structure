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



//线性表的动态分配顺序存储结构
typedef struct
{
	ElemType *elem;
	int length;
	int listsize;
}SqList, *LinkList_Sq;

//初始化顺序表(构造一个空的线性表)
int InitList_Sq(SqList &L)
{
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

//构造一个动态顺序表
ElemType CreatList_Sq(SqList &L, int n)
{
	int i, j;
	L.length = n;
	L.listsize = LIST_INIT_SIZE;
	if (n > 100)
	{
		j = (n - 100) / 10 + 1;
		L.elem = (ElemType*)malloc((LIST_INIT_SIZE + j*LISTINCREMENT)*sizeof(ElemType));
		L.listsize = LIST_INIT_SIZE + j *LISTINCREMENT;
	}
	for (i = 0; i <n; i++)
	{
		scanf_s("%d", &L.elem[i]);
	}
	return OK;
}

//输出顺序表
ElemType DispList_Sq(SqList L)
{
	int i;
	for (i = 0; i < L.length; i++)
	{
		printf("%d ", L.elem[i]);
	}
	return 0;
}

//顺序表中数据元素的逆置
void InverseList_Sq(SqList &L)
{
	int n = L.length;
	int i;
	ElemType k;
	if (n % 2 == 0)
	{
		for (i = 0; i < (n / 2); i++)
		{
			k = L.elem[i];
			L.elem[i] = L.elem[n - 1 - i];
			L.elem[n - 1 - i] = k;

		}
	}
	else
	{
		for (i = 0; i < ((n - 1) / 2); i++)
		{
			k = L.elem[i];
			L.elem[i] = L.elem[n - 1 - i];
			L.elem[n - 1 - i] = k;
		}
	}
	printf("\n");

}

//令顺序表中数据元素按值非递减排列
void NondecList_Sq(SqList &L)
{
	int n = L.length;
	int i, j = 0; ElemType k;
	for (i = 0; i <n; i++)
		for (j = i + 1; j<n; j++)
		{
			if (L.elem[i] > L.elem[j])
			{
				k = L.elem[i];
				L.elem[i] = L.elem[j];
				L.elem[j] = k;
			}
		}

}





//实现
int main()
{
	SqList L1;
	InitList_Sq(L1);
	printf("Input five numbers to creat a SqList: L1.\n");
	CreatList_Sq(L1, 5);
	printf("\nInverse set.");
	InverseList_Sq(L1);
	DispList_Sq(L1);
	Sleep(3000);
}

////实现2
//int main()
//{
//	SqList L1;
//	InitList_Sq(L1);
//	printf("Input five numbers to creat a SqList: L1.\n");
//	CreatList_Sq(L1, 5);
//	printf("Making the numbers non decreasing.\n");
//	NondecList_Sq(L1);
//	DispList_Sq(L1);
//	Sleep(3000);
//}