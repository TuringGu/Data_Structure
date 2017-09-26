//����������ʽ��ʾ
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h> 
#include<windows.h>

//�������״̬���� 
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

//�������� ���е���ʽ����ṹ
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

//�ж�һ�������Ƿ�Ϊ�գ���Ϊ���򷵻�1�����򷵻�0
int QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear) return 1;
	else return 0;
}

//���ض��еĳ���
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

//�������Ԫ�ص�ֵ
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

//�õ���ͷԪ�ص�ֵ
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



//���ɶ���,����n��Ԫ��
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

//��Q��Ϊ�ն���
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

//������У��Ƚ��ȳ���
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

//ʵ��
void main()
{
	int i, n;
	QElemType k, h, a, f;
	LinkQueue Q;
	printf("����һ���ն��У�\n");
	InitQueue(Q);
	printf("�ж϶����Ƿ�Ϊ�գ�\n");
	printf("QueueEmpty(Q)=%d\n", QueueEmpty(Q));
	printf("�������е�Ԫ�ظ�����\n");
	scanf_s("%d", &n);
	printf("����%d��������е�Ԫ�ص�ֵ��\n", n);
	for (i = 0; i<n; i++)
	{
		scanf_s("%d", &k);
		EnQueue(Q, k);
	}
	printf("�������Ԫ�صĸ�����%d\n", QueueLength(Q));
	printf("�������Ԫ�ص�ֵ��\n");
	QueueTraverse(Q);
	printf("���������е�Ԫ�ص�ֵ��");
	scanf_s("%d", &h);
	EnQueue(Q, h);
	printf("�������һ������Ԫ�غ����Ԫ�ص�ֵ��\n");
	QueueTraverse(Q);
	DeQueue(Q, a);
	printf("�����1��ɾ���Ķ�ͷԪ�ص�ֵ��%d\n", a);
	DeQueue(Q, a);
	printf("�����2��ɾ���Ķ�ͷԪ�ص�ֵ��%d\n", a);
	printf("�������ɾ����ͷԪ�غ���е�Ԫ��ֵ��");
	QueueTraverse(Q);
	GetHead(Q, f);
	printf("�����ͷԪ�ص�ֵ��%d\n", f);
	printf("�������Ԫ�صĸ�����%d\n", QueueLength(Q));
	printf("��Q��Ϊ�ն��У�\n");
	ClearQueue(Q);
	printf("�������Ԫ�صĸ�����%d\n", QueueLength(Q));
	printf("�ж϶����Ƿ�Ϊ�գ�\n");
	printf("QueueEmpty(Q)=%d\n", QueueEmpty(Q));
	Sleep(20000);
}
