//单链队列链式表示
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


#define MaxSize 100 
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int QElemType;
typedef int Status;

//单链队列 队列的链式储存结构
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;


//基本操作的算法描述

//构造一个空队列
Status InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}

//判断一个队列是否为空，若为空则返回1，否则返回0
int QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear) return 1;
	else return 0;
}

//返回队列的长度
int QueueLength(LinkQueue Q)
{
	QueuePtr q;
	q = (QueuePtr)malloc(sizeof(QNode));
	q = Q.front->next;
	if (q == NULL) return 0;
	else
	{
		int i = 1;
		while (q != Q.rear)
		{
			q = q->next;
			++i;
		}
		return i;
	}
}

//输出队列元素的值
Status QueueTraverse(LinkQueue Q)
{
	QueuePtr q;
	q = (QueuePtr)malloc(sizeof(QNode));
	q = Q.front;
	while (q->next != NULL)
	{
		printf("%d   ", q->next->data);
		q = q->next;
	}
	printf("\n");
	return OK;
}


//销毁队列
Status DestroyQueue(LinkQueue &Q)
{
	while (Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}

//插入元素e为Q的新的队尾元素
Status EnQueue(LinkQueue &Q, QElemType e)
{
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(OVERFLOW);
	p->data = e; p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK
Status DeQueue(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;
	if (Q.front == Q.rear) return ERROR;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p) Q.rear = Q.front;
	free(p);
	return OK;
}

//得到队头元素的值
Status GetHead(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;
	if (Q.front == Q.rear) return ERROR;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p) Q.rear = Q.front;
	free(p);
	return OK;
}



//生成队列,具有n个元素
Status CreatQueue(LinkQueue &Q)
{
	int i; int n; int e;
	printf("Please input the numbers of the queue:\n");
	scanf_s("%d", &n);
	if (n < 0) exit(ERROR);
	printf("Please input the queue:\n");
	for (i = 0; i < n; i++)
	{
		scanf_s("%d", &e);
		EnQueue(Q, e);
	}
	return OK;
}

//将Q清为空队列
int ClearQueue(LinkQueue Q)
{
	int e;
	if (Q.front == Q.rear) return ERROR;
	while (Q.front != Q.rear)
	{
		DeQueue(Q, e);
	}
	return OK;
}

//输出队列（先进先出）
void OutpQueue(LinkQueue Q)
{
	QElemType e;
	while (Q.front != Q.rear)
	{
		DeQueue(Q, e);
		printf("%d   ", e);
	}
	printf("\n");
}

//实现
void main()
{
	int i, n;
	QElemType k, h, a, f;
	LinkQueue Q;
	printf("创建一个空队列！\n");
	InitQueue(Q);
	printf("判断队列是否为空！\n");
	printf("QueueEmpty(Q)=%d\n", QueueEmpty(Q));
	printf("创建队列的元素个数：\n");
	scanf_s("%d", &n);
	printf("输入%d个插入队列的元素的值：\n", n);
	for (i = 0; i<n; i++)
	{
		scanf_s("%d", &k);
		EnQueue(Q, k);
	}
	printf("输出队列元素的个数：%d\n", QueueLength(Q));
	printf("输出队列元素的值：\n");
	QueueTraverse(Q);
	printf("输入插入队列的元素的值：");
	scanf_s("%d", &h);
	EnQueue(Q, h);
	printf("输出插入一个队列元素后队列元素的值：\n");
	QueueTraverse(Q);
	DeQueue(Q, a);
	printf("输出第1个删除的队头元素的值：%d\n", a);
	DeQueue(Q, a);
	printf("输出第2个删除的队头元素的值：%d\n", a);
	printf("输出两次删除队头元素后队列的元素值：");
	QueueTraverse(Q);
	GetHead(Q, f);
	printf("输出队头元素的值：%d\n", f);
	printf("输出队列元素的个数：%d\n", QueueLength(Q));
	printf("将Q清为空队列！\n");
	ClearQueue(Q);
	printf("输出队列元素的个数：%d\n", QueueLength(Q));
	printf("判断队列是否为空！\n");
	printf("QueueEmpty(Q)=%d\n", QueueEmpty(Q));
	Sleep(20000);
}
