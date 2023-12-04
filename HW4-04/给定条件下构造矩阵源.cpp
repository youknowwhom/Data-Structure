#include <iostream>
#include <cstring>
using namespace std;
int n, m;
struct ArcNode {
	int adjvex;				//该弧的终点
	ArcNode* nextarc;		//后继的弧
	//本题中边无权重
};

typedef struct VNode {
	int in_degree = 0;		//额外存放入度
	ArcNode* firstarc = NULL;
}*AdjList;

struct ALGraph {
	AdjList vertices;		//存放图的结点
	int vexnum, arcnum;
};

void AddArc(ALGraph& graph, int src, int dst)
{
	ArcNode* p = graph.vertices[src].firstarc;
	ArcNode* q = new(nothrow) ArcNode;
	if (!q)
		exit(-1);
	q->adjvex = dst;

	if (p) {
		while (p->nextarc)
			p = p->nextarc;
		p->nextarc = q;
	}
	else
		graph.vertices[src].firstarc = q;

	q->nextarc = NULL;
}


bool TopologicalSort(ALGraph& G, int* arr)
{
	int cnt = 0;
	while (true) {
		int cur = -1;
		for (cur = 1; cur <= G.vexnum; cur++)
			if (G.vertices[cur].in_degree == 0)
				break;
		if (cur > G.vexnum)
			break;		//没有入度为0的点了
		cnt++;
		arr[cur] = cnt;
		G.vertices[cur].in_degree--;	//置为-1
		for (ArcNode* p = G.vertices[cur].firstarc; p; p = p->nextarc)
			G.vertices[p->adjvex].in_degree--;
	}
	if (cnt == G.vexnum)
		return true;
	else
		return false;
}


int main()
{
	ALGraph graph, graph2;
	cin >> graph.vexnum >> graph.arcnum >> graph2.arcnum;
	graph2.vexnum = graph.vexnum;
	//下标从1开始
	graph.vertices = new(nothrow) VNode[graph.vexnum + 1];
	graph2.vertices = new(nothrow) VNode[graph2.vexnum + 1];
	int* row, * col;
	row = new(nothrow) int[graph.vexnum + 1];
	col = new(nothrow) int[graph2.vexnum + 1];
	int map[405][405];
	memset(map, 0, sizeof(map));

	int src, dst;
	for (int i = 1; i <= graph.arcnum; i++) {
		cin >> src >> dst;
		graph.vertices[dst].in_degree++;
		AddArc(graph, src, dst);
	}

	if (!TopologicalSort(graph, row)) {
		cout << "-1" << endl;
		exit(0);
	}

	for (int i = 1; i <= graph2.arcnum; i++) {
		cin >> src >> dst;
		graph2.vertices[dst].in_degree++;
		AddArc(graph2, src, dst);
	}

	if (!TopologicalSort(graph2, col)) {
		cout << "-1" << endl;
		exit(0);
	}

	for (int i = 1; i <= graph.vexnum; i++)
		map[row[i]][col[i]] = i;

	for (int i = 1; i <= graph.vexnum; i++) {
		for (int j = 1; j <= graph.vexnum; j++)
			cout << map[i][j] << " ";
		cout << endl;
	}

	return 0;
}