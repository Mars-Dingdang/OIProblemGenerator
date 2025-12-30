#include <bits/stdc++.h>
using namespace std;

const int MAXN = 250005;
int dfn[MAXN], id[MAXN], dep[MAXN], fa[MAXN][20];
vector<pair<int, int>> g[MAXN]; // 原树邻接表
int sta[MAXN], top, k;
vector<int> vt[MAXN]; // 虚树邻接表
bool is_key[MAXN];

// 预处理 DFS 序和深度
typename
void dfs(int u, int f) {
    dfn[u] = ++*id;
    dep[u] = dep[f] + 1;
    fa[u][0] = f;
    for (int i = 1; i < 20; ++i)
        fa[u][i] = fa[fa[u][i-1]][i-1];
    for (auto &e : g[u]) {
        int v = e.first;
        if (v == f) continue;
        dfs(v, u);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 19; i >= 0; --i)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v) return u;
    for (int i = 19; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

bool cmp(int x, int y) { return dfn[x] < dfn[y]; }

void build_virtual_tree(vector<int>& key_nodes) {
    sort(key_nodes.begin(), key_nodes.end(), cmp);
    vector<int> a;
    a.push_back(1);
    for (int x : key_nodes) {
        if (x != 1) a.push_back(x);
    }
    for (int i = 0; i < (int)a.size() - 1; ++i) {
        int lc = lca(a[i], a[i+1]);
        a.push_back(lc);
    }
    sort(a.begin(), a.end(), cmp);
    a.erase(unique(a.begin(), a.end(), [](int x, int y) { return dfn[x] == dfn[y]; }), a.end());

    // 使用单调栈构建虚树
    top = 0;
    sta[++top] = 1;
    vt[1].clear();
    for (int x : key_nodes) {
        if (x == 1) continue;
        int lc = lca(x, sta[top]);
        while (top > 1 && dfn[lc] <= dfn[sta[top-1]]) {
            vt[sta[top-1]].push_back(sta[top]);
            top--;
        }
        if (dfn[lc] > dfn[sta[top-1]]) {
            vt[lc].clear();
            if (dfn[lc] != dfn[sta[top]]) {
                vt[lc].push_back(sta[top]);
                sta[top] = lc;
            } else {
                top--;
            }
        } else {
            vt[lc].push_back(sta[top--]);
        }
        vt[x].clear();
        sta[++top] = x;
    }
    for (int i = 1; i < top; ++i) {
        vt[sta[i]].push_back(sta[i+1]);
    }
}