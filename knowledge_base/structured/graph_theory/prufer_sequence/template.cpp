#include <vector>
#include <set>
using namespace std;

// Linear-time Prüfer code construction from tree (0-indexed)
vector<int> prufer_code(const vector<vector<int>>& adj) {
    int n = adj.size();
    if (n == 1) return {};
    vector<int> parent(n, -1);
    
    // DFS to set up parent pointers (rooted at last node)
    vector<bool> visited(n, false);
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                parent[v] = u;
                dfs(v);
            }
        }
    };
    dfs(n - 1);
    
    int ptr = -1;
    vector<int> degree(n);
    for (int i = 0; i < n; ++i) {
        degree[i] = adj[i].size();
        if (degree[i] == 1 && ptr == -1) ptr = i;
    }
    
    vector<int> code(n - 2);
    int leaf = ptr;
    for (int i = 0; i < n - 2; ++i) {
        int next = parent[leaf];
        code[i] = next;
        if (--degree[next] == 1 && next < ptr) {
            leaf = next;
        } else {
            ++ptr;
            while (ptr < n && degree[ptr] != 1) ++ptr;
            leaf = ptr;
        }
    }
    return code;
}

// Reconstruct tree from Prüfer code (returns list of edges, 0-indexed)
vector<pair<int, int>> prufer_decode(const vector<int>& code) {
    int n = code.size() + 2;
    vector<int> degree(n, 1);
    for (int u : code) degree[u]++;
    
    int ptr = 0;
    while (degree[ptr] != 1) ++ptr;
    int leaf = ptr;
    
    vector<pair<int, int>> edges;
    for (int u : code) {
        edges.emplace_back(leaf, u);
        if (--degree[u] == 1 && u < ptr) {
            leaf = u;
        } else {
            ++ptr;
            while (ptr < n && degree[ptr] != 1) ++ptr;
            leaf = ptr;
        }
    }
    edges.emplace_back(leaf, n - 1);
    return edges;
}