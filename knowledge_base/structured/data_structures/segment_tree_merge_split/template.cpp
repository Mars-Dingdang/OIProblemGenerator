#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100005;
const int MAXM = 5000005; // 动态开点空间
const int MAXV = 100000;

int n, m, cnt = 0;
int root[MAXN];
int sum[MAXM], ls[MAXM], rs[MAXM], res[MAXM];
vector<int> adj[MAXN];

void pushup(int x) {
    if (sum[ls[x]] >= sum[rs[x]]) {
        sum[x] = sum[ls[x]];
        res[x] = res[ls[x]];
    } else {
        sum[x] = sum[rs[x]];
        res[x] = res[rs[x]];
    }
}

int build() {
    ++cnt;
    sum[cnt] = 0;
    ls[cnt] = rs[cnt] = 0;
    res[cnt] = 0;
    return cnt;
}

int add(int p, int l, int r, int pos, int val) {
    if (!p) p = build();
    if (l == r) {
        sum[p] += val;
        res[p] = (sum[p] > 0 ? l : 0);
        return p;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        ls[p] = add(ls[p], l, mid, pos, val);
    else
        rs[p] = add(rs[p], mid + 1, r, pos, val);
    pushup(p);
    return p;
}

int merge(int a, int b, int l, int r) {
    if (!a || !b) return a | b;
    if (l == r) {
        sum[a] += sum[b];
        return a;
    }
    int mid = (l + r) >> 1;
    ls[a] = merge(ls[a], ls[b], l, mid);
    rs[a] = merge(rs[a], rs[b], mid + 1, r);
    pushup(a);
    return a;
}

void dfs(int u, int parent) {
    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs(v, u);
        root[u] = merge(root[u], root[v], 1, MAXV);
    }
}

// 示例：差分更新路径 u-v 上添加颜色 c
void update_path(int u, int v, int c, int rt[]) {
    rt[u] = add(rt[u], 1, MAXV, c, 1);
    rt[v] = add(rt[v], 1, MAXV, c, 1);
    // 假设已预处理 LCA 和父节点信息
    int w = lca(u, v); // 需要额外实现 LCA
    rt[w] = add(rt[w], 1, MAXV, c, -1);
    rt[parent[w]] = add(rt[parent[w]], 1, MAXV, c, -1);
}