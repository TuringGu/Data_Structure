#include<stdio.h>
#include<malloc.h>
#include<stdlib.h> 
#include<windows.h>
#include<time.h>
#include<limits.h>
#include<string.h>
//�������״̬���� 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MaxSize 100 

typedef int Status;
typedef char ElemType;

//ͼ�����飨�ڽӾ��󣩴洢��ʾ
#define INFINITY INT_MAX        //���ֵ
#define MAX_VERTEX_NUM 20       //��󶥵����
#define MAX_NAME 5              //�����ַ�������󳤶�+1
#define MAX_INFO 20             //�����Ϣ�ַ�������󳤶�+1

typedef char VertexType[MAX_NAME];
typedef char infoType;          //��Ϣ������
typedef int VRType;             //�����ϵ����������
typedef char VertexType[MAX_NAME]; //���������������ͼ�����
typedef enum{ DG, DN, UDG, UDN }GraphKind;//{����ͼ��������������ͼ��������}

//�ڽӾ������ݽṹ
typedef struct ArcCell
{
	VRType adj;                 //�����ϵ���͡�����Ȩͼ����0��1��ʾ���ڷ񣻶Դ�Ȩͼ����ΪȨֵ����
	infoType *info;             //�û������Ϣ��ָ��
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

//ͼ�����ݽṹ
typedef struct
{
	VertexType vexs[MAX_VERTEX_NUM];     //��������
	AdjMatrix arcs;                      //�ڽӾ���
	int vexnum, arcnum;                  //ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind;                      //ͼ�������־
}MGraph;

//ȷ������v�ڶ�������G�е�λ��,���򷵻�-1
int LocateVex(MGraph G, VertexType u)
{
	int i;
	for (i = 0; i < G.vexnum; ++i)
	{
		if (strcmp(u, G.vexs[i]) == 0)
			return i;
	}
	return -1;
}

//�������飨�ڽӾ��󣩱�ʾ������������ͼG
Status CreateDG(MGraph &G)
{
	int i, j, k, l; int IncInfo;
	char s[MAX_INFO], *info;   VertexType va, vb;
	printf("Please input these one by one��vexnum,arcnum,IncInfo(Yes:1,No:0)\n");
	scanf("%d%d%d%*c", &G.vexnum, &G.arcnum, &IncInfo);   //IncInfoΪ0���������������Ϣ
	printf("Please input %d vertexs' value(<%d characters):\n", G.vexnum, MAX_NAME);
	for (i = 0; i < G.vexnum; ++i) scanf("%s", &G.vexs[i]);//���춥������
	for (i = 0; i < G.vexnum; ++i)                          //��ʼ���ڽӾ���
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = { 0, NULL };              //{adj,info}
	printf("Please input two vertexes (input space as the interval) which an edge attach itself to :\n");
	for (k = 0; k < G.arcnum; ++k)                          //�����ڽӾ���
	{
		scanf("%s%s%*c", va, vb);                   //����һ���������Ķ���(�� %*c ���� �Ե��س���)
		i = LocateVex(G, va); j = LocateVex(G, vb);         //ȷ��v1��v2��G��λ��
		G.arcs[i][j].adj = 1;                               //��<v1,v2>��Ȩֵ
		if (IncInfo)                                        //�������������Ϣ��������
		{
			printf("Please input the edge's informations(<% character)\n", MAX_INFO);
			gets(s);
			l = strlen(s);
			if (l)
			{
				info = (char*)malloc((l + 1)*sizeof(char));
				strcpy(info, s);
				G.arcs[i][j].info = info;                   //����
			}
		}
	}
	G.kind = DG;
	return OK;
}

//�������飨�ڽӾ��󣩱�ʾ��������������G
Status CreateDN(MGraph &G)
{
	int i, j, k, w; int IncInfo;
	char s[MAX_INFO], *info;   VertexType va, vb;
	printf("Please input these one by one��vexnum,arcnum,IncInfo(Yes:1,No:0)\n");
	scanf("%d%d%d%*c", &G.vexnum, &G.arcnum, &IncInfo);   //IncInfoΪ0���������������Ϣ
	printf("Please input %d vertexs' value(<%d characters):\n", G.vexnum, MAX_NAME);
	for (i = 0; i < G.vexnum; ++i) scanf("%s", &G.vexs[i]);//���춥������
	for (i = 0; i < G.vexnum; ++i)                          //��ʼ���ڽӾ���
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = { INFINITY, NULL };              //{adj,info}
	printf("Please input two vertexes (input space as the interval) which an edge attach itself to and weights :\n");
	for (k = 0; k < G.arcnum; ++k)                          //�����ڽӾ���
	{
		scanf("%s%s%d%*c", va, vb, &w);                   //����һ���������Ķ��㼰Ȩֵ(�� %*c ���� �Ե��س���)
		i = LocateVex(G, va); j = LocateVex(G, vb);         //ȷ��v1��v2��G��λ��
		G.arcs[i][j].adj = w;                               //��<v1,v2>��Ȩֵ
		if (IncInfo)                                        //�������������Ϣ��������
		{
			printf("Please input the edge's informations(<%d character)\n", MAX_INFO);
			gets(s);
			w = strlen(s);
			if (w)
			{
				info = (char*)malloc((w + 1)*sizeof(char));
				strcpy(info, s);
				G.arcs[i][j].info = info;                   //����
			}
		}
	}
	G.kind = DN;
	return OK;
}

//�������飨�ڽӾ��󣩱�ʾ������������ͼG
Status CreateUDG(MGraph &G)
{
	int i, j, k, l; int IncInfo;
	char s[MAX_INFO], *info;   VertexType va, vb;
	printf("Please input these one by one��vexnum,arcnum,IncInfo(Yes:1,No:0)\n");
	scanf("%d%d%d%*c", &G.vexnum, &G.arcnum, &IncInfo);    //IncInfoΪ0���������������Ϣ
	printf("Please input %d vertexs' value(<%d characters):\n", G.vexnum, MAX_NAME);
	for (i = 0; i < G.vexnum; ++i) scanf("%s", &G.vexs[i]);//���춥������
	for (i = 0; i < G.vexnum; ++i)                          //��ʼ���ڽӾ���
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = { 0, NULL };          //{adj,info}
	printf("Please input two vertexes (input space as the interval) which an edge attach itself to :\n");
	for (k = 0; k < G.arcnum; ++k)                          //�����ڽӾ���
	{
		scanf("%s%s%*c", va, vb);                   //����һ���������Ķ���(�� %*c ���� �Ե��س���)
		i = LocateVex(G, va); j = LocateVex(G, vb);         //ȷ��v1��v2��G��λ��
		G.arcs[i][j].adj = G.arcs[j][i].adj = 1;                               //��<v1,v2>��Ȩֵ
		if (IncInfo)                                        //�������������Ϣ��������
		{
			printf("Please input the edge's informations(<%d character)\n", MAX_INFO);
			gets(s);
			l = strlen(s);
			if (l)
			{
				info = (char*)malloc((l + 1)*sizeof(char));
				strcpy(info, s);
				G.arcs[i][j].info = G.arcs[j][i].info = info;
			}
		}
	}
	G.kind = UDG;
	return OK;
}

//�������飨�ڽӾ��󣩱�ʾ��������������G
Status CreateUDN(MGraph &G)
{
	int i, j, k, w; int IncInfo;
	char s[MAX_INFO], *info;   VertexType va, vb;
	printf("Please input these one by one��vexnum,arcnum,IncInfo(Yes:1,No:0)\n");
	scanf("%d%d%d%*c", &G.vexnum, &G.arcnum, &IncInfo);    //IncInfoΪ0���������������Ϣ
	printf("Please input %d vertexs' value(<%d characters):\n", G.vexnum, MAX_NAME);
	for (i = 0; i < G.vexnum; ++i) scanf("%s", &G.vexs[i]);//���춥������
	for (i = 0; i < G.vexnum; ++i)                          //��ʼ���ڽӾ���
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = { INFINITY, NULL };          //{adj,info}
	printf("Please input two vertexes (input space as the interval) which an edge attach itself to and weights:\n");
	for (k = 0; k < G.arcnum; ++k)                          //�����ڽӾ���
	{
		scanf("%s%s%d%*c", va, vb, &w);                   //����һ���������Ķ��㼰Ȩֵ(�� %*c ���� �Ե��س���)
		i = LocateVex(G, va); j = LocateVex(G, vb);         //ȷ��v1��v2��G��λ��
		G.arcs[i][j].adj = G.arcs[j][i].adj = w;                               //��<v1,v2>��Ȩֵ
		if (IncInfo)                                        //�������������Ϣ��������
		{
			printf("Please input the edge's informations(<%d character)\n", MAX_INFO);
			gets(s);
			w = strlen(s);
			if (w)
			{
				info = (char*)malloc((w + 1)*sizeof(char));
				strcpy(info, s);
				G.arcs[i][j].info = G.arcs[j][i].info = info;
			}
		}
	}
	G.kind = UDN;
	return OK;
}

//����ڽӾ���
void list(MGraph G) {
	int i, j;
	printf("����ڽӾ���\n");
	for (i = 0; i<G.vexnum; ++i) {
		printf("%s----", G.vexs[i]);
		for (j = 0; j<G.vexnum; ++j)
			if (G.arcs[i][j].adj == INFINITY)
				printf("%4s", "��");
			else
				printf("%4d", G.arcs[i][j].adj);
		printf("\n");
	}
}

//�������飨�ڽӾ��󣩱�ʾ��������ͼG
Status CreateGraph(MGraph &G)
{
	printf("Please choose a kind of graph you want to create:\n");
	printf("0:DG  1:DN  2:UDG  3:UDN\n");
	scanf("%d", &G.kind);
	switch (G.kind)
	{
	case DG:return CreateDG(G);          //��������ͼ
	case DN:return CreateDN(G);          //����������
	case UDG:return CreateUDG(G);        //��������ͼ
	case UDN:return CreateUDN(G);        //����������
	default:return ERROR;
	}
}


//Dijkstra�㷨��������������������������������������������������������������������������������������������������������������������������������������������������������������������

/******************************************************************
*** 1��ʼ���� S �� { v0 };                                      ***
***         D[j] �� arcs[0][j],   j = 1, 2, ��, n-1;            ***
***                                         // nΪͼ�ж������  ***
*** 2������·���ĳ��ȣ�                                       ***
***         D[k] �� min{ D[i] },  i �� V- S ;                   ***
***        S �� S U { k };                                      ***
*** 3�޸ģ�                                                     ***
***        D[i] �� min{ D[i], D[k] + arcs[k][i] },              ***
***               ����ÿһ�� i �� V- S ;                        ***
*** 4�жϣ�  ��S = V, ���㷨����������ת2��                     ***
*******************************************************************/

typedef int ShortPathTable[MAX_VERTEX_NUM];          //��������
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];    //���·������ 

