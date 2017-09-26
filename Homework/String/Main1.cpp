//串的定长顺序存储表示————————————
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<malloc.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
#define MAXSTRLEN 255	
typedef unsigned char SString[MAXSTRLEN + 1];

//用T返回由S1和S2联接而成的新串。若未截断，则返回TRUE，否则FALSE
Status Concat(SString &T, SString S1, SString S2)
{
	int uncut; int i;
	if (S1[0] + S2[0] <= MAXSTRLEN)
	{
		for (i = 1; i <= S1[0]; i++)
		{
			T[i] = S1[i];
		}
		for (i = 1; i <= S2[0]; i++)
		{
			T[S1[0] + i] = S2[i];
		}
		T[0] = S1[0] + S2[0]; uncut = TRUE;
	}
	else if (S1[0] < MAXSTRLEN)
	{
		for (i = 1; i <= S1[0]; i++)
		{
			T[i] = S1[i];
		}
		for (i = 1; i <= (MAXSTRLEN - S1[0]); i++)
		{
			T[S1[0] + i] = S2[i];
		}
		T[0] = MAXSTRLEN; uncut = FALSE;
	}
	else
	{
		for (i = 1; i <= MAXSTRLEN; i++)
		{
			T[i] = S1[i];
		}
		uncut = FALSE;
	}
	return uncut;
}


//用Sub返回串S的第pos个字符起长度为len的字串
Status SubString(SString &Sub, SString S, int pos, int len)
{
	int i;
	if (pos<1 || pos>S[0] || len < 0 || len>S[0] - pos + 1)
		return ERROR;
	for (i = 1; i <=len ; i++)
	{
		Sub[i] = S[pos + i-1];
	}
	Sub[0] = len; return OK;
}



//主函数
int main()
{
	SString T, S1, S2, S, Sub;
	int i, pos, len;
	char e;
	printf("输入串S1的长度：");
	scanf("%d", &S1[0]);      //接收串的长度
	scanf("%c", &e);         //接收回车键，否则S1[1]将接收回车键，使串S1的值出现错误
	printf("输入串S1的值：");
	for (i = 1; i <= S1[0]; i++)
	{
		scanf("%c", &S1[i]);
	}
	printf("输出串S1的值：\n");
	for (i = 1; i <= S1[0]; i++)
	{
		printf("%c", S1[i]);
	}
	printf("\n");
	printf("输入串S2的长度：");
	scanf("%d", &S2[0]);      //接收串的长度
	scanf("%c", &e);         //接收回车键，否则S2[1]将接收回车键，使串S2的值出现错误
	printf("输入串S2的值：");
	for (i = 1; i <= S2[0]; i++)
	{
		scanf("%c", &S2[i]);
	}
	printf("输出串S2的值：\n");
	for (i = 1; i <= S2[0]; i++)
	{
		printf("%c", S2[i]);
	}
	printf("\n");
	Concat(T, S1, S2);
	printf("输出串S1和串S2的联接串T的值：\n");
	for (i = 1; i <= T[0]; i++)
	{
		printf("%c", T[i]);
	}
	printf("\n");
	printf("输入串S的长度：");
	scanf("%d", &S[0]);      //接收串的长度
	scanf("%c", &e);        //接收回车键，否则S[1]将接收回车键，使串S的值出现错误
	printf("输入串S的值：");
	for (i = 1; i <= S[0]; i++)
	{
		scanf("%c", &S[i]);
	}
	printf("输出串S的值：\n");
	for (i = 1; i <= S[0]; i++)
	{
		printf("%c", S[i]);
	}
	printf("\n");
	printf("输入串S的子串Sub的开始字符位置：");
	scanf("%d", &pos);
	printf("输入串S的子串Sub的长度：");
	scanf("%d", &len);
	SubString(Sub, S, pos, len);
	printf("输出子串Sub的值：\n");
	for (i = 1; i <= Sub[0]; i++)
	{
		printf("%c", Sub[i]);
	}
	printf("\n");
	Sleep(20000);
}

