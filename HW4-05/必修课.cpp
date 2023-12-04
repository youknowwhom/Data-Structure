#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
int n, m;
struct ArcNode {
	int adjvex;				//该弧的终点
	ArcNode* nextarc;		//后继的弧
	//本题中边无权重
};

typedef struct VNode {
	int in_degree = 0;
	int val;				//所需学时
	int max_preval = 0;		//前驱结点的累计最大分支
	vector<int> pre;		//前驱结点(可能多个相同)
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

bool TopologicalSort(ALGraph& G)
{
	int cnt = 0;
	while (true) {
		int cur;
		for (cur = 1; cur <= G.vexnum; cur++)
			if (G.vertices[cur].in_degree == 0)
				break;

		if (cur > G.vexnum)
			break;		//没有入度为0的点了

		//cout << "现在到" << cur <<",前驱提供" <<G.vertices[cur].max_preval << endl;

		cnt++;
		G.vertices[cur].in_degree--;	//置为-1
		G.vertices[cur].val += G.vertices[cur].max_preval;
		for (ArcNode* p = G.vertices[cur].firstarc; p; p = p->nextarc) {
			G.vertices[p->adjvex].in_degree--;
			//更新对下一个结点的贡献值
			if (G.vertices[p->adjvex].max_preval < G.vertices[cur].val) {
				//if (G.vertices[p->adjvex].pre.size() != 0)
				//	cout << p->adjvex << "的最大值原先是由" << G.vertices[p->adjvex].pre[0] << "提供的" << G.vertices[p->adjvex].max_preval << ", 现在更新为" << cur << "提供的" << G.vertices[cur].val << endl;
				//else
				//	cout << p->adjvex << "由" << cur << "提供首个最大值" << G.vertices[cur].val << endl;
				G.vertices[p->adjvex].pre.clear();
				G.vertices[p->adjvex].pre.push_back(cur);
				G.vertices[p->adjvex].max_preval = G.vertices[cur].val;
			}
			else if (G.vertices[p->adjvex].max_preval == G.vertices[cur].val)
				G.vertices[p->adjvex].pre.push_back(cur);
		}
	}
	if (cnt == G.vexnum)
		return true;
	else
		return false;
}

/**
 * @brief 深搜求某结点是否是关键结点
 * @param graph 搜索的图
 * @param cur 当前所在结点
 * @param tgt 欲搜索的节点
 * @return 是否是影响总时长的关键结点
*/
bool dfs_relevance(ALGraph graph, int cur, int tgt){
	if (cur == tgt)
		return true;
	//成功走到第一门基础先修 该支路没有tgt
	if (graph.vertices[cur].pre.size() == 0)
		return false;

	//遍历所有最耗时前驱
	for (int i = 0; i < graph.vertices[cur].pre.size(); i++) {
		//有一条分支中含tgt 就会改变总时间
		if (dfs_relevance(graph, graph.vertices[cur].pre[i], tgt) == true)
			return true;
	}
	return false;
}

int main()
{
	ALGraph graph;
	cin >> graph.vexnum;
	//下标从1开始 额外一个结点存superend
	graph.vertices = new(nothrow) VNode[graph.vexnum + 2];

	for (int i = 1; i <= graph.vexnum; i++) {
		int num, pre;
		cin >> graph.vertices[i].val;
		cin >> num;
		for (int j = 0; j < num; j++) {
			cin >> pre;
			graph.vertices[i].in_degree++;
			AddArc(graph, pre, i);
		}
	}

	for (int i = 1; i <= graph.vexnum; i++) {
		//出度为0的点加一条边到superend
		if (!graph.vertices[i].firstarc) {
			AddArc(graph, i, graph.vexnum + 1);
		}
	}

	TopologicalSort(graph);

	for (int i = 1; i <= graph.vexnum; i++) {
		cout << graph.vertices[i].val << " " << dfs_relevance(graph, graph.vexnum + 1, i) << endl;
	}


	return 0;
}