/**
 * @file    template.cpp
 * @name    p57模板程序
 * @date    2022-11-22
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
int newarr[100010];
using namespace std;

/********************************/
/*     以下是你需要提交的代码     */
/********************************/
class Solution {
private:

	/* 归并排序 */
		/**
		 * @brief 将两个有序的序列合并
		 * @param arr 存放序列的数组
		 * @param l 前一个序列的开始
		 * @param m 两序列的分隔下标
		 * @param r 后一个序列的结束
		*/
	void Merge(vector<int>& arr, int l, int m, int r)
	{
		int i = l, j = m + 1, k;
		//此处k起始值是l不是1
		for (k = l; i <= m && j <= r; k++) {
			//在此处取等
			if (arr[i] <= arr[j])
				newarr[k] = arr[i++];
			else
				newarr[k] = arr[j++];
		}

		while (i <= m)
			newarr[k++] = arr[i++];

		while (j <= r)
			newarr[k++] = arr[j++];

		for (int i = l; i <= r; i++)
			arr[i] = newarr[i];
	}

	/**
	 * @brief 归并排序
	 * @param arr 排序的数组
	 * @param l 此时在排序序列的最左侧下标
	 * @param r 此时在排序序列的最右侧下标
	*/
	void MergeSort(vector<int>& arr, int l, int r)
	{
		if (l == r)
			return;
		else {
			int m = (l + r) / 2;
			MergeSort(arr, l, m);
			//注意此处是 m+1
			MergeSort(arr, m + 1, r);
			Merge(arr, l, m, r);
		}
	}

	/* 快速排序 */

	/**
	 * @brief 三数取中法找枢轴
	 * @param L 排序的vector
	 * @param low 当前排序的序列起始下标
	 * @param high 当前排序的序列结束下标
	*/
	void findpivotkey(vector<int>& L, int low, int high)
	{
		int min, max, mid = (low + high) / 2;
		if (L[low] < L[high]) {
			min = low;
			max = high;
		}
		else {
			min = high;
			max = low;
		}

		if (L[mid] < L[min])
			min = mid;

		if (L[mid] > L[max])
			max = mid;

		mid = low + high + mid - min - max;
		swap(L[low], L[mid]);
		return;
	}

	/**
	 * @brief （快速排序）将枢轴前后按大小分割
	 * @param L 排序的vector
	 * @param low 当前排序的序列起始下标
	 * @param high 当前排序的序列结束下标
	 * @return 枢轴的下标
	*/
	int Partition(vector<int>& L, int low, int high)
	{
		findpivotkey(L, low, high);
		int pivotkey = L[low];
		while (low < high) {
			while (low < high && L[high] > pivotkey)
				high--;
			swap(L[low], L[high]);
			while (low < high && L[low] <= pivotkey)
				low++;
			swap(L[high], L[low]);
		}

		return low;
	}

	/**
	 * @brief 快速排序
	 * @param L 排序的vector
	 * @param low 当前排序的序列起始下标
	 * @param high 当前排序的序列结束下标
	*/
	void Qsort(vector<int>& L, int low, int high)
	{
		if (low < high) {
			int mid = Partition(L, low, high);
			Qsort(L, low, mid - 1);
			Qsort(L, mid + 1, high);
		}
		return;
	}

	void QuickSort(vector<int>& L)
	{
		Qsort(L, 0, L.size() - 1);
		return;
	}



	/* 归并排序 */
	/**
	 * @brief 将两个有序的序列合并
	 * @param arr 存放序列的数组
	 * @param l 前一个序列的开始
	 * @param m 两序列的分隔下标
	 * @param r 后一个序列的结束
	*/
	void Merge(vector<int>& arr, int l, int m, int r)
	{
		int i = l, j = m + 1, k;
		//此处k起始值是l不是1
		for (k = l; i <= m && j <= r; k++) {
			//在此处取等
			if (arr[i] <= arr[j])
				newarr[k] = arr[i++];
			else
				newarr[k] = arr[j++];
		}

		while (i <= m)
			newarr[k++] = arr[i++];

		while (j <= r)
			newarr[k++] = arr[j++];

		for (int i = l; i <= r; i++)
			arr[i] = newarr[i];
	}

	/**
	 * @brief 归并排序
	 * @param arr 排序的数组
	 * @param l 此时在排序序列的最左侧下标
	 * @param r 此时在排序序列的最右侧下标
	*/
	void MergeSort(vector<int>& arr, int l, int r)
	{
		if (l == r)
			return;
		else {
			int m = (l + r) / 2;
			MergeSort(arr, l, m);
			//注意此处是 m+1
			MergeSort(arr, m + 1, r);
			Merge(arr, l, m, r);
		}
	}

	/* 快速排序 */

	/**
	 * @brief 三数取中法找枢轴
	 * @param L 排序的vector
	 * @param low 当前排序的序列起始下标
	 * @param high 当前排序的序列结束下标
	*/
	void findpivotkey(vector<int>& L, int low, int high)
	{
		int min, max, mid = (low + high) / 2;
		if (L[low] < L[high]) {
			min = low;
			max = high;
		}
		else {
			min = high;
			max = low;
		}

		if (L[mid] < L[min])
			min = mid;

		if (L[mid] > L[max])
			max = mid;

		mid = low + high + mid - min - max;
		swap(L[low], L[mid]);
		return;
	}

	/**
	 * @brief （快速排序）将枢轴前后按大小分割
	 * @param L 排序的vector
	 * @param low 当前排序的序列起始下标
	 * @param high 当前排序的序列结束下标
	 * @return 枢轴的下标
	*/
	int Partition(vector<int>& L, int low, int high)
	{
		findpivotkey(L, low, high);
		int pivotkey = L[low];
		while (low < high) {
			while (low < high && L[high] > pivotkey)
				high--;
			swap(L[low], L[high]);
			while (low < high && L[low] <= pivotkey)
				low++;
			swap(L[high], L[low]);
		}

		return low;
	}

	/**
	 * @brief 快速排序
	 * @param L 排序的vector
	 * @param low 当前排序的序列起始下标
	 * @param high 当前排序的序列结束下标
	*/
	void Qsort(vector<int>& L, int low, int high)
	{
		if (low < high) {
			int mid = Partition(L, low, high);
			Qsort(L, low, mid - 1);
			Qsort(L, mid + 1, high);
		}
		return;
	}

	void QuickSort(vector<int>& L)
	{
		Qsort(L, 0, L.size() - 1);
		return;
	}
	/**
	 * @brief 调整s到m的堆使其满足堆的性质
	 * @param H 堆
	 * @param s 起始下标
	 * @param m 终止下标
	*/
	void HeapAdjust(vector<int>& H, int s, int m)
	{
		int record = H[s];
		for (int j = 2 * s; j <= m; j *= 2) {
			//判断左/右 子树?
			if (j < m && H[j] < H[j + 1])
				j++;
			if (record >= H[j])
				break;
			H[s] = H[j];
			s = j;
		}
		H[s] = record;
	}

	/**
	 * @brief 堆排序
	 * @param H 用于排序的数组
	*/
	void HeapSort(vector<int>& H)
	{
		int Hlength = H.size();
		//扩充一位
		H.push_back(0);
		for (int i = Hlength; i > 0; i--)
			H[i] = H[i - 1];

		for (int i = Hlength / 2; i > 0; i--)
			HeapAdjust(H, i, H.size());

		for (int i = Hlength; i > 1; --i) {
			swap(H[1], H[i]);
			HeapAdjust(H, 1, i - 1);
		}

		for (int i = 0; i < Hlength; i++)
			H[i] = H[i + 1];
		H.pop_back();
		//删除一位
	}

	/**
	 * @brief 希尔排序的某一趟
	 * @param nums 排序的数组
	 * @param dk 增量
	*/
	void ShellInsert(vector<int>& nums, int dk)
	{
		int rec, j;
		for (int i = dk; i < nums.size(); i++) {
			if (nums[i] < nums[i - dk]) {
				rec = nums[i];
				for (j = i - dk; j >= 0 && rec < nums[j]; j -= dk)
					nums[j + dk] = nums[j];
				nums[j + dk] = rec;
			}
		}
	}

	/**
	 * @brief 希尔排序
	 * @param nums 排序的数组
	*/
	void ShellSort(vector<int>& nums)
	{
		for (int i = nums.size(); i >= 1; i /= 2)
			ShellInsert(nums, i);
	}

public:
	std::vector<int> mySort(std::vector<int>& nums)
	{
		// 这里填写你的代码
		ShellSort(nums);
		return nums;
	}
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main()
{
	int n;
	std::cin >> n;
	//存放输入的数用于排序
	std::vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		std::cin >> nums[i];
	}
	Solution s;
	std::vector<int> after_sort(s.mySort(nums));
	std::cout << after_sort[0];
	for (int i = 1; i < n; i++) {
		std::cout << ' ' << after_sort[i];
	}
	std::cout << std::endl;
	return 0;
}
