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


//�������Ķ�������洢��ʾ
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode *lchild, *rchild;    //���Һ���ָ��
	int visitcount;                     //�������Ҫ�õ�
}BiTNode, *BiTree;

//˳��ջ���塪��������������������������������������������������������������������������
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
		printf("%d ",*S.base);
		++S.base;
	}
	printf("\n");
}
//����������������������������������������������������������������������������������

//�������� ���е���ʽ����ṹ��������������������������������������������������������
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
	free( p->next);
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
//������������������������������������������������������������������������������������������������


//��ʼ����������
Status InitBiTree(BiTree &T)
{
	T = (BiTNode*)malloc(sizeof(BiTNode));
	if (T) return OK;
	else return ERROR;
}


//������������ʾ�Ķ�����T������������죬�ո��ַ���ʾ������һ���ַ���Ӧһ���ڵ�
Status CreateBiTree(BiTree &T)
{
	char ch;
	scanf_s("%c", &ch);
	if (ch == ' ') T = NULL;
	else
	{
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
		T->data = ch;             //���ɸ��ڵ�
		T->visitcount = 0;
		CreateBiTree(T->lchild);  //������ָ��
		CreateBiTree(T->rchild);  //������ָ��
	}
	return OK;
}


//����������������ǵݹ��㷨��
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


//����������������ǵݹ��㷨��
Status InOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	SqStack S; BiTree p;
	InitStack(S); Push(S, T);   //��ָ���ջ
	while (!StackEmpty(S))
	{
		while (GetTop(S, p) && p) Push(S, p->lchild);   //�����ߵ���ͷ
		Pop(S, p);            //��ָ����ջ
		if (!StackEmpty(S))   //���ʽ�㣬����һ��
		{
			Pop(S, p); if (!Visit(p->data)) return ERROR;
			Push(S, p->rchild);
		}
	}
	return OK;
}


//*****�������������*****// visitcountֵ�ᱻ�ı��Ǹ�ȱ��
void PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e))         //��ջ���εĽڵ���з���
{
	SqStack S;
	BiTree p = T;
	InitStack(S);
	while (p || !StackEmpty(S))         //��ջS�ǿջ���pָ��ǿ�ʱ�����в���
	{
		if (p)                          //��pָ��ǿ�
		{
			if (p->visitcount != 2)     //��pָ����ʴ�����Ϊ��������Ϊһ������ջ
			{
				p->visitcount = 1;
				Push(S, p);
			}
			p = p->lchild;              //�����ߵ���ͷ
		}
		else                            //��pָ��Ϊ��
		{
			Pop(S, p);
			if (p->visitcount == 2)     //��pָ����ʴ���Ϊ�������ʴ˽ڵ�
			{
				Visit(p->data);
			}
			else
			{                           //����Ϊ�������ʴ�����һ������ջ
				p->visitcount++;
				Push(S, p);
			}
			p = p->rchild;              //������һ��
		}
	}
}

//��α������������ǵݹ��㷨��
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

//���ض����������(�ǵݹ��㷨)
Status Depth(BiTree T)
{
	SqStack S; BiTree p;
	int num = 0; T->visitcount = 1;
	InitStack(S); Push(S, T);   //��ָ���ջ
	while (!StackEmpty(S))
	{
		while (GetTop(S, p) && p)
		{
			if (p->lchild)
			    p->lchild->visitcount = p->visitcount + 1;
			Push(S, p->lchild);   //�����ߵ���ͷ
		}
		Pop(S, p);            //��ָ����ջ
		if (!StackEmpty(S))   //���ʽ�㣬����һ��
		{
			Pop(S, p); 
			if (!(p->rchild))  //����ָ��Ϊ�գ���num���浱ǰ����֧���ֵ����ջ
			{
				num = p->visitcount> num ? p->visitcount : num;    //��num���浱ǰ����֧���ֵ
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


//�������Ҷ�ӽڵ������ǵݹ��㷨��
Status LeafCount(BiTree T)
{
	SqStack S; BiTree p; int count=0;
	InitStack(S); Push(S, T);   //��ָ���ջ
	while (!StackEmpty(S))
	{
		while (GetTop(S, p) && p) Push(S, p->lchild);   //�����ߵ���ͷ
		Pop(S, p);            //��ָ����ջ
		if (!StackEmpty(S))   //���ʽ�㣬����һ��
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


//�����������������������ǵݹ��㷨��
Status ExchangeBiTree(BiTree T)
{
	LinkQueue Q; InitQueue(Q);
	BiTree e; BiTree q;
	EnQueue(Q, T);
	while (!QueueEmpty(Q))
	{
		while (DeQueue(Q, e) && e)
		{
			q = e->lchild;                //����ָ�뽻��
			e->lchild = e->rchild;
			e->rchild = q;
			EnQueue(Q, e->lchild);
			EnQueue(Q, e->rchild);
		}
	}
	return OK;
}





//���������
Status PrintElement(TElemType e)
{
	printf("%-2c",e);
	return OK;
}


//������
void main()
{
	BiTree T;
	printf("�������������������������������н���ֵ��\n");
	CreateBiTree(T);
	printf("�������������������ǣ�\n");
	PreOrderTraverse(T, PrintElement);
	printf("\n");
	printf("�������������������ǣ�\n");
	InOrderTraverse(T, PrintElement);
	printf("\n");
	printf("�������������������ǣ�\n");
	PostOrderTraverse(T, PrintElement);
	printf("\n");
	printf("��α���������������ǣ�\n");
	LevelOrderTraverse(T, PrintElement);
	printf("\n");
	printf("�����������Ϊ��%d\n", Depth(T));
	printf("�����������Ҷ�ӽ�㣺%d\n",LeafCount(T));
	printf("��������������������\n");
	ExchangeBiTree(T);
	printf("��α���������������ǣ�\n");
	LevelOrderTraverse(T, PrintElement);
	printf("\n");
	Sleep(300000);
}
