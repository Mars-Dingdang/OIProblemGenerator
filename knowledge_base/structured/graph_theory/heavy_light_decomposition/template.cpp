#include <iostream>
#include <vector>
#include <algorithm>

const int MAXN = 100010;

int n, m, root = 1;
std::vector<int> G[MAXN];
int fa[MAXN], dep[MAXN], siz[MAXN], son[MAXN], top[MAXN], dfn[MAXN], rnk[MAXN];
int idx;

void dfs1(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    son[u] = 0;
    for (int v : G[u]) {
        if (v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]])
            son[u] = v;
    }
}

void dfs2(int u, int tp) {
    top[u] = tp;
    dfn[u] = ++idx;
    rnk[idx] = u;
    if (son[u])
        dfs2(son[u], tp);
    for (int v : G[u]) {
        if (v != fa[u] && v != son[u])
            dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            std::swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

// Example: Path sum using segment tree (simplified)
// Segment tree would support range add/query on dfn[] order

void modify_path(int u, int v, int w, void (*seg_update)(int, int, int)) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            std::swap(u, v);
        seg_update(dfn[top[u]], dfn[u], w);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) std::swap(u, v);
    seg_update(dfn[u], dfn[v], w);
}

void modify_subtree(int u, int w, void (*seg_update)(int, int, int)) {
    seg_update(dfn[u], dfn[u] + siz[u] - 1, w);
}