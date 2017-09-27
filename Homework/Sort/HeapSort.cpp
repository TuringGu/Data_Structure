//头文件
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h> 
#include<windows.h>
#include<time.h>

//函数结果状态代码 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

//--对数值型关键字
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)< (b))
#define LQ(a,b) ((a)<=(b))

/*//--对字符串型关键字
#define EQ(a,b) (!strcmp((a),(b)))
#define LT(a,b) (strcmp((a),(b))<0)
#define LQ(a,b) (strcmp((a),(b))<=0)
*/

//顺序静态链表存储结构
#define MAXSIZE 20          //一个用作事例的小顺序表的最大长度
typedef int KeyType;        //定义关键字类型为整数类型
typedef int InfoType;       //定义其他数据项类型为整数类型
typedef int Status;
typedef char ElemType;
typedef struct
{
	KeyType key;            //关键字项
	InfoType otherinfo;     //其他数据项
}RedType;                   //记录类型
typedef struct
{
	RedType r[MAXSIZE + 1]; //r[0]闲置或用作哨兵单元
	int length;             //顺序表长度
}SqList;                    //顺序表类型

//初始化链表
Status InitList(SqList &L)
{
	L.length = 0;
	return OK;
}

//创建顺序表
Status CreateList(SqList &L, int n)
{
	int i = 0;
	for (i = 1; i <= n; i++)
	{
		scanf_s("%d", &L.r[i]);
	}
	L.length = n;
	return OK;
}

//输出顺序表
Status DispList(SqList L)
{
	int i = 0;
	for (i = 1; i <= L.length; i++)
	{
		printf("%-2d ", L.r[i]);
	}
	printf("\n");
	return OK;
}

typedef SqList HeapType;                       //堆采用顺序表存储表示
//Heap Sort--------------------------------------------------------------------
void HeapAdjust(HeapType &H, int s, int m)       //已知H.r[s..m]中记录的关键字除H.r[s].key之外均满足堆的
{                                                //定义，本函数调整H.r[s]的关键字，使H.r[s..m]成为一个
	                                             //大堆顶（对其中记录的关键字而言）
	RedType rc; int j = 0;
	rc = H.r[s];
	for (j = 2 * s; j <= m; j *= 2)              //沿key较大的孩子结点向下筛选
	{
		if (j < m&&LT(H.r[j].key, H.r[j + 1].key))
			++j;                                 //j为key较大的记录的下标
		if (!LT(rc.key, H.r[j].key)) break;      //rc应插入在位置s上
		H.r[s] = H.r[j]; s = j;
	}
	H.r[s] = rc;                                 //插入
}//HeapAdjust

void HeapSort(HeapType &H)                       //对顺序表进行堆排序
{
	int i; int temp = 0;
	for (i = H.length / 2; i > 0; --i)           //把H.r[1..H.length]建成大顶堆
		HeapAdjust(H, i, H.length);
	for (i = H.length; i > 1; --i)               //将堆顶记录和当前未经排序子序列Hr[1..i]中
	{                                            //最后一个记录相互交换
		temp = H.r[1].key;
		H.r[1].key = H.r[i].key;
		H.r[i].key = temp;
		HeapAdjust(H, 1, i - 1);                 //将H.r[1..i-1]重新调整为大顶堆
	}
}//HeapSort

//-----------------------------------------------------------------------------

//main function
void main()
{
	SqList L;
	int n;
	printf("初始化顺序表，");
	InitList(L);
	if (L.length == 0)
		printf("顺序表为空！\n");
	printf("输入顺序表的元素个数：");
	scanf_s("%d", &n); getchar();
	printf("输入%d个元素：\n", n);
	CreateList(L, n); getchar();
	printf("输出%d个元素的顺序表如下：\n", n);
	DispList(L);
	HeapSort(L);
	printf("堆排序排序结果如下：\n");
	DispList(L);
	system("pause");
}