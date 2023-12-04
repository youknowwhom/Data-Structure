#include <iostream>
#include <iomanip>
#include <conio.h>
#include "./long_long_int.h"
#include "./sqstack.hpp"
#include "./linkstack.hpp"
using namespace std;

/* 用栈消解方式模拟函数存放的信息 */
struct Data {
	int n;					//传入的参数, 表示当前的数n
	int returnAddress;		//函数的返回地址 此处实际用于表示该函数进行到的模块0/1
	Data(){					//无参构造函数
		n = 1;
		returnAddress = 0;
	};					
	Data(int _n, int _ra)	//双参构造函数
	{
		n = _n;
		returnAddress = _ra;
	}
};

/**
 * @brief 递归方式求阶乘
 * @param n 求n!
 * @return 阶乘结果
*/
LONG_LONG_INT Factorial_1(int n)
{
	if (n == 1)
		return 1;
	else
		return LONG_LONG_INT(n) * Factorial_1(n - 1);
}

/**
 * @brief 栈消解方式求阶乘
 * @tparam stack 栈的类型
 * @param n 求n!
 * @param function 存放函数信息的栈
 * @return 阶乘结果
*/
template <class stack>
LONG_LONG_INT Factorial_2(int n, stack& function)
{
	LONG_LONG_INT ret;		  //模拟通过寄存器传递的各个函数返回值

	function.Push({ n, 0 });  //模拟第一个函数被main调用
	while (!function.StackEmpty()) {
		Data now;
		function.Top(now);
		switch (now.returnAddress) {
			//递归调用的部分
			case 0:
				function.Pop(now);
				if (now.n > 1) {
					function.Push({ now.n, 1 });		//保存现场
					function.Push({ now.n - 1, 0 });	//调用下一层
				}
				else {
					ret = 1;		//返回
				}
				break;
			//回溯的部分
			case 1:
				function.Pop(now);						//恢复现场
				ret = ret * LONG_LONG_INT(now.n);		//计算返回值
				break;
		}
	}
	
	return ret;
}

/**
 * @brief 等待回车输入
 * @param prompt 提示语
*/
void wait_for_enter(const char* prompt)
{
	cout << endl << prompt << ",请按回车键继续";
	while (getchar() != '\n')
		;
	cout << endl << endl;
}

/**
 * @brief 可视化菜单界面
 * @return 选择的菜单项
*/
int Menu()
{
	//system("mode con: cols=83 lines=30");
	cout << endl << endl << endl << endl;
	cout << "\t\t\t\t   PA2-栈的应用" << endl;

	cout << endl << endl;
	cout << "\t\t\t\t    菜单选择" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl;
	cout << "\t|\t1\t|\t2\t|\t3\t|\t0\t|" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << "\t|   顺序表栈\t|     链表栈\t|    普通递归\t|    退出演示\t|" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl << endl << endl;
	cout << "\t\t\t     [请按对应数字选择功能]" << endl;
	cout << "\t\t\t\t\t";
	while (char ch = _getch())
		if (ch >= '0' && ch <= '7')
			return ch - '0';
	return 0;
}

int main()
{
	LinkStack<Data> linkstack;
	SqStack<Data> sqstack;
	int ret;
	int n;
	while (ret = Menu()) {
		switch (ret){
			case 1:
				system("cls");
				cout << "------测试(顺序表)栈消解方式计算n的阶乘-----" << endl << endl;
				cout << "请输入求阶乘的最大值" << endl;
				cin >> n;
				wait_for_enter("演示即将开始");
				cout << "n\t阶乘结果" << endl;
				cout << "------------------------------------" << endl;
				for (int i = 1; i <= n; i++)
					cout << i << "\t" << Factorial_2(i, sqstack) << endl;
				wait_for_enter("演示完毕");
				system("cls");
				break;
			case 2:
				system("cls");
				cout << "------测试(链表)栈消解方式计算n的阶乘-----" << endl << endl;
				cout << "请输入求阶乘的最大值" << endl;
				cin >> n;
				wait_for_enter("演示即将开始");
				cout << "n\t阶乘结果" << endl;
				cout << "------------------------------------" << endl;
				for (int i = 1; i <= n; i++)
					cout << i << "\t" << Factorial_2(i, linkstack) << endl;
				wait_for_enter("演示完毕");
				system("cls");
				break;
			case 3:
				system("cls");
				cout << "-----测试递归函数方式计算n的阶乘-----" << endl << endl;
				cout << "请输入求阶乘的最大值" << endl;
				cin >> n;
				wait_for_enter("演示即将开始");
				cout << "n\t阶乘结果" << endl;
				cout << "-------------------------------------" << endl;
				for (int i = 1; i <= n; i++)
					cout << i << "\t" << Factorial_1(i) << endl;
				system("cls");
				break;
		}
	}

	return 0;
}