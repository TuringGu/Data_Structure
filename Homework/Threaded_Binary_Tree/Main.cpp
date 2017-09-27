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

//二叉树的二叉线索存储表示
typedef enum PointerTag{Link,Thread};    //Link==0:指针，Thread==1：线索
typedef struct BiThrNode
{
	TElemType data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;               //左右标志
}BiThrNode,*BiThrTree;

//全局变量 保存线索化过程中的前驱结点 
static BiThrTree pre_in = NULL; 
static BiThrTree pre_pre = NULL;
static BiThrTree pre_post = NULL;

//先序递归创建一个二叉树
Status CreatBiTree(BiThrTree &T)
{
	char ch;
	scanf_s("%c", &ch);
	if (ch == ' ') T = NULL;
	else
	{
		if (!(T = (BiThrNode*)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
		T->data = ch;
		T->LTag = Link;
		T->RTag = Link;     //建表时初始化都为Link(即0）,不初始化会出错
		CreatBiTree(T->lchild);
		CreatBiTree(T->rchild);
	}
	return OK;
}

//中序————————————————————————————————————————————
//中序遍历二叉线索树T的非递归算法
Status InOrderTraverse_Thr(BiThrTree T, Status(*Visit)(TElemType e))
{
	BiThrTree p;
	p = T->lchild;                                         //p指向根节点
	while (p != T)                                         //空指针遍历结束时，p==T
	{
		while (p->LTag == Link)
		{
			p = p->lchild;
		}
		if (!Visit(p->data)) return ERROR;                 //访问其左子树为空的节点
		while (p->RTag == Thread&&p->rchild != T)
		{
			p = p->rchild; Visit(p->data);                 //访问后集结点
		}
		p = p->rchild;
	}
	return OK;
}

//中序遍历进行中序线索化
void InThreading(BiThrTree p)
{
	if (p)
	{
		InThreading(p->lchild);               //左子树线索化
		if (!p->lchild)                       //前驱线索
		{
			p->LTag = Thread; p->lchild = pre_in;
		}
		if (!pre_in->rchild)                     //后继线索
		{
			pre_in->RTag = Thread;
			pre_in->rchild = p;
		}
		pre_in = p;                              //保持pre_in指向p的前驱
		InThreading(p->rchild);               //右子树线索化
	}
}

//中序遍历二叉树T，并将其中序线索化，Thrt指向头结点
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
	Thrt->LTag = Link; Thrt->RTag = Thread;             //建头结点
	Thrt->rchild = Thrt;                                //右指针回指
	if (!T) Thrt->lchild = Thrt;                        //若二叉树为空，则左指针回指
	else
	{
		Thrt->lchild = T; pre_in = Thrt;
		InThreading(T);                                 //中序遍历进行中序线索化
		pre_in->rchild = Thrt; pre_in->RTag = Thread;         //最后一个节点线索化
		Thrt->rchild = pre_in;
	}
	return OK;
}



//先序——————————————————————————————————————————————
//先序遍历二叉线索树T的非递归算法
Status PreOrderTraverse_Thr(BiThrTree T, Status(*Visit)(TElemType e))
{
	BiThrTree p;
	p = T->lchild;                                         //p指向根节点
	while (p != T)                                         //空指针遍历结束时，p==T
	{
		Visit(p->data);
		while (p->LTag == Link)
		{
			p = p->lchild;
			Visit(p->data);
		}
		p = p->rchild;
	}
	return OK;
}

//先序遍历进行先序线索化
void PreThreading(BiThrTree p)
{
	if (p)
	{
		if (!p->lchild)                       //前驱线索
		{
			p->LTag = Thread; p->lchild = pre_pre;
		}
		else 
		{
			p->LTag = Link;
		}
		if (!pre_pre->rchild)                     //后继线索
		{
			pre_pre->RTag = Thread;
			pre_pre->rchild = p;
		}
		else
		{
			p->RTag = Link;
		}
		pre_pre = p;                           //保持pre_pre指向p的前驱
		if (p->LTag!=Thread)
		    PreThreading(p->lchild);               //左子树线索化
		if (p->RTag!=Thread)
		    PreThreading(p->rchild);               //右子树线索化
	}
}

//先序遍历二叉树T，并将其先序线索化，Thrt指向头结点
Status PreOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
	Thrt->LTag = Link; Thrt->RTag = Thread;             //建头结点
	Thrt->rchild = Thrt;                                //右指针回指
	if (!T) Thrt->lchild = Thrt;                        //若二叉树为空，则左指针回指
	else
	{
		Thrt->lchild = T; pre_pre = Thrt;
		PreThreading(T);
		pre_pre->rchild = Thrt; pre_pre->RTag = Thread;
		Thrt->rchild = pre_pre;
	}
	return OK;
}

