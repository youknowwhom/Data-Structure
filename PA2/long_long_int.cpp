#include "./long_long_int.h"

/**
 * @brief 大整数的无参构造（置0）
*/
LONG_LONG_INT::LONG_LONG_INT()
{
	memset(this->number, 0, sizeof(this->number));
	length = 1;
}

/**
 * @brief 通过long long构造大整数
 * @param n 大整数的值n
*/
LONG_LONG_INT::LONG_LONG_INT(long long n)
{
	memset(this->number, 0, sizeof(this->number));
	for (int i = 0; ; i++) {
		this->number[i] = n % 10;
		n /= 10;
		if (!n) {
			length = i + 1;
			return;
		}
	}
}

/**
 * @brief 重载运算符* 大整数乘法
 * @param that 参与乘法的另一个大整数
 * @return 乘积
*/
const LONG_LONG_INT LONG_LONG_INT:: operator*(const LONG_LONG_INT& that) const
{
	LONG_LONG_INT answer;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < that.length; j++) {
			int newn = answer.number[i + j] + this->number[i] * that.number[j];
			answer.number[i + j] = newn % 10;
			answer.number[i + j + 1] += newn / 10;
		}
	}

	//特判0
	if ((length == 1 && !number[0]) || (that.length == 1 && !that.number[0])) {
		answer.length = 1;
		return answer;
	}

	answer.length = answer.number[length + that.length - 1] ? length + that.length : length + that.length - 1;
	return answer;
}

/**
 * @brief 重载运算符+ 大整数加法
 * @param that 参与加法的另一个大整数
 * @return 运算的和
*/
const LONG_LONG_INT LONG_LONG_INT:: operator+(const LONG_LONG_INT& that) const
{
	LONG_LONG_INT answer;
	for (int i = 0; i < max(that.length, length); i++) {
		answer.number[i] += number[i] + that.number[i];
		answer.number[i + 1] += answer.number[i] / 10;
		answer.number[i] %= 10;
	}

	answer.length = answer.number[max(that.length, length)] ? max(that.length, length) + 1 : max(that.length, length);
	return answer;
}

/**
 * @brief 重载>> 流输入大整数
 * @param in 输入流
 * @param that 输入的大整数对象
*/
istream& operator >> (istream& in, LONG_LONG_INT& that)
{
	char input[2048];
	in >> input;

	that.length = strlen(input);

	for (int i = that.length - 1; i >= 0; i--)
		that.number[that.length - 1 - i] = input[i] - '0';

	return in;
}

/**
 * @brief 重载<< 流输出大整数
 * @param in 输出流
 * @param that 输出的大整数对象
*/
ostream& operator << (ostream& out, const LONG_LONG_INT& that)
{
	for (int i = that.length - 1; i >= 0; i--)
		out << that.number[i] + 0;		//整型提升, int输出

	return out;
}
