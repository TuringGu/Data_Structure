#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20     //最大顶点个数
typedef enum { DG, UDG } GraphKind;   //{有向图，无向图}
typedef int Status;
typedef int TElemType;
typedef int InfoType;              //该弧相关信息的类型
typedef struct ArcNode {
	int adjvex;                    //该弧所指向的顶点位置
	struct ArcNode *nextarc;       //指向下一条弧的指针
	InfoType *info;                //该弧相关信息的指针
}ArcNode;
typedef char VertexType;
typedef struct VNode {
	VertexType data;               //顶点信息
	ArcNode *firstarc;             //指向第一条依附该顶点的弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;            //图的当前顶点数和弧数
	int kind;                      //图的种类标志
}ALGraph;

//队列______________________________________________________________________
//单链队列 队列的链式储存结构————————————————————————————
typedef  int QElemType;
typedef int Status;

typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;


//基本操作的算法描述

//构造一个空队列
Status InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}

//判断队列是否为空，若为空返回值为1，否则返回值为0
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear) return OK;
	else return ERROR;
}

//销毁队列
Status DestroyQueue(LinkQueue &Q)
{
	while (Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}

//插入元素e为Q的新的队尾元素
Status EnQueue(LinkQueue &Q, QElemType e)
{
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(OVERFLOW);
	p->data = e; p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

//删除队尾元素
Status DeEQueue(LinkQueue &Q)
{
	QueuePtr p;
	if (Q.front == Q.rear) return ERROR;
	p = Q.front->next;
	while (p->next->next != NULL)
	{
		p = p->next;
	}
	Q.rear = p;
	free(p->next);
	Q.rear->next = NULL;
	return OK;
}

//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK
Status DeQueue(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;
	if (Q.front == Q.rear) return ERROR;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p) Q.rear = Q.front;
	free(p);
	return OK;
}

//若队列不空，用e返回队头元素的值，并返回OK
Status GetTQueue(LinkQueue Q, QElemType &e)
{
	if (Q.front == Q.rear) return ERROR;
	e = Q.front->data;
	return OK;
}

//输出队列（先进先出）
void OutpQueue(LinkQueue &Q)
{
	QElemType e;
	while (Q.front != Q.rear)
	{
		DeQueue(Q, e);
		printf("%c", e);
	}
	printf("\n");
}

//______________________________________________________________________


//访问函数visit
void visit(ALGraph G, int v)
{
	printf("%c   ", G.vertices[v].data);
}

//深度优先遍历___________________________________________________________
#define MAX 100
//全局变量
bool visited[MAX];                //访问标志数组
Status(*VisitFunc)(int v);         //函数变量

//v的第一个邻接点
int FirstAdjVex(ALGraph G, int v)
{
	if (G.vertices[v].firstarc != NULL)
		return G.vertices[v].firstarc->adjvex;
	else return -1;
}

//v相对于w的下一个邻接点
int NextAdjVex(const ALGraph G, int v, int w)
{
	ArcNode *p;
	for (p = G.vertices[v].firstarc; NULL != p; p = p->nextarc)
	{
		if (p->adjvex == w && p->nextarc != NULL)
		{
			return p->nextarc->adjvex;
		}
	}
	return -1;
}

//从第v个顶点出发递归地深度优先遍历图G
void DFS(ALGraph G, int v)
{
	int w;
	visited[v] = TRUE; visit(G, v);                    //访问第v个顶点
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))   //w>=0表示存在邻接点
		if (!visited[w]) DFS(G, w);                       //对v的尚未访问的邻接顶点w递归调用DFS
}

//深度优先搜索遍历图G
void DFSTraverse(ALGraph G)
{
	int v;
	for (v = 0; v < G.vexnum; ++v) visited[v] = FALSE;    //访问标志数组初始化为FALSE
	for (v = 0; v < G.vexnum; ++v)
		if (!visited[v]) DFS(G, v);                       //对尚未访问的顶点调用DFS
	printf("\n");
}
//_________________________________________________________________________________


//广度优先遍历______________________________________________________________________

//按广度优先非递归遍历图G。使用辅助队列Q和访问标志数组visited。
void BFSTraverse(ALGraph G)
{
	int v, w, u;
	for (v = 0; v < G.vexnum; ++v) visited[v] = FALSE;
	LinkQueue Q; InitQueue(Q);                           //置空的辅助队列Q
	for (v = 0; v < G.vexnum; ++v)
		if (!visited[v])                                 //v尚未访问
		{
			visited[v] = TRUE; visit(G, v);
			EnQueue(Q, v);                               //v入队列
			while (!QueueEmpty(Q))                       //当队列不空时，执行
			{
				DeQueue(Q, u);                           //队头元素出队并置为u
				for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
					if (!visited[w])                     //w为u的尚未访问的邻接顶点
					{
						visited[w] = TRUE; visit(G, w);
						EnQueue(Q, w);
					}//if
			}//while
		}//if
	printf("\n");
}//BFSTraverse


int LocateVex(ALGraph G, char v) {
	int i;
	for (i = 0; i<G.vexnum; ++i)
		if (G.vertices[i].data == v) return i;
	return -1;
}

