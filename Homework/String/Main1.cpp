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

//��T������S1��S2���Ӷ��ɵ��´�����δ�ضϣ��򷵻�TRUE������FALSE
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



//������
int main()
{
	SString T, S1, S2, S, Sub;
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
	printf("�����S2��ֵ��\n");
	for (i = 1; i <= S2[0]; i++)
	{
		printf("%c", S2[i]);
	}
	printf("\n");
	Concat(T, S1, S2);
	printf("�����S1�ʹ�S2�����Ӵ�T��ֵ��\n");
	for (i = 1; i <= T[0]; i++)
	{
		printf("%c", T[i]);
	}
	printf("\n");
	printf("���봮S�ĳ��ȣ�");
	scanf("%d", &S[0]);      //���մ��ĳ���
	scanf("%c", &e);        //���ջس���������S[1]�����ջس�����ʹ��S��ֵ���ִ���
	printf("���봮S��ֵ��");
	for (i = 1; i <= S[0]; i++)
	{
		scanf("%c", &S[i]);
	}
	printf("�����S��ֵ��\n");
	for (i = 1; i <= S[0]; i++)
	{
		printf("%c", S[i]);
	}
	printf("\n");
	printf("���봮S���Ӵ�Sub�Ŀ�ʼ�ַ�λ�ã�");
	scanf("%d", &pos);
	printf("���봮S���Ӵ�Sub�ĳ��ȣ�");
	scanf("%d", &len);
	SubString(Sub, S, pos, len);
	printf("����Ӵ�Sub��ֵ��\n");
	for (i = 1; i <= Sub[0]; i++)
	{
		printf("%c", Sub[i]);
	}
	printf("\n");
	Sleep(20000);
}

