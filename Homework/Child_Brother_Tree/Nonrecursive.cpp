#include<stdarg.h>        //标准头文件，提供宏va_start.va_arg和va_end,用于存取变长参数表
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
#define UNDERFLOW -3


typedef char TElemType;
typedef int Status;

//树的二叉链表（孩子兄弟）存储表示（非递归算法）———————————————
typedef char ElemType;
typedef struct CSNode
{
	ElemType data;
	struct CSNode *firstchild, *nextsibling;
	int level=0;                                                //节点所在层
}CSNode, *CSTree;


//顺序栈定义——————————————————————————————————————
#define MaxSize 100 
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef CSTree SElemType;
typedef  struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack, *Stack;

//构造一个空栈
Status InitStack(SqStack &S)
{
	S.base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

//判断栈空
Status StackEmpty(SqStack S)
{
	if (S.top == S.base)
		return 1;
	else return 0;
}

//若栈不空，用e返回S的栈顶元素，并返回OK；否则返回ERROR
Status GetTop(SqStack S, SElemType &e)
{
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1);
	return OK;
}

//插入元素e为新的栈顶元素
Status Push(SqStack &S, SElemType e)
{
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT)*sizeof(SElemType));
		if (!S.base) exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}

//若栈不空，删除S的栈顶元素，用e返回其值
Status Pop(SqStack &S, SElemType &e)
{
	if (S.top == S.base) return ERROR;
	e = *--S.top;
	return OK;
}

//输出顺序栈元素值
void StackTraverse(SqStack S)
{
	while (S.top != S.base)
	{
		printf("%d ", *S.base);
		++S.base;
	}
	printf("\n");
}
//—————————————————————————————————————————

//单链队列 队列的链式储存结构————————————————————————————
typedef CSTree QElemType;
typedef int Status;

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

//判断队列是否为空，若为空返回值为1，否则返回值为0
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear) return OK;
	else return ERROR;
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

//删除队尾元素
Status DeEQueue(LinkQueue &Q)
{
	QueuePtr p;
	if (Q.front == Q.rear) return ERROR;
	p = Q.front->next;
	while (p->next->next != NULL)
	{
		p = p->next;
	}
	Q.rear = p;
	free(p->next);
	Q.rear->next = NULL;
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

//若队列不空，用e返回队头元素的值，并返回OK
Status GetTQueue(LinkQueue Q, QElemType &e)
{
	if (Q.front == Q.rear) return ERROR;
	e = Q.front->data;
	return OK;
}

//输出队列（先进先出）
void OutpQueue(LinkQueue &Q)
{
	QElemType e;
	while (Q.front != Q.rear)
	{
		DeQueue(Q, e);
		printf("%c", e);
	}
	printf("\n");
}
//_______________________________________

//按先序次序递归创建树
Status CreateCSTree(CSTree &T)
{
	char ch;
	scanf_s("%c", &ch);
	if (ch == '#') T = NULL;
	else
	{
		if (!(T = (CSTree)malloc(sizeof(CSNode)))) exit(OVERFLOW);
		T->data = ch;
		CreateCSTree(T->firstchild);
		CreateCSTree(T->nextsibling);
	}
	return OK;
}

//先根遍历二叉树（非递归算法）
Status PreOrderTraverse(CSTree T) 
{
	SqStack S; CSTree p;
	InitStack(S); Push(S, T);
	while (!StackEmpty(S))
	{
		while (GetTop(S, p) && p)
		{
			printf("%-2c", p->data);
			Push(S, p->firstchild);
		}
		Pop(S, p);
		if (!StackEmpty(S))
		{
			Pop(S, p);
			Push(S, p->nextsibling);
		}
	}
	return OK;
}

//后根遍历树T（非递归算法）
Status PostOrderTraverse(CSTree T)
{
	SqStack S; CSTree p;
	InitStack(S); Push(S, T);
	while (!StackEmpty(S))
	{
		while (GetTop(S, p) && p) Push(S, p->firstchild);
		Pop(S, p);
		if (!StackEmpty(S))
		{
			Pop(S, p); printf("%-2c", p->data);
			Push(S, p->nextsibling);
		}
	}
	return OK;
}

//层次遍历树（非递归算法）
Status LevelOrderTraverse(CSTree T)
{
	LinkQueue Q; CSTree q;InitQueue(Q);
	CSTree s;
	EnQueue(Q, T);
	while (!QueueEmpty(Q))
	{
		DeQueue(Q, q);
		s = q;
		while (s)
		{
			printf("%-2c", s->data);
			if (s->firstchild)
				EnQueue(Q, s->firstchild);
			s = s->nextsibling;
		}
	}
	return OK;
}

//返回树的深度(非递归算法)，采用层次遍历为每个节点编上所在层，返回最深一层层数。
Status CSTreeDepth(CSTree T)
{
	LinkQueue Q; CSTree q; InitQueue(Q);
	CSTree s; 
	q = T;                                     //初始化q，防止此编译器报错
	EnQueue(Q, T);
	T->level = 1;
	while (!QueueEmpty(Q))
	{
		DeQueue(Q, q);
		s = q;
		while (s)
		{
			if (s->firstchild)
			{
				s->firstchild->level = q->level + 1;
				EnQueue(Q, s->firstchild);
			}
			if (s->nextsibling)
				s->nextsibling->level = q->level;
			s = s->nextsibling;
		}
	}
	return q->level;
}

//输出二叉树的叶子节点（非递归算法）
Status LeafCountCSTree(CSTree T)
{
	SqStack S; CSTree p;
	InitStack(S); Push(S, T);
	while (!StackEmpty(S))
	{
		while (GetTop(S, p) && p) Push(S, p->firstchild);
		Pop(S, p);
		if (!StackEmpty(S))
		{
			Pop(S, p);
			if (!p->firstchild) printf("%-2c", p->data);
			Push(S, p->nextsibling);
		}
	}
	return OK;
}

//求二叉树叶子节点数（非递归算法）
Status LeafCount(CSTree T)
{
	SqStack S; CSTree p; int count = 0;
	InitStack(S); Push(S, T);
	while (!StackEmpty(S))
	{
		while (GetTop(S, p) && p) Push(S, p->firstchild);
		Pop(S, p);
		if (!StackEmpty(S))
		{
			Pop(S, p);
			if (!p->firstchild) count++;
			Push(S, p->nextsibling);
		}
	}
	return count;
}


//主函数
void main()
{
	CSTree T; int Count = 0;
	printf("创建树，按先序次序输入树中结点的值：\n");
	CreateCSTree(T);
	printf("树的深度为：%d\n", CSTreeDepth(T));
	printf("先根遍历树，结果是：\n");
	PreOrderTraverse(T);
	printf("\n");
	printf("后根遍历树，结果是：\n");
	PostOrderTraverse(T);
	printf("\n");
	printf("层次遍历树，结果是：\n");
	LevelOrderTraverse(T);
	printf("\n");
	printf("输出树的叶子结点：\n");
	LeafCountCSTree(T);
	printf("\n");
	printf("统计树的叶子结点个数：%d\n", LeafCount(T));
	system("pause");
}
