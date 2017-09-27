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

//Quick Sort------------------------------------------------------------------
int Partition(SqList &L, int low, int high)        //����˳���L���ӱ�r[low..high]�ļ�¼�������¼��λ������
{                                                  //��������λ�ã���ʱ����֮ǰ��֮�󣩵ļ�¼������С������
	int pivotkey;
	L.r[0] = L.r[low];                             //���ӱ�ĵ�һ����¼�������¼
	pivotkey = L.r[low].key;                       //�����¼�ؼ���
	while (low < high)                             //�ӱ�����˽�������м�ɨ��
	{
		while (low < high&&L.r[high].key >= pivotkey) --high;
		L.r[low] = L.r[high];                      //���������¼С�ļ�¼�Ƶ��Ͷ�
		while (low < high&&L.r[low].key <= pivotkey) ++low;
		L.r[high] = L.r[low];                      //���������¼��ļ�¼�Ƶ��߶�
	}
	L.r[low] = L.r[0];                             //�����¼��λ
	return low;                                    //��������λ��
}//Partition

void QSort(SqList &L, int low, int high)           //��˳���L�е�������L.r[low..high]����������
{
	int pivotloc;
	if (low < high)                                //���ȴ���1
	{
		pivotloc = Partition(L, low, high);        //��L.r[low..high]һ��Ϊ��
		QSort(L, low, pivotloc - 1);               //�Ե��ӱ�ݹ�����pivotloc������λ��
		QSort(L, pivotloc + 1, high);              //�Ը��ӱ�ݹ�����
	}
}//QSort

void QuickSort(SqList &L)                          //��˳���L����������
{
	QSort(L, 1, L.length);
}//QuickSort
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
	QuickSort(L);
	printf("�����������������£�\n");
	DispList(L);
	system("pause");
}