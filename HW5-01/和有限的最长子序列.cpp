#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

/**
 * @brief 求前缀和数组
 * @param n 数组元素个数
 * @param nums 原数组
 * @param presum 前缀和数组
*/
void getPrefixSum(int n, int* nums, int* presum)
{
	memset(presum, 0, n * sizeof(int));
	for (int i = 0; i < n; i++) {
		if (i == 0)
			presum[i] = nums[i];
		else
			presum[i] = presum[i - 1] + nums[i];
	}
}

/**
 * @brief 二分查找最小长度
 * @param n 数组元素个数
 * @param nums 前缀和数组
 * @param tgt 所求的序列和
 * @return 
*/
int searchBin(int n, int* nums, int tgt)
{
	int l = 0, r = n;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (nums[mid] <= tgt)
			l = mid;
		else
			r = mid;
	}

	//特殊处理 数组内所有元素都小于queries[i]的情况
	if (nums[l] > tgt)
		return l - 1;

	return l;
}

int main()
{
	int n, m;
	//nums用于存储读入的数组，并进行排序
	//preSum用于存储排序后的前缀和
	int nums[1000], preSum[1000];
	cin >> n >> m;

	for (int i = 0; i < n; i++)
		cin >> nums[i];

	//先排序
	sort(nums, nums + n);

	getPrefixSum(n, nums, preSum);

	
	for (int i = 0; i < m; i++) {
		int query;
		cin >> query;
		cout << searchBin(n, preSum, query) + 1 << " ";
	}

	return 0;
}