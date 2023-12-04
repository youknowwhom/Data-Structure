#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include  "./HuffmanTree.h"
using namespace std;

/**
 * @brief 打印一定数量的空格(iomanip)
 * @param n 打印的空格数
*/
static void PrintSpace(int n)
{
	for (int i = 0; i < n; i++)
		cout << " ";
}

/**
 * @brief 求2的n次幂
 * @param n 求幂的数n
 * @return 2的n次幂结果
*/
static int pow2(int n)
{
	int ans = 1;
	for (int i = 0; i < n; i++)
		ans *= 2;
	return ans;
}


/**
 * @brief 构建哈夫曼树
*/
HuffmanTree::HuffmanTree()
{
	tree = NULL;
	char_list = NULL;
	code_list = NULL;
}


/**
 * @brief 销毁哈夫曼树
*/
HuffmanTree::~HuffmanTree()
{
	if(char_list)
		delete[] char_list;
	if(code_list)
		delete[] code_list;
	if (tree)
		delete[] tree;
}


/**
 * @brief 计算文件中每个字符出现的频数
 * @param filename 输入的压缩文件
 * @param filename1 输出的字符频数文件
 * @param output 是否要输出到文件
*/
void HuffmanTree::CalCharFreq(const char* filename, const char* filename1, bool output)
{
	int* templist = new(nothrow) int[CHAR_NUM_TOT];
	int order[CHAR_NUM_TOT];
	for (int i = 0; i < CHAR_NUM_TOT; i++)
		order[i] = i;

	if (!templist)
		exit(OVER_FLOW);
	memset(templist, 0, CHAR_NUM_TOT * sizeof(int));
	ifstream infile;
	ofstream outfile;
	infile.open(filename, ios::in | ios::binary);		//打开文件
	if (!infile.is_open()) {
		cout << "文件" << filename << "打开失败!" << endl;
		exit(0);
	}
	if (output) {
		outfile.open(filename1, ios::out);	//打开文件
		if (!outfile.is_open()) {
			cout << "文件" << filename1 << "写入失败!" << endl;
			exit(0);
		}
	}

	unsigned char ch;
	while (infile.peek() != EOF) {
		ch = infile.get();
		templist[ch] += 1;
	}

	unsigned int i, j;

	n = 0;
	for (int i = 0; i < CHAR_NUM_TOT; i++)
		if (templist[i])
			++n;

	char_list = new(nothrow) CharWithNode[n];
	if (!char_list)
		exit(OVER_FLOW);
	j = 0;
	for (i = 0; i < n; i++) {
		while (templist[j] == 0)
			j++;
		char_list[i].weight = templist[j];
		char_list[i].ch = (unsigned char)j;
		j++;
	}

	//演示时输出每个字频数的文件
	if (output) {
		for (unsigned int i = 0; i < n; i++)
			outfile << char_list[i].ch + 0 << " " << char_list[i].weight + 0 << endl;
	}

	delete[] templist;
	infile.close();
	if (output)
		outfile.close();
}


/**
 * @brief 计算字符串中每个字符出现的频数(函数重载)
 * @param str 输入的字符串
 * @param output 是否要输出到文件
*/
void HuffmanTree::CalCharFreq(const char* str)
{
	int* templist = new(nothrow) int[CHAR_NUM_TOT];
	int order[CHAR_NUM_TOT];
	for (int i = 0; i < CHAR_NUM_TOT; i++)
		order[i] = i;

	if (!templist)
		exit(OVER_FLOW);
	memset(templist, 0, CHAR_NUM_TOT * sizeof(int));

	for (unsigned int i = 0; i < strlen(str); i++) {
		templist[str[i]] += 1;
	}

	unsigned int i, j;

	n = 0;
	for (int i = 0; i < CHAR_NUM_TOT; i++)
		if (templist[i])
			++n;

	char_list = new(nothrow) CharWithNode[n];
	if (!char_list)
		exit(OVER_FLOW);
	j = 0;
	for (i = 0; i < n; i++) {
		while (templist[j] == 0)
			j++;
		char_list[i].weight = templist[j];
		char_list[i].ch = (unsigned char)j;
		j++;
	}

	for (unsigned int i = 0; i < n; i++)
		cout << char_list[i].ch << "的出现频次为 : " << char_list[i].weight + 0 << endl;

	delete[] templist;
}