//��Dijkstra�㷨��������G��v0���㵽���ඥ��v�����·��P[v]�����Ȩ·������D[v]��
//��P[v][w]ΪTRUE,��w�Ǵ�v0��v��ǰ������·���ϵĶ��㡣
//final[v]ΪTRUE���ҽ���v����S,���Ѿ�������·���ϵĶ��㡣
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D)
{
	int v, i, w, min; bool final[MAX_VERTEX_NUM];
	for (v = 0; v < G.vexnum; ++v)
	{
		final[v] = FALSE; D[v] = G.arcs[v0][v].adj;
		for (w = 0; w < G.vexnum; ++w) P[v][w] = FALSE;     //���·��
		if (D[v] < INFINITY) { P[v][v0] = TRUE; P[v][v] = TRUE; }
	}//for
	D[v0] = 0; final[v0] = TRUE;                            //��ʼ����v0��������S��
	for (i = 1; i < G.vexnum; ++i)                          //��ʼ��ѭ����ÿ�����v0��ĳ����������·��������v��S��
	{
		min = INFINITY;
		for (w = 0; w < G.vexnum; ++w)
			if (!final[w])                                  //w������V-S�У�������S�У�
				if (D[w] < min) { v = w; min = D[w]; }      //w������v0�������(�ҵ�v0�����ж���������Ķ���)
		final[v] = TRUE;                                    //�鲢����v��S����
		for (w = 0; w < G.vexnum; ++w)                       //���µ�ǰ���·��������
			if (!final[w] && min<INFINITY&&G.arcs[v][w].adj<INFINITY && (min + G.arcs[v][w].adj < D[w]))//�޸�D[w]��P[w],w����(V-S)
			{
				D[w] = min + G.arcs[v][w].adj;
				for (int j = 0; j<G.vexnum; ++j)
					P[w][j] = P[v][j];
				P[w][w] = TRUE;
			}//if
	}//for                                                    
}//ShortextPath_DIJ



//��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������



//ʵ��
int main()
{
	int i, j;
	MGraph G;
	int v0 = 0;
	PathMatrix P;
	ShortPathTable D;
	CreateGraph(G);
	list(G);
	printf("����ԭ�����v0��");
	scanf("%d", &v0); getchar();
	ShortestPath_DIJ(G, v0, P, D);
	printf("�����ԭ��%d�����ඥ������·�����£�\n", v0);
	printf("���·������p[i][j]����:\n");
	for (i = 0; i<G.vexnum; ++i)
	{
		for (j = 0; j<G.vexnum; ++j)
			printf("%2d", P[i][j]);
		printf("\n");
	}
	printf("%s������������·������Ϊ��\n", G.vexs[0]);
	for (i = 1; i<G.vexnum; ++i)
		printf("%s-%s:%d\n", G.vexs[0], G.vexs[i], D[i]);
	printf("\n");
}




