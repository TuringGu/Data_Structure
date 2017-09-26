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


//二叉树的二叉链表存储表示
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode *lchild, *rchild;    //左右孩子指针
	int visitcount;                     //后序遍历要用到
}BiTNode, *BiTree;

//顺序栈定义——————————————————————————————————————
#define MaxSize 100 
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef BiTree SElemType;
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
		printf("%d ",*S.base);
		++S.base;
	}
	printf("\n");
}
//—————————————————————————————————————————

//单链队列 队列的链式储存结构————————————————————————————
typedef BiTree QElemType;
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
	free( p->next);
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
//————————————————————————————————————————————————


//初始化二叉链表
Status InitBiTree(BiTree &T)
{
	T = (BiTNode*)malloc(sizeof(BiTNode));
	if (T) return OK;
	else return ERROR;
}


//构造二叉链表表示的二叉树T，按先序次序构造，空格字符表示空树，一个字符对应一个节点
Status CreateBiTree(BiTree &T)
{
	char ch;
	scanf_s("%c", &ch);
	if (ch == ' ') T = NULL;
	else
	{
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
		T->data = ch;             //生成根节点
		T->visitcount = 0;
		CreateBiTree(T->lchild);  //构造左指数
		CreateBiTree(T->rchild);  //构造右指数
	}
	return OK;
}


//先序遍历二叉树（非递归算法）
Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	SqStack S; BiTree p;
	InitStack(S); Push(S, T);
	while (!StackEmpty(S))
	{
		while (GetTop(S, p) && p)
		{
			if (!Visit(p->data)) return ERROR;
			Push(S, p->lchild);
		}
		Pop(S, p);
		if (!StackEmpty(S))
		{
			Pop(S, p);
			Push(S, p->rchild);
		}
	}
	return OK;
}


//中序遍历二叉树（非递归算法）
Status InOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	SqStack S; BiTree p;
	InitStack(S); Push(S, T);   //根指针进栈
	while (!StackEmpty(S))
	{
		while (GetTop(S, p) && p) Push(S, p->lchild);   //向左走到尽头
		Pop(S, p);            //空指针退栈
		if (!StackEmpty(S))   //访问结点，向右一步
		{
			Pop(S, p); if (!Visit(p->data)) return ERROR;
			Push(S, p->rchild);
		}
	}
	return OK;
}


//*****后序遍历二叉树*****// visitcount值会被改变是个缺陷
void PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e))         //进栈两次的节点进行访问
{
	SqStack S;
	BiTree p = T;
	InitStack(S);
	while (p || !StackEmpty(S))         //当栈S非空或者p指针非空时，进行操作
	{
		if (p)                          //若p指针非空
		{
			if (p->visitcount != 2)     //若p指针访问次数不为二，令其为一，并进栈
			{
				p->visitcount = 1;
				Push(S, p);
			}
			p = p->lchild;              //向左走到尽头
		}
		else                            //若p指针为空
		{
			Pop(S, p);
			if (p->visitcount == 2)     //若p指针访问次数为二，访问此节点
			{
				Visit(p->data);
			}
			else
			{                           //若不为二，访问次数加一，并进栈
				p->visitcount++;
				Push(S, p);
			}
			p = p->rchild;              //向右走一步
		}
	}
}

//层次遍历二叉树（非递归算法）
Status LevelOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	LinkQueue Q; InitQueue(Q);
	BiTree e;
	EnQueue(Q, T);
	while (!QueueEmpty(Q))
	{
		while (DeQueue(Q, e)&&e)
		{
			Visit(e->data);
			EnQueue(Q, e->lchild);
			EnQueue(Q, e->rchild);
		}
	}
	return OK;
}

//返回二叉树的深度(非递归算法)
Status Depth(BiTree T)
{
	SqStack S; BiTree p;
	int num = 0; T->visitcount = 1;
	InitStack(S); Push(S, T);   //根指针进栈
	while (!StackEmpty(S))
	{
		while (GetTop(S, p) && p)
		{
			if (p->lchild)
			    p->lchild->visitcount = p->visitcount + 1;
			Push(S, p->lchild);   //向左走到尽头
		}
		Pop(S, p);            //空指针退栈
		if (!StackEmpty(S))   //访问结点，向右一步
		{
			Pop(S, p); 
			if (!(p->rchild))  //若右指针为空，用num储存当前单分支最大值，退栈
			{
				num = p->visitcount> num ? p->visitcount : num;    //用num储存当前单分支最大值
				Pop(S, p);
				if (p->rchild)  p->rchild->visitcount = p->visitcount + 1;
				Push(S, p->rchild);
			}
			else
			{
				p->rchild->visitcount = p->visitcount + 1;
				Push(S, p->rchild);
			}
		}
	}
	return num;
}


//求二叉树叶子节点数（非递归算法）
Status LeafCount(BiTree T)
{
	SqStack S; BiTree p; int count=0;
	InitStack(S); Push(S, T);   //根指针进栈
	while (!StackEmpty(S))
	{
		while (GetTop(S, p) && p) Push(S, p->lchild);   //向左走到尽头
		Pop(S, p);            //空指针退栈
		if (!StackEmpty(S))   //访问结点，向右一步
		{
			Pop(S, p);
			if (!p->rchild)
			{
				count++;
				Pop(S, p);
				Push(S, p->rchild);
			}
			else
			{
				Push(S, p->rchild);
			}
		}
	}
	return count;
}


//交换二叉树的左右子树（非递归算法）
Status ExchangeBiTree(BiTree T)
{
	LinkQueue Q; InitQueue(Q);
	BiTree e; BiTree q;
	EnQueue(Q, T);
	while (!QueueEmpty(Q))
	{
		while (DeQueue(Q, e) && e)
		{
			q = e->lchild;                //左右指针交换
			e->lchild = e->rchild;
			e->rchild = q;
			EnQueue(Q, e->lchild);
			EnQueue(Q, e->rchild);
		}
	}
	return OK;
}





//输出二叉树
Status PrintElement(TElemType e)
{
	printf("%-2c",e);
	return OK;
}


//主函数
void main()
{
	BiTree T;
	printf("创建二叉树，按先序次序输入二叉树中结点的值：\n");
	CreateBiTree(T);
	printf("先序遍历二叉树，结果是：\n");
	PreOrderTraverse(T, PrintElement);
	printf("\n");
	printf("中序遍历二叉树，结果是：\n");
	InOrderTraverse(T, PrintElement);
	printf("\n");
	printf("后序遍历二叉树，结果是：\n");
	PostOrderTraverse(T, PrintElement);
	printf("\n");
	printf("层次遍历二叉树，结果是：\n");
	LevelOrderTraverse(T, PrintElement);
	printf("\n");
	printf("二叉树的深度为：%d\n", Depth(T));
	printf("输出二叉树的叶子结点：%d\n",LeafCount(T));
	printf("交换二叉树的左右子树\n");
	ExchangeBiTree(T);
	printf("层次遍历二叉树，结果是：\n");
	LevelOrderTraverse(T, PrintElement);
	printf("\n");
	Sleep(300000);
}
