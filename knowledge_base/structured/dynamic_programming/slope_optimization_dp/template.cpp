#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 例题: "玩具装箱" (HNOI2008)
// 状态转移: f[i] = min_{j<i} f[j] + (pre[i] - pre[j] + i - j - 1 - L)^2
// 令 s[i] = pre[i] + i, Lp = L + 1
// 则 f[i] = min_{j<i} f[j] + (s[i] - s[j] - Lp)^2
// 转化为直线截距最小化: b[i] = min_{j<i} (y[j] - k[i] * x[j])
// 其中 x[j] = s[j], y[j] = f[j] + s[j]^2, k[i] = -2*(Lp - s[i]), b[i] = f[i] - (s[i] - Lp)^2

struct SlopeDP {
    int n;
    ll L;
    vector<ll> c, pre, s, f;
    
    // 计算斜率 (注意用 double 或乘法避免除法)
    inline double slope(int j1, int j2) {
        ll x1 = s[j1], y1 = f[j1] + s[j1]*s[j1];
        ll x2 = s[j2], y2 = f[j2] + s[j2]*s[j2];
        return (double)(y2 - y1) / (x2 - x1);
    }
    
    // 单调队列版本 (要求 k[i] 单调递增, x[j] 单调递增)
    ll solve_monotone() {
        deque<int> dq;
        dq.push_back(0);
        f[0] = 0;
        
        for (int i = 1; i <= n; ++i) {
            ll k = -2 * (L - s[i]); // 注意: 此处 L 实际为 Lp = L+1 (已预处理)
            // 队首剔除劣决策 (斜率单调递增时)
            while (dq.size() >= 2 && slope(dq[0], dq[1]) <= k) {
                dq.pop_front();
            }
            int j = dq.front();
            f[i] = f[j] + (s[i] - s[j] - L) * (s[i] - s[j] - L);
            
            // 队尾维护下凸壳
            while (dq.size() >= 2) {
                int l = dq[dq.size()-2], r = dq.back();
                if (slope(l, r) >= slope(r, i)) {
                    dq.pop_back();
                } else {
                    break;
                }
            }
            dq.push_back(i);
        }
        return f[n];
    }
    
    // CDQ分治版本 (通用, 不要求单调性)
    void cdq(int l, int r) {
        if (l == r) return;
        int mid = (l + r) / 2;
        cdq(l, mid);
        
        // 构建左区间凸包
        vector<int> hull;
        for (int i = l; i <= mid; ++i) {
            while (hull.size() >= 2) {
                int a = hull[hull.size()-2], b = hull.back();
                if (slope(a, b) >= slope(b, i)) hull.pop_back();
                else break;
            }
            hull.push_back(i);
        }
        
        // 更新右区间 (假设已按 k 排序)
        int ptr = 0;
        for (int i = mid+1; i <= r; ++i) {
            ll k = -2 * (L - s[i]);
            while (ptr+1 < hull.size() && slope(hull[ptr], hull[ptr+1]) <= k) {
                ptr++;
            }
            int j = hull[ptr];
            f[i] = min(f[i], f[j] + (s[i] - s[j] - L) * (s[i] - s[j] - L));
        }
        
        cdq(mid+1, r);
        // 通常还需要按 x 归并排序以便外层使用
    }
};

int main() {
    // 使用示例
    int n;
    ll L;
    cin >> n >> L;
    L++; // Lp = L + 1
    
    SlopeDP solver;
    solver.n = n;
    solver.L = L;
    solver.c.resize(n+1);
    solver.pre.resize(n+1);
    solver.s.resize(n+1);
    solver.f.assign(n+1, 1e18);
    
    for (int i = 1; i <= n; ++i) {
        cin >> solver.c[i];
        solver.pre[i] = solver.pre[i-1] + solver.c[i];
        solver.s[i] = solver.pre[i] + i;
    }
    
    // 根据单调性选择版本
    // ll ans = solver.solve_monotone();
    // 或使用 CDQ
    solver.cdq(0, n);
    ll ans = solver.f[n];
    
    cout << ans << endl;
    return 0;
}