#include<stdarg.h>        //��׼ͷ�ļ����ṩ��va_start.va_arg��va_end,���ڴ�ȡ�䳤������
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h> 
#include<windows.h>
#include<time.h>

//�������״̬���� 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define UNDERFLOW -3


typedef char TElemType;
typedef int Status;


//���Ķ������������ֵܣ��洢��ʾ���ݹ��㷨��������������������������������
typedef char ElemType;
typedef struct CSNode
{
	ElemType data;
	struct CSNode *firstchild, *nextsibling;
}CSNode,*CSTree;

//���������ݹ鴴����
Status CreateCSTree(CSTree &T)
{
	char ch;
	scanf_s("%c", &ch);
	if (ch == '#') T = NULL;
	else
	{
		if (!(T = (CSTree)malloc(sizeof(CSNode)))) exit(OVERFLOW);
		T->data = ch;
		CreateCSTree(T->firstchild);
		CreateCSTree(T->nextsibling);
	}
	return OK;
}

//���������(�ݹ��㷨)
Status CSTreeDepth(CSTree T)
{
	int f, n;
	if (T == NULL) return 0;
	else
	{
		f = CSTreeDepth(T->firstchild);
		n = CSTreeDepth(T->nextsibling);
		return ((f > n - 1) ? f : n - 1) + 1;
	}
}

//�������Ҷ�ӽڵ㣨�ݹ��㷨��
Status LeafCountCSTree(CSTree T)
{
	if (T)
	{
		if (LeafCountCSTree(T->firstchild))
		{
			printf("%-2c", T->data);
		}
		LeafCountCSTree(T->nextsibling);
		return ERROR;
	}
	return OK;
}

//��Count��������Ҷ�ӽڵ����
Status LeafCount(CSTree T, int &Count)
{
	if (T)
	{
		if (LeafCount(T->firstchild, Count))
		{
			Count++;
		}
		LeafCount(T->nextsibling, Count);
		return ERROR;
	}
	return OK;
}

//������T����B
Status CopyCSTree(CSTree T, CSTree &B)
{
	if (!T) B = NULL;
	else
	{
		if (!(B = (CSTree)malloc(sizeof(CSNode)))) exit(OVERFLOW);
		B->data = T->data;
		CopyCSTree(T->firstchild, B->firstchild);
		CopyCSTree(T->nextsibling, B->nextsibling);
	}
	return OK;
}

//������
Status DestroyCSTree(CSTree &T)
{
	if (T) // �ǿ��� 
	{
		if (T->firstchild)
			DestroyCSTree(T->firstchild);
		if (T->nextsibling)
			DestroyCSTree(T->nextsibling);
		free(T); // �ͷŸ���� 
		T = NULL; // ��ָ�븳0 
		return OK;
	}
	else return ERROR;
}

//����T��Ϊ����
Status ClearCSTree(CSTree &T)
{
	if (!T)
	{
		T = NULL;
		return OK;
	}
	else return ERROR;
}


//�ȸ����������ݹ��㷨��
Status PreOrderTraverse(CSTree T)
{
	if (T)
	{
		if(printf("%-2c", T->data))
		if(PreOrderTraverse(T->firstchild))
		if (PreOrderTraverse(T->nextsibling))
			return OK;
		return ERROR;
	}
	else return OK;
}

//������������ݹ��㷨��
Status PostOrderTraverse(CSTree T)
{
	if (T)
	{
		if (PostOrderTraverse(T->firstchild))
		{
			printf("%-2c", T->data);
			if (PostOrderTraverse(T->nextsibling))
				return OK;
		}
		return ERROR;
	}
	else return OK;
}


//������
void main()
{
	CSTree T, B; int Count = 0;
	printf("������������������������н���ֵ��\n");
	CreateCSTree(T);
	printf("�������Ϊ��%d\n", CSTreeDepth(T));
	printf("�ȸ�������������ǣ�\n");
	PreOrderTraverse(T);
	printf("\n");
	printf("���������������ǣ�\n");
	PostOrderTraverse(T);
	printf("\n");
	printf("�������Ҷ�ӽ�㣺\n");
	LeafCountCSTree(T);
	printf("\n");
	LeafCount(T,Count);
	printf("ͳ������Ҷ�ӽ�������%d\n", Count);
	if (CopyCSTree(T, B) == OK) printf("�ɹ�������T����B��\n");
	if (DestroyCSTree(T) == OK) printf("�ɹ�������T��\n");
	if (ClearCSTree(T) == OK) printf("����T��Ϊ������\n");
	printf("�ȸ�������B������ǣ�\n");
	PreOrderTraverse(B);
	printf("\n");
	printf("���������B������ǣ�\n");
	PostOrderTraverse(B);
	printf("\n");
	system("pause");
}
