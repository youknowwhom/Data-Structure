#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

/* Trie的结点 */
struct node{
	//以当前节点为结束的单词出现次数
	int times; 
	//单词的下一个字符 当前结点的子结点
	node* nextNode[26];
public:
	//建立新的字典树结点
	node();
};

/* 维护的前top_num频次数组元素 */
struct info {
	//字符串内容
	string str;
	//出现次数
	int times;
};

/* Trie的类 */
class Trie {
private:
	//字典树的根节点
	node* root;
	//存放文件内容
	string file_content;
	//统计前n的词频（目前top_num）
	const unsigned int top_num = 10;
	//存放前top_num词频的词
	vector<info> top_frequency;
	//递归释放所有节点
	void Delete_dfs(node* cur);
	//递归遍历字典树输出所有单词及频数
	void Traverse_dfs(node* cur, queue<char> q, ostream& out);
	//维护前top_num的数组
	void MaintainTop(string str, int times);
public:
	//构造空字典树
	Trie();
	//销毁字典树
	~Trie();
	//从文件读入单词构造字典树
	bool ReadFromFile(const char* filename);
	//在字典树插入新单词
	int InsertWord(node* cur, string word);
	//遍历字典树输出所有单词及频数
	void Traverse(ostream& out);
	//打印前top_num个出现频次的字符
	void PrintTop(ostream& out);
};