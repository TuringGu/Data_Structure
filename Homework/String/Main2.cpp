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
	char *ch;            //若串为非空串，则按串长分配存储区，否则ch为NULL
	int length;          //串长度
}HString;

//生成一个其值等于串常量chars的串T
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

//在串S的第pos个字符前插入串T 
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

//返回S的元素个数，称为串的长度
int StrLength(HString S)
{
	return S.length;
}

//若S>T，则返回值>0；若S=T,则返回值=0;若S<T,则返回值<0
int StrCompare(HString S, HString T)
{
	int i;
	for (i = 0; i < S.length&&i < T.length; ++i)
	if (S.ch[i] != T.ch[i]) return S.ch[i] - T.ch[i];
	return S.length - T.length;
}

//将S清为空串
Status ClearString(HString &S)
{
	if (S.ch) { free(S.ch); S.ch = NULL; }
	S.length = 0;
	return	OK;
}

//用T返回由S1和S2联接而成的新串
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

//用Sub返回串S的第pos个字符起长度为len的字串
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

//将串T的值复制到串S中
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

//显示串
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

//删除串中第pos个字符起，长度为len的字串
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


//主函数
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
	printf("输出字符串常量chars：%s\n", chars);
	StrAssign(T, chars);
	printf("生成一个其值等于串常量chars的串T：");
	DispStr(T);
	StrCopy(S, T);
	printf("将串T的值复制到串S中，串S的值为：");
	DispStr(S);
	printf("串S的长度为：%d\n", StrLength(S));
	printf("比较串S和串T的大小：%d\n", StrCompare(S, T));
	printf("将S清为空串！\n");
	ClearString(S);
	printf("串S的值为：");
	DispStr(S);
	printf("串T的值为：");
	DispStr(T);
	a = str;
	printf("输入串S1：");
	scanf("%s", a);
	StrAssign(S1, a);
	printf("串S1的值为：");
	DispStr(S1);
	printf("输入串S2：");
	scanf("%s", a);
	StrAssign(S2, a);
	printf("串S2的值为：");
	DispStr(S2);
	printf("返回由S1和S2联接而成的新串S：");
	Concat(S, S1, S2);
	DispStr(S);
	printf("输入S的子串的起始字符位置：");
	scanf("%d", &pos);
	printf("输入S的子串的长度：");
	scanf("%d", &len);
	printf("用Sub返回串S的第%d个字符起长度为%d的子串：", pos, len);
	SubString(Sub, S, pos, len);
	DispStr(Sub);
	printf("输入串S的插入位置：");
	scanf("%d", &pos);
	printf("在串S的第%d个位置插入串T，插入后串S的值为：", pos);
	StrInsert(S, pos, T);
	DispStr(S);
	printf("输入串S删除的子串的起始字符位置：");
	scanf("%d", &pos);
	printf("输入串S删除的子串的长度：");
	scanf("%d", &len);
	printf("串S中删除第%d个字符起长度为%d的子串，删除后S的值为：", pos, len);
	StrDelete(S, pos, len);
	DispStr(S);
	Sleep(20000);
}
