#include<stdarg.h>        //��׼ͷ�ļ����ṩ��va_start.va_arg��va_end,���ڴ�ȡ�䳤������
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h> 
#include<windows.h>
#include<time.h>
#include<string.h>

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

//-----�շ������ͺշ�������Ĵ洢��ʾ-----
typedef struct
{
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;                      //��̬��������洢�շ�����
typedef char** HuffmanCode;                 //��̬��������洢�ĺշ��������
//char*���Ϊָ��һ���ַ�����һ���ֵ�ָ��,char**���Ϊ�ַ�������


//��HT[1..i-1]ѡ��parentΪ0��weight��С�������ڵ�,����ŷֱ�Ϊs1��s2.
void Select(HuffmanTree HT, int x, unsigned int &s1, unsigned int &s2)
{
	int i = 1; int m = 1;
	while (HT[m].parent)             //�ҵ���һ��parent=0�ĵ�Ԫ
	{
		m++;
	}
	s1 = m;
	for (i = m + 1; i <= x; i++)
	{
		if (!(HT[i].parent) && HT[s1].weight >HT[i].weight)
			s1 = i;                  //��Сֵ
	}
	HT[s1].parent = 1;               //�ų���һСֵ
	m = 1;
	while (HT[m].parent)             //�ҵ���һ��parent=0�ĵ�Ԫ
	{
		m++;
	}
	s2 = m;
	for (i = m + 1; i <= x; i++)
	{
		if (!(HT[i].parent) && HT[s2].weight > HT[i].weight)
			s2 = i;                  //�ڶ�Сֵ
	}
}

//�շ��������㷨
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{                                                                        //w���n���ַ���Ȩֵ����>0��,����Huffman tree HT,
	int m, i; unsigned int s1 = 0; unsigned int s2 = 0; HuffmanTree p;    //�����n���ַ���Huffmancode HC
	if (n <= 1) return;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1)*sizeof(HTNode));    //0�ŵ�Ԫδ��
	p = HT;
	for (++p, i = 1; i <= n; ++i, ++p, ++w)              //��ǰn����Ԫ��ʼ��
		*p = { *w, 0, 0, 0 };
	for (; i <= m; ++i, ++p)                             //��Ҷ��֮��Ĵ��浥Ԫ����(i=n+1��ʼ)
		*p = { 0, 0, 0, 0 };
	for (i = n + 1; i <= m; ++i)           //���շ�����
	{                                      //��HT[1..i-1](����1��n��1��n+1,...,1��m-1)ѡ��parentΪ0��weight��С�������ڵ�,
		Select(HT, i - 1, s1, s2);         //����ŷֱ�Ϊs1��s2.
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//-----��ջ�ǵݹ�����շ���������շ�������-----
	char *cd;
	HC = (HuffmanCode)malloc((n + 1)*sizeof(char *));
	cd = (char *)malloc(n*sizeof(char));
	int k; int cdlen;
	k = m; cdlen = 0;
	for (i = 1; i <= m; ++i) HT[i].weight = 0;                     //�����շ�����ʱ�����ڵ�״̬��־
	while (k)
	{
		if (HT[k].weight == 0)                                    //����
		{
			HT[k].weight = 1;
			if (HT[k].lchild != 0){ k = HT[k].lchild; cd[cdlen++] = '0'; }
			else if (HT[k].rchild == 0)                           //�Ǽ�Ҷ�ӽ����ַ��ı���
			{
				HC[k] = (char*)malloc((cdlen + 1)*sizeof(char));
				cd[cdlen] = '\0'; strcpy(HC[k], cd);              //���Ʊ��루����
			}
		}
		else if (HT[k].weight == 1)                               //����
		{
			HT[k].weight = 2;
			if (HT[k].rchild != 0) { k = HT[k].rchild; cd[cdlen++] = '1'; }
		}
		else                                                      //HT[p].weight==2,�˻�
		{
			HT[k].weight = 0; k = HT[k].parent; --cdlen;          //�˵����ڵ㣬���볤�ȼ�1
		}//else
	}//While
	free(cd);
}

//������
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
