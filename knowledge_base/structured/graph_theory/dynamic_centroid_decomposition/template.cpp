#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;

int n, m;
vector<int> g[MAXN];
bool vis[MAXN];
int sz[MAXN], maxx[MAXN], totsz, rt;
int fa[MAXN], dep[MAXN];

void get_rt(int u, int f) {
    sz[u] = 1; maxx[u] = 0;
    for (int v : g[u]) {
        if (v == f || vis[v]) continue;
        get_rt(v, u);
        sz[u] += sz[v];
        maxx[u] = max(maxx[u], sz[v]);
    }
    maxx[u] = max(maxx[u], totsz - sz[u]);
    if (maxx[u] < maxx[rt]) rt = u;
}

void build(int u) {
    vis[u] = true;
    for (int v : g[u]) {
        if (vis[v]) continue;
        rt = 0; totsz = sz[v];
        get_rt(v, 0);
        get_rt(rt, 0);
        fa[rt] = u;
        dep[rt] = dep[u] + 1;
        build(rt);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    rt = 0; totsz = n; maxx[0] = INF;
    get_rt(1, 0); get_rt(rt, 0);
    dep[rt] = 1;
    build(rt);
    // Further implementation depends on specific problem
    return 0;
}