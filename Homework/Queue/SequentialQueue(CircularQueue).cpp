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
#define MAXQSIZE 100
typedef int QElemType;
typedef int Status;

//ѭ������ �����������е�˳�򴢴�ṹ��������
typedef struct
{
	QElemType *base;
	int front;
	int rear;
}SqQueue;

//ѭ�����еĻ����������㷨����
//����һ���ն���Q
Status InitQueue(SqQueue &Q)
{
	Q.base = (QElemType*)malloc(MAXQSIZE  * sizeof(QElemType));
	if (!Q.base) exit(OVERFLOW);
	Q.front = Q.rear = 0;
	return OK;
}

//�ж϶����Ƿ�Ϊ�գ���Ϊ�շ���1�����򷵻�0��
int QueueEmpty(SqQueue Q)
{
	if (Q.front == Q.rear) return 1;
	else return 0;
}

//����Q��Ԫ�ظ����������еĳ���
int QueueLength(SqQueue Q)
{
	return(Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

//ȡ��ͷԪ��,��eֵ����
Status GetHead(SqQueue Q, QElemType &e)
{
	if (Q.front == Q.rear) return ERROR;
	e = Q.base[Q.front];
	return OK;
}

//����Ԫ��eΪQ���µĶ�βԪ��
Status EnQueue(SqQueue &Q, QElemType &e)
{
	if ((Q.rear + 1) % MAXQSIZE == Q.front) return ERROR;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	return OK;
}

//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK
Status DeQueue(SqQueue &Q, QElemType &e)
{
	if (Q.front == Q.rear) return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	return OK;
}

//��ն���
int ClearQueue(SqQueue &Q)
{
	int e;
	while (Q.front != Q.rear)
	{
		DeQueue(Q, e);
	}
	return OK;
}

//����һ������,Ԫ�ظ���Ϊn
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

//��������Ԫ��ֵ�������ֵ
void QueueTravers(SqQueue Q)
{
	int i = 0;
	while ((Q.front+i )!= Q.rear)
	{
		printf("%d   ", Q.base[Q.front + i]);
		i++;
	}
}

//������У��Ƚ��ȳ���
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


//ʵ��
int main()
{
	SqQueue Q; QElemType i;
    QElemType j;
	InitQueue(Q);
	CreatQueue(Q);
	printf("�������Ԫ��ֵ��\n");
	QueueTravers(Q);
	printf("The length of the queue is:%d\n", QueueLength(Q));
	GetHead(Q, i);
	printf("ȡ��ͷԪ�أ�%d\n", i);
	printf("��βԪ�ز���һ��ֵ:");
	scanf_s("%d", &j);
	EnQueue(Q, j);
	printf("�������Ԫ��ֵ:");
	QueueTravers(Q);
	printf("ɾ����ͷԪ��\n");
	DeQueue(Q, j);
	QueueTravers(Q);
	printf("�������Ԫ�أ�");
	OutpQueue(Q);
	printf("��β����һ��ֵ��");
	scanf_s("%d", &j);
	EnQueue(Q, j);
	printf("��ն��С�\n");
	ClearQueue(Q);
	printf("�ж϶����Ƿ�Ϊ�գ�%d", QueueEmpty(Q));
	Sleep(20000);
}