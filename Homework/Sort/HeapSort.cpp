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

//˳��̬����洢�ṹ
#define MAXSIZE 20          //һ������������С˳������󳤶�
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
	int length;             //˳�����
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
		printf("%-2d ", L.r[i]);
	}
	printf("\n");
	return OK;
}

typedef SqList HeapType;                       //�Ѳ���˳���洢��ʾ
//Heap Sort--------------------------------------------------------------------
void HeapAdjust(HeapType &H, int s, int m)       //��֪H.r[s..m]�м�¼�Ĺؼ��ֳ�H.r[s].key֮�������ѵ�
{                                                //���壬����������H.r[s]�Ĺؼ��֣�ʹH.r[s..m]��Ϊһ��
	                                             //��Ѷ��������м�¼�Ĺؼ��ֶ��ԣ�
	RedType rc; int j = 0;
	rc = H.r[s];
	for (j = 2 * s; j <= m; j *= 2)              //��key�ϴ�ĺ��ӽ������ɸѡ
	{
		if (j < m&&LT(H.r[j].key, H.r[j + 1].key))
			++j;                                 //jΪkey�ϴ�ļ�¼���±�
		if (!LT(rc.key, H.r[j].key)) break;      //rcӦ������λ��s��
		H.r[s] = H.r[j]; s = j;
	}
	H.r[s] = rc;                                 //����
}//HeapAdjust

void HeapSort(HeapType &H)                       //��˳�����ж�����
{
	int i; int temp = 0;
	for (i = H.length / 2; i > 0; --i)           //��H.r[1..H.length]���ɴ󶥶�
		HeapAdjust(H, i, H.length);
	for (i = H.length; i > 1; --i)               //���Ѷ���¼�͵�ǰδ������������Hr[1..i]��
	{                                            //���һ����¼�໥����
		temp = H.r[1].key;
		H.r[1].key = H.r[i].key;
		H.r[i].key = temp;
		HeapAdjust(H, 1, i - 1);                 //��H.r[1..i-1]���µ���Ϊ�󶥶�
	}
}//HeapSort

//-----------------------------------------------------------------------------

//main function
void main()
{
	SqList L;
	int n;
	printf("��ʼ��˳���");
	InitList(L);
	if (L.length == 0)
		printf("˳���Ϊ�գ�\n");
	printf("����˳����Ԫ�ظ�����");
	scanf_s("%d", &n); getchar();
	printf("����%d��Ԫ�أ�\n", n);
	CreateList(L, n); getchar();
	printf("���%d��Ԫ�ص�˳������£�\n", n);
	DispList(L);
	HeapSort(L);
	printf("���������������£�\n");
	DispList(L);
	system("pause");
}