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

//ͼ�����飨�ڽӾ��󣩴洢��ʾ-----------------------------------------------------------------
#define INFINITY INT_MAX        //���ֵ
#define MAX_VERTEX_NUM 20       //��󶥵����
#define MAX_NAME 5              //�����ַ�������󳤶�+1
#define MAX_INFO 20             //�����Ϣ�ַ�������󳤶�+1

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
//---------------------------------------------------------------------------------------


//Prim�㷨-----------------------------------------------------------------------------


//��¼�Ӷ��㼯U��V-U�Ĵ�����С�ıߵĸ������鶨��
typedef struct close           //��Խṹ��������close��������DEV C++����
{
	VertexType adjvex;
	VRType lowcost;
}closedge[MAX_VERTEX_NUM];

// ��closedge.lowcost����С��ֵ 
int minimum(MGraph G, closedge SZ)
{
	int i = 0, j, k, min;
	while (!SZ[i].lowcost)
		i++;
	min = SZ[i].lowcost; // ��һ����Ϊ0��ֵ  
	k = i;
	for (j = i + 1; j<G.vexnum; j++)
		if (SZ[j].lowcost>0)
			if (min > SZ[j].lowcost)
			{
				min = SZ[j].lowcost;
				k = j;
			}
	return k;
}

//Prim�㷨 �ӵ�u���������������G����С������T�����T�ĸ����ߡ�
void MiniSpanTree_PRIM(MGraph G, VertexType u)
{
	int k, i, j; closedge closedge;
	k = LocateVex(G, u);                                    //��ѡ��ʼԪ��u��λ��
	for (j = 0; j < G.vexnum; ++j)                          //���������ʼ��
		if (j != k)
		{
			strcpy(closedge[j].adjvex, u);
			closedge[j].lowcost = G.arcs[k][j].adj;          //{adjvex,lowcost}
		}
	closedge[k].lowcost = 0;                                //��ʼ��U={u}
	for (i = 1; i < G.vexnum; ++i)
	{
		k = minimum(G, closedge);                            //���T����һ����㣺��k����
		printf("%s---%s\n", closedge[k].adjvex, G.vexs[k]);   //����������ı�
		closedge[k].lowcost = 0;                            //��k���㲢��U��
		for (j = 0; j < G.vexnum; ++j)
			if (G.arcs[k][j].adj < closedge[j].lowcost)     //�¶��㲢��U������ѡ����С��
			{
				strcpy(closedge[j].adjvex, G.vexs[k]);
				closedge[j].lowcost = G.arcs[k][j].adj;
			}
	}
}//MiniSpanTree

//-----------------------------------------------------------------------------------

//������
int main() {
	MGraph G; VertexType A;
	CreateGraph(G);
	list(G);
	printf("Please input the vertex you want to start.\n");
	scanf("%s*c", A);
	printf("MiniSpanTree:\n");
	MiniSpanTree_PRIM(G, A);
	printf("\n");
}
