#include <stack>
#include <vector>
using namespace std;

// 构建单调递增栈，返回每个元素对应的左边第一个更小元素的位置
vector<int> buildMonotonicStack(vector<int>& nums) {
    stack<int> sta;
    vector<int> left(nums.size(), -1); // 记录左边第一个小于当前元素的位置

    for (int i = 0; i < nums.size(); ++i) {
        while (!sta.empty() && nums[sta.top()] >= nums[i]) {
            sta.pop();
        }
        if (!sta.empty()) {
            left[i] = sta.top();
        }
        sta.push(i);
    }

    return left;
}