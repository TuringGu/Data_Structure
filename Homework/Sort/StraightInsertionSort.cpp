//ͷ�ļ�
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

//--����ֵ�͹ؼ���
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)< (b))
#define LQ(a,b) ((a)<=(b))

/*//--���ַ����͹ؼ���
#define EQ(a,b) (!strcmp((a),(b)))
#define LT(a,b) (strcmp((a),(b))<0)
#define LQ(a,b) (strcmp((a),(b))<=0)
*/

//˳��̬�����洢�ṹ
#define MAXSIZE 20          //һ������������С˳�������󳤶�
typedef int KeyType;        //����ؼ�������Ϊ��������
typedef int InfoType;       //������������������Ϊ��������
typedef int Status;
typedef char ElemType;
typedef struct
{
	KeyType key;            //�ؼ�����
	InfoType otherinfo;     //����������
}RedType;                   //��¼����
typedef struct
{
	RedType r[MAXSIZE + 1]; //r[0]���û������ڱ���Ԫ
	int length;             //˳�������
}SqList;                    //˳�������

//��ʼ������
Status InitList(SqList &L)
{
	L.length = 0;
	return OK;
}

//����˳���
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

//���˳���
Status DispList(SqList L)
{
	int i = 0;
	for (i = 1; i <= L.length; i++)
	{
		printf("%-2d", L.r[i]);
	}
	printf("\n");
	return OK;
}

//Straight Insertion Sort
void InsertSort(SqList &L)
{
	int i = 0; int j = 0;
	for (i = 2; i <= L.length; ++i)
		if (LT(L.r[i].key, L.r[i - 1].key))         //"<"���轫L.r[i]���������ӱ�
		{
			L.r[0] = L.r[i];                        //����Ϊ�ڱ�
			L.r[i] = L.r[i - 1];
			for (j = i - 2; LT(L.r[0].key, L.r[j].key); --j)
				L.r[j + 1] = L.r[j];                //��¼����
			L.r[j + 1] = L.r[0];
		}
}//InsertSort

//main function
void main()
{
	SqList L;
	int n;
	printf("��ʼ��˳�����");
	InitList(L);
	if (L.length == 0)
		printf("˳���Ϊ�գ�\n");
	printf("����˳�����Ԫ�ظ�����"); 
	scanf_s("%d", &n); getchar();
	printf("����%d��Ԫ�أ�\n", n);
	CreateList(L, n); getchar();
	printf("���%d��Ԫ�ص�˳������£�\n", n);
	DispList(L);
	InsertSort(L);
	printf("ֱ�Ӳ������������£�\n");
	DispList(L);
	system("pause");
}