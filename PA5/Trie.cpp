#include "./Trie.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
using namespace std;

/**
 * @brief 创建新的字典树结点
*/
node::node()
{
	times = 0;
	memset(nextNode, 0, sizeof(nextNode));
}

/**
 * @brief 创建空的字典树
*/
Trie::Trie()
{
	root = new(nothrow) node;
	if (!root)
		exit(-1);
}

/**
 * @brief 递归删除所有结点(析构函数调用 )
 * @param cur 当前遍历的结点
*/
void Trie::Delete_dfs(node* cur)
{
	for (int i = 0; i < 26; i++)
		if (cur->nextNode[i])
			Delete_dfs(cur->nextNode[i]);
	delete cur;
}

/**
 * @brief 销毁字典树(调用Delete_dfs)
*/
Trie::~Trie()
{
	Delete_dfs(root);
}

/**
 * @brief 在字典树中插入新单词
 * @param cur 当前的结点位置
 * @param word 新插入的单词
 * @return 该单词目前的出现频次
*/
int Trie::InsertWord(node* cur, string word)
{
	int index = word[0] - 'a';
	// 如果没有该节点就新建
	if (cur->nextNode[index] == NULL) {
		cur->nextNode[index] = new(nothrow) node;
		if (!cur->nextNode[index])
			exit(-1);
	}
	//单词结束了
	if (word.size() == 1)
		return (++cur->nextNode[index]->times);
	else {
		word.replace(0, 1, "");
		return InsertWord(cur->nextNode[index], word);
	}
}

/**
 * @brief 深度优先搜索递归遍历
 * @param cur 当前搜索的结点
 * @param q 存储字符串的队列
 * @param out 输出流
*/
void Trie::Traverse_dfs(node* cur, queue <char> q, ostream& out)
{
	queue<char> q1(q), q2;

	if (cur->times > 0) {
		out << "<";
		while (!q1.empty()) {
			out << q1.front();
			q1.pop();
		}
		out << ", " << cur->times << ">" << endl;
	}

	for (int i = 0; i < 26; i++) {
		if (!cur->nextNode[i])
			continue;
		q2 = q;
		q2.push(i + 'a');
		Traverse_dfs(cur->nextNode[i], q2, out);
	}
}

/**
 * @brief 遍历字典树输出所有单词及频数
*/
void Trie::Traverse(ostream& out)
{
	queue<char> q;
	Traverse_dfs(root, q, out);
}

/**
 * @brief 维护前top_num个出现频次最多的字符串
 * @param str 当前新字符串
 * @param times 新字符串出现频数
*/
void Trie::MaintainTop(string str, int times)
{
	unsigned int i = top_frequency.size();
	while (i > 0 && times >= top_frequency[i - 1].times){
		if (top_frequency[i - 1].str == str) {
			top_frequency.erase(top_frequency.begin() + i - 1);
		}
		i--;
	}
	top_frequency.insert(top_frequency.begin() + i, info{str, times});
	if (top_frequency.size() > top_num)
		top_frequency.pop_back();
}

/**
 * @brief 打印出现频次为前top_num的单词
 * @param out 输出流
*/
void Trie::PrintTop(ostream& out)
{
	for (unsigned int i = 0; i < top_frequency.size(); i++) {
		out << top_frequency[i].str << "\t" << top_frequency[i].times << endl;
	}
}

/**
 * @brief 从文件读入单词构建字典树
 * @param filename 读入的文件名
*/
bool Trie::ReadFromFile(const char* filename)
{
	ifstream infile(filename, ios::in);
	stringstream filestream;
	if (!infile.is_open()) {
		cout << "文件[" << filename << "]不存在!" << endl;
		return false;
	}

	filestream << infile.rdbuf();
	infile.close();
	file_content = filestream.str();
	
	//处理换行连字符
	while (file_content.find("-\n") != string::npos) {
		file_content.replace(file_content.find("-\n"), strlen("-\n"), "");
	}

	//将剩余连字符转空格
	while (file_content.find("-") != string::npos) {
		file_content.replace(file_content.find("-"), strlen("-"), " ");
	}

	bool invalid = false;
	//大写转小写
	for (unsigned int i = 0; i < file_content.size(); i++) {
		if (file_content[i] >= 'a' && file_content[i] <= 'z')
			continue;
		else if (file_content[i] >= 'A' && file_content[i] <= 'Z')
			file_content[i] += ('a' - 'A');
		else {
			if (file_content[i] < 0)
				invalid = true;
			file_content[i] = ' ';
		}
	}

	if(invalid)
		clog << "文件中存在非ASCII字符，已跳过处理" << endl;
	
	/* 文件读入部分结束 以下开始建树 */

	filestream.clear();
	filestream.str("");
	filestream << file_content;
	while (filestream.good()) {
		string newword;
		filestream >> newword;
		if (newword == "")
			break;
		MaintainTop(newword, InsertWord(root, newword));
	}
	
	return true;
}