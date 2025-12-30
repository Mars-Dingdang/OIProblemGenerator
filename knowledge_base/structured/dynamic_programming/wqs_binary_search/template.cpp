// WQS 二分模板（一维，最小化问题）
// 假设 solve(penalty) 返回带惩罚的最优值以及对应的限制数量 cnt
// 目标：找到恰好选取 m 个物品时的最优值
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<ll, int>; // 值, 数量

// 示例：种树问题（最大收益，凹函数）
// 这里以最小化负收益为例，转化为凸函数最小化
pii solve(ll penalty, const vector<int>& a) {
    int n = a.size();
    // dp[i][0/1]: 前 i 个坑，最后一个是否种树
    vector<ll> dp0(n+1, 0), dp1(n+1, -1e18);
    vector<int> cnt0(n+1, 0), cnt1(n+1, 0);
    dp1[0] = -1e18; // 不可能状态
    for (int i = 1; i <= n; ++i) {
        // 不种树
        dp0[i] = dp0[i-1];
        cnt0[i] = cnt0[i-1];
        if (dp1[i-1] > dp0[i] || (dp1[i-1] == dp0[i] && cnt1[i-1] > cnt0[i])) {
            dp0[i] = dp1[i-1];
            cnt0[i] = cnt1[i-1];
        }
        // 种树（收益 a[i-1]，惩罚 penalty）
        dp1[i] = dp0[i-1] + a[i-1] - penalty;
        cnt1[i] = cnt0[i-1] + 1;
        if (i >= 2) {
            ll val = dp1[i-2] + a[i-1] - penalty;
            int c = cnt1[i-2] + 1;
            if (val > dp1[i] || (val == dp1[i] && c > cnt1[i])) {
                dp1[i] = val;
                cnt1[i] = c;
            }
        }
    }
    // 返回最优值及数量（注意处理共线：优先数量大）
    ll best = dp0[n];
    int cnt = cnt0[n];
    if (dp1[n] > best || (dp1[n] == best && cnt1[n] > cnt)) {
        best = dp1[n];
        cnt = cnt1[n];
    }
    return {best, cnt};
}

ll wqs_binary_search(int m, const vector<int>& a) {
    ll lo = -1e12, hi = 1e12; // 惩罚值范围
    ll ans = 0;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        auto [val, cnt] = solve(mid, a);
        if (cnt >= m) { // 注意共线处理：优先数量大，所以用 >=
            ans = val + mid * m; // 原问题值 = 带惩罚值 + penalty * m
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}

int main() {
    // 示例用法
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    // 种树问题是最大化收益，这里取负转化为最小化
    // 实际应用时需调整符号
    cout << wqs_binary_search(m, a) << endl;
    return 0;
}