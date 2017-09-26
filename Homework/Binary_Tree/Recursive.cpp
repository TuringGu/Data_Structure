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

//�������Ķ�������洢��ʾ(�ݹ��㷨)
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode *lchild, *rchild;    //���Һ���ָ��
}BiTNode,*BiTree;

//������������ʾ�Ķ�����T������������죬�ո��ַ���ʾ������һ���ַ���Ӧһ���ڵ�
Status CreateBiTree(BiTree &T)
{
	char ch;
	scanf_s("%c",&ch);
	if (ch == ' ') T = NULL;
	else
	{
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
		T->data = ch;             //���ɸ��ڵ�
		CreateBiTree(T->lchild);  //������ָ��
		CreateBiTree(T->rchild);  //������ָ��
	}
	return OK;
}


//���ض������Ľڵ����,��Nodenum������ֵ
Status NodeCount(BiTree T,int &Nodenum)
{
	if (T)
	{
		Nodenum++;
		if (NodeCount(T->lchild,Nodenum))
			NodeCount(T->rchild,Nodenum);
		return OK;
	}
	return OK;
}

//�����������Ҷ�ӽڵ�
Status LeafCount(BiTree T, Status(*Visit)(TElemType e))
{
	if (T)
	{
		if ((!T->lchild) && (!T->rchild))
			Visit(T->data);
		else
		{
			LeafCount(T->lchild, Visit);
			LeafCount(T->rchild, Visit);
		}
	}
	return OK;
}

//ͳ�ƶ�������Ҷ�ӽ�����
Status LeafNum(BiTree T, int &Count)
{
	if (T)
	{
		if ((!T->lchild) && (!T->rchild))
			++Count;
		else
		{
			LeafNum(T->lchild, Count);
			LeafNum(T->rchild, Count);
		}
	}
	return OK;
}

//���ض���������ȣ�����������ʣ�
Status Depth(BiTree T)
{
	{
		int LD, RD;
		if (T == NULL)
			return 0;//����ǿ������򷵻�0��������������Ϊ0��
		else
		{
			LD = Depth(T->lchild);
			RD = Depth(T->rchild);
			return (LD>RD ? LD : RD) + 1;
		}
	}
}


//���Ԫ��e��ֵ
Status PrintElement(TElemType e)
{
	printf("%-2c", e);
	return OK;
}

//�������������T�ĵݹ��㷨 ����ÿ������Ԫ�ص��ú���Visit��
//Visit�Ƕ�����Ԫ�ز����ĺ���
Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	if (T)
	{
		if (Visit(T->data))
		if (PreOrderTraverse(T->lchild, Visit))
	    if (PreOrderTraverse(T->rchild, Visit)) 
			return OK;
		return ERROR;
	}
	else return OK;
}

//�������������T�ݹ��㷨 ����ÿ������Ԫ�ص��ú���Visit��
//Visit�Ƕ�����Ԫ�ز����ĺ���
Status InOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	if (T)
	{
		if (InOrderTraverse(T->lchild, Visit))
		if (Visit(T->data))
		if (InOrderTraverse(T->rchild, Visit))
			return OK;
		return ERROR;
	}
	else return OK;
}

//�������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
//Visit�Ƕ�����Ԫ�ز����ĺ���
int  PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	if (T)
	{
		if (PostOrderTraverse(T->lchild, Visit))
		if (PostOrderTraverse(T->rchild, Visit))
		if (Visit(T->data))
			return OK;
		return ERROR;
	}
	else return OK;
}

//���������������н�����������
Status ExchangeBiTree(BiTree &T)
{
	if (T)
	{
		BiTree pp;
		pp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = pp;
		if (T->lchild) ExchangeBiTree(T->lchild);
		if (T->rchild) ExchangeBiTree(T->rchild);
	}
	return ERROR;
}

//���ƶ�����T��������B
Status CopyBiTree(BiTree T, BiTree &B)
{
	if (T == NULL) B = NULL;
	else
	{
		B = (BiTNode*)malloc(sizeof(BiTNode));
		B->data = T->data;
		CopyBiTree(T->lchild, B->lchild);
		CopyBiTree(T->rchild, B->rchild);
	}
	return OK;
}


//���ٶ�����
Status DestroyTree(BiTree &T)
{
	if (T) // �ǿ��� 
	{
		if ((T)->lchild) // ������ 
			DestroyTree(T->lchild); // ������������ 
		if ((T)->rchild) // ���Һ��� 
			DestroyTree(T->rchild); // �����Һ������� 
		free(T); // �ͷŸ���� 
		T = NULL; // ��ָ�븳0 
		return OK;
	}
	else return ERROR;
}

//����������Ϊ����
Status ClearTree(BiTree &T)
{
	if (T)
	{
		T = NULL;
		return OK;
	}
	else return ERROR;
}

//ʵ��
void main()
{
	BiTree T, B; int Nodenum=0; int Count=0;
	printf("�������������������������������н���ֵ��\n");
	CreateBiTree(T);
	NodeCount(T,Nodenum);
	printf("�������Ľ�����Ϊ��%d\n", Nodenum);
	printf("�����������Ϊ��%d\n", Depth(T));
	printf("�������������������ǣ�\n");
	PreOrderTraverse(T, PrintElement);
	printf("\n");
	printf("�������������������ǣ�\n");
	InOrderTraverse(T, PrintElement);
	printf("\n");
	printf("�������������������ǣ�\n");
	PostOrderTraverse(T, PrintElement);
	printf("\n");
	printf("�����������Ҷ�ӽ�㣺\n");
	LeafCount(T, PrintElement);
	printf("\n");
	LeafNum(T, Count);
	printf("ͳ�ƶ�������Ҷ�ӽ�������%d\n", Count);
	printf("���������������н�������������\n");
	ExchangeBiTree(T);
	if (CopyBiTree(T, B) == OK) printf("�ɹ����ƶ�����T��������B��\n");
	if (DestroyTree(T) == OK) printf("�ɹ����ٶ�����T��\n");
	if (ClearTree(T) == OK) printf("��������T��Ϊ������\n");
	printf("�������������B������ǣ�\n");
	PreOrderTraverse(B, PrintElement);
	printf("\n");
	printf("�������������B������ǣ�\n");
	InOrderTraverse(B, PrintElement);
	printf("\n");
	printf("�������������B������ǣ�\n");
	PostOrderTraverse(B, PrintElement);
	printf("\n");
	Sleep(200000);
}
