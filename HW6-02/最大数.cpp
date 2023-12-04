/**
 * @file    template.cpp
 * @name    模板程序
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
using namespace std;

/********************************/
/*     以下是你需要提交的代码     */
/********************************/
class Solution {
private:
    //将每个整数转为string方便比较 存入vector中
    vector<string> numarray;
    
    /**
     * @brief 将数字数组转为string数组
     * @param nums 输入的数组数组
    */
    void convert(vector<int>& nums)
    {
        for (int i = 0; i < nums.size(); i++)
            numarray.push_back(to_string(nums[i]));
    }
    
    /**
     * @brief 定义string比较大小
     * @param a 字符串a
     * @param b 字符串b
    */
    static bool LT(string a, string b)
    {
        return a + b < b + a;
    }
public:
    std::string largestNumber(std::vector<int>& nums)
    {
        string output;
        convert(nums);
        sort(numarray.begin(), numarray.end(), LT);
        for (int i = numarray.size() - 1; i >= 0 ; i--)
            output +=  numarray[i];
        return output;
    }
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }
    Solution s;
    std::cout << s.largestNumber(nums) << std::endl;
    return 0;
}