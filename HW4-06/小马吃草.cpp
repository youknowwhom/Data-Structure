#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
int n, m;

#define MAX_NODE_NUM 1005
int map[MAX_NODE_NUM][MAX_NODE_NUM];	//存储两点最短距离的矩阵
int vis[MAX_NODE_NUM][MAX_NODE_NUM];	//存储该点是否访问的矩阵

struct ArcNode {
	int adjvex;				//该弧的终点
	ArcNode* nextarc;		//后继的弧
	int val;				//边权
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


void AddArc(ALGraph& graph, int src, int dst, int val)
{
	ArcNode* p = graph.vertices[src].firstarc;
	ArcNode* q = new(nothrow) ArcNode;
	if (!q)
		exit(-1);
	q->adjvex = dst;
	q->val = val;

	if (p) {
		while (p->nextarc)
			p = p->nextarc;
		p->nextarc = q;
	}
	else
		graph.vertices[src].firstarc = q;

	q->nextarc = NULL;
}

struct node {
	int dis;
	int vex;
	bool operator<(const node& a) const{
		return dis > a.dis;
	}
};

/**
 * @brief Dijkstra求两点最短路
 * @param graph 图
 * @param dis 存放最终dis的数组
 * @param vis 存放是否访问过的数组
 * @param s 所求和其他点距离的某节点
*/
void dijkstra(ALGraph graph, int* dis, int* vis, int s)
{
	memset(vis, 0, MAX_NODE_NUM * sizeof(int));
	memset(dis, 0x3f, MAX_NODE_NUM * sizeof(int));
	dis[s] = 0;
	priority_queue<node> q;
	q.push({ 0, s });
	while (!q.empty()) {
		int u = q.top().vex;
		q.pop();
		if (vis[u])
			continue;
		vis[u] = true;
		for (ArcNode* p = graph.vertices[u].firstarc; p; p = p->nextarc) {
			if (dis[p->adjvex] > dis[u] + p->val) {
				dis[p->adjvex] = dis[u] + p->val;
				q.push({ dis[p->adjvex], p->adjvex });
			}
		}
	}
}

int main()
{
	ALGraph graph;
	cin >> graph.vexnum >> graph.arcnum;
	graph.vertices = new(nothrow) VNode[graph.vexnum + 1];

	int src, dst, val;
	for (int i = 0; i < graph.arcnum; i++) {
		cin >> src >> dst >> val;
		AddArc(graph, src, dst, val);
		AddArc(graph, dst, src, val);
	}

	int grass_num, horse_num;
	cin >> grass_num >> horse_num;
	vector<int> grass;

	for (int i = 0; i < grass_num; i++) {
		int g;
		cin >> g;
		//cout << "第" << i + 1 << "个草丛" << endl;
		grass.push_back(g);
		dijkstra(graph, map[g], vis[g], g);
	}

	for (int i = 0; i < horse_num; i++) {
		int src, dst;
		cin >> src >> dst;
		int min = 0x7fffffff;
		for (int j = 0; j < grass.size(); j++) {
			if (map[grass[j]][src] + map[grass[j]][dst] < min)
				min = map[grass[j]][src] + map[grass[j]][dst];
		}
		cout << min << endl;
	}

	return 0;
}