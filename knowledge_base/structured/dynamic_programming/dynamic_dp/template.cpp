#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int INF = 0x3f3f3f3f;

struct Matrix {
    int g[2][2];
    Matrix() { memset(g, 0, sizeof(g)); }
    Matrix operator*(const Matrix& b) const {
        Matrix c;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k)
                    c.g[i][j] = max(c.g[i][j], g[i][k] + b.g[k][j]);
        return c;
    }
};

class DynamicDP {
    int n;
    vector<int> a;
    vector<vector<int>> adj;
    vector<int> fa, dep, sz, son, top, id, End;
    vector<Matrix> g, tree;
    vector<int> f0, f1;
    int dfs1(int u, int p) {
        fa[u] = p; dep[u] = dep[p] + 1; sz[u] = 1;
        f1[u] = a[u];
        for (int v : adj[u]) if (v != p) {
            sz[u] += dfs1(v, u);
            if (sz[v] > sz[son[u]]) son[u] = v;
            f1[u] += f0[v];
            f0[u] += max(f0[v], f1[v]);
        }
        return sz[u];
    }
    void dfs2(int u, int t) {
        top[u] = t; id[u] = ++id[0]; End[t] = id[u];
        g[u].g[1][0] = a[u]; g[u].g[1][1] = -INF;
        if (son[u]) {
            dfs2(son[u], t);
            g[u].g[0][0] += max(f0[son[u]], f1[son[u]]);
            g[u].g[1][0] += f0[son[u]];
        }
        for (int v : adj[u]) if (v != fa[u] && v != son[u]) {
            dfs2(v, v);
            g[u].g[0][0] += max(f0[v], f1[v]);
            g[u].g[1][0] += f0[v];
        }
        g[u].g[0][1] = g[u].g[0][0];
    }
    void build(int rt, int l, int r) {
        if (l == r) { tree[rt] = g[l]; return; }
        int mid = (l + r) >> 1;
        build(rt<<1, l, mid); build(rt<<1|1, mid+1, r);
        tree[rt] = tree[rt<<1] * tree[rt<<1|1];
    }
    void modify(int rt, int l, int r, int pos) {
        if (l == r) { tree[rt] = g[l]; return; }
        int mid = (l + r) >> 1;
        if (pos <= mid) modify(rt<<1, l, mid, pos);
        else modify(rt<<1|1, mid+1, r, pos);
        tree[rt] = tree[rt<<1] * tree[rt<<1|1];
    }
    Matrix query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return tree[rt];
        int mid = (l + r) >> 1;
        if (R <= mid) return query(rt<<1, l, mid, L, R);
        if (L > mid) return query(rt<<1|1, mid+1, r, L, R);
        return query(rt<<1, l, mid, L, R) * query(rt<<1|1, mid+1, r, L, R);
    }
public:
    DynamicDP(int _n, vector<int>& _a, vector<pair<int,int>>& edges) : n(_n), a(_a) {
        adj.resize(n+1); fa.resize(n+1); dep.resize(n+1); sz.resize(n+1);
        son.resize(n+1); top.resize(n+1); id.resize(n+1); End.resize(n+1);
        g.resize(n+1); tree.resize(4*(n+1)); f0.resize(n+1); f1.resize(n+1);
        for (auto& e : edges) {
            adj[e.first].push_back(e.second);
            adj[e.second].push_back(e.first);
        }
        dfs1(1, 0); dfs2(1, 1); build(1, 1, n);
    }
    void update(int x, int val) {
        g[x].g[1][0] += val - a[x]; a[x] = val;
        while (x) {
            Matrix last = query(1, 1, n, id[top[x]], End[top[x]]);
            modify(1, 1, n, id[x]);
            Matrix now = query(1, 1, n, id[top[x]], End[top[x]]);
            x = fa[top[x]];
            g[x].g[0][0] += max(now.g[0][0], now.g[1][0]) - max(last.g[0][0], last.g[1][0]);
            g[x].g[0][1] = g[x].g[0][0];
            g[x].g[1][0] += now.g[0][0] - last.g[0][0];
        }
    }
    int query() {
        Matrix res = query(1, 1, n, id[1], End[1]);
        return max(res.g[0][0], res.g[1][0]);
    }
};