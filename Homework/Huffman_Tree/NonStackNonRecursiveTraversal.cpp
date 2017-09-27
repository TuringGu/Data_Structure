#include<stdarg.h>        //标准头文件，提供宏va_start.va_arg和va_end,用于存取变长参数表
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h> 
#include<windows.h>
#include<time.h>
#include<string.h>

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

//-----赫夫曼树和赫夫曼编码的存储表示-----
typedef struct
{
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;                      //动态分配数组存储赫夫曼树
typedef char** HuffmanCode;                 //动态分配数组存储的赫夫曼编码表
//char*理解为指向一个字符串第一个字的指针,char**理解为字符串数组


//在HT[1..i-1]选择parent为0且weight最小的两个节点,其序号分别为s1和s2.
void Select(HuffmanTree HT, int x, unsigned int &s1, unsigned int &s2)
{
	int i = 1; int m = 1;
	while (HT[m].parent)             //找到第一个parent=0的单元
	{
		m++;
	}
	s1 = m;
	for (i = m + 1; i <= x; i++)
	{
		if (!(HT[i].parent) && HT[s1].weight >HT[i].weight)
			s1 = i;                  //最小值
	}
	HT[s1].parent = 1;               //排除第一小值
	m = 1;
	while (HT[m].parent)             //找到第一个parent=0的单元
	{
		m++;
	}
	s2 = m;
	for (i = m + 1; i <= x; i++)
	{
		if (!(HT[i].parent) && HT[s2].weight > HT[i].weight)
			s2 = i;                  //第二小值
	}
}

//赫夫曼编码算法
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{                                                                        //w存放n个字符的权值（均>0）,构造Huffman tree HT,
	int m, i; unsigned int s1 = 0; unsigned int s2 = 0; HuffmanTree p;    //并求出n个字符的Huffmancode HC
	if (n <= 1) return;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1)*sizeof(HTNode));    //0号单元未用
	p = HT;
	for (++p, i = 1; i <= n; ++i, ++p, ++w)              //给前n个单元初始化
		*p = { *w, 0, 0, 0 };
	for (; i <= m; ++i, ++p)                             //对叶子之后的储存单元清零(i=n+1开始)
		*p = { 0, 0, 0, 0 };
	for (i = n + 1; i <= m; ++i)           //建赫夫曼树
	{                                      //在HT[1..i-1](即从1至n，1至n+1,...,1至m-1)选择parent为0且weight最小的两个节点,
		Select(HT, i - 1, s1, s2);         //其序号分别为s1和s2.
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//-----无栈非递归遍历赫夫曼树，求赫夫曼编码-----
	char *cd;
	HC = (HuffmanCode)malloc((n + 1)*sizeof(char *));
	cd = (char *)malloc(n*sizeof(char));
	int k; int cdlen;
	k = m; cdlen = 0;
	for (i = 1; i <= m; ++i) HT[i].weight = 0;                     //遍历赫夫曼树时用作节点状态标志
	while (k)
	{
		if (HT[k].weight == 0)                                    //向左
		{
			HT[k].weight = 1;
			if (HT[k].lchild != 0){ k = HT[k].lchild; cd[cdlen++] = '0'; }
			else if (HT[k].rchild == 0)                           //登记叶子结点的字符的编码
			{
				HC[k] = (char*)malloc((cdlen + 1)*sizeof(char));
				cd[cdlen] = '\0'; strcpy(HC[k], cd);              //复制编码（串）
			}
		}
		else if (HT[k].weight == 1)                               //向右
		{
			HT[k].weight = 2;
			if (HT[k].rchild != 0) { k = HT[k].rchild; cd[cdlen++] = '1'; }
		}
		else                                                      //HT[p].weight==2,退回
		{
			HT[k].weight = 0; k = HT[k].parent; --cdlen;          //退到父节点，编码长度减1
		}//else
	}//While
	free(cd);
}

//主函数
int main()
{
	printf("The weight of each character:\n");
	printf("5,29,7,8,14,23,3,11\n");
	int w[] = { 5, 29, 7, 8, 14, 23, 3, 11 }, n = 8;
	HuffmanTree HT;
	HuffmanCode HC;
	HuffmanCoding(HT, HC, w, n);
	printf("Showing the Huffman cording:\n");
	int t;
	for (t = 1; t <= 8; t++)
	{
		printf("%s\n", HC[t]);
	}
	return 0;
}
