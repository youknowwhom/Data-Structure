#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "./queue.hpp"
using namespace std;
const char* CommodityNameList[] = { "数据结构（C语言版）\t", "离散数学学习指导与习题解析", "数字逻辑与组成原理实践教程", "概率论与数理统计\t", "概率论与数理统计同步习题册", "跨文化商务交际\t", "计算机科学概论\t" };
struct Data {
	char CommodityName[128];	//商品名称
	float Price;				//商品价格
	int RequestTime;			//请求的时间
	friend ostream& operator<<(ostream& out, const Data& that);
};

ostream& operator<<(ostream& out, const Data& that)
{
	cout << "商品名称:" << that.CommodityName << "\t\t\t商品价格:" << that.Price << "\t\t请求时间:第" << that.RequestTime << "秒" << endl;
	return out;
}

void wait_for_enter()
{
	cout << endl << "请按回车键继续";
	while (getchar() != '\n')
		;
	cout << endl << endl;
}

int Menu()
{
	system("mode con: cols=83 lines=30");
	cout << endl << endl << endl << endl;
	cout << "\t\t\t\t PA2*-队列的应用" << endl;
	
	cout << endl << endl;
	cout << "\t\t\t\t    菜单选择" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << "\t|\t1\t|\t2\t|\t3\t|\t0\t|" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << "\t|   测试队列\t|   无消息队列\t|   有消息队列\t|      退出\t|" << endl;
	cout << "\t|   基础功能\t|    场景模拟\t|    场景模拟\t|      QUIT\t|" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl << endl << endl;
	cout << "\t\t\t     [请按对应数字选择功能]" << endl;
	cout << "\t\t\t\t\t";
	while (char ch = _getch()) 
		if (ch >= '0' && ch <= '3')
			return ch - '0';
	return 0;
}

void TestBasicFunction()
{
	system("cls");
	int e;
	cout << "下面开始测试SqQueue的各个功能" << endl;
	cout << "-----------------------------" << endl;

	cout << endl << "<测试构造函数>" << endl;
	cout << "请输入队列的最大长度:";
	int maxsize;
	cin >> maxsize;
	while (!cin.good()) {
		cout << "输入有误, 请重新输入:";
		cin.clear();
		cin.ignore(65536, '\n');
		cin >> maxsize;
	}
	getchar();
	{
		SqQueue<int> queue(maxsize);
		cout << "最大长度为" << maxsize << "的空队列建立成功" << endl;
		wait_for_enter();


#if 1
		cout << endl << "<测试Enqueue功能>" << endl;
		for (int i = 0; i <= maxsize + 2; i++) {
			if (queue.EnQueue(i * 2 + 1) == OK)
				cout << "元素(" << i * 2 + 1 << ")插入完毕" << endl;
			else
				cout << "元素(" << i * 2 + 1 << ")插入失败" << endl;
		}
		wait_for_enter();
#endif


#if 1
		cout << endl << "<测试Dequeue功能>" << endl;
		for (int i = 0; i <= maxsize + 2; i++) {
			if (queue.DeQueue(e) == OK)
				cout << "元素(" << e << ")已成功出队" << endl;
			else
				cout << "队列已空, 出队失败!" << endl;
		}
		wait_for_enter();
#endif


#if 1
		cout << endl << "<测试GetHead功能>" << endl;
		cout << "先将队列重新填充" << endl;
		for (int i = 0; i <= maxsize + 2; i++) {
			if (queue.EnQueue(i * 2 + 1) == OK)
				cout << "元素(" << i * 2 + 1 << ")插入完毕" << endl;
			else
				cout << "元素(" << i * 2 + 1 << ")插入失败" << endl;
		}

		cout << endl << "填充完毕, 下面开始测试" << endl;
		for (int i = 0; i <= maxsize + 2; i++) {
			if (queue.GetHead(e) == OK)
				cout << "元素(" << e << ")当前在队首" << endl;
			else
				cout << "队列已空, 队首获取失败!" << endl;
			if (queue.DeQueue(e) == OK)
				cout << "元素(" << e << ")已成功出队" << endl;
			else
				cout << "队列已空, 出队失败!" << endl;
		}
		wait_for_enter();
#endif


#if 1
		cout << endl << "<测试PrintQueue功能>" << endl;
		cout << "先将队列重新填充" << endl;
		for (int i = 0; i <= maxsize + 2; i++) {
			if (queue.EnQueue(i * 2 + 1) == OK)
				cout << "元素(" << i * 2 + 1 << ")插入完毕" << endl;
			else
				cout << "元素(" << i * 2 + 1 << ")插入失败" << endl;
		}
		cout << "队列内元素cout打印如下:" << endl;
		queue.PrintQueue(cout);
		cout << "下面测试输出到文件,";
		ofstream out;
		out.open("test.txt", ios::out);
		out << "队列内元输出到文件打印如下:" << endl;
		queue.PrintQueue(out);
		cout << "请打开可执行文件所在目录检查test.txt文件中输出" << endl;
		out.close();
		wait_for_enter();
#endif


#if 1
		cout << endl << "<测试ClearQueue功能>" << endl;
		cout << "下面开始清空队列" << endl;
		queue.ClearQueue();
		cout << "队列清空完毕, 队列内元素打印如下:" << endl;
		queue.PrintQueue(cout);
		wait_for_enter();
#endif


#if 1
		cout << endl << "<测试QueueEmpty功能>" << endl;
		cout << "当前队列状态是:" << (queue.QueueEmpty() ? "空" : "非空") << endl;
		cout << "将队列重新填充" << endl;
		for (int i = 0; i <= maxsize + 2; i++) {
			if (queue.EnQueue(i * 2 + 1) == OK)
				cout << "元素(" << i * 2 + 1 << ")插入完毕" << endl;
			else
				cout << "元素(" << i * 2 + 1 << ")插入失败" << endl;
		}
		cout << "当前队列状态是:" << (queue.QueueEmpty() ? "空" : "非空") << endl;
		wait_for_enter();
#endif


#if 1
		cout << endl << "<测试QueueLength功能>" << endl;
		cout << "当前队列长度是:" << queue.QueueLength() << endl;
		for (int i = 0; i <= maxsize + 2; i++) {
			if (queue.DeQueue(e) == OK)
				cout << "元素(" << e << ")已成功出队" << endl;
			else
				cout << "队列已空, 出队失败!" << endl;
			cout << "当前队列长度是:" << queue.QueueLength() << endl;
		}
		wait_for_enter();
#endif


		cout << endl << "<测试析构函数>" << endl;
	}
	cout << "Queue队列已经被销毁成功" << endl;
	wait_for_enter();

	cout << "队列功能测试完毕, 按任意键返回主菜单";
	getchar();
}

