/**
 * @name    template.cpp
 * @brief   p142模板程序
 * @date    2022-12-02
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
class FreqStack {
private:
    map<int, int> num_freq;           //存放每个数出现频率
    map<int, stack<int>> freq_num;    //存放某频率为下标的所有整数
    int max_freq;                     //当前最大的出现频率
public:
    FreqStack()
    {
        max_freq = 0;
    }

    /**
     * @brief 向最大频率栈插入新元素
     * @param val 元素值
    */
    void push(int val)
    {
        //该数第一次出现
        if (num_freq.count(val))
            num_freq[val]++;
        else
            num_freq[val] = 1;

        max_freq = max(max_freq, num_freq[val]);  //更新最大频率值

        if (freq_num.count(num_freq[val]))
            freq_num[num_freq[val]].push(val);
        else {
            stack<int> newstack;
            freq_num[num_freq[val]] = newstack;
            freq_num[num_freq[val]].push(val);
        }
    }

    /**
     * @brief 最大频数栈弹出元素
     * @return 弹出的元素值
    */
    int pop()
    {
        int ret = freq_num[max_freq].top();
        
        freq_num[max_freq].pop();

        num_freq[ret]--;        //当前数频数减少

        //当前频率全部弹出 不存在该频率了
        if (freq_num[max_freq].empty())
            max_freq--;

        return ret;
    }
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main()
{
    int n;
    std::cin >> n;
    FreqStack fs;
    while (n--) {
        std::string order;
        std::cin >> order;
        if (order == "push") {
            int val;
            std::cin >> val;
            fs.push(val);
        }
        else if (order == "pop") {
            std::cout << fs.pop() << std::endl;
        }
    }
    return 0;
}
