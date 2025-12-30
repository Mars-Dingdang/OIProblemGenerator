#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
const int LOG = 17;

vector<int> e[MAXN], g[MAXN], h[MAXN];
int n, w[MAXN], p[MAXN], d[MAXN], f[MAXN][LOG], siz[MAXN];

void topo() {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (!w[i]) q.push(i);
    }
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        p[++cnt] = u;
        for (int v : e[u]) {
            if (--w[v] == 0) q.push(v);
        }
    }
}

int lca(int x, int y) {
    if (d[x] < d[y]) swap(x, y);
    for (int i = LOG - 1; i >= 0; --i) {
        if (d[f[x][i]] >= d[y]) x = f[x][i];
    }
    if (x == y) return x;
    for (int i = LOG - 1; i >= 0; --i) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

void build() {
    d[0] = 0;
    for (int i = 2; i <= n + 1; ++i) {
        int x = p[i], y = g[x][0];
        for (int j = 1, q = g[x].size(); j < q; ++j) {
            y = lca(y, g[x][j]);
        }
        h[y].push_back(x);
        d[x] = d[y] + 1;
        f[x][0] = y;
        for (int i = 1; i < LOG; ++i) {
            f[x][i] = f[f[x][i - 1]][i - 1];
        }
    }
}

void dfs(int u) {
    siz[u] = 1;
    for (int v : h[u]) {
        dfs(v);
        siz[u] += siz[v];
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x;
        while (cin >> x && x) {
            e[x].push_back(i);
            g[i].push_back(x);
            ++w[i];
        }
    }
    topo();
    build();
    dfs(0);
    for (int i = 1; i <= n; ++i) {
        cout << siz[i] - 1 << '\n';
    }
    return 0;
}