void Simulation1()
{
	system("cls");
	int TotalMiss = 0;
	cout << "即将开始模拟100秒内的请求" << endl;
	wait_for_enter();
	for (int i = 1; i <= 100; i++) {
		int request = rand() % 3000 + 500;
		cout << endl << "第" << i << "秒内产生了" << request << "个请求" << endl;
		if (request >= 1000) {
			request -= 1000;
			cout << "B系统处理1000个请求" << endl;
			if (request >= 1000) {
				request -= 1000;
				cout << "C系统处理1000个请求" << endl;
			}
			else {
				cout << "C系统处理" << request << "个请求" << endl;
				request = 0;
			}
		}
		else {
			cout << "B系统处理" << request << "个请求" << endl;
			request = 0;
		}
		if(request)
			cout << "本秒有" << request << "个请求被阻塞" << endl;
		TotalMiss += request;
		Sleep(100);
	}
	cout << endl << endl << "总共有" << TotalMiss << "条请求被阻塞" << endl;
	wait_for_enter();
}

void Simulation2()
{
	system("cls");
	SqQueue<Data> MessageQueue(10000);
	int RequestTot = 0, WaitSum = 0;
	cout << "即将开始模拟100秒内的请求" << endl;
	wait_for_enter();
	for (int i = 1; i <= 100; i++) {
		int request = rand() % 3000 + 500;
		cout << endl << "第" << i << "秒内产生了" << request << "个请求" << endl;
		Data e;
		for (int j = 0; j < request; j++) {
			strcpy(e.CommodityName, CommodityNameList[rand() % 7]);		//随机模拟商品名称
			e.Price = (rand() % 200 + 100) / 10.0f;						//随机模拟订单价格
			e.RequestTime = i;		//请求的时间点
			MessageQueue.EnQueue(e);
		}

		//系统开始处理请求
		int j;
		for (j = 1; j <= 1000; j++) {
			if (MessageQueue.DeQueue(e) != OK) 
				break;
				//队列已经为空
			RequestTot++;
			WaitSum += i - e.RequestTime;	//等待时间
		}
		cout << "系统B处理了" << j - 1 << "个请求" << endl;

		for (j = 1; j <= 1000; j++) {
			if (MessageQueue.DeQueue(e) != OK) 
				break;
				//队列已经为空
			RequestTot++;
			WaitSum += i - e.RequestTime;	//等待时间
		}
		cout << "系统C处理了" << j - 1 << "个请求" << endl;
		cout << "消息队列中有" << MessageQueue.QueueLength() << "个请求" << endl;
		Sleep(100);
	}

	cout << endl << endl<< "总共成功处理请求" << RequestTot << "个" << endl;
	cout<< "平均每位用户等待请求被处理花费" << WaitSum * 1.0f / RequestTot << "秒" << endl;
	wait_for_enter();

	system("mode con: cols=150 lines=50");
	cout << "截止到第100秒, 还有" << MessageQueue.QueueLength() << "个请求未被处理，具体如下:" << endl;
	wait_for_enter();
	MessageQueue.PrintQueue(cout);

	cout << "测试已结束, 即将返回主菜单" << endl;
	wait_for_enter();
}

int main()
{
	int ret;
	srand((unsigned)time(NULL));
	while (ret = Menu()) {
		switch (ret){
			case 1:
				TestBasicFunction();
				break;
			case 2:
				Simulation1();
				break;
			case 3:
				Simulation2();
				break;
		}
	}
	
	return 0;
}