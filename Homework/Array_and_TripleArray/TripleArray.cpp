//ϵ���������Ԫ��˳���洢��ʾ
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


#define MAXSIZE 12500             //�������Ԫ���������ֵΪ12500 
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int ElemType;
typedef char Status;

typedef struct{                 
	int i, j;                      //�÷���Ԫ�����±�����±�
	ElemType e;
}Triple;
 
typedef struct{                   
	Triple data[MAXSIZE + 1];      //����Ԫ��Ԫ���data[0]δ��
	int mu, nu, tu;                //����������������ͷ���Ԫ����
}TSMatrix;

#define  MU        5
#define  NU        6
Status CreateMatrix(TSMatrix &M){//����һ����Ԫ���
	int e, i, j, k = 1;
	int status = 0;
	M.mu = MU; M.nu = NU;
	srand((unsigned)time(NULL));
	M.tu = rand() % 15;
	for (i = 1; i <= M.mu; i++)
	{
		for (j = 1; j <= M.nu; j++)
		{
			e = rand() % 3;
			if (e != 0)
			{
				M.data[k].i = i;
				M.data[k].j = j;
				M.data[k].e = e;
				k++;
				if ((k - 1) == M.tu)
				{
					status = 1;
					break;
				}
			}
		}
		if (status) break;
	}
	return OK;
}


void print(TSMatrix M){//�����Ԫ�����Ԫ��ֵ
	int k;
	printf("mu=%-2d,  nu=%-2d,  tu=%-2d", M.mu, M.nu, M.tu);
	printf("\n");
	for (k = 1; k <= M.tu; k++){
		printf("i=%-2d,  j=%-2d,  e=%-2d", M.data[k].i, M.data[k].j, M.data[k].e);
		printf("\n");
	}
}


//������Ԫ���洢��ʾ����ϡ�����M��ת�þ���T(ת�������㷨)
Status TransposeSMatrix(TSMatrix M, TSMatrix &T)
{
	int q, col, p;
	T.mu = M.nu; T.nu = M.mu; T.tu = M.tu;
	if (T.tu)
	{
		q = 1;
		for (col = 1; col <= M.nu; ++col)
		    for (p = 1; p <= M.tu; ++p)
		        if (M.data[p].j == col)
		        {
			        T.data[q].i = M.data[p].j; T.data[q].j = M.data[p].i;
			        T.data[q].e = M.data[p].e; ++q;
	            }
	}
	return OK;
}

//����Ŀ���ת��
Status FastTransposeSMatrix(TSMatrix M, TSMatrix &T)
{
	int col, t, p,q; 
	T.mu = M.nu; T.nu = M.mu; T.tu = M.tu;
	int num[NU+1], cpot[NU+1];
	if (T.tu)
	{
		for (col = 1; col <= M.nu; ++col)
			num[col] = 0;
		for (t = 1; t <= M.tu; ++t) 
			++num[M.data[t].j];  //��M��ÿһ�к�����Ԫ����
		cpot[1] = 1;              //���col���е�һ������Ԫ��b.data�е����
		for (col = 2; col <= M.nu; ++col)  
			cpot[col] = cpot[col - 1] + num[col - 1];
		for (p = 1; p <= M.tu; ++p)
		{
			col = M.data[p].j; q = cpot[col];    //qΪ��Ԫ��ת�þ����д���λ�ô���
			T.data[q].i = M.data[p].j; T.data[q].j = M.data[p].i;
			T.data[q].e = M.data[p].e; ++cpot[col];
		}
	}
	return OK;
}


//������
int main(){
	TSMatrix M, T,TF;
	CreateMatrix(M);
	TransposeSMatrix(M, T);
	printf("���ϡ�����M��\n");
	print(M);
	printf("���ת�þ���T��\n");
	print(T);
	FastTransposeSMatrix(M, TF);
	printf("�������ת�þ���\n");
	print(TF);
	Sleep(200000);
}
