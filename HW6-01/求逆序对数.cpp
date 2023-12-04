#include <iostream>
#include <cstring>
#define MAXN 20005
using namespace std;
int cnt = 0;
//int型数组存放输入的数字 并用于排序
//newarr用于暂存merge后的新数组
int arr[MAXN], newarr[MAXN];

/**
 * @brief 将两个有序的序列合并
 * @param arr 存放序列的数组
 * @param l 前一个序列的开始
 * @param m 两序列的分隔下标
 * @param r 后一个序列的结束
*/
void Merge(int arr[], int l, int m, int r)
{
	int i = l, j = m + 1, k;
	//此处k起始值是l不是1
	for (k = l; i <= m && j <= r; k++) {
		//在此处取等
		if (arr[i] <= arr[j])
			newarr[k] = arr[i++];
		else {
			cnt += m - i + 1;
			newarr[k] = arr[j++];
		}
	}

	while (i <= m)
		newarr[k++] = arr[i++];

	while (j <= r)
		newarr[k++] = arr[j++];

	memcpy(arr + l, newarr + l, (r - l + 1) * sizeof(int));
}

/**
 * @brief 归并排序
 * @param arr 排序的数组
 * @param l 此时在排序序列的最左侧下标
 * @param r 此时在排序序列的最右侧下标
*/
void MergeSort(int arr[], int l, int r)
{
	if (l == r)
		return;
	else {
		int m = (l + r) / 2;
		MergeSort(arr, l, m);
		//注意此处是 m+1
		MergeSort(arr, m + 1, r);
		Merge(arr, l, m, r);
		//printf("此时l为%d, r为%d, 数组为", l, r);
		//for (int i = l; i <= r; i++)
		//	cout << arr[i] << " ";
		//cout << endl;
	}
}

int main()
{
	int n;

	while (true) {
		cin >> n;
		if (!n)
			break;
		cnt = 0;
		for (int i = 1; i <= n; i++)
			cin >> arr[i];
		MergeSort(arr, 1, n);
		cout << cnt << endl;
	}
	return 0;
}