Status CreateDG(ALGraph &G) {
	// 采用邻接表存储表示，构造无向图G（G.kind=UDG）。
	int i, j, k, IncInfo;
	ArcNode *pi;
	char v1, v2;
	printf("输入顶点数G.vexnum: "); scanf("%d", &G.vexnum);    // IncInfo为0表明各弧不含其它信息
	printf("输入边数G.arcnum: ");   scanf("%d", &G.arcnum);
	printf("输入边包含其它信息情况(1--包含，0--不包含)：");   scanf("%d", &IncInfo);
	getchar();                                                  //得到换行字符
	for (i = 0; i<G.vexnum; ++i) {                // 构造表头向量
		printf("输入顶点G.vertices[%d].data: ", i);
		scanf("%c", &G.vertices[i].data);        // 输入顶点值
		getchar();
		G.vertices[i].firstarc = NULL;              // 初始化链表头指针为"空"
	}//for
	for (k = 0; k<G.arcnum; ++k)                    // 输入各边并构造邻接表
	{
		printf("请输入第%d条边的两个顶点：\n", k + 1);
		scanf("%c%c", &v1, &v2);                  // 输入一条边的始点和终点
		getchar();
		i = LocateVex(G, v1);  j = LocateVex(G, v2);// 确定v1和v2在G中位置，即顶点的序号
		if (!(pi = (ArcNode *)malloc(sizeof(ArcNode)))) exit(OVERFLOW);
		pi->adjvex = j;                             // 对弧结点赋邻接点"位置"信息
		pi->nextarc = G.vertices[i].firstarc;  G.vertices[i].firstarc = pi;
		// 插入链表G.vertices[i]             
		if (IncInfo)                               // 若弧含有相关信息，则输入
		{
			printf("请输入弧包含的相关信息情况：\n");
			scanf("%d", &pi->info);
			getchar();
		}
	}//for
	G.kind = DG;
	return OK;
} // CreateUDG

Status CreateUDG(ALGraph &G) {
	// 采用邻接表存储表示，构造无向网G（G.kind=UDG）。
	int i, j, k, IncInfo;
	ArcNode *pi, *pj;
	char v1, v2;
	printf("输入顶点数G.vexnum: "); scanf("%d", &G.vexnum);    // IncInfo为0表明各弧不含其它信息
	printf("输入边数G.arcnum: ");   scanf("%d", &G.arcnum);
	printf("输入边包含其它信息情况(1--包含，0--不包含)：");   scanf("%d", &IncInfo);
	getchar();                                                  //得到换行字符
	for (i = 0; i<G.vexnum; ++i) {                // 构造表头向量
		printf("输入顶点G.vertices[%d].data: ", i);
		scanf("%c", &G.vertices[i].data);        // 输入顶点值
		getchar();
		G.vertices[i].firstarc = NULL;              // 初始化链表头指针为"空"
	}//for
	for (k = 0; k<G.arcnum; ++k)                    // 输入各边并构造邻接表
	{
		printf("请输入第%d条边的两个顶点：\n", k + 1);
		scanf("%c%c", &v1, &v2);                  // 输入一条边的始点和终点
		getchar();
		i = LocateVex(G, v1);  j = LocateVex(G, v2);// 确定v1和v2在G中位置，即顶点的序号
		if (!(pi = (ArcNode *)malloc(sizeof(ArcNode)))) exit(OVERFLOW);
		pi->adjvex = j;                             // 对弧结点赋邻接点"位置"信息
		pi->nextarc = G.vertices[i].firstarc;  G.vertices[i].firstarc = pi;
		// 插入链表G.vertices[i] 
		if (!(pj = (ArcNode *)malloc(sizeof(ArcNode)))) exit(OVERFLOW);
		pj->adjvex = i;                             // 对弧结点赋邻接点"位置"信息
		pj->nextarc = G.vertices[j].firstarc;  G.vertices[j].firstarc = pj;
		// 插入链表G.vertices[j]（无向图）                
		if (IncInfo)                               // 若弧含有相关信息，则输入
		{
			printf("请输入弧包含的相关信息情况：\n");
			scanf("%d", &pj->info);
			pi->info = pj->info;
			getchar();
		}
	}//for
	G.kind = UDG;
	return OK;
} // CreateUDG

Status CreateGraph(ALGraph &G) {
	// 采用邻接表，构造图G。
	printf("请输入图的种类：0表示DG，1表示UDG\n");
	scanf("%d", &G.kind);  // 自定义输入函数，读入一个随机值
	switch (G.kind) {
	case 0: return CreateDG(G);   // 构造有向图G
	case 1: return CreateUDG(G);  // 构造无向图G
	default: return ERROR;
	}
} // CreateGraph



void list(ALGraph G) {
	int i;
	ArcNode *p;
	printf("输出邻接表：\n");
	for (i = 0; i<G.vexnum; ++i) {
		printf("%d：%c--->", i, G.vertices[i].data);
		p = G.vertices[i].firstarc;
		while (p) {
			printf("%3d", p->adjvex);
			p = p->nextarc;
		}
		printf("\n");
	}
}

int main()
{
	ALGraph G;
	CreateGraph(G);
	list(G);
	printf("Depth_First Search:\n");
	DFSTraverse(G);
	printf("Breadth_First Search:\n");
	BFSTraverse(G);
	system("pause");
	return 0;
}


