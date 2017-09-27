#include<stdarg.h>        //��׼ͷ�ļ����ṩ��va_start.va_arg��va_end,���ڴ�ȡ�䳤������
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h> 
#include<windows.h>
#include<time.h>

//�������״̬���� 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define UNDERFLOW -3


typedef char TElemType;
typedef int Status;

//���Ķ������������ֵܣ��洢��ʾ���ǵݹ��㷨��������������������������������
typedef char ElemType;
typedef struct CSNode
{
	ElemType data;
	struct CSNode *firstchild, *nextsibling;
	int level=0;                                                //�ڵ����ڲ�
}CSNode, *CSTree;


//˳��ջ���塪��������������������������������������������������������������������������
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

//����һ����ջ
Status InitStack(SqStack &S)
{
	S.base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

//�ж�ջ��
Status StackEmpty(SqStack S)
{
	if (S.top == S.base)
		return 1;
	else return 0;
}

//��ջ���գ���e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
Status GetTop(SqStack S, SElemType &e)
{
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1);
	return OK;
}

//����Ԫ��eΪ�µ�ջ��Ԫ��
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

//��ջ���գ�ɾ��S��ջ��Ԫ�أ���e������ֵ
Status Pop(SqStack &S, SElemType &e)
{
	if (S.top == S.base) return ERROR;
	e = *--S.top;
	return OK;
}

//���˳��ջԪ��ֵ
void StackTraverse(SqStack S)
{
	while (S.top != S.base)
	{
		printf("%d ", *S.base);
		++S.base;
	}
	printf("\n");
}
//����������������������������������������������������������������������������������

//�������� ���е���ʽ����ṹ��������������������������������������������������������
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

//�����������㷨����

//����һ���ն���
Status InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}

//�ж϶����Ƿ�Ϊ�գ���Ϊ�շ���ֵΪ1�����򷵻�ֵΪ0
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear) return OK;
	else return ERROR;
}

//���ٶ���
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

//����Ԫ��eΪQ���µĶ�βԪ��
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

//ɾ����βԪ��
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

//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK
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

//�����в��գ���e���ض�ͷԪ�ص�ֵ��������OK
Status GetTQueue(LinkQueue Q, QElemType &e)
{
	if (Q.front == Q.rear) return ERROR;
	e = Q.front->data;
	return OK;
}

//������У��Ƚ��ȳ���
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

//���������ݹ鴴����
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

//�ȸ��������������ǵݹ��㷨��
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

//���������T���ǵݹ��㷨��
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

//��α��������ǵݹ��㷨��
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

//�����������(�ǵݹ��㷨)�����ò�α���Ϊÿ���ڵ�������ڲ㣬��������һ�������
Status CSTreeDepth(CSTree T)
{
	LinkQueue Q; CSTree q; InitQueue(Q);
	CSTree s; 
	q = T;                                     //��ʼ��q����ֹ�˱���������
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

//�����������Ҷ�ӽڵ㣨�ǵݹ��㷨��
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

//�������Ҷ�ӽڵ������ǵݹ��㷨��
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


//������
void main()
{
	CSTree T; int Count = 0;
	printf("������������������������н���ֵ��\n");
	CreateCSTree(T);
	printf("�������Ϊ��%d\n", CSTreeDepth(T));
	printf("�ȸ�������������ǣ�\n");
	PreOrderTraverse(T);
	printf("\n");
	printf("���������������ǣ�\n");
	PostOrderTraverse(T);
	printf("\n");
	printf("��α�����������ǣ�\n");
	LevelOrderTraverse(T);
	printf("\n");
	printf("�������Ҷ�ӽ�㣺\n");
	LeafCountCSTree(T);
	printf("\n");
	printf("ͳ������Ҷ�ӽ�������%d\n", LeafCount(T));
	system("pause");
}
