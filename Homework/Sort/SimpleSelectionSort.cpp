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

//Simple Selection Sort--------------------------------------------------------
int SelectMinKey(SqList L, int i)
{ /* 返回在L.r[i..L.length]中key最小的记录的序号 */
	KeyType min;
	int j, k;
	k = i; /* 设第i个为最小 */
	min = L.r[i].key;
	for (j = i + 1; j <= L.length; j++)
		if (L.r[j].key<min) /* 找到更小的 */
		{
			k = j;
			min = L.r[j].key;
		}
	return k;
}

void SelectSort(SqList &L)                         //对顺序表L作简单选择排序
{
	int i = 0; int j = 0; int temp = 0;
	for (i = 1; i < L.length; ++i)                 //选择第i小的记录，并交换到位
	{ 
		j = SelectMinKey(L, i);                    //在L.r[i..L.length]中选择key最小的记录
		if (i != j)                                //与第i个记录交换
		{
			temp = L.r[i].key;
			L.r[i].key = L.r[j].key;
			L.r[j].key = temp;
		}
	}
}//SelectSort
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
	SelectSort(L);
	printf("简单选择排序排序结果如下：\n");
	DispList(L);
	system("pause");
}