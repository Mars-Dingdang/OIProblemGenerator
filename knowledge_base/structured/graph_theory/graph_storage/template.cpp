#include <iostream>
#include <vector>
using namespace std;

// Adjacency list (most versatile)
int n, m;
vector<vector<int>> adj; // for weighted: vector<vector<pair<int, int>>> adj;
vector<bool> vis;

void add_edge(int u, int v) {
    adj[u].push_back(v);
    // For undirected graph: adj[v].push_back(u);
}

bool find_edge(int u, int v) {
    for (int w : adj[u]) {
        if (w == v) return true;
    }
    return false;
}

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = true;
    for (int v : adj[u]) {
        dfs(v);
    }
}

int main() {
    cin >> n >> m;
    adj.resize(n + 1);
    vis.resize(n + 1, false);
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }
    
    // Example usage
    dfs(1);
    return 0;
}