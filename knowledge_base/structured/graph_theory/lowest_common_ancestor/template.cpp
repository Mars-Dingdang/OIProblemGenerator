#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 5e5 + 5;
const int LOG = 20;

vector<int> adj[MAXN];
int depth[MAXN];
int parent[MAXN][LOG];
bool visited[MAXN];

void dfs(int u, int p) {
    visited[u] = true;
    parent[u][0] = p;
    for (int i = 1; i < LOG; ++i) {
        if (parent[u][i-1] != -1) {
            parent[u][i] = parent[parent[u][i-1]][i-1];
        } else {
            parent[u][i] = -1;
        }
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    
    // Lift u up to the same depth as v
    int diff = depth[u] - depth[v];
    for (int i = 0; i < LOG; ++i) {
        if (diff & (1 << i)) {
            u = parent[u][i];
        }
    }
    
    if (u == v) return u;
    
    // Move both up until their parents meet
    for (int i = LOG - 1; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, m, root;
    cin >> n >> m >> root;
    
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    memset(parent, -1, sizeof(parent));
    depth[root] = 0;
    dfs(root, -1);
    
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
    
    return 0;
}