//后序——————————————————————————————————————————————
//后序遍历二叉线索树T的非递归算法
Status PostOrderTraverse_Thr(BiThrTree &T, Status(*Visit)(TElemType e))
{
	BiThrTree q = T->lchild;BiThrTree p=NULL, r=NULL;              //q指向后序遍历第一个元素
	while (q->LTag == Link || q->RTag == Link)           //当结点q孩子有指针不为线索指针时，执行。
	{
		if (q->LTag == Link) q = q->lchild;
		else q = q->rchild;
	}
	while (1)
	{
		while (q->RTag == Thread && q != T->lchild)
		{
			Visit(q->data); q = q->rchild;        //q指向后继结点
		}
		Visit(q->data);
		if (q == T->lchild) break;                //当q为根节点T时，结束while.
		else
		{
			p = T->lchild;
			while (p != q)
			{
				while (p->RTag == Link && p != q)
				{
					r = p; p = p->rchild;
				}
				if (p != q)
				{
					r = p; p = p->lchild;
				}
				if (p != q)
				while (p->LTag == Thread)
				{
					r = p; p = p->lchild;
				}
			}
			q = r;                              //q指向其双亲结点
		}
	}
	return OK;
}

//后序遍历进行后序线索化			
void PostThreading(BiThrTree p)
{
	if (p)
	{
		PostThreading(p->lchild);
		PostThreading(p->rchild);
		if (!p->lchild)                              // p没有左孩子  
		{
			p->LTag = Thread;
			p->lchild = pre_post;
		}
		if (!pre_post->rchild)                       // p的前驱没有右孩子 
		{
			pre_post->RTag = Thread;
			pre_post->rchild = p;                    //p前驱的后继指向p
		}
		pre_post = p;                                //保持pre_post指向p的前驱
	}
}

//后序遍历二叉树T，并将其后序线索化，Thrt指向头结点
Status PostOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))
		exit(OVERFLOW);
	Thrt->LTag = Link; Thrt->RTag = Thread;   
	if (!T) Thrt->lchild = Thrt->rchild = Thrt;
	else
	{
		Thrt->lchild = Thrt->rchild = T;
		pre_post = Thrt;
		PostThreading(T);
		if (!pre_post->rchild)                         //若根节点T无右孩子，则线索化其指向Thrt。
		{
			pre_post->rchild = Thrt;
			pre_post->RTag = Thread;
		}
		
	}
	return OK;
}

//输出元素e的值
Status PrintElement(TElemType e)
{
	printf("%-2c", e);
	return OK;
}

Status DestroyBiTree(BiThrTree &T)
{ /* DestroyBiThrTree调用的递归函数，T指向根结点 */
	if (T) /* 非空树 */
	{
		if (T->LTag == 0) /* 有左孩子 */
			DestroyBiTree(T->lchild); /* 销毁左孩子子树 */
		if (T->RTag == 0) /* 有右孩子 */
			DestroyBiTree(T->rchild); /* 销毁右孩子子树 */
		free(T); /* 释放根结点 */
		T = NULL; /* 空指针赋0 */
	}
	return OK;
}

Status DestroyBiThrTree(BiThrTree &Thrt)
{ /* 初始条件：线索二叉树Thrt存在。操作结果：销毁线索二叉树Thrt */
	if (Thrt) /* 头结点存在 */
	{
		if ((Thrt)->lchild) /* 根结点存在 */
			DestroyBiTree(Thrt->lchild); /* 递归销毁头结点lchild所指二叉树 */
		free(Thrt); /* 释放头结点 */
		Thrt = NULL; /* 线索二叉树Thrt指针赋0 */
	}
	return OK;
}

//将二叉树置为空树
Status ClearTree(BiThrTree &T)
{
	if (T)
	{
		T = NULL;
		return OK;
	}
	else return ERROR;
}

//实现
int main()
{
	BiThrTree T, Thrt; int choose=0;
	printf("Creat a threaded binary tree:\n");
	CreatBiTree(T);
	printf("Please choose one method by number to thread the binary tree:\n");
	printf("1:Preorder a threaded binary tree\n");
	printf("2:Inorder a threaded binary tree\n");
	printf("3:Postorder a threaded binary tree\n");
	scanf_s("%d", &choose);
	switch (choose)
	{
	case 1:
		//先序--------------------------------------------
		PreOrderThreading(Thrt, T);                                //先序线索化
		printf("Output the tree by preorder traversal:\n");
		PreOrderTraverse_Thr(Thrt, PrintElement);
		printf("\n"); break;
	case 2:
		//中序--------------------------------------------
		InOrderThreading(Thrt, T);                                 //中序线索化
		printf("Output the tree by inorder traversal:\n");
		InOrderTraverse_Thr(Thrt, PrintElement);
		printf("\n"); break;
	case 3:
		//后序--------------------------------------------
		PostOrderThreading(Thrt, T);                                 //中序线索化
		printf("Output the tree by postorder traversal:\n");
		PostOrderTraverse_Thr(Thrt, PrintElement);
		printf("\n"); break;
	}
	printf("Thanks for your using!\n");
	system("pause");
	return OK;
}


