#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int INF = 2e9;

vector<int> g[N];
int sz[N], mx[N], fa[N], dep[N];
bool vis[N];
int rt, sum;

void calcsiz(int u, int f) {
    sz[u] = 1;
    mx[u] = 0;
    for (int v : g[u]) {
        if (v == f || vis[v]) continue;
        calcsiz(v, u);
        sz[u] += sz[v];
        mx[u] = max(mx[u], sz[v]);
    }
    mx[u] = max(mx[u], sum - sz[u]);
    if (mx[u] < mx[rt]) rt = u;
}

void dfs(int u, int f, int d, vector<int>& dist) {
    dist.push_back(d);
    for (int v : g[u]) {
        if (v == f || vis[v]) continue;
        dfs(v, u, d + 1, dist);
    }
}

void build(int u) {
    vis[u] = true;
    for (int v : g[u]) {
        if (vis[v]) continue;
        rt = 0;
        sum = sz[v];
        mx[rt] = INF;
        calcsiz(v, -1);
        calcsiz(rt, -1);
        fa[rt] = u;
        dep[rt] = dep[u] + 1;
        build(rt);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    rt = 0;
    mx[rt] = INF;
    sum = n;
    calcsiz(1, -1);
    calcsiz(rt, -1);
    build(rt);
    return 0;
}