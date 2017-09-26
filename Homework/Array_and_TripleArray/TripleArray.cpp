//系数矩阵的三元组顺序表存储表示
#include<stdarg.h>        //标准头文件，提供宏va_start.va_arg和va_end,用于存取变长参数表
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h> 
#include<windows.h>
#include<time.h>

//函数结果状态代码 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define UNDERFLOW -3


#define MAXSIZE 12500             //假设非零元个数的最大值为12500 
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int ElemType;
typedef char Status;

typedef struct{                 
	int i, j;                      //该非零元的行下标和列下标
	ElemType e;
}Triple;
 
typedef struct{                   
	Triple data[MAXSIZE + 1];      //非零元三元组表，data[0]未用
	int mu, nu, tu;                //矩阵的行数，列数和非零元个数
}TSMatrix;

#define  MU        5
#define  NU        6
Status CreateMatrix(TSMatrix &M){//建立一个三元组表
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


void print(TSMatrix M){//输出三元组表中元素值
	int k;
	printf("mu=%-2d,  nu=%-2d,  tu=%-2d", M.mu, M.nu, M.tu);
	printf("\n");
	for (k = 1; k <= M.tu; k++){
		printf("i=%-2d,  j=%-2d,  e=%-2d", M.data[k].i, M.data[k].j, M.data[k].e);
		printf("\n");
	}
}


//采用三元组表存储表示，求稀疏矩阵M的转置矩阵T(转置运算算法)
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

//矩阵的快速转置
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
			++num[M.data[t].j];  //求M中每一列含非零元个数
		cpot[1] = 1;              //求第col列中第一个非零元在b.data中的序号
		for (col = 2; col <= M.nu; ++col)  
			cpot[col] = cpot[col - 1] + num[col - 1];
		for (p = 1; p <= M.tu; ++p)
		{
			col = M.data[p].j; q = cpot[col];    //q为此元素转置矩阵中储存位置次序
			T.data[q].i = M.data[p].j; T.data[q].j = M.data[p].i;
			T.data[q].e = M.data[p].e; ++cpot[col];
		}
	}
	return OK;
}


//主函数
int main(){
	TSMatrix M, T,TF;
	CreateMatrix(M);
	TransposeSMatrix(M, T);
	printf("输出稀疏矩阵M：\n");
	print(M);
	printf("输出转置矩阵T：\n");
	print(T);
	FastTransposeSMatrix(M, TF);
	printf("输出快速转置矩阵：\n");
	print(TF);
	Sleep(200000);
}
