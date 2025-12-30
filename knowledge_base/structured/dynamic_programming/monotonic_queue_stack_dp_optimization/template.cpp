#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

// 通用单调队列优化 DP 模板（以多重背包为例）
int monotonic_queue_knapsack(int n, int W, vector<int>& v, vector<int>& w, vector<int>& k) {
    vector<int> dp(W + 1, 0), prev(W + 1, 0);
    for (int i = 0; i < n; ++i) {
        prev = dp;
        for (int y = 0; y < w[i]; ++y) {
            deque<int> q;
            for (int x = 0; x * w[i] + y <= W; ++x) {
                int idx = x * w[i] + y;
                while (!q.empty() && q.front() < x - k[i]) q.pop_front();
                while (!q.empty() && prev[q.back() * w[i] + y] - q.back() * v[i] <= prev[idx] - x * v[i]) q.pop_back();
                q.push_back(x);
                dp[idx] = prev[q.front() * w[i] + y] - q.front() * v[i] + x * v[i];
            }
        }
    }
    return dp[W];
}

// 单调栈优化模板（以寻找每个元素右侧第一个更大元素为例）
vector<int> monotonic_stack_next_greater(vector<int>& arr) {
    int n = arr.size();
    vector<int> res(n, -1);
    deque<int> stk;
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && arr[stk.back()] < arr[i]) {
            res[stk.back()] = arr[i];
            stk.pop_back();
        }
        stk.push_back(i);
    }
    return res;
}