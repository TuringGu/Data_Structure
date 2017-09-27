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

//Quick Sort------------------------------------------------------------------
int Partition(SqList &L, int low, int high)        //交换顺序表L中子表r[low..high]的记录，枢轴记录到位，并反
{                                                  //回其所在位置，此时在它之前（之后）的记录均不大（小）于它
	int pivotkey;
	L.r[0] = L.r[low];                             //用子表的第一个记录作枢轴记录
	pivotkey = L.r[low].key;                       //枢轴记录关键字
	while (low < high)                             //从表的两端交替地向中间扫描
	{
		while (low < high&&L.r[high].key >= pivotkey) --high;
		L.r[low] = L.r[high];                      //将比枢轴记录小的记录移到低端
		while (low < high&&L.r[low].key <= pivotkey) ++low;
		L.r[high] = L.r[low];                      //将比枢轴记录大的记录移到高端
	}
	L.r[low] = L.r[0];                             //枢轴记录到位
	return low;                                    //返回枢轴位置
}//Partition

void QSort(SqList &L, int low, int high)           //对顺序表L中的子序列L.r[low..high]作快速排序
{
	int pivotloc;
	if (low < high)                                //长度大于1
	{
		pivotloc = Partition(L, low, high);        //将L.r[low..high]一分为二
		QSort(L, low, pivotloc - 1);               //对低子表递归排序，pivotloc是枢轴位置
		QSort(L, pivotloc + 1, high);              //对高子表递归排序
	}
}//QSort

void QuickSort(SqList &L)                          //对顺序表L作快速排序
{
	QSort(L, 1, L.length);
}//QuickSort
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
	QuickSort(L);
	printf("快速排序排序结果如下：\n");
	DispList(L);
	system("pause");
}