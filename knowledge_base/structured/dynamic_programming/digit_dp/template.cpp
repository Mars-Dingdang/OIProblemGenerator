#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 典型记忆化搜索模板
// 状态定义: pos - 当前处理位(从高位到低位), state - 额外状态(如前一位数字, 数字和等), tight - 是否紧贴上界, lead - 是否有前导零
// 返回值: 满足条件的数字个数
ll dp[20][200][2][2]; // 根据具体问题调整维度
vector<int> digits;

ll dfs(int pos, int state, bool tight, bool lead) {
    if (pos == (int)digits.size()) {
        // 到达终点，根据state判断是否合法
        return 1; // 或 state == target_state
    }
    if (!tight && !lead && dp[pos][state][tight][lead] != -1) {
        return dp[pos][state][tight][lead];
    }
    int limit = tight ? digits[pos] : 9;
    ll res = 0;
    for (int d = 0; d <= limit; ++d) {
        // 根据题目条件过滤非法数字
        // if (d == 4) continue; // 例: 不要4
        // if (lead && d == 0) { // 处理前导零
        //     res += dfs(pos + 1, state, tight && (d == limit), true);
        // } else {
        //     int new_state = ...; // 更新状态
        //     res += dfs(pos + 1, new_state, tight && (d == limit), false);
        // }
    }
    if (!tight && !lead) {
        dp[pos][state][tight][lead] = res;
    }
    return res;
}

ll solve(ll x) {
    digits.clear();
    while (x) {
        digits.push_back(x % 10);
        x /= 10;
    }
    reverse(digits.begin(), digits.end());
    memset(dp, -1, sizeof(dp));
    return dfs(0, 0, true, true);
}

int main() {
    ll l, r;
    cin >> l >> r;
    // 常用技巧: ans[l, r] = solve(r) - solve(l - 1)
    cout << solve(r) - solve(l - 1) << endl;
    return 0;
}