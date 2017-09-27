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

//图的数组（邻接矩阵）存储表示
#define INFINITY INT_MAX        //最大值
#define MAX_VERTEX_NUM 20       //最大顶点个数
#define MAX_NAME 5              //顶点字符串的最大长度+1
#define MAX_INFO 20             //相关信息字符串的最大长度+1

typedef char VertexType[MAX_NAME];
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


//Dijkstra算法——————————————————————————————————————————————————————————————————————————————————

/******************************************************************
*** 1初始化： S ← { v0 };                                      ***
***         D[j] ← arcs[0][j],   j = 1, 2, …, n-1;            ***
***                                         // n为图中顶点个数  ***
*** 2求出最短路径的长度：                                       ***
***         D[k] ← min{ D[i] },  i ∈ V- S ;                   ***
***        S ← S U { k };                                      ***
*** 3修改：                                                     ***
***        D[i] ← min{ D[i], D[k] + arcs[k][i] },              ***
***               对于每一个 i ∈ V- S ;                        ***
*** 4判断：  若S = V, 则算法结束，否则转2。                     ***
*******************************************************************/

typedef int ShortPathTable[MAX_VERTEX_NUM];          //辅助向量
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];    //最短路径数组 

//用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及其带权路径长度D[v]。
//若P[v][w]为TRUE,则w是从v0到v当前求得最短路径上的顶点。
//final[v]为TRUE当且仅当v属于S,即已经求得最短路径上的顶点。
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D)
{
	int v, i, w, min; bool final[MAX_VERTEX_NUM];
	for (v = 0; v < G.vexnum; ++v)
	{
		final[v] = FALSE; D[v] = G.arcs[v0][v].adj;
		for (w = 0; w < G.vexnum; ++w) P[v][w] = FALSE;     //设空路径
		if (D[v] < INFINITY) { P[v][v0] = TRUE; P[v][v] = TRUE; }
	}//for
	D[v0] = 0; final[v0] = TRUE;                            //初始化，v0定点属于S集
	for (i = 1; i < G.vexnum; ++i)                          //开始主循环，每次求得v0到某个顶点的最短路径，并加v到S集
	{
		min = INFINITY;
		for (w = 0; w < G.vexnum; ++w)
			if (!final[w])                                  //w顶点在V-S中（即不在S中）
				if (D[w] < min) { v = w; min = D[w]; }      //w顶点离v0顶点更近(找到v0到所有顶点中最近的顶点)
		final[v] = TRUE;                                    //归并顶点v到S集；
		for (w = 0; w < G.vexnum; ++w)                       //更新当前最短路径及距离
			if (!final[w] && min<INFINITY&&G.arcs[v][w].adj<INFINITY && (min + G.arcs[v][w].adj < D[w]))//修改D[w]和P[w],w属于(V-S)
			{
				D[w] = min + G.arcs[v][w].adj;
				for (int j = 0; j<G.vexnum; ++j)
					P[w][j] = P[v][j];
				P[w][w] = TRUE;
			}//if
	}//for                                                    
}//ShortextPath_DIJ



//——————————————————————————————————————————————————————————————————————————————————————————————



//实现
int main()
{
	int i, j;
	MGraph G;
	int v0 = 0;
	PathMatrix P;
	ShortPathTable D;
	CreateGraph(G);
	list(G);
	printf("输入原点序号v0：");
	scanf("%d", &v0); getchar();
	ShortestPath_DIJ(G, v0, P, D);
	printf("输出从原点%d到其余顶点的最短路径如下：\n", v0);
	printf("最短路径数组p[i][j]如下:\n");
	for (i = 0; i<G.vexnum; ++i)
	{
		for (j = 0; j<G.vexnum; ++j)
			printf("%2d", P[i][j]);
		printf("\n");
	}
	printf("%s到各顶点的最短路径长度为：\n", G.vexs[0]);
	for (i = 1; i<G.vexnum; ++i)
		printf("%s-%s:%d\n", G.vexs[0], G.vexs[i], D[i]);
	printf("\n");
}




