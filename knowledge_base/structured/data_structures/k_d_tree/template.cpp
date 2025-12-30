#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 200000;
const int K = 2; // Dimensions

struct Point {
    long long x[K];
    long long val, sum;
    long long L[K], R[K]; // Bounding box
    int l, r; // Children
} t[MAXN + 5];

int root;

void maintain(int p) {
    t[p].sum = t[p].val + t[t[p].l].sum + t[t[p].r].sum;
    for (int k = 0; k < K; ++k) {
        t[p].L[k] = t[p].R[k] = t[p].x[k];
        if (t[p].l) {
            t[p].L[k] = min(t[p].L[k], t[t[p].l].L[k]);
            t[p].R[k] = max(t[p].R[k], t[t[p].l].R[k]);
        }
        if (t[p].r) {
            t[p].L[k] = min(t[p].L[k], t[t[p].r].L[k]);
            t[p].R[k] = max(t[p].R[k], t[t[p].r].R[k]);
        }
    }
}

int build(vector<int>& idx, int dep = 0) {
    if (idx.empty()) return 0;
    if (idx.size() == 1) {
        maintain(idx[0]);
        return idx[0];
    }
    int d = dep % K;
    auto cmp = [d](int a, int b) { return t[a].x[d] < t[b].x[d]; };
    int mid = idx.size() / 2;
    nth_element(idx.begin(), idx.begin() + mid, idx.end(), cmp);
    int p = idx[mid];
    vector<int> left(idx.begin(), idx.begin() + mid);
    vector<int> right(idx.begin() + mid + 1, idx.end());
    t[p].l = build(left, dep + 1);
    t[p].r = build(right, dep + 1);
    maintain(p);
    return p;
}

long long query(int p, const vector<long long>& low, const vector<long long>& high) {
    if (!p) return 0;
    // Fully outside
    for (int k = 0; k < K; ++k)
        if (t[p].R[k] < low[k] || high[k] < t[p].L[k])
            return 0;
    // Fully inside
    bool full = true;
    for (int k = 0; k < K; ++k)
        if (!(low[k] <= t[p].L[k] && t[p].R[k] <= high[k]))
            full = false;
    if (full) return t[p].sum;
    // Partially inside
    long long res = 0;
    bool inside = true;
    for (int k = 0; k < K; ++k)
        if (!(low[k] <= t[p].x[k] && t[p].x[k] <= high[k]))
            inside = false;
    if (inside) res += t[p].val;
    return res + query(t[p].l, low, high) + query(t[p].r, high, high);
}