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

typedef struct{
	char *ch;            //����Ϊ�ǿմ����򰴴�������洢��������chΪNULL
	int length;          //������
}HString;

//����һ����ֵ���ڴ�����chars�Ĵ�T
Status StrAssign(HString &T, char *chars)
{
	int i; int n; char *c;
	if (T.ch) free(T.ch);
	for (i = 0, c = chars; *c; ++i, ++c);
	if (!i) { T.ch = NULL; T.length = 0; }
	else
	{
		if (!(T.ch = (char*)malloc(i*sizeof(char))))
			exit(OVERFLOW);
		for (n = 0; n <= i - 1; n++)
		{
			T.ch[n] = chars[n];
			T.length = i;
		}
		T.length = i;
	}
	return OK;
}

//�ڴ�S�ĵ�pos���ַ�ǰ���봮T 
Status StrInsert(HString &S, int pos, HString T)
{
	int i;
	if (pos<1 || pos>S.length + 1) return ERROR;
	if (T.length)
	{
		if (!(S.ch = (char *)realloc(S.ch, (S.length + T.length)*sizeof(char))))
			exit(OVERFLOW);
		for (i = S.length - 1; i >= pos - 1; --i)
		{
			S.ch[i + T.length] = S.ch[i];
		}
		for (i = 0; i <= T.length - 1; i++)
		{
			S.ch[pos - 1 + i] = T.ch[i];
		}
		S.length += T.length;
	}
	return OK;
}

//����S��Ԫ�ظ�������Ϊ���ĳ���
int StrLength(HString S)
{
	return S.length;
}

//��S>T���򷵻�ֵ>0����S=T,�򷵻�ֵ=0;��S<T,�򷵻�ֵ<0
int StrCompare(HString S, HString T)
{
	int i;
	for (i = 0; i < S.length&&i < T.length; ++i)
	if (S.ch[i] != T.ch[i]) return S.ch[i] - T.ch[i];
	return S.length - T.length;
}

//��S��Ϊ�մ�
Status ClearString(HString &S)
{
	if (S.ch) { free(S.ch); S.ch = NULL; }
	S.length = 0;
	return	OK;
}

//��T������S1��S2���Ӷ��ɵ��´�
Status Concat(HString &T, HString S1, HString S2)
{
	int i;
	if (T.ch) free(T.ch);
	if (!(T.ch = (char *)malloc((S1.length + S2.length)*sizeof(char))))
		exit(OVERFLOW);
	for (i = 0; i <= S1.length - 1; i++)
	{
		T.ch[i] = S1.ch[i];
	}
	T.length = S1.length + S2.length;
	for (i = 0; i <= S2.length - 1; i++)
	{
		T.ch[S2.length + i] = S2.ch[i];
	}
	return OK;
}

//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���ִ�
Status SubString(HString &Sub, HString S, int pos, int len)
{
	int i;
	if (pos<1 || pos>S.length || len<0 || len>S.length - pos + 1)
		return ERROR;
	if (Sub.ch) free(Sub.ch);
	if (!len) { Sub.ch = NULL; Sub.length = 0; }
	else
	{
		Sub.ch = (char *)malloc(len *sizeof(char));
		for (i = 0; i <= len - 1; i++)
		{
			Sub.ch[i] = S.ch[pos - 1 + i];
		}
		Sub.length = len;
	}
	return OK;
}

//����T��ֵ���Ƶ���S��
Status StrCopy(HString &S, HString T)
{
	int i;
	if (S.ch) free(S.ch);
	if (!T.length) { S.ch = NULL; S.length = 0; }
	else
	{
		if (!(S.ch = (char *)malloc(StrLength(T)*sizeof(char))))
			exit(OVERFLOW);
		for (i = 0; i <= StrLength(T) - 1; i++)
		{
			S.ch[i] = T.ch[i];
			S.length = i + 1;
		}
	}
	return OK;
}

//��ʾ��
Status DispStr(HString T)
{
	int i;
	for (i = 0; i <= T.length - 1; i++)
	{

		printf("%c", T.ch[i]);
	}
	printf("\n");
	return OK;
}

//ɾ�����е�pos���ַ��𣬳���Ϊlen���ִ�
Status StrDelete(HString &S, int pos, int len)
{
	int i;
	if (pos<1 || pos>S.length || len < 0 || len>S.length - pos + 1)
		return ERROR;
	HString temp;
	if (!(temp.ch = (char *)malloc(S.length*sizeof(char))))
		exit(OVERFLOW);
	for (i = 0; i <= S.length - len - pos + 1; i++)
	{
		S.ch[pos - 1 + i] = S.ch[pos + len - 1 + i];
	}
	for (i = 0; i <= S.length - 1 - len; i++)
	{
		temp.ch[i] = S.ch[i];
	}
	if (S.ch) free(S.ch);
	S.ch = temp.ch;
	S.length = S.length - len;
	temp.ch = NULL;
	return OK;
}


//������
int main()
{
	HString T, S, S1, S2, Sub;
	int pos, len;
	char *a, str[100], *chars = "House";
	T.ch = NULL;
	S.ch = NULL;
	S1.ch = NULL;
	S2.ch = NULL;
	Sub.ch = NULL;
	printf("����ַ�������chars��%s\n", chars);
	StrAssign(T, chars);
	printf("����һ����ֵ���ڴ�����chars�Ĵ�T��");
	DispStr(T);
	StrCopy(S, T);
	printf("����T��ֵ���Ƶ���S�У���S��ֵΪ��");
	DispStr(S);
	printf("��S�ĳ���Ϊ��%d\n", StrLength(S));
	printf("�Ƚϴ�S�ʹ�T�Ĵ�С��%d\n", StrCompare(S, T));
	printf("��S��Ϊ�մ���\n");
	ClearString(S);
	printf("��S��ֵΪ��");
	DispStr(S);
	printf("��T��ֵΪ��");
	DispStr(T);
	a = str;
	printf("���봮S1��");
	scanf("%s", a);
	StrAssign(S1, a);
	printf("��S1��ֵΪ��");
	DispStr(S1);
	printf("���봮S2��");
	scanf("%s", a);
	StrAssign(S2, a);
	printf("��S2��ֵΪ��");
	DispStr(S2);
	printf("������S1��S2���Ӷ��ɵ��´�S��");
	Concat(S, S1, S2);
	DispStr(S);
	printf("����S���Ӵ�����ʼ�ַ�λ�ã�");
	scanf("%d", &pos);
	printf("����S���Ӵ��ĳ��ȣ�");
	scanf("%d", &len);
	printf("��Sub���ش�S�ĵ�%d���ַ��𳤶�Ϊ%d���Ӵ���", pos, len);
	SubString(Sub, S, pos, len);
	DispStr(Sub);
	printf("���봮S�Ĳ���λ�ã�");
	scanf("%d", &pos);
	printf("�ڴ�S�ĵ�%d��λ�ò��봮T�������S��ֵΪ��", pos);
	StrInsert(S, pos, T);
	DispStr(S);
	printf("���봮Sɾ�����Ӵ�����ʼ�ַ�λ�ã�");
	scanf("%d", &pos);
	printf("���봮Sɾ�����Ӵ��ĳ��ȣ�");
	scanf("%d", &len);
	printf("��S��ɾ����%d���ַ��𳤶�Ϊ%d���Ӵ���ɾ����S��ֵΪ��", pos, len);
	StrDelete(S, pos, len);
	DispStr(S);
	Sleep(20000);
}
