#include<stdio.h>
#include<malloc.h>
#include<stdlib.h> 
#include<windows.h>

//函数结果状态代码 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXQSIZE 100
typedef int QElemType;
typedef int Status;

//循环队列 ————队列的顺序储存结构————
typedef struct
{
	QElemType *base;
	int front;
	int rear;
}SqQueue;

//循环队列的基本操作的算法描述
//构造一个空队列Q
Status InitQueue(SqQueue &Q)
{
	Q.base = (QElemType*)malloc(MAXQSIZE  * sizeof(QElemType));
	if (!Q.base) exit(OVERFLOW);
	Q.front = Q.rear = 0;
	return OK;
}

//判断队列是否为空，若为空返回1；否则返回0。
int QueueEmpty(SqQueue Q)
{
	if (Q.front == Q.rear) return 1;
	else return 0;
}

//返回Q的元素个数，即队列的长度
int QueueLength(SqQueue Q)
{
	return(Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

//取队头元素,用e值返回
Status GetHead(SqQueue Q, QElemType &e)
{
	if (Q.front == Q.rear) return ERROR;
	e = Q.base[Q.front];
	return OK;
}

//插入元素e为Q的新的队尾元素
Status EnQueue(SqQueue &Q, QElemType &e)
{
	if ((Q.rear + 1) % MAXQSIZE == Q.front) return ERROR;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	return OK;
}

//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK
Status DeQueue(SqQueue &Q, QElemType &e)
{
	if (Q.front == Q.rear) return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	return OK;
}

//清空队列
int ClearQueue(SqQueue &Q)
{
	int e;
	while (Q.front != Q.rear)
	{
		DeQueue(Q, e);
	}
	return OK;
}

//构造一个队列,元素个数为n
Status CreatQueue(SqQueue &Q)
{
	int n; int i; QElemType e;
	printf("Please input the numbers(n) of the queue:\n");
	scanf_s("%d", &n);
	if (n < 0 || n >= MAXQSIZE) exit(ERROR);
	printf("Please input the queue:\n");
	for (i = 0; i < n; i++)
	{
		scanf_s("%d", &e);
		EnQueue(Q, e);
	}
	printf("\n");
	return OK;
}

//遍历队列元素值且输出其值
void QueueTravers(SqQueue Q)
{
	int i = 0;
	while ((Q.front+i )!= Q.rear)
	{
		printf("%d   ", Q.base[Q.front + i]);
		i++;
	}
}

//输出队列（先进先出）
void OutpQueue(SqQueue &Q)
{
	QElemType m;
	while (Q.front != Q.rear)
	{
		DeQueue(Q, m);
		printf("%d   ", m);
	}
	printf("\n");
}


//实现
int main()
{
	SqQueue Q; QElemType i;
    QElemType j;
	InitQueue(Q);
	CreatQueue(Q);
	printf("输出队列元素值：\n");
	QueueTravers(Q);
	printf("The length of the queue is:%d\n", QueueLength(Q));
	GetHead(Q, i);
	printf("取队头元素：%d\n", i);
	printf("队尾元素插入一个值:");
	scanf_s("%d", &j);
	EnQueue(Q, j);
	printf("输出队列元素值:");
	QueueTravers(Q);
	printf("删除队头元素\n");
	DeQueue(Q, j);
	QueueTravers(Q);
	printf("输出队列元素：");
	OutpQueue(Q);
	printf("队尾插入一个值：");
	scanf_s("%d", &j);
	EnQueue(Q, j);
	printf("清空队列。\n");
	ClearQueue(Q);
	printf("判断队列是否为空：%d", QueueEmpty(Q));
	Sleep(20000);
}