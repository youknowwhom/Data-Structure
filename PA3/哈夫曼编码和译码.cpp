#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <iomanip>
#include "./HuffmanTree.h"

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
	cout << "Usage: " << procname << " { --display }" << endl;
	cout << setw(wkey) << ' ' << "{ --encode filename1 filename2 filename3 }" << endl;
	cout << setw(wkey) << ' ' << "{ --decode filename1 filename2 filename3 }" << endl;
	cout << setw(wkey) << ' ' << "{ --compress filename1 filename2 }" << endl;
	cout << setw(wkey) << ' ' << "{ --decompress filename1 filename2 }" << endl;
	cout << endl;

	cout << setw(wkey) << ' ' << "必选项：指定程序功能(五选一)" << endl;
	cout << setw(wopt) << ' ' << "--display : 展示哈夫曼树型结构" << endl;
	cout << setw(wopt) << ' ' << "--encode : (演示用)将文件进行哈夫曼编码 [待编码文件] [输出的字符频数文件] [编码后文件]" << endl;
	cout << setw(wopt) << ' ' << "--decode : (演示用)将哈夫曼编码文件解码 [待解码文件] [输入的字符频数文件] [解码后文件]" << endl;
	cout << setw(wopt) << ' ' << "--compress : 将文件用哈夫曼编码压缩 [待压缩文件] [压缩后文件]" << endl;
	cout << setw(wopt) << ' ' << "--decompress : 将哈夫曼编码文件解压 [待解压文件] [解压后文件]" << endl;
	cout << endl;
}


int main(int argc, char** argv)
{
	HuffmanTree tree;

	if (argc == 1)
		usage(argv[0], argc);

	/* display模式 */
	else if (strcmp(argv[1], "--display") == 0 && argc == 2) {
		char input[128];
		cout << "\n请输入演示用字符串 : ";
		cin >> input;
		tree.Display(input);
	}

	/* encode模式 */
	else if (strcmp(argv[1], "--encode") == 0 && argc == 5)
		tree.Encode(argv[2], argv[3], argv[4]);

	/* decode模式 */
	else if (strcmp(argv[1], "--decode") == 0 && argc == 5)
		tree.Decode(argv[2], argv[3], argv[4]);

	/* compress模式 */
	else if (strcmp(argv[1], "--compress") == 0 && argc == 4)
		tree.Compress(argv[2], argv[3]);

	/* decompress模式 */
	else if (strcmp(argv[1], "--decompress") == 0 && argc == 4)
		tree.Decompress(argv[2], argv[3]);

	else 
		usage(argv[0], argc);

	return 0;
}