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

//若S>T,返回值>0;若=，返回值=0;若<0，返回值<0 
int StrCompare(SString S,SString T)
{
	int i;
	for(i=0;i<=S[0]&&i<=T[0];++i)
	{
		if(S[i]!=T[i]) return S[i]-T[i];
	}
	return S[0]-T[0];
}

//Horspool 
//若主串S中第pos个字符之后存在与T相等的子串，则返回第一个这样的子串在S中的位置，否则返回0 
int Index(SString S,SString T,int pos)
{
	SString sub;
	int n,i,m;
	if(pos>0)
	{
		n=S[0]; m=T[0]; i=pos;
		while(i<=n-m+1)
		{
			SubString(sub,S,i,m);
			if(StrCompare(sub,T)!=0) ++i;
			else return i; 
		} 
	}
	return 0;
}
 


//主函数
int main()
{
	SString S1, S2;
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
	printf("输出串S2的值：");
	for (i = 1; i <= S2[0]; i++)
	{
		printf("%c", S2[i]);
	}
	printf("\n"); 
    printf("进行子串匹配，反回第一个这样的子串S2在S1中的位置:%d",Index(S1,S2,1));
}


