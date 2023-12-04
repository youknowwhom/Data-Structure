#pragma once
#include <iostream>
#include <cstring>
using namespace std;
#define MAXN 1024	//最长存放的大整数位数(十进制)

//表示大整数的类
class LONG_LONG_INT {
private:
	//存放大整数的数组
	char number[MAXN];
	//大整数长度
	int length;

public:
	//无参构造大整数(0)
	LONG_LONG_INT();
	//用long long构造大整数
	LONG_LONG_INT(long long n);
	//重载大整数加法
	const LONG_LONG_INT operator+ (const LONG_LONG_INT& that) const;
	//重载大整数乘法
	const LONG_LONG_INT operator* (const LONG_LONG_INT& that) const;
	//重载>> 输入大整数
	friend istream& operator >> (istream& in, LONG_LONG_INT& that);
	//重载<< 输出大整数
	friend ostream& operator << (ostream& out, const LONG_LONG_INT& that);
};