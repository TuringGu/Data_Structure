#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20     //��󶥵����
typedef enum { DG, UDG } GraphKind;   //{����ͼ������ͼ}
typedef int Status;
typedef int TElemType;
typedef int InfoType;              //�û������Ϣ������
typedef struct ArcNode {
	int adjvex;                    //�û���ָ��Ķ���λ��
	struct ArcNode *nextarc;       //ָ����һ������ָ��
	InfoType *info;                //�û������Ϣ��ָ��
}ArcNode;
typedef char VertexType;
typedef struct VNode {
	VertexType data;               //������Ϣ
	ArcNode *firstarc;             //ָ���һ�������ö���Ļ���ָ��
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;            //ͼ�ĵ�ǰ�������ͻ���
	int kind;                      //ͼ�������־
}ALGraph;

//����______________________________________________________________________
//�������� ���е���ʽ����ṹ��������������������������������������������������������
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


//�����������㷨����

//����һ���ն���
Status InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}

//�ж϶����Ƿ�Ϊ�գ���Ϊ�շ���ֵΪ1�����򷵻�ֵΪ0
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear) return OK;
	else return ERROR;
}

//���ٶ���
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

//����Ԫ��eΪQ���µĶ�βԪ��
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

//ɾ����βԪ��
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

//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK
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

//�����в��գ���e���ض�ͷԪ�ص�ֵ��������OK
Status GetTQueue(LinkQueue Q, QElemType &e)
{
	if (Q.front == Q.rear) return ERROR;
	e = Q.front->data;
	return OK;
}

//������У��Ƚ��ȳ���
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


//���ʺ���visit
void visit(ALGraph G, int v)
{
	printf("%c   ", G.vertices[v].data);
}

//������ȱ���___________________________________________________________
#define MAX 100
//ȫ�ֱ���
bool visited[MAX];                //���ʱ�־����
Status(*VisitFunc)(int v);         //��������

//v�ĵ�һ���ڽӵ�
int FirstAdjVex(ALGraph G, int v)
{
	if (G.vertices[v].firstarc != NULL)
		return G.vertices[v].firstarc->adjvex;
	else return -1;
}

//v�����w����һ���ڽӵ�
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

//�ӵ�v����������ݹ��������ȱ���ͼG
void DFS(ALGraph G, int v)
{
	int w;
	visited[v] = TRUE; visit(G, v);                    //���ʵ�v������
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))   //w>=0��ʾ�����ڽӵ�
		if (!visited[w]) DFS(G, w);                       //��v����δ���ʵ��ڽӶ���w�ݹ����DFS
}

//���������������ͼG
void DFSTraverse(ALGraph G)
{
	int v;
	for (v = 0; v < G.vexnum; ++v) visited[v] = FALSE;    //���ʱ�־�����ʼ��ΪFALSE
	for (v = 0; v < G.vexnum; ++v)
		if (!visited[v]) DFS(G, v);                       //����δ���ʵĶ������DFS
	printf("\n");
}
//_________________________________________________________________________________


//������ȱ���______________________________________________________________________

//��������ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited��
void BFSTraverse(ALGraph G)
{
	int v, w, u;
	for (v = 0; v < G.vexnum; ++v) visited[v] = FALSE;
	LinkQueue Q; InitQueue(Q);                           //�ÿյĸ�������Q
	for (v = 0; v < G.vexnum; ++v)
		if (!visited[v])                                 //v��δ����
		{
			visited[v] = TRUE; visit(G, v);
			EnQueue(Q, v);                               //v�����
			while (!QueueEmpty(Q))                       //�����в���ʱ��ִ��
			{
				DeQueue(Q, u);                           //��ͷԪ�س��Ӳ���Ϊu
				for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
					if (!visited[w])                     //wΪu����δ���ʵ��ڽӶ���
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
	// �����ڽӱ�洢��ʾ����������ͼG��G.kind=UDG����
	int i, j, k, IncInfo;
	ArcNode *pi;
	char v1, v2;
	printf("���붥����G.vexnum: "); scanf("%d", &G.vexnum);    // IncInfoΪ0������������������Ϣ
	printf("�������G.arcnum: ");   scanf("%d", &G.arcnum);
	printf("����߰���������Ϣ���(1--������0--������)��");   scanf("%d", &IncInfo);
	getchar();                                                  //�õ������ַ�
	for (i = 0; i<G.vexnum; ++i) {                // �����ͷ����
		printf("���붥��G.vertices[%d].data: ", i);
		scanf("%c", &G.vertices[i].data);        // ���붥��ֵ
		getchar();
		G.vertices[i].firstarc = NULL;              // ��ʼ������ͷָ��Ϊ"��"
	}//for
	for (k = 0; k<G.arcnum; ++k)                    // ������߲������ڽӱ�
	{
		printf("�������%d���ߵ��������㣺\n", k + 1);
		scanf("%c%c", &v1, &v2);                  // ����һ���ߵ�ʼ����յ�
		getchar();
		i = LocateVex(G, v1);  j = LocateVex(G, v2);// ȷ��v1��v2��G��λ�ã�����������
		if (!(pi = (ArcNode *)malloc(sizeof(ArcNode)))) exit(OVERFLOW);
		pi->adjvex = j;                             // �Ի���㸳�ڽӵ�"λ��"��Ϣ
		pi->nextarc = G.vertices[i].firstarc;  G.vertices[i].firstarc = pi;
		// ��������G.vertices[i]             
		if (IncInfo)                               // �������������Ϣ��������
		{
			printf("�����뻡�����������Ϣ�����\n");
			scanf("%d", &pi->info);
			getchar();
		}
	}//for
	G.kind = DG;
	return OK;
} // CreateUDG

Status CreateUDG(ALGraph &G) {
	// �����ڽӱ�洢��ʾ������������G��G.kind=UDG����
	int i, j, k, IncInfo;
	ArcNode *pi, *pj;
	char v1, v2;
	printf("���붥����G.vexnum: "); scanf("%d", &G.vexnum);    // IncInfoΪ0������������������Ϣ
	printf("�������G.arcnum: ");   scanf("%d", &G.arcnum);
	printf("����߰���������Ϣ���(1--������0--������)��");   scanf("%d", &IncInfo);
	getchar();                                                  //�õ������ַ�
	for (i = 0; i<G.vexnum; ++i) {                // �����ͷ����
		printf("���붥��G.vertices[%d].data: ", i);
		scanf("%c", &G.vertices[i].data);        // ���붥��ֵ
		getchar();
		G.vertices[i].firstarc = NULL;              // ��ʼ������ͷָ��Ϊ"��"
	}//for
	for (k = 0; k<G.arcnum; ++k)                    // ������߲������ڽӱ�
	{
		printf("�������%d���ߵ��������㣺\n", k + 1);
		scanf("%c%c", &v1, &v2);                  // ����һ���ߵ�ʼ����յ�
		getchar();
		i = LocateVex(G, v1);  j = LocateVex(G, v2);// ȷ��v1��v2��G��λ�ã�����������
		if (!(pi = (ArcNode *)malloc(sizeof(ArcNode)))) exit(OVERFLOW);
		pi->adjvex = j;                             // �Ի���㸳�ڽӵ�"λ��"��Ϣ
		pi->nextarc = G.vertices[i].firstarc;  G.vertices[i].firstarc = pi;
		// ��������G.vertices[i] 
		if (!(pj = (ArcNode *)malloc(sizeof(ArcNode)))) exit(OVERFLOW);
		pj->adjvex = i;                             // �Ի���㸳�ڽӵ�"λ��"��Ϣ
		pj->nextarc = G.vertices[j].firstarc;  G.vertices[j].firstarc = pj;
		// ��������G.vertices[j]������ͼ��                
		if (IncInfo)                               // �������������Ϣ��������
		{
			printf("�����뻡�����������Ϣ�����\n");
			scanf("%d", &pj->info);
			pi->info = pj->info;
			getchar();
		}
	}//for
	G.kind = UDG;
	return OK;
} // CreateUDG

Status CreateGraph(ALGraph &G) {
	// �����ڽӱ�����ͼG��
	printf("������ͼ�����ࣺ0��ʾDG��1��ʾUDG\n");
	scanf("%d", &G.kind);  // �Զ������뺯��������һ�����ֵ
	switch (G.kind) {
	case 0: return CreateDG(G);   // ��������ͼG
	case 1: return CreateUDG(G);  // ��������ͼG
	default: return ERROR;
	}
} // CreateGraph



void list(ALGraph G) {
	int i;
	ArcNode *p;
	printf("����ڽӱ�\n");
	for (i = 0; i<G.vexnum; ++i) {
		printf("%d��%c--->", i, G.vertices[i].data);
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


