#include<stdio.h>
#include<malloc.h>
#include<stdlib.h> 
#include<windows.h>

//函数结果状态代码 
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int ElemType;
typedef char SElemType;
typedef struct
{
	SElemType *base;    //在栈构造之前和销毁之后，base的值为NULL
	SElemType *top;     //栈顶指针
	int stacksize;      //当前已分配的存储空间，以元素为单位
}SqStack;

//构造一个空栈
ElemType InitStack(SqStack &S)
{
	S.base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

//插入元素e为新的栈顶元素
ElemType Push(SqStack &S, SElemType e)
{
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT)*sizeof(SElemType));
		if (!S.base) exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}

//若栈不空，删除S的栈顶元素，用e返回其值
ElemType Pop(SqStack &S, SElemType &e)
{
	if (S.top == S.base) e = ERROR;
	else e = *--S.top;
	return OK;
}

//输出顺序栈元素值
void StackTraverse(SqStack S)
{
	while (S.top != S.base)
	{
		printf("%d ", *S.base);
		++S.base;
	}
	printf("\n");
}

//逆序输出顺序栈元素值
void Stackoutput(SqStack S)
{
	ElemType e;
	while (S.top != S.base)
	{
		GetTop(S, e);
		printf("%d ", e);
		--S.top;
	}
	printf("\n");
}

ElemType Correct(SElemType str[]){
	//使用运算符栈S，当遇到'('、'['时进栈，遇到')'、']'出栈并判断出栈元素是否为相应的符号，
	//若是则继续下一个，否则算法结束
	SqStack S;
	InitStack(S);      // 构造空栈
	int i, state = 1;
	SElemType e;
	for (i = 0; str[i] != '\0'; i++)
	{
		switch (str[i])
		{
		case '(':Push(S, '('); break;
		case '[':Push(S, '['); break;
		case ')':
			Pop(S, e);
			if (e != '(')
				state = 0; break;
		case ']':
			Pop(S, e);
			if (e != '[')
				state = 0; break;
		}
		if (!state) break;//if(state==0) break;
	}
	if (S.top == S.base&& state == 1)
		return OK;
	else
		return ERROR;
}//Correct

int main()
{
	SElemType str[100];
	printf("请输入带括号的表达式：\n");
	scanf_s("%s", str);
	if (Correct(str) == OK)
		printf("括号匹配正确！\n");
	else
		printf("括号匹配不正确！\n");
	Sleep(3000);
}