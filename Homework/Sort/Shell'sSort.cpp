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

//Shell's Sort(Diminishing Increment Sort)----------------------------------------
void ShellInsert(SqList &L, int dk)
{
	int i = 0; int j = 0;
	for (i = dk + 1; i <= L.length;++i)
		if (LT(L.r[i].key, L.r[i - dk].key))          //需将L.r[i]插入有序增量子表
		{
			L.r[0] = L.r[i];                          //暂存在L.r[0]
			for (j = i - dk; j > 0 && LT(L.r[0].key, L.r[j].key); j -= dk)
				L.r[j + dk] = L.r[j];                 //记录后移，查找插入位置
			L.r[j + dk] = L.r[0];                     //插入
		}
}//ShellInsert

void ShellSort(SqList &L, int dlta[], int t)
{
	int k = 0;
	for (k = 0; k < t; ++k)
	{
		ShellInsert(L, dlta[k]);                      //一趟增量为dlta[k]的插入排序
		printf("第%d趟排序结果: ", k + 1);
		DispList(L);
	}
}

//main function
void main()
{
	SqList L;
	int n; int dlta[MAXSIZE]; int i = 0; int t = 0;
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
	printf("输入希尔排序总趟数："); scanf_s("%d", &t); getchar();
	printf("依次输入希尔排序增量：\n"); 
	for (i = 0; i < t; i++)
	{
		scanf_s("%d", &dlta[i]);
	}
	getchar();
	printf("进行希尔排序：\n");
	ShellSort(L, dlta, t);
	printf("希尔排序排序结果如下：\n");
	DispList(L);
	system("pause");
}