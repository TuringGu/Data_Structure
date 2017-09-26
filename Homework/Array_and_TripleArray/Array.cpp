#include<stdarg.h>        //��׼ͷ�ļ����ṩ��va_start.va_arg��va_end,���ڴ�ȡ�䳤������
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
#define UNDERFLOW -3


#define MaxSize 100 
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int ElemType;
typedef char Status;


#define MAX_ARRAY_DIM 8
typedef struct{
	ElemType *base;              //����Ԫ�ػ�ַ
	int dim;                     //����ά��
	int *bounds;                 //����ά���ַ
	int *constants;              //����ӳ����������ַ
}Array;

//��������
Status InitArray(Array &A, int dim,...)    //��������������������Ӧ����A��������OK
{
	int elemtotal; int i;
	va_list ap;
	if (dim<1 || dim>MAX_ARRAY_DIM) return ERROR;
	A.dim = dim;
	A.bounds = (int *)malloc(dim *sizeof(int));
	if (!A.bounds) exit(OVERFLOW);               //����ά���ȺϷ��������A.bounds�������A��Ԫ������elemtotal
	elemtotal = 1; 
	va_start(ap, dim);                           //apΪva_list���ͣ��Ǵ�ű䳤��������Ϣ������
	for (i = 0; i < dim; ++i)
	{
		A.bounds[i] = va_arg(ap, int);
		if (A.bounds[i] < 0) return UNDERFLOW;
		elemtotal *= A.bounds[i];
	}
	va_end(ap);
	A.base = (ElemType *)malloc(elemtotal*sizeof(ElemType));
	if (!A.base) exit(OVERFLOW);                  
	A.constants = (int *)malloc(dim*sizeof(int));//��ӳ�����ĳ�����ci��������A.constant[i-1],i=1,...,dim
	if (!A.constants) exit(OVERFLOW);
	A.constants[dim - 1] = 1;                    //L=1��ָ���������Ԫ�صĴ�СΪ��λ
	for (i = dim - 2; i >=0; --i)
	{
		A.constants[i] = A.bounds[i + 1] * A.constants[i + 1];
	}
	return OK;
}

Status DestroyArray(Array &A)            //��������A
{
	if (!A.base) return ERROR;
	free(A.base); A.base = NULL;
	if(!A.bounds) return ERROR;
	free(A.bounds); A.bounds = NULL;
	if(!A.constants) return ERROR;
	free(A.constants); A.constants = NULL;
	return OK;
}

Status Locate(Array A, va_list ap, int &off)     //��apָʾ�ĸ��±�ֵ�Ϸ����������Ԫ����A�е���Ե�ַoff
{
	off = 0; int i; int ind;
	for (i = 0; i < A.dim;++i)
	{
		ind = va_arg(ap, int);
		if (ind < 0 || ind >= A.bounds[i])
			return OVERFLOW;
		off += A.constants[i] * ind;
	}
	return OK;
}

Status Value(ElemType &e, Array A, ...)    //��e��ֵΪ��ָ����A��Ԫ�أ�������OK
{
	int result; int off;
	va_list ap;
	va_start(ap, A);
	if ((result = Locate(A, ap, off)) ==OVERFLOW) return result; 
	e = *(A.base + off);
	return OK;
}

Status Assign(Array &A, ElemType e,...)      //A��nά���飬���±겻���磬��e��ֵ������ָ����A��Ԫ�أ�������OK
{                                            //vc++��...ǰ����������
	int result; int off;
	va_list ap; 
	va_start(ap, e);
	if ((result = Locate(A,ap, off)) ==OVERFLOW) return result;
	*(A.base + off) = e;
	return OK;
}



//������
void main()
{
	Array A;
	ElemType e = 0;
	InitArray(A, 3, 2, 3, 4);    //��2������Ϊά��������3�������Ǹ�ά�ĳ���
	Assign(A, 100, 1, 2, 3);      //��3-5������Ϊ��ά���±�ֵ����0��ʼ�����ֵΪ��ά�ĳ��ȼ�һ��
	if (Value(e,A,1, 2, 3) == OK) printf("���e��ֵ��%d\n", e);
	if (DestroyArray(A) == OK) printf("����A���ٳɹ���\n");
	Sleep(200000);
}
