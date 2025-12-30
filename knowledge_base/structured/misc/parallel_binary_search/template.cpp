#include <bits/stdc++.h>
using namespace std;
const int N = 200010;

struct Query {
    int l, r, k, id, type; // type: 1 for query, 0 for update
} q[N * 2], q1[N * 2], q2[N * 2];

int n, m, tot;
int ans[N], bit[N];

void add(int p, int x) {
    for (; p <= n; p += p & -p) bit[p] += x;
}

int sum(int p) {
    int res = 0;
    for (; p; p -= p & -p) res += bit[p];
    return res;
}

void solve(int l, int r, int ql, int qr) {
    if (ql > qr) return;
    if (l == r) {
        for (int i = ql; i <= qr; ++i)
            if (q[i].type == 1) ans[q[i].id] = l;
        return;
    }
    int mid = (l + r) >> 1, cnt1 = 0, cnt2 = 0;
    for (int i = ql; i <= qr; ++i) {
        if (q[i].type == 0) { // update
            if (q[i].k <= mid) {
                add(q[i].l, q[i].r); // q[i].r is +1/-1 for insertion/deletion
                q1[++cnt1] = q[i];
            } else {
                q2[++cnt2] = q[i];
            }
        } else { // query
            int t = sum(q[i].r) - sum(q[i].l - 1);
            if (q[i].k <= t) {
                q1[++cnt1] = q[i];
            } else {
                q[i].k -= t;
                q2[++cnt2] = q[i];
            }
        }
    }
    // rollback BIT changes
    for (int i = 1; i <= cnt1; ++i)
        if (q1[i].type == 0) add(q1[i].l, -q1[i].r);
    // merge back
    for (int i = 1; i <= cnt1; ++i) q[ql + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; ++i) q[ql + cnt1 + i - 1] = q2[i];
    solve(l, mid, ql, ql + cnt1 - 1);
    solve(mid + 1, r, ql + cnt1, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // read input, discretize if needed, build initial q array
    // call solve(value_min, value_max, 1, tot);
    // output ans[]
    return 0;
}