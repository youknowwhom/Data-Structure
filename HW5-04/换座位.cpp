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
using namespace std;

/********************************/
/*     以下是你需要提交的代码     */
/********************************/
class Solution {
private:
    //将二维数组转换为一维进行存储便于排序
    vector<string> old_vec, new_vec;
    /**
     * @brief 把二维数组vector数组转一维
     * @param old_chart 错误座位二维数组
     * @param new_chart 正确座位二维数组
    */
    void changeIntoVector(std::vector<vector<std::string>>& old_chart, std::vector<std::vector<std::string>>& new_chart)
    {
        for (int i = 0; i < old_chart.size(); i++)
            old_vec.insert(old_vec.end(), old_chart[i].begin(), old_chart[i].end());
        for (int i = 0; i < new_chart.size(); i++)
            new_vec.insert(new_vec.end(), new_chart[i].begin(), new_chart[i].end());
    }

public:
    int solve(std::vector<vector<std::string>>& old_chart, std::vector<std::vector<std::string>>& new_chart)
    {
        changeIntoVector(old_chart, new_chart);
        int cnt = 0;
        map<string, int> mp;

        for (int i = 0; i < old_vec.size(); i++)
            mp[old_vec[i]] = i;
        
        for (int i = 0; i < new_vec.size(); i++) {
            while(new_vec[i] != old_vec[i]) {
                swap(new_vec[i], new_vec[mp[new_vec[i]]]);
                cnt++;
            }
        }

        return cnt;
    }
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::string>> old_chart(n, std::vector<std::string>(m));
    std::vector<std::vector<std::string>> new_chart(n, std::vector<std::string>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> old_chart[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> new_chart[i][j];
        }
    }

    Solution s;
    std::cout << s.solve(old_chart, new_chart) << std::endl;
    return true;
}
