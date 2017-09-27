#include<stdio.h>
#include<malloc.h>
#include<stdlib.h> 
#include<windows.h>
#include<time.h>
#include<limits.h>
#include<string.h>
//函数结果状态代码 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MaxSize 100 

typedef int Status;
typedef char ElemType;

//图的数组（邻接矩阵）存储表示-----------------------------------------------------------------
#define INFINITY INT_MAX        //最大值
#define MAX_VERTEX_NUM 20       //最大顶点个数
#define MAX_NAME 5              //顶点字符串的最大长度+1
#define MAX_INFO 20             //相关信息字符串的最大长度+1

typedef char infoType;          //信息的类型
typedef int VRType;             //顶点关系的数据类型
typedef char VertexType[MAX_NAME]; //顶点向量数据类型及长度
typedef enum{ DG, DN, UDG, UDN }GraphKind;//{有向图，有向网，无向图，无向网}

//邻接矩阵数据结构
typedef struct ArcCell
{
	VRType adj;                 //顶点关系类型。对无权图，用0或1表示相邻否；对带权图，则为权值类型
	infoType *info;             //该弧相关信息的指针
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

//图的数据结构
typedef struct
{
	VertexType vexs[MAX_VERTEX_NUM];     //顶点向量
	AdjMatrix arcs;                      //邻接矩阵
	int vexnum, arcnum;                  //图的当前顶点数和弧数
	GraphKind kind;                      //图的种类标志
}MGraph;

//确定顶点v在顶点向量G中的位置,否则返回-1
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

//采用数组（邻接矩阵）表示法，构造有向图G
Status CreateDG(MGraph &G)
{
	int i, j, k, l; int IncInfo;
	char s[MAX_INFO], *info;   VertexType va, vb;
	printf("Please input these one by one：vexnum,arcnum,IncInfo(Yes:1,No:0)\n");
	scanf("%d%d%d%*c", &G.vexnum, &G.arcnum, &IncInfo);   //IncInfo为0则各弧不含其它信息
	printf("Please input %d vertexs' value(<%d characters):\n", G.vexnum, MAX_NAME);
	for (i = 0; i < G.vexnum; ++i) scanf("%s", &G.vexs[i]);//构造顶点向量
	for (i = 0; i < G.vexnum; ++i)                          //初始化邻接矩阵
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = { 0, NULL };              //{adj,info}
	printf("Please input two vertexes (input space as the interval) which an edge attach itself to :\n");
	for (k = 0; k < G.arcnum; ++k)                          //构造邻接矩阵
	{
		scanf("%s%s%*c", va, vb);                   //输入一条边依附的顶点(“ %*c ”： 吃掉回车符)
		i = LocateVex(G, va); j = LocateVex(G, vb);         //确定v1和v2在G中位置
		G.arcs[i][j].adj = 1;                               //弧<v1,v2>的权值
		if (IncInfo)                                        //若弧含有相关信息，则输入
		{
			printf("Please input the edge's informations(<% character)\n", MAX_INFO);
			gets(s);
			l = strlen(s);
			if (l)
			{
				info = (char*)malloc((l + 1)*sizeof(char));
				strcpy(info, s);
				G.arcs[i][j].info = info;                   //有向
			}
		}
	}
	G.kind = DG;
	return OK;
}

//采用数组（邻接矩阵）表示法，构造有向网G
Status CreateDN(MGraph &G)
{
	int i, j, k, w; int IncInfo;
	char s[MAX_INFO], *info;   VertexType va, vb;
	printf("Please input these one by one：vexnum,arcnum,IncInfo(Yes:1,No:0)\n");
	scanf("%d%d%d%*c", &G.vexnum, &G.arcnum, &IncInfo);   //IncInfo为0则各弧不含其它信息
	printf("Please input %d vertexs' value(<%d characters):\n", G.vexnum, MAX_NAME);
	for (i = 0; i < G.vexnum; ++i) scanf("%s", &G.vexs[i]);//构造顶点向量
	for (i = 0; i < G.vexnum; ++i)                          //初始化邻接矩阵
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = { INFINITY, NULL };              //{adj,info}
	printf("Please input two vertexes (input space as the interval) which an edge attach itself to and weights :\n");
	for (k = 0; k < G.arcnum; ++k)                          //构造邻接矩阵
	{
		scanf("%s%s%d%*c", va, vb, &w);                   //输入一条边依附的顶点及权值(“ %*c ”： 吃掉回车符)
		i = LocateVex(G, va); j = LocateVex(G, vb);         //确定v1和v2在G中位置
		G.arcs[i][j].adj = w;                               //弧<v1,v2>的权值
		if (IncInfo)                                        //若弧含有相关信息，则输入
		{
			printf("Please input the edge's informations(<%d character)\n", MAX_INFO);
			gets(s);
			w = strlen(s);
			if (w)
			{
				info = (char*)malloc((w + 1)*sizeof(char));
				strcpy(info, s);
				G.arcs[i][j].info = info;                   //有向
			}
		}
	}
	G.kind = DN;
	return OK;
}

//采用数组（邻接矩阵）表示法，构造无向图G
Status CreateUDG(MGraph &G)
{
	int i, j, k, l; int IncInfo;
	char s[MAX_INFO], *info;   VertexType va, vb;
	printf("Please input these one by one：vexnum,arcnum,IncInfo(Yes:1,No:0)\n");
	scanf("%d%d%d%*c", &G.vexnum, &G.arcnum, &IncInfo);    //IncInfo为0则各弧不含其它信息
	printf("Please input %d vertexs' value(<%d characters):\n", G.vexnum, MAX_NAME);
	for (i = 0; i < G.vexnum; ++i) scanf("%s", &G.vexs[i]);//构造顶点向量
	for (i = 0; i < G.vexnum; ++i)                          //初始化邻接矩阵
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = { 0, NULL };          //{adj,info}
	printf("Please input two vertexes (input space as the interval) which an edge attach itself to :\n");
	for (k = 0; k < G.arcnum; ++k)                          //构造邻接矩阵
	{
		scanf("%s%s%*c", va, vb);                   //输入一条边依附的顶点(“ %*c ”： 吃掉回车符)
		i = LocateVex(G, va); j = LocateVex(G, vb);         //确定v1和v2在G中位置
		G.arcs[i][j].adj = G.arcs[j][i].adj = 1;                               //弧<v1,v2>的权值
		if (IncInfo)                                        //若弧含有相关信息，则输入
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

//采用数组（邻接矩阵）表示法，构造无向网G
Status CreateUDN(MGraph &G)
{
	int i, j, k, w; int IncInfo;
	char s[MAX_INFO], *info;   VertexType va, vb;
	printf("Please input these one by one：vexnum,arcnum,IncInfo(Yes:1,No:0)\n");
	scanf("%d%d%d%*c", &G.vexnum, &G.arcnum, &IncInfo);    //IncInfo为0则各弧不含其它信息
	printf("Please input %d vertexs' value(<%d characters):\n", G.vexnum, MAX_NAME);
	for (i = 0; i < G.vexnum; ++i) scanf("%s", &G.vexs[i]);//构造顶点向量
	for (i = 0; i < G.vexnum; ++i)                          //初始化邻接矩阵
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = { INFINITY, NULL };          //{adj,info}
	printf("Please input two vertexes (input space as the interval) which an edge attach itself to and weights:\n");
	for (k = 0; k < G.arcnum; ++k)                          //构造邻接矩阵
	{
		scanf("%s%s%d%*c", va, vb, &w);                   //输入一条边依附的顶点及权值(“ %*c ”： 吃掉回车符)
		i = LocateVex(G, va); j = LocateVex(G, vb);         //确定v1和v2在G中位置
		G.arcs[i][j].adj = G.arcs[j][i].adj = w;                               //弧<v1,v2>的权值
		if (IncInfo)                                        //若弧含有相关信息，则输入
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

//输出邻接矩阵
void list(MGraph G) {
	int i, j;
	printf("输出邻接矩阵：\n");
	for (i = 0; i<G.vexnum; ++i) {
		printf("%s----", G.vexs[i]);
		for (j = 0; j<G.vexnum; ++j)
			if (G.arcs[i][j].adj == INFINITY)
				printf("%4s", "∞");
			else
				printf("%4d", G.arcs[i][j].adj);
		printf("\n");
	}
}

//采用数组（邻接矩阵）表示法，构造图G
Status CreateGraph(MGraph &G)
{
	printf("Please choose a kind of graph you want to create:\n");
	printf("0:DG  1:DN  2:UDG  3:UDN\n");
	scanf("%d", &G.kind);
	switch (G.kind)
	{
	case DG:return CreateDG(G);          //构造有向图
	case DN:return CreateDN(G);          //构造有向网
	case UDG:return CreateUDG(G);        //构造无向图
	case UDN:return CreateUDN(G);        //构造无向网
	default:return ERROR;
	}
}
//---------------------------------------------------------------------------------------


//Prim算法-----------------------------------------------------------------------------


//记录从顶点集U到V-U的代价最小的边的辅助数组定义
typedef struct close           //需对结构体命名（close），否则DEV C++报错
{
	VertexType adjvex;
	VRType lowcost;
}closedge[MAX_VERTEX_NUM];

// 求closedge.lowcost的最小正值 
int minimum(MGraph G, closedge SZ)
{
	int i = 0, j, k, min;
	while (!SZ[i].lowcost)
		i++;
	min = SZ[i].lowcost; // 第一个不为0的值  
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

//Prim算法 从第u个顶点出发构造网G的最小生成树T，输出T的各条边。
void MiniSpanTree_PRIM(MGraph G, VertexType u)
{
	int k, i, j; closedge closedge;
	k = LocateVex(G, u);                                    //所选择开始元素u的位置
	for (j = 0; j < G.vexnum; ++j)                          //辅助数组初始化
		if (j != k)
		{
			strcpy(closedge[j].adjvex, u);
			closedge[j].lowcost = G.arcs[k][j].adj;          //{adjvex,lowcost}
		}
	closedge[k].lowcost = 0;                                //初始，U={u}
	for (i = 1; i < G.vexnum; ++i)
	{
		k = minimum(G, closedge);                            //求出T的下一个结点：第k顶点
		printf("%s---%s\n", closedge[k].adjvex, G.vexs[k]);   //输出生成树的边
		closedge[k].lowcost = 0;                            //第k顶点并入U集
		for (j = 0; j < G.vexnum; ++j)
			if (G.arcs[k][j].adj < closedge[j].lowcost)     //新顶点并入U后重新选择最小边
			{
				strcpy(closedge[j].adjvex, G.vexs[k]);
				closedge[j].lowcost = G.arcs[k][j].adj;
			}
	}
}//MiniSpanTree

//-----------------------------------------------------------------------------------

//主函数
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
