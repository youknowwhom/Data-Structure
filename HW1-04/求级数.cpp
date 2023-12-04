#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1024;
int A[maxn], Apow[maxn], I[maxn], MUL[maxn], ANS[maxn];
int n;
void print(int* c)
{
	bool cflag = 0;
	for (int i = maxn - 1; i >= 0; i--) {
		if (c[i])
			cflag = 1;
		if (cflag)
			printf("%d", c[i]);
	}
	if (!cflag)
		printf("0");
	cout << endl;
}

/* a*b,乘积存入b中 */
void mul(int* a, int* b)
{
	int c[maxn];
	memset(c, 0, maxn);
	for (int i = 0; i < maxn / 2 - 1; i++) {
		for (int j = 0; j < maxn / 2 - 1; j++) {
			int newn = c[i + j] + a[i] * b[j];
			c[i + j] = newn % 10;
			c[i + j + 1] += newn / 10;
		}
	}
	memcpy(b, c, maxn);
}

/* a+b,和存入a中 */
void add(int* a, int* b)
{
	for (int i = 0; i < maxn - 1; i++) {
		a[i] += b[i];
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
	}
}

int main()
{
	int a, n;
	cin >> n >> a;
	A[1] = a / 10;
	A[0] = a % 10;
	Apow[0] = 1;

	for (int i = 1; i <= n; i++) {
		I[0] = i % 10;
		I[1] = i / 10;
		mul(A, Apow);   //求此时的次幂
		memcpy(MUL, Apow, maxn);
		mul(I, MUL);	//求系数
		add(ANS, MUL);	//求次数和
	}

	print(ANS);
	return 0;
}