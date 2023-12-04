#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <stack>
#include "./Trie.h"
using namespace std;

/* void usage(const char* const procname, const int args_num)
 * @brief 打印函数提示信息
 * @param procname 可执行文件名称
 * @param args_num 参数个数
*/
void usage(const char* const procname, const int args_num)
{
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;

	cout << endl;
	cout << "Usage: " << procname << " { --count filename1 (filename2) }" << endl;
	cout << setw(wkey) << ' ' << "{ --top10 filename1 (filename2) }" << endl;
	cout << endl;

	cout << setw(wkey) << ' ' << "必选项：指定程序功能(二选一)" << endl;
	cout << setw(wopt) << ' ' << "--count : 统计词频 [输入文件] [输出文件(未指定则为屏幕)]" << endl;
	cout << setw(wopt) << ' ' << "--top10 : 输出出现频率最高的前top_num单词 [输入文件] [输出文件(未指定则为屏幕)]" << endl;
	cout << endl;
}

int main(int argc, char** argv)
{
	Trie trie;
	ofstream outfile;
	if ((argc == 3 || argc == 4) && (strcmp(argv[1], "--count") == 0 || strcmp(argv[1], "--top10") == 0)) {
		if (strcmp(argv[1], "--count") == 0){
			if (!trie.ReadFromFile(argv[2]))
				return -1;
			switch (argc) {
				case 3:
					trie.Traverse(cout);
					break;
				case 4:
					outfile.open(argv[3], ios::out);
					if (!outfile.is_open()) {
						cout << "文件[" << argv[3] << "]无法写入!" << endl;
						return -1;
					}
					trie.Traverse(outfile);
					cout << "统计信息已成功写入文件[" << argv[3] << "]中" << endl;
					outfile.close();
					break;
			}
		}
		else if (strcmp(argv[1], "--top10") == 0) {
			if (!trie.ReadFromFile(argv[2]))
				return -1;
			switch (argc) {
				case 3:
					trie.PrintTop(cout);
					break;
				case 4:
					outfile.open(argv[3], ios::out);
					if (!outfile.is_open()) {
						cout << "文件[" << argv[3] << "]无法写入!" << endl;
						return -1;
					}
					trie.PrintTop(outfile);
					cout << "统计信息已成功写入文件[" << argv[3] << "]中" << endl;
					outfile.close();
					break;
			}
		}
	}
	else
		usage(argv[0], argc);

	return 0;
}