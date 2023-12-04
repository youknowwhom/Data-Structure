#include <iostream>
using namespace std;
const int maxn = 2100;
const int maxnPow2 = (int)5e6;
int a[maxn], b[maxn], add[maxnPow2], mul[maxnPow2];

void AddPoly()
{
	for (int i = 0; i < maxn; i++)
		add[i] = a[i] + b[i];
}

void MulPoly()
{
	for (int i = 0; i < maxn; i++) 
		for (int j = 0; j < maxn; j++)
			mul[i + j] += a[i] * b[j];
}

void InputPoly(int* input, int n)
{
	for (int i = 0; i < n; i++) {
		int e, p;
		cin >> p >> e;
		input[e] = p;
	}
}

void PrintPoly(int* output)
{
	for (int i = 0; i < maxnPow2; i++) {
		if (output[i]) {
			cout << output[i] << " " << i << " ";
		}
	}
	cout << endl;
}

int main()
{
	int n;
	cin >> n;
	InputPoly(a, n);
	cin >> n;
	InputPoly(b, n);
	cin >> n;

	switch (n) {
		case 2:
		case 0:
			AddPoly();
			PrintPoly(add);
			if (!n)
				break;
		case 1:
			MulPoly();
			PrintPoly(mul);
	}

	return 0;
}