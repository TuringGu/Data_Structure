#include<stdarg.h>        //标准头文件，提供宏va_start.va_arg和va_end,用于存取变长参数表
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h> 
#include<windows.h>
#include<time.h>

//函数结果状态代码 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define UNDERFLOW -3


typedef char TElemType;
typedef int Status;


//树的二叉链表（孩子兄弟）存储表示（递归算法）———————————————
typedef char ElemType;
typedef struct CSNode
{
	ElemType data;
	struct CSNode *firstchild, *nextsibling;
}CSNode,*CSTree;

//按先序次序递归创建树
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

//求树的深度(递归算法)
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

//输出树的叶子节点（递归算法）
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

//用Count返回树的叶子节点个数
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

//复制树T到树B
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

//销毁树
Status DestroyCSTree(CSTree &T)
{
	if (T) // 非空树 
	{
		if (T->firstchild)
			DestroyCSTree(T->firstchild);
		if (T->nextsibling)
			DestroyCSTree(T->nextsibling);
		free(T); // 释放根结点 
		T = NULL; // 空指针赋0 
		return OK;
	}
	else return ERROR;
}

//将树T置为空树
Status ClearCSTree(CSTree &T)
{
	if (!T)
	{
		T = NULL;
		return OK;
	}
	else return ERROR;
}


//先根遍历树（递归算法）
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

//后根遍历树（递归算法）
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


//主函数
void main()
{
	CSTree T, B; int Count = 0;
	printf("创建树，按先序次序输入树中结点的值：\n");
	CreateCSTree(T);
	printf("树的深度为：%d\n", CSTreeDepth(T));
	printf("先根遍历树，结果是：\n");
	PreOrderTraverse(T);
	printf("\n");
	printf("后根遍历树，结果是：\n");
	PostOrderTraverse(T);
	printf("\n");
	printf("输出树的叶子结点：\n");
	LeafCountCSTree(T);
	printf("\n");
	LeafCount(T,Count);
	printf("统计树的叶子结点个数：%d\n", Count);
	if (CopyCSTree(T, B) == OK) printf("成功复制树T到树B！\n");
	if (DestroyCSTree(T) == OK) printf("成功销毁树T！\n");
	if (ClearCSTree(T) == OK) printf("将树T置为空树！\n");
	printf("先根遍历树B，结果是：\n");
	PreOrderTraverse(B);
	printf("\n");
	printf("后根遍历树B，结果是：\n");
	PostOrderTraverse(B);
	printf("\n");
	system("pause");
}