/**
 * @brief 读入字符频数文件信息写入list
 * @param filename 读入的字符频数文件
*/
void HuffmanTree::ReadCharFreq(const char* filename)
{
	int* templist = new(nothrow) int[CHAR_NUM_TOT];
	if (!templist)
		exit(OVER_FLOW);
	memset(templist, 0, sizeof(int) * CHAR_NUM_TOT);

	ifstream infile;
	ofstream outfile;
	infile.open(filename, ios::in);		//打开文件
	n = 0;	//置零开始计数
	while (infile.good()) {
		int order, num;
		infile >> order >> num;
		if (!infile.good())
			break;
		n++;
		templist[order] = num;
	}

	char_list = new(nothrow) CharWithNode[n];
	if (!char_list)
		exit(OVER_FLOW);
	int j = 0;
	for (unsigned int i = 0; i < n; i++) {
		while (templist[j] == 0)
			j++;
		char_list[i].weight = templist[j];
		char_list[i].ch = (char)j;
		j++;
	}

	infile.close();
}



/**
 * @brief 选择根结点中权值最小的两个结点
 * @param max 从1-max的范围中查找
 * @param s1 权值最小的结点
 * @param s2 权值次小的结点
*/
void HuffmanTree::Select(int max, int& s1, int& s2)
{
	s1 = -1, s2 = -1;
	for (int i = 1; i <= max; i++) {
		//已经有父结点 跳过
		if (tree[i].parent)
			continue;
		if (s1 == -1 || tree[i].weight < tree[s1].weight) {
			s2 = s1;
			s1 = i;
		}
		else if (s2 == -1 || tree[i].weight < tree[s2].weight)
			s2 = i;
	}
}



