#include <algorithm>
#include <iostream>
using namespace std;

constexpr int N = 5e5 + 5, INF = 0x7fffffff;
int n, m, a[N];

struct Node {
    long long sum;
    int mx, mn, mx2, mn2, cmx, cmn;
    int tag_add, tag_mx, tag_mn;
};

Node t[N << 2];

void pushup(int u) {
    const int l = u << 1, r = u << 1 | 1;
    t[u].sum = t[l].sum + t[r].sum;

    // Merge max and second max
    if (t[l].mx == t[r].mx) {
        t[u].mx = t[l].mx;
        t[u].cmx = t[l].cmx + t[r].cmx;
        t[u].mx2 = max(t[l].mx2, t[r].mx2);
    } else if (t[l].mx > t[r].mx) {
        t[u].mx = t[l].mx;
        t[u].cmx = t[l].cmx;
        t[u].mx2 = max(t[l].mx2, t[r].mx);
    } else {
        t[u].mx = t[r].mx;
        t[u].cmx = t[r].cmx;
        t[u].mx2 = max(t[l].mx, t[r].mx2);
    }

    // Merge min and second min
    if (t[l].mn == t[r].mn) {
        t[u].mn = t[l].mn;
        t[u].cmn = t[l].cmn + t[r].cmn;
        t[u].mn2 = min(t[l].mn2, t[r].mn2);
    } else if (t[l].mn < t[r].mn) {
        t[u].mn = t[l].mn;
        t[u].cmn = t[l].cmn;
        t[u].mn2 = min(t[l].mn2, t[r].mn);
    } else {
        t[u].mn = t[r].mn;
        t[u].cmn = t[r].cmn;
        t[u].mn2 = min(t[l].mn, t[r].mn2);
    }
}

void push_add(int u, int len, int v) {
    t[u].sum += 1LL * len * v;
    t[u].mx += v; t[u].mn += v;
    if (t[u].mx2 != -INF) t[u].mx2 += v;
    if (t[u].mn2 != INF) t[u].mn2 += v;
    if (t[u].tag_mx != -INF) t[u].tag_mx += v;
    if (t[u].tag_mn != INF) t[u].tag_mn += v;
    t[u].tag_add += v;
}

void push_min(int u, int v) {
    if (t[u].mx <= v) return;
    t[u].sum += 1LL * (v - t[u].mx) * t[u].cmx;
    if (t[u].mn2 == t[u].mx) t[u].mn2 = v;
    if (t[u].mn == t[u].mx) t[u].mn = v;
    if (t[u].tag_mx > v) t[u].tag_mx = v;
    t[u].mx = t[u].tag_mn = v;
}

void push_max(int u, int v) {
    if (t[u].mn >= v) return;
    t[u].sum += 1LL * (v - t[u].mn) * t[u].cmn;
    if (t[u].mx2 == t[u].mn) t[u].mx2 = v;
    if (t[u].mx == t[u].mn) t[u].mx = v;
    if (t[u].tag_mn < v) t[u].tag_mn = v;
    t[u].mn = t[u].tag_mx = v;
}

void pushdown(int u, int l, int r) {
    int mid = (l + r) >> 1, len1 = mid - l + 1, len2 = r - mid;
    int lu = u << 1, ru = u << 1 | 1;

    if (t[u].tag_add) {
        push_add(lu, len1, t[u].tag_add);
        push_add(ru, len2, t[u].tag_add);
        t[u].tag_add = 0;
    }

    if (t[u].tag_mx != -INF) {
        push_max(lu, t[u].tag_mx);
        push_max(ru, t[u].tag_mx);
        t[u].tag_mx = -INF;
    }

    if (t[u].tag_mn != INF) {
        push_min(lu, t[u].tag_mn);
        push_min(ru, t[u].tag_mn);
        t[u].tag_mn = INF;
    }
}

void build(int u = 1, int l = 1, int r = n) {
    t[u].tag_mx = -INF; t[u].tag_mn = INF;
    if (l == r) {
        t[u].sum = t[u].mx = t[u].mn = a[l];
        t[u].mx2 = -INF; t[u].mn2 = INF;
        t[u].cmx = t[u].cmn = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void add(int L, int R, int v, int u = 1, int l = 1, int r = n) {
    if (R < l || r < L) return;
    if (L <= l && r <= R) { push_add(u, r - l + 1, v); return; }
    pushdown(u, l, r);
    int mid = (l + r) >> 1;
    add(L, R, v, u << 1, l, mid);
    add(L, R, v, u << 1 | 1, mid + 1, r);
    pushup(u);
}

void tomin(int L, int R, int v, int u = 1, int l = 1, int r = n) {
    if (R < l || r < L || t[u].mx <= v) return;
    if (L <= l && r <= R && t[u].mx2 < v) { push_min(u, v); return; }
    pushdown(u, l, r);
    int mid = (l + r) >> 1;
    tomin(L, R, v, u << 1, l, mid);
    tomin(L, R, v, u << 1 | 1, mid + 1, r);
    pushup(u);
}

void tomax(int L, int R, int v, int u = 1, int l = 1, int r = n) {
    if (R < l || r < L || t[u].mn >= v) return;
    if (L <= l && r <= R && t[u].mn2 > v) { push_max(u, v); return; }
    pushdown(u, l, r);
    int mid = (l + r) >> 1;
    tomax(L, R, v, u << 1, l, mid);
    tomax(L, R, v, u << 1 | 1, mid + 1, r);
    pushup(u);
}

long long query_sum(int L, int R, int u = 1, int l = 1, int r = n) {
    if (R < l || r < L) return 0;
    if (L <= l && r <= R) return t[u].sum;
    pushdown(u, l, r);
    int mid = (l + r) >> 1;
    return query_sum(L, R, u << 1, l, mid) + query_sum(L, R, u << 1 | 1, mid + 1, r);
}

int query_max(int L, int R, int u = 1, int l = 1, int r = n) {
    if (R < l || r < L) return -INF;
    if (L <= l && r <= R) return t[u].mx;
    pushdown(u, l, r);
    int mid = (l + r) >> 1;
    return max(query_max(L, R, u << 1, l, mid), query_max(L, R, u << 1 | 1, mid + 1, r));
}

int query_min(int L, int R, int u = 1, int l = 1, int r = n) {
    if (R < l || r < L) return INF;
    if (L <= l && r <= R) return t[u].mn;
    pushdown(u, l, r);
    int mid = (l + r) >> 1;
    return min(query_min(L, R, u << 1, l, mid), query_min(L, R, u << 1 | 1, mid + 1, r));
}