#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;
int n, m;
struct ArcNode {
	int adjvex;				//下一顶点的位置
	ArcNode* nextarc;		//下一条弧
	//本题中边无权重
};

typedef struct VNode {
	//本题数组下标就当作是结点名称
	bool vis = false;
	ArcNode* firstarc = NULL;
}*AdjList;

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

int cnt;

void bfs(ALGraph& graph, int vex)
{
	ArcNode* p = graph.vertices[vex].firstarc;
	struct node {
		int vex;
		int depth;
		node(int v, int d){
			vex = v;
			depth = d;
		}
	};
	queue<node> vexlist;
	vexlist.push(node{vex, 0});

	while (!vexlist.empty()) {
		node cur = vexlist.front();
		vexlist.pop();
		if (cur.depth >= 6)
			break;
		ArcNode* p = graph.vertices[cur.vex].firstarc;
		for (; p; p = p->nextarc) {
			if (!graph.vertices[p->adjvex].vis) {
				//cout << " " << p->adjvex + 1 << " ";
				cnt++;
				graph.vertices[p->adjvex].vis = true;
				vexlist.push(node(p->adjvex, cur.depth + 1));
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
		AddArc(graph, src - 1, dst - 1);
		AddArc(graph, dst - 1, src - 1);
	}

	for (int i = 0; i < graph.vexnum; i++) {
		cnt = 1;
		cout << i + 1 << ": ";
		graph.vertices[i].vis = true;
		bfs(graph, i);
		cout << setiosflags(ios::fixed) << setprecision(2) << cnt * 100.0 / graph.vexnum << "%" << endl;
		//清除vis
		for (int j = 0; j < graph.vexnum; j++)
			graph.vertices[j].vis = false;
	}

	cout << endl;


	return 0;
}