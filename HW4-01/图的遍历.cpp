#include <iostream>
#include <queue>
using namespace std;
int n, m;

struct ArcNode{
	int adjvex;				//下一顶点的位置
	ArcNode* nextarc;		//下一条弧
	//本题中边无权重
};

typedef struct VNode {
	//本题数组下标就当作是结点名称
	bool vis = false;
	ArcNode* firstarc = NULL;
}* AdjList;

struct ALGraph {
	AdjList vertices;
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


void dfs(ALGraph& graph, int vex)
{
	ArcNode* p = graph.vertices[vex].firstarc;
	if (!p)
		return;
	for (; p; p = p->nextarc) {
		if (!graph.vertices[p->adjvex].vis) {
			cout << " " << p->adjvex;
			graph.vertices[p->adjvex].vis = true;
			dfs(graph, p->adjvex);
		}
	}
}

void bfs(ALGraph& graph, int vex)
{
	ArcNode* p = graph.vertices[vex].firstarc;
	queue<int> vexlist;
	vexlist.push(vex);

	while (!vexlist.empty()) {
		int cur = vexlist.front();
		vexlist.pop();
		ArcNode* p = graph.vertices[cur].firstarc;
		for (; p; p = p->nextarc) {
			if (!graph.vertices[p->adjvex].vis) {
				cout << " " << p->adjvex;
				graph.vertices[p->adjvex].vis = true;
				vexlist.push(p->adjvex);
			}
		}
	}
}


int main()
{
	ALGraph graph;
	cin >> graph.vexnum >> graph.arcnum;
	graph.vertices = new(nothrow) VNode[graph.vexnum];

	int src, dst;
	for (int i = 0; i < graph.arcnum; i++) {
		cin >> src >> dst;
		AddArc(graph, src, dst);
		AddArc(graph, dst, src);
	}

	for (int i = 0; i < graph.vexnum; i++) {
		if (graph.vertices[i].vis == false) {
			cout << "{" << i;
			graph.vertices[i].vis = true;
			dfs(graph, i);
			cout << "}";
		}
	}
	
	cout << endl;

	//清除vis
	for (int i = 0; i < graph.vexnum; i++)
		graph.vertices[i].vis = false;

	for (int i = 0; i < graph.vexnum; i++) {
		if (graph.vertices[i].vis == false) {
			cout << "{" << i;
			graph.vertices[i].vis = true;
			bfs(graph, i);
			cout << "}";
		}
	}

	return 0;
}