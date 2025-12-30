// 分治法实现 (随机访问 w(j,i))
typedef long long val_t;
const val_t INF = 1e18;
const int N = 100005;
val_t w(int j, int i);  // 成本函数，需满足四边形不等式
val_t f[N];             // 最优值
int opt[N];             // 最小最优决策

void calc(int l, int r, int opt_l, int opt_r) {
    int mid = (l + r) / 2;
    for (int j = opt_l; j <= min(opt_r, mid); ++j) {
        val_t cost = w(j, mid);
        if (cost < f[mid]) {
            f[mid] = cost;
            opt[mid] = j;
        }
    }
    if (l < mid) calc(l, mid - 1, opt_l, opt[mid]);
    if (r > mid) calc(mid + 1, r, opt[mid], opt_r);
}

void solve(int n) {
    fill(f + 1, f + n + 1, INF);
    calc(1, n, 1, n);
}

// 二分队列法实现 (支持动态计算 w(j,i))
#include <deque>
int lt[N], rt[N];
void solve_queue(int n) {
    deque<int> dq;
    for (int j = 1; j <= n; ++j) {
        if (!dq.empty() && rt[dq.front()] < j) dq.pop_front();
        if (!dq.empty()) lt[dq.front()] = j;
        while (!dq.empty() && w(j, lt[dq.back()]) < w(dq.back(), lt[dq.back()]))
            dq.pop_back();
        if (dq.empty()) {
            lt[j] = j; rt[j] = n;
            dq.push_back(j);
        } else if (w(j, rt[dq.back()]) >= w(dq.back(), rt[dq.back()])) {
            if (rt[dq.back()] < n) {
                lt[j] = rt[dq.back()] + 1; rt[j] = n;
                dq.push_back(j);
            }
        } else {
            int ll = lt[dq.back()], rr = rt[dq.back()], i = rr;
            while (ll <= rr) {
                int mm = (ll + rr) / 2;
                if (w(j, mm) < w(dq.back(), mm)) {
                    i = mm;
                    rr = mm - 1;
                } else {
                    ll = mm + 1;
                }
            }
            rt[dq.back()] = i - 1;
            lt[j] = i; rt[j] = n;
            dq.push_back(j);
        }
        f[j] = w(dq.front(), j);
        opt[j] = dq.front();
    }
}