/**
 * @brief 建立哈夫曼树 并计算对应每个字符的01串
*/
void HuffmanTree::HuffmanCoding()
{
	unsigned int m = 2 * n - 1;
	HTPointer p;
	unsigned int i;
	tree = new(nothrow) HTNode[2 * n];
	if (!tree)
		exit(OVER_FLOW);
	CharWithNode* q = char_list;
	for (p = tree + 1, i = 1; i <= n; ++i, ++p, ++q) {
		p->weight = q->weight;
		p->value = q->ch;
		p->lchild = p->rchild = 0;
		p->parent = 0;
	}
	for (; i <= m; ++i, ++p) {
		p->weight = 0;
		p->value = 0;
		p->lchild = p->rchild = 0;
		p->parent = 0;
	}

	//下面开始建树
	for (unsigned int i = n + 1; i <= m; ++i) {
		int s1, s2;
		Select(i - 1, s1, s2);
		tree[s1].parent = i;
		tree[s2].parent = i;
		tree[i].lchild = s1;
		tree[i].rchild = s2;
		tree[i].value = '^';
		tree[i].weight = tree[s1].weight + tree[s2].weight;
	}

	code_list = new(nothrow) char* [n + 1];
	if (!code_list)
		exit(OVER_FLOW);
	char* cd = new(nothrow) char[n];
	if (!cd)
		exit(OVER_FLOW);
	cd[n - 1] = '\0';

	for (unsigned int i = 1; i <= n; ++i) {
		int start = n - 1;
		int f, c;
		for (c = i, f = tree[i].parent; f; c = f, f = tree[f].parent) {
			if (tree[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		code_list[i] = new(nothrow) char[n - start];
		if (!code_list[i])
			exit(OVER_FLOW);
		strcpy(code_list[i], &cd[start]);
	}

	delete[] cd;
}



/**
 * @brief 获取某字符在list的下标
 * @param ch 要查找的字符
*/
int HuffmanTree::GetIndex(unsigned char ch)
{
	for (unsigned int i = 1; i <= n; i++)
		if (tree[i].value == ch)
			return i;
	return -1;
}


/**
 * @brief 编码功能
 * @param infilename 待编码的文件名
 * @param outfilename 编码后的文件名
*/
void HuffmanTree::Inner_Encode(const char* infilename, const char* outfilename)
{
	ifstream infile;
	ofstream outfile;
	infile.open(infilename, ios::in);		//打开文件
	if (!infile.is_open()) {
		cout << "文件" << infilename << "打开失败!" << endl;
		exit(0);
	}
	outfile.open(outfilename, ios::out);	//打开文件
	if (!outfile.is_open()) {
		cout << "文件" << outfilename << "写入失败!" << endl;
		exit(0);
	}

	char ch;
	while (infile.peek() != EOF) {
		ch = infile.get();
		int ret = GetIndex(ch);
		if (ret == -1) {
			cout << "文件内包含ASCII码不在0-127内的字符!" << endl;
			exit(0);
		}
		outfile << code_list[ret];
	}

	cout << "文件" << infilename << "已成功编码, 请打开" << outfilename << "查看具体信息。" << endl;

	infile.close();
	outfile.close();
}


/**
 * @brief 解码功能
 * @param infilename 待解码的文件名
 * @param outfilename 解码后的文件名
*/
void HuffmanTree::Inner_Decode(const char* infilename, const char* outfilename)
{
	ifstream infile;
	ofstream outfile;
	infile.open(infilename, ios::in);		//打开输入文件
	if (!infile.is_open()) {
		cout << "文件" << infilename << "打开失败!" << endl;
		exit(0);
	}
	outfile.open(outfilename, ios::out);	//打开输出文件
	if (!outfile.is_open()) {
		cout << "文件" << outfilename << "写入失败!" << endl;
		exit(0);
	}

	unsigned char ch;
	HTPointer now = &tree[2 * n - 1];
	while (infile.peek() != EOF) {
		ch = infile.get();
		if (ch == '0' && now->lchild) {
			now = &tree[now->lchild];
		}
		else if (ch == '1' && now->rchild) {
			now = &tree[now->rchild];
		}
		else if (ch != '1' && ch != '0') {
			cout << "文件编码格式有误!" << endl;
			exit(0);
		}
		else {
			outfile << now->value;
			now = &tree[2 * n - 1];
			if (ch == '0' && now->lchild) {
				now = &tree[now->lchild];
			}
			else if (ch == '1' && now->rchild) {
				now = &tree[now->rchild];
			}
		}
	}

	/* 补上最后一个字符 */
	outfile << now->value;
	cout << "文件" << infilename << "已经成功解码为文件" << outfilename << endl;

	infile.close();
	outfile.close();
}



/**
 * @brief 压缩功能
 * @param infilename 待压缩的文件名
 * @param outfilename 待解压的文件名
*/
void HuffmanTree::Inner_Compress(const char* infilename, const char* outfilename)
{
	ifstream infile;
	ofstream outfile;

	infile.open(infilename, ios::in | ios::binary);					//打开输入文件
	if (!infile.is_open()) {
		cout << "文件" << infilename << "打开失败!" << endl;
		exit(0);
	}

	outfile.open(outfilename, ios::out | ios::binary);	//打开输出文件
	if (!outfile.is_open()) {
		cout << "文件" << outfilename << "写入失败!" << endl;
		exit(0);
	}

	outfile << (unsigned char)n;			//把字符个数写入
	for (unsigned int i = 1; i <= n; i++) {
		outfile << tree[i].value;			//二进制写入, 节省空间
		for (int j = 0; j < 4; j++) {	//unsigned int分4次写入
			outfile << char(tree[i].weight >> (j * 8));
		}
	}

	//等到8个字节完整后输出一次
	unsigned char ch, outch = 0;
	int i = 1;
	int org_tot = 0, aft_tot = 0;		//统计字符个数
	while (infile.peek() != EOF) {
		ch = infile.get();
		org_tot++;
		int ret = GetIndex(ch);
		if (ret == -1) {
			cout << "文件中存在非0-127内字符!" << endl;
			exit(0);
		}
		for (unsigned int j = 0; j < strlen(code_list[ret]); j++) {
			if (code_list[ret][j] == '1')
				outch |= (1 << (8 - i));
			i++;
			if (i == 9) {
				aft_tot++;
				outfile << outch;
				outch = 0;
				i = 1;
			}
		}
	}

	if (i != 1) {
		aft_tot++;
		outfile << outch;
	}

	cout << "文件" << infilename << "已经压缩成功, 压缩率为" << aft_tot * 100.0 / org_tot << "%" << endl;

	infile.close();
	outfile.close();
}



/**
 * @brief 解压功能
 * @param infilename 待解压的文件名
 * @param outfilename 解压后的文件名
*/
void HuffmanTree::Inner_Decompress(const char* infilename, const char* outfilename)
{
	ifstream infile;
	ofstream outfile;
	infile.open(infilename, ios::in | ios::binary);		//打开输入文件
	if (!infile.is_open()) {
		cout << "文件" << infilename << "打开失败!" << endl;
		exit(0);
	}
	outfile.open(outfilename, ios::out | ios::binary);	//打开输出文件
	if (!outfile.is_open()) {
		cout << "文件" << outfilename << "写入失败!" << endl;
		exit(0);
	}

	unsigned char ch;
	//读取n的信息
	ch = infile.get();
	//若所有字符都占 则会溢出为0
	n = ch ? ch : 256;
	//从文件头读取字符频数信息
	char_list = new(nothrow) CharWithNode[n];
	if (!char_list)
		exit(OVER_FLOW);

	int tot_ch = 0, cur_ch = 0;			//统计文档总字符数量

	for (unsigned int i = 0; i < n; i++) {
		ch = infile.get();
		char_list[i].ch = ch;
		char_list[i].weight = 0;
		for (int j = 0; j < 4; j++) {
			ch = infile.get();
			char_list[i].weight |= (ch << (j * 8));
		}
		tot_ch += char_list[i].weight;
	}

	HuffmanCoding();

	unsigned char cur;
	HTPointer now = &tree[2 * n - 1];					//这个位置是哈夫曼树的根节点
	while (infile.peek() != EOF) {
		cur = infile.get();
		//在哈夫曼树中找对应的编码
		for (int i = 1; i <= 8; i++) {
			char bit = !!(cur & (1 << (8 - i)));
			if (bit == 0 && now->lchild) {
				now = &tree[now->lchild];
			}
			else if (bit == 1 && now->rchild) {
				now = &tree[now->rchild];
			}
			else {
				cur_ch++;				//记录字符数
				if (cur_ch > tot_ch)	//文件长度到了 防止末尾0被误判
					break;
				outfile << now->value;
				now = &tree[2 * n - 1];
				if (bit == 0 && now->lchild) {
					now = &tree[now->lchild];
				}
				else if (bit == 1 && now->rchild) {
					now = &tree[now->rchild];
				}
			}
		}
	}

	//最后一个字节正好结束 没来得及输出
	if (cur_ch < tot_ch)
		outfile << now->value;

	cout << "文件" << infilename << "已解压成功!" << endl;

	infile.close();
	outfile.close();
}



/**
 * @brief 打印哈夫曼树
*/
void HuffmanTree::PrintTree()
{
	int depth = 0;
	{
		struct NodeWithDepth {
			HTPointer node;
			int depth;
			NodeWithDepth(HTPointer bb = NULL, int dd = 1)
			{
				node = bb;
				depth = dd;
			}
		};
		SqQueue<NodeWithDepth> queue(1000);  //queue的最大长度

		NodeWithDepth p;
		queue.EnQueue(NodeWithDepth(&tree[2 * n - 1], 1));
		while (!queue.QueueEmpty()) {
			queue.DeQueue(p);
			depth = max(depth, p.depth);
			if (p.node->lchild)
				queue.EnQueue(NodeWithDepth(&tree[p.node->lchild], p.depth + 1));
			if (p.node->rchild)
				queue.EnQueue(NodeWithDepth(&tree[p.node->rchild], p.depth + 1));
		}
	}
	/* 以上求算队列深度 */

	/* 以下开始做输出 */
	{
		struct NodeWithNo {
			HTPointer node;
			int depth;
			int no;
			NodeWithNo(HTPointer bb = NULL, int dd = 1, int nn = 1)
			{
				node = bb;
				depth = dd;
				no = nn;
			}
		};
		SqQueue<NodeWithNo> queue(1000), queue2(1000);  //queue的最大长度

		queue.ClearQueue();
		queue.EnQueue(NodeWithNo(&tree[2 * n - 1], 1, 1));
		NodeWithNo p, q, r, s;
		//补第一行的前置空格
		PrintSpace(pow2(depth - 1) - 1);
		while (!queue.QueueEmpty()) {
			queue.DeQueue(p);
			if (p.node->lchild)
				queue.EnQueue(NodeWithNo(&tree[p.node->lchild], p.depth + 1, 2 * p.no));
			if (p.node->rchild)
				queue.EnQueue(NodeWithNo(&tree[p.node->rchild], p.depth + 1, 2 * p.no + 1));
			//输出当前节点
			cout << p.node->value;
			queue2.EnQueue(p);		  //塞入另一个队列 是为了下一行输出 / \ 
			if (queue.QueueEmpty())   //最后一个节点输出结束了 换行
				cout << endl;
			else {
				queue.GetHead(q);
				if (q.depth == p.depth) {   //在相同层次
					PrintSpace((q.no - p.no) * pow2((depth - p.depth) + 1) - 1);
				}
				else {					    //在不同层次
					cout << endl;
					//先处理行首空格
					queue2.GetHead(r);
					PrintSpace(pow2(depth - p.depth) - 2 + (r.no - pow2(p.depth - 1)) * pow2((depth - p.depth) + 1));
					while (!queue2.QueueEmpty()) {
						queue2.DeQueue(r);
						cout << (r.node->lchild ? '/' : ' ') << ' ' << (r.node->rchild ? '\\' : ' ');
						if (!queue2.QueueEmpty()) {  //不是行末
							queue2.GetHead(s);
							PrintSpace((s.no - r.no) * pow2((depth - s.depth) + 1) - 3);
						}
					}
					cout << endl;
					PrintSpace(pow2(depth - q.depth) - 1 + (q.no - pow2(p.depth)) * pow2((depth - q.depth) + 1));
				}
			}
		}
	}
}


/**
 * @brief 展示模式
 * @param str 输入的字符串
*/
void HuffmanTree::Display(const char* str)
{
	CalCharFreq(str);
	HuffmanCoding();
	PrintTree();
}


/**
 * @brief 编码模式
 * @param infilename 待编码文件
 * @param outfilelist 字符频数文件
 * @param outfilename 编码后文件
*/
void HuffmanTree::Encode(const char* infilename, const char* outfilelist, const char* outfilename)
{
	CalCharFreq(infilename, outfilelist);
	HuffmanCoding();
	Inner_Encode(infilename, outfilename);
}


/**
 * @brief 解码模式
 * @param infilename 待解码文件
 * @param infilelist 字符频数文件
 * @param outfilename 解码后文件
*/
void HuffmanTree::Decode(const char* infilename, const char* infilelist, const char* outfilename)
{
	ReadCharFreq(infilelist);
	HuffmanCoding();
	Inner_Decode(infilename, outfilename);
}


/**
 * @brief 压缩模式
 * @param infilename 待压缩文件
 * @param outfilename 压缩后文件
*/
void HuffmanTree::Compress(const char* infilename, const char* outfilename)
{
	CalCharFreq(infilename, NULL, false);	//该模式不另外写入文件中
	HuffmanCoding();
	Inner_Compress(infilename, outfilename);
}


/**
 * @brief 解压模式
 * @param infilename 待解压文件
 * @param outfilename 解压后文件
*/
void HuffmanTree::Decompress(const char* infilename, const char* outfilename)
{
	Inner_Decompress(infilename, outfilename);
	//先从文件中读入 因此在函数内调用HuffmanCoding
}