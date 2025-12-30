#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;

const int MAXN = 1005;
int n, m;
int deg[MAXN]; // 度数（无向图）或 出度-入度（有向图）
bool vis[MAXN][MAXN]; // 用于标记边是否访问过（适用于稠密图）
vector<vector<int>> adj(MAXN);
stack<int> ans;

void hierholzer(int u) {
    for (int &v : adj[u]) { // 使用引用，便于删除已访问的边
        if (!vis[u][v] && !vis[v][u]) {
            vis[u][v] = true; // 标记边 u-v 已访问
            hierholzer(v);
        }
    }
    ans.push(u);
}

int main() {
    cin >> n >> m;
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    // 寻找起点：优先选择奇度点，否则任选非零度点
    int start = 1;
    while (start <= n && deg[start] == 0) start++;
    for (int i = 1; i <= n; ++i) {
        if ((deg[i] & 1) && deg[i] > 0) {
            start = i;
            break;
        }
    }

    hierholzer(start);

    while (!ans.empty()) {
        cout << ans.top() << ' ';
        ans.pop();
    }
    cout << endl;
    return 0;
}