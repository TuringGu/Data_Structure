#include<stdarg.h>        //标准头文件，提供宏va_start.va_arg和va_end,用于存取变长参数表
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h> 
#include<windows.h>

//函数结果状态代码 
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
	ElemType *base;              //数组元素基址
	int dim;                     //数组维数
	int *bounds;                 //数组维界基址
	int *constants;              //数组映像函数常量基址
}Array;

//基本操作
Status InitArray(Array &A, int dim,...)    //构造数组若合理，则构造相应数组A，并返回OK
{
	int elemtotal; int i;
	va_list ap;
	if (dim<1 || dim>MAX_ARRAY_DIM) return ERROR;
	A.dim = dim;
	A.bounds = (int *)malloc(dim *sizeof(int));
	if (!A.bounds) exit(OVERFLOW);               //若各维长度合法，则存入A.bounds，并求出A的元素总数elemtotal
	elemtotal = 1; 
	va_start(ap, dim);                           //ap为va_list类型，是存放变长参数表信息的数组
	for (i = 0; i < dim; ++i)
	{
		A.bounds[i] = va_arg(ap, int);
		if (A.bounds[i] < 0) return UNDERFLOW;
		elemtotal *= A.bounds[i];
	}
	va_end(ap);
	A.base = (ElemType *)malloc(elemtotal*sizeof(ElemType));
	if (!A.base) exit(OVERFLOW);                  
	A.constants = (int *)malloc(dim*sizeof(int));//求映像函数的常函数ci，并存入A.constant[i-1],i=1,...,dim
	if (!A.constants) exit(OVERFLOW);
	A.constants[dim - 1] = 1;                    //L=1，指针的增减以元素的大小为单位
	for (i = dim - 2; i >=0; --i)
	{
		A.constants[i] = A.bounds[i + 1] * A.constants[i + 1];
	}
	return OK;
}

Status DestroyArray(Array &A)            //销毁数组A
{
	if (!A.base) return ERROR;
	free(A.base); A.base = NULL;
	if(!A.bounds) return ERROR;
	free(A.bounds); A.bounds = NULL;
	if(!A.constants) return ERROR;
	free(A.constants); A.constants = NULL;
	return OK;
}

Status Locate(Array A, va_list ap, int &off)     //若ap指示的各下标值合法，则求出该元素在A中的相对地址off
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

Status Value(ElemType &e, Array A, ...)    //用e赋值为所指定的A的元素，并返回OK
{
	int result; int off;
	va_list ap;
	va_start(ap, A);
	if ((result = Locate(A, ap, off)) ==OVERFLOW) return result; 
	e = *(A.base + off);
	return OK;
}

Status Assign(Array &A, ElemType e,...)      //A是n维数组，若下标不超界，则将e的值赋给所指定的A的元素，并返回OK
{                                            //vc++中...前不能用引用
	int result; int off;
	va_list ap; 
	va_start(ap, e);
	if ((result = Locate(A,ap, off)) ==OVERFLOW) return result;
	*(A.base + off) = e;
	return OK;
}



//主函数
void main()
{
	Array A;
	ElemType e = 0;
	InitArray(A, 3, 2, 3, 4);    //第2个参数为维数，后面3个参数是各维的长度
	Assign(A, 100, 1, 2, 3);      //第3-5个参数为各维的下标值，从0开始，最大值为各维的长度减一。
	if (Value(e,A,1, 2, 3) == OK) printf("输出e的值：%d\n", e);
	if (DestroyArray(A) == OK) printf("数组A销毁成功！\n");
	Sleep(200000);
}
