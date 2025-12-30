#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const long long INF = 0x3f3f3f3f3f3f3f3fll;

int n, q, num;
int st[505], ed[505], belong[MAXN], size_[505];
double a[MAXN], t[MAXN]; // original and sorted block arrays
double delta[505];         // lazy delta for range add / assign

void build() {
    num = sqrt(n);
    for (int i = 1; i <= num; i++) {
        st[i] = (i - 1) * (n / num) + 1;
        ed[i] = i * (n / num);
    }
    ed[num] = n;
    for (int i = 1; i <= num; i++) {
        for (int j = st[i]; j <= ed[i]; j++) {
            belong[j] = i;
        }
        size_[i] = ed[i] - st[i] + 1;
    }
}

void sort_block(int k) {
    for (int i = st[k]; i <= ed[k]; i++) {
        t[i] = a[i];
    }
    sort(t + st[k], t + ed[k] + 1);
}

void pushdown(int k) {
    if (delta[k] != INF) {
        for (int i = st[k]; i <= ed[k]; i++) {
            a[i] = t[i] = delta[k];
        }
        delta[k] = INF;
    }
}

void modify_add(int l, int r, double c) {
    int x = belong[l], y = belong[r];
    if (x == y) {
        for (int i = l; i <= r; i++) a[i] += c;
        sort_block(x);
        return;
    }
    for (int i = l; i <= ed[x]; i++) a[i] += c;
    for (int i = st[y]; i <= r; i++) a[i] += c;
    for (int i = x + 1; i < y; i++) delta[i] += c;
    sort_block(x);
    sort_block(y);
}

void modify_assign(int l, int r, double c) {
    int x = belong[l], y = belong[r];
    pushdown(x);
    if (x == y) {
        for (int i = l; i <= r; i++) a[i] = c;
        sort_block(x);
        return;
    }
    pushdown(y);
    for (int i = l; i <= ed[x]; i++) a[i] = c;
    for (int i = st[y]; i <= r; i++) a[i] = c;
    sort_block(x);
    sort_block(y);
    for (int i = x + 1; i < y; i++) delta[i] = c;
}

int query_ge(int l, int r, double c) {
    int x = belong[l], y = belong[r];
    int ans = 0;
    if (x == y) {
        for (int i = l; i <= r; i++)
            if (a[i] + (delta[x] == INF ? 0 : delta[x]) >= c) ans++;
        return ans;
    }
    for (int i = l; i <= ed[x]; i++)
        if (a[i] + (delta[x] == INF ? 0 : delta[x]) >= c) ans++;
    for (int i = st[y]; i <= r; i++)
        if (a[i] + (delta[y] == INF ? 0 : delta[y]) >= c) ans++;
    for (int i = x + 1; i < y; i++) {
        double target = c - (delta[i] == INF ? 0 : delta[i]);
        ans += ed[i] - (lower_bound(t + st[i], t + ed[i] + 1, target) - t) + 1;
    }
    return ans;
}

int query_le(int l, int r, double c) {
    int x = belong[l], y = belong[r];
    int ans = 0;
    pushdown(x);
    if (x == y) {
        for (int i = l; i <= r; i++)
            if (a[i] <= c) ans++;
        return ans;
    }
    pushdown(y);
    for (int i = l; i <= ed[x]; i++)
        if (a[i] <= c) ans++;
    for (int i = st[y]; i <= r; i++)
        if (a[i] <= c) ans++;
    for (int i = x + 1; i < y; i++) {
        ans += upper_bound(t + st[i], t + ed[i] + 1, c) - (t + st[i]);
    }
    return ans;
}