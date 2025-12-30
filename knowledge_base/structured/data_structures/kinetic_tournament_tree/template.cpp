#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5 + 5;
const int inf = 0x3f3f3f3f;

struct node {
    int l, r;
    int tag;   // lazy propagation: left shift delta
    int k, b;  // linear function f(x) = k*x + b
    int swc;   // switch time: when the certificate fails (intersection with sibling)
};

vector<node> v;
int n, k[MAXN], b[MAXN];

int IntegerPart(double x) {
    if (x >= 0 && x <= inf) return (int)ceil(x);
    return inf;
}

void push_up(int rt) {
    int lc = rt << 1, rc = rt << 1 | 1;
    // Choose child with larger value at x=0
    int mx = (v[lc].b > v[rc].b) ? lc : rc;
    int mi = (mx == lc) ? rc : lc;
    v[rt].k = v[mx].k;
    v[rt].b = v[mx].b;
    // Compute next certificate failure time: intersection of two lines
    if (v[mx].k < v[mi].k) {
        v[rt].swc = IntegerPart(1.0 * (v[mx].b - v[mi].b) / (v[mi].k - v[mx].k));
    } else {
        v[rt].swc = inf;
    }
}

void push_tag(int rt, int val) {
    v[rt].tag += val;
    v[rt].swc -= val;  // shift failure time
    v[rt].b += v[rt].k * val;  // update value at x=0
}

void push_down(int rt) {
    if (v[rt].tag) {
        push_tag(rt << 1, v[rt].tag);
        push_tag(rt << 1 | 1, v[rt].tag);
        v[rt].tag = 0;
    }
}

void checkswitch(int rt) {
    if (v[rt].l == v[rt].r) return;
    push_down(rt);
    if (v[rt].swc <= 0) {
        checkswitch(rt << 1);
        checkswitch(rt << 1 | 1);
    }
    push_up(rt);
}

void build(int rt, int l, int r) {
    v[rt].l = l, v[rt].r = r;
    if (l == r) {
        v[rt].k = k[l];
        v[rt].b = b[l];
        v[rt].swc = inf;
        return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    push_up(rt);
}

void translate_left(int rt, int l, int r, int val) {
    if (l <= v[rt].l && v[rt].r <= r) {
        push_tag(rt, val);
        checkswitch(rt);
        return;
    }
    push_down(rt);
    int mid = v[rt << 1].r;
    if (l <= mid) translate_left(rt << 1, l, r, val);
    if (mid < r) translate_left(rt << 1 | 1, l, r, val);
    push_up(rt);
}

int query_max(int rt, int l, int r) {
    if (l <= v[rt].l && v[rt].r <= r) return v[rt].b;
    push_down(rt);
    int mid = v[rt << 1].r;
    int res = 0;
    if (l <= mid) res = max(res, query_max(rt << 1, l, r));
    if (mid < r) res = max(res, query_max(rt << 1 | 1, l, r));
    return res;
}

// Example usage in main:
// int main() {
//     ios::sync_with_stdio(false), cin.tie(nullptr);
//     cin >> n;
//     for (int i = 1; i <= n; ++i) cin >> k[i] >> b[i];
//     v.resize(4 * n);
//     build(1, 1, n);
//     int m; cin >> m;
//     while (m--) {
//         char op; cin >> op;
//         int l, r; cin >> l >> r;
//         if (op == 'Q') cout << query_max(1, l, r) << '\n';
//         else if (op == 'P') { int d; cin >> d; translate_left(1, l, r, d); }
//     }
//     return 0;
// }