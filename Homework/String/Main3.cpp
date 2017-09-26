//���Ķ���˳��洢��ʾ������������������������
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

//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���ִ�
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

//��S>T,����ֵ>0;��=������ֵ=0;��<0������ֵ<0 
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
//������S�е�pos���ַ�֮�������T��ȵ��Ӵ����򷵻ص�һ���������Ӵ���S�е�λ�ã����򷵻�0 
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
 


//������
int main()
{
	SString S1, S2;
	int i, pos, len;
	char e;
	printf("���봮S1�ĳ��ȣ�");
	scanf("%d", &S1[0]);      //���մ��ĳ���
	scanf("%c", &e);         //���ջس���������S1[1]�����ջس�����ʹ��S1��ֵ���ִ���
	printf("���봮S1��ֵ��");
	for (i = 1; i <= S1[0]; i++)
	{
		scanf("%c", &S1[i]);
	}
	printf("�����S1��ֵ��\n");
	for (i = 1; i <= S1[0]; i++)
	{
		printf("%c", S1[i]);
	}
	printf("\n");
	printf("���봮S2�ĳ��ȣ�");
	scanf("%d", &S2[0]);      //���մ��ĳ���
	scanf("%c", &e);         //���ջس���������S2[1]�����ջس�����ʹ��S2��ֵ���ִ���
	printf("���봮S2��ֵ��");
	for (i = 1; i <= S2[0]; i++)
	{
		scanf("%c", &S2[i]);
	}
	printf("�����S2��ֵ��");
	for (i = 1; i <= S2[0]; i++)
	{
		printf("%c", S2[i]);
	}
	printf("\n"); 
    printf("�����Ӵ�ƥ�䣬���ص�һ���������Ӵ�S2��S1�е�λ��:%d",Index(S1,S2,1));
}


