#include <iostream>
#include <conio.h>
#include <string>
#include <cstring>
using namespace std;
#define MAX_VEX_NUM 20

struct Graph {
	//记录结点、边数
	int vex_num = 5;
	int arc_num = 8;	
	//邻接矩阵
	int map[MAX_VEX_NUM + 1][MAX_VEX_NUM + 1] =
	{
		//下标从1开始 下标0记录该点连接的边数
		{},				
		{3, 0, 1, 1, 0, 1},
		{3, 1, 0, 1, 0, 1},
		{4, 1, 1, 0, 1, 1},
		{2, 0, 0, 1, 0, 1},
		{4, 1, 1, 1, 1, 0}
	};
};

/**
 * @brief 深度优先搜索遍历图（用于判断图是否联通）
 * @param graph 判断的图
 * @param cur 当前的结点
 * @param vis 存储结点是否被访问过
*/
void dfsGraph(const Graph& graph, int cur, bool* vis)
{
	vis[cur] = true;
	for (int i = 1; i <= graph.vex_num; i++)
		if (graph.map[cur][i] && !vis[i])
			dfsGraph(graph, i, vis);
}

/**
 * @brief 判断当前图是否存在可行的欧拉路径
 * @param graph 判断的图
*/
bool isEulerPathExist(const Graph& graph)
{
	//先判断图是否连通
	bool vis[MAX_VEX_NUM] = {0};
	dfsGraph(graph, 1, vis);
	for (int i = 1; i <= graph.vex_num; i++)
		if (!vis[i])
			return false;

	//再判断边数为奇数的点个数
	int odd_num = 0;
	for (int i = 1; i <= graph.vex_num; i++) {
		if (graph.map[i][0] % 2 == 1)
			odd_num++;
	}

	if (odd_num == 0 || odd_num == 2)
		return true;
	else
		return false;
}

/**
 * @brief 按照 "顶点 边数 边具体信息" 的方式输入图
 * @param graph 输入的图
*/
void inputGraph(Graph& graph)
{
	while (true) {
		cout << "请输入顶点数 : ";
		cin >> graph.vex_num;
		if (cin.good() && graph.vex_num <= MAX_VEX_NUM)
			break;
		else if (cin.good())
			cout << "顶点个数应该不超过" << MAX_VEX_NUM << "!" << endl;
		else
			cout << "输入格式非法！" << endl;
		cin.clear();
		cin.ignore(1024, '\n');
	}

	while (true) {
		cout << "请输入边数 : ";
		cin >> graph.arc_num;
		if (cin.good())
			break;
		else
			cout << "输入格式非法！" << endl;
		cin.clear();
		cin.ignore(1024, '\n');
	}

	cout << "请输入" << graph.arc_num << "组以边连接的顶点序号 :" << endl;
	memset(graph.map, 0, sizeof(graph.map));
	for (int i = 0; i < graph.arc_num; i++) {
		int src, dst;
		while (true) {
			cin >> src >> dst;
			if (cin.good())
				break;
			else
				cout << "输入格式非法, 请再次输入该边的两顶点!" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		//0表示两点之间无边, 1表示有边
		graph.map[src][dst] = 1;
		graph.map[dst][src] = 1;
		//下标0处记录每个结点连接的边数
		graph.map[src][0]++;
		graph.map[dst][0]++;
	}
}

/**
 * @brief 深搜打印欧拉路径 
 * @param graph 遍历的图 
 * @param pst 当前所在端点
 * @param dep 扩展的深度
 * @param s	  输出的序列
*/
void printEulerPath(Graph& graph, int pst, int dep, string s)
{
	static int count = 0;
	if (dep >= graph.arc_num) {
		cout << "path" << ++count << " : " << s << endl;
		return;
	}
	else {
		for (int i = 1; i <= graph.vex_num; i++) {
			if (graph.map[pst][i]) {
				//删除走过的边
				graph.map[pst][i] = 0;
				graph.map[i][pst] = 0;

				printEulerPath(graph, i, dep + 1, s + to_string(i) + ' ');

				graph.map[pst][i] = 1;
				graph.map[i][pst] = 1;
			}
		}
	}
}

int main(){
	Graph graph;

	cout << "是否打印题目样例? [题目样例(Y/y) : 自行指定(N/n)]" << endl;
	bool input;
	while (true) {
		char ch = _getche();
		if (ch == 'Y' || ch == 'y') {
			input = false;
			break;
		}
		else if (ch == 'N' || ch == 'n') {
			input = true;
			break;
		}
		cout << endl << "请输入Y(y) 或 N(n) 进行选择!" << endl;
	}
	cout << endl;

	if (input)
		inputGraph(graph);

	if (isEulerPathExist(graph)) {
		cout << endl << "可行的一笔画路径如下 : " << endl;
		for (int i = 1; i <= graph.arc_num; i++)
			printEulerPath(graph, i, 0, to_string(i) + ' ');
	}
	else
		cout << "当前的图不存在可行的一笔画路径!" << endl;

	return 0;
}