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

//二叉树的二叉链表存储表示(递归算法)
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode *lchild, *rchild;    //左右孩子指针
}BiTNode,*BiTree;

//构造二叉链表表示的二叉树T，按先序次序构造，空格字符表示空树，一个字符对应一个节点
Status CreateBiTree(BiTree &T)
{
	char ch;
	scanf_s("%c",&ch);
	if (ch == ' ') T = NULL;
	else
	{
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
		T->data = ch;             //生成根节点
		CreateBiTree(T->lchild);  //构造左指数
		CreateBiTree(T->rchild);  //构造右指数
	}
	return OK;
}


//返回二叉树的节点个数,用Nodenum返回其值
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

//输出二叉树的叶子节点
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

//统计二叉树的叶子结点个数
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

//返回二叉树的深度（采用先序访问）
Status Depth(BiTree T)
{
	{
		int LD, RD;
		if (T == NULL)
			return 0;//如果是空树，则返回0（定义空树的深度为0）
		else
		{
			LD = Depth(T->lchild);
			RD = Depth(T->rchild);
			return (LD>RD ? LD : RD) + 1;
		}
	}
}


//输出元素e的值
Status PrintElement(TElemType e)
{
	printf("%-2c", e);
	return OK;
}

//先序遍历二叉树T的递归算法 ，对每个数据元素调用函数Visit。
//Visit是对数据元素操作的函数
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

//中序遍历二叉树T递归算法 ，对每个数据元素调用函数Visit。
//Visit是对数据元素操作的函数
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

//后序遍历二叉树T的递归算法，对每个数据元素调用函数Visit。
//Visit是对数据元素操作的函数
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

//交换二叉树中所有结点的左右子树
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

//复制二叉树T到二叉树B
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


//销毁二叉树
Status DestroyTree(BiTree &T)
{
	if (T) // 非空树 
	{
		if ((T)->lchild) // 有左孩子 
			DestroyTree(T->lchild); // 销毁左孩子子树 
		if ((T)->rchild) // 有右孩子 
			DestroyTree(T->rchild); // 销毁右孩子子树 
		free(T); // 释放根结点 
		T = NULL; // 空指针赋0 
		return OK;
	}
	else return ERROR;
}

//将二叉树置为空树
Status ClearTree(BiTree &T)
{
	if (T)
	{
		T = NULL;
		return OK;
	}
	else return ERROR;
}

//实现
void main()
{
	BiTree T, B; int Nodenum=0; int Count=0;
	printf("创建二叉树，按先序次序输入二叉树中结点的值：\n");
	CreateBiTree(T);
	NodeCount(T,Nodenum);
	printf("二叉树的结点个数为：%d\n", Nodenum);
	printf("二叉树的深度为：%d\n", Depth(T));
	printf("先序遍历二叉树，结果是：\n");
	PreOrderTraverse(T, PrintElement);
	printf("\n");
	printf("中序遍历二叉树，结果是：\n");
	InOrderTraverse(T, PrintElement);
	printf("\n");
	printf("后序遍历二叉树，结果是：\n");
	PostOrderTraverse(T, PrintElement);
	printf("\n");
	printf("输出二叉树的叶子结点：\n");
	LeafCount(T, PrintElement);
	printf("\n");
	LeafNum(T, Count);
	printf("统计二叉树的叶子结点个数：%d\n", Count);
	printf("交换二叉树中所有结点的左右子树！\n");
	ExchangeBiTree(T);
	if (CopyBiTree(T, B) == OK) printf("成功复制二叉树T到二叉树B！\n");
	if (DestroyTree(T) == OK) printf("成功销毁二叉树T！\n");
	if (ClearTree(T) == OK) printf("将二叉树T置为空树！\n");
	printf("先序遍历二叉树B，结果是：\n");
	PreOrderTraverse(B, PrintElement);
	printf("\n");
	printf("中序遍历二叉树B，结果是：\n");
	InOrderTraverse(B, PrintElement);
	printf("\n");
	printf("后序遍历二叉树B，结果是：\n");
	PostOrderTraverse(B, PrintElement);
	printf("\n");
	Sleep(200000);
}
