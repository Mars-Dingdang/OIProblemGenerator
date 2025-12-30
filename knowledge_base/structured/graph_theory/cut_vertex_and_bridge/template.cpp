#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100001;

int n, m;
int dfn[MAXN], low[MAXN], idx;
bool is_cut[MAXN];
int child_cnt;
vector<int> adj[MAXN];

void tarjan_cut(int u, int parent) {
    dfn[u] = low[u] = ++idx;
    child_cnt = 0;
    int children = 0;
    for (int v : adj[u]) {
        if (!dfn[v]) {
            children++;
            tarjan_cut(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u] && u != parent) {
                is_cut[u] = true;
            }
            child_cnt++;
        } else if (v != parent) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (u == parent && children >= 2) {
        is_cut[u] = true;
    }
}

// 桥（适用于无重边）
bool is_bridge[MAXN];
void tarjan_bridge(int u, int parent) {
    dfn[u] = low[u] = ++idx;
    for (int v : adj[u]) {
        if (!dfn[v]) {
            tarjan_bridge(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                is_bridge[v] = true; // 边 (u, v) 是桥
            }
        } else if (v != parent) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

// 桥（适用于有重边）
void tarjan_bridge_multi(int u, int parent) {
    dfn[u] = low[u] = ++idx;
    bool flag = false;
    for (int v : adj[u]) {
        if (!dfn[v]) {
            tarjan_bridge_multi(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                is_bridge[v] = true;
            }
        } else {
            if (v == parent && !flag) {
                flag = true;
                continue;
            }
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            idx = 0;
            tarjan_cut(i, i);
        }
    }

    // 输出割点
    int cut_count = 0;
    for (int i = 1; i <= n; i++) if (is_cut[i]) cut_count++;
    cout << "割点数量: " << cut_count << endl;
    for (int i = 1; i <= n; i++) if (is_cut[i]) cout << i << " ";
    cout << endl;

    // 重置 dfn 和 low 数组求桥
    fill(dfn, dfn + n + 1, 0);
    idx = 0;
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan_bridge(i, -1);
        }
    }

    // 输出桥的数量
    int bridge_count = 0;
    for (int i = 1; i <= n; i++) if (is_bridge[i]) bridge_count++;
    cout << "桥的数量: " << bridge_count << endl;

    return 0;
}