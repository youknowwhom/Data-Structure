#pragma once
#include "./queue.hpp"

#define CHAR_NUM_TOT 256	

/* 哈夫曼树的结点 */
typedef struct HTNode {
	unsigned int weight;	//结点的权重
	unsigned char value;	//结点的字符值
	unsigned int parent, lchild, rchild;	//结点的双亲、左孩子、右孩子
}*HTPointer;

/* 字符-出现频数 */
struct CharWithNode {
	unsigned char ch;		//字符
	unsigned int weight;	//权重-出现的次数
};

/* 哈夫曼编码表 */
typedef char** HuffmanCode;

/* 哈夫曼树的结构体 */
class HuffmanTree {
private:
	HTPointer tree;					//哈夫曼树数组
	CharWithNode* char_list;		//字符出现频率的列表
	HuffmanCode code_list;			//哈夫曼编码的列表
	unsigned int n;					//字符种类数
	//统计字符出现频率
	void CalCharFreq(const char* filename, const char* filename1, bool output = true);
	void CalCharFreq(const char* str);
	//读入字符出现频率
	void ReadCharFreq(const char* filename);
	//选择根节点中权值最小的
	void Select(int max, int& s1, int& s2);
	//建立哈夫曼树 并计算对应每个字符的01串
	void HuffmanCoding();
	//获取某字符在list的下标
	int GetIndex(unsigned char ch);
	//编码功能
	void Inner_Encode(const char* infilename, const char* outfilename);
	//解码功能
	void Inner_Decode(const char* infilename, const char* outfilename);
	//压缩功能
	void Inner_Compress(const char* infilename, const char* outfilename);
	//解压功能
	void Inner_Decompress(const char* infilename, const char* outfilename);
	//打印哈夫曼树
	void PrintTree();
public:
	//哈夫曼树的构建
	HuffmanTree();
	//哈夫曼树的销毁
	~HuffmanTree();
	//演示模式
	void Display(const char* str);
	//编码模式
	void Encode(const char* infilename, const char* outfilelist, const char* outfilename);
	//解码模式
	void Decode(const char* infilename, const char* infilelist, const char* outfilename);
	//压缩模式
	void Compress(const char* infilename, const char* outfilename);
	//解压模式
	void Decompress(const char* infilename, const char* outfilename);
};
