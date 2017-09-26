#include<stdio.h>
#include<malloc.h>
#include<stdlib.h> 
#include<windows.h>

//�������״̬���� 
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
	SElemType *base;    //��ջ����֮ǰ������֮��base��ֵΪNULL
	SElemType *top;     //ջ��ָ��
	int stacksize;      //��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}SqStack;

//����һ����ջ
ElemType InitStack(SqStack &S)
{
	S.base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

//����Ԫ��eΪ�µ�ջ��Ԫ��
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

//��ջ���գ�ɾ��S��ջ��Ԫ�أ���e������ֵ
ElemType Pop(SqStack &S, SElemType &e)
{
	if (S.top == S.base) e = ERROR;
	else e = *--S.top;
	return OK;
}

//���˳��ջԪ��ֵ
void StackTraverse(SqStack S)
{
	while (S.top != S.base)
	{
		printf("%d ", *S.base);
		++S.base;
	}
	printf("\n");
}

//�������˳��ջԪ��ֵ
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
	//ʹ�������ջS��������'('��'['ʱ��ջ������')'��']'��ջ���жϳ�ջԪ���Ƿ�Ϊ��Ӧ�ķ��ţ�
	//�����������һ���������㷨����
	SqStack S;
	InitStack(S);      // �����ջ
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
	printf("����������ŵı��ʽ��\n");
	scanf_s("%s", str);
	if (Correct(str) == OK)
		printf("����ƥ����ȷ��\n");
	else
		printf("����ƥ�䲻��ȷ��\n");
	Sleep(3000);
}