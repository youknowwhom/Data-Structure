#include <iostream>
#include <algorithm>
#include <queue>
#define MAXN 2010
using namespace std;

/**
 * @brief 读入新的一行new_arr后 维护新的前n小和
 * @param ans 已经读入行的前n小和
 * @param new_arr 新读入的一行
 * @param n 每行元素个数
*/
void maintain_sum(int* ans, int* new_arr, int n)
{
    priority_queue<int> q;

    // O(n^2)的时间复杂度 依次比较原先队列
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            //新的一个sum 后续判断是否要更新
            int sum = ans[i] + new_arr[j];

            //q要先填充满n个的大小
            if (q.size() < n) 
                q.push(sum);
            else if (sum < q.top()){
                q.pop();
                q.push(sum);
            }
            //剪枝 因为两个序列均有序 若当前已经超过，则之后均不符合题意
            else 
                break;
        }
    }

    //q是大根堆 ans数组的排序保持从小到大 因此反过来
    for (int i = n - 1; i >= 0; i--){
        ans[i] = q.top();
        q.pop();
    }

}
int main()
{
    int T, m, n;

    //ans通过不断更新累加保持个数为n个 即输入i行之后，前i行各出一个元素的前n小和数组
    int ans[MAXN];
    //new_arr代表新输入的一行
    int new_arr[MAXN];

    cin >> T;

    while (T--){
        cin >> m >> n;

        for (int i = 0; i < n; i++)
            cin >> ans[i];

        //排序是方便之后的剪枝 快排约O(nlogn)时间复杂度
        sort(ans, ans + n);

        for (int i = 1; i < m; i++){
            for (int j = 0; j < n; j++)
                cin >> new_arr[j];
            sort(new_arr, new_arr + n);
            maintain_sum(ans, new_arr, n);
        }

        for (int i = 0; i < n; ++i)
            cout << ans[i] << " ";

        cout << endl;
    }

    return 0;
}