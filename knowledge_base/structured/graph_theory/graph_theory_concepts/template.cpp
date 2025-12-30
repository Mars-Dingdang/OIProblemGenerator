#include <bits/stdc++.h>
using namespace std;

// Adjacency list representation (directed/undirected)
vector<vector<int>> adj;

// Add edge for undirected graph
void addEdgeUndirected(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// Add edge for directed graph
void addEdgeDirected(int u, int v) {
    adj[u].push_back(v);
}

// BFS traversal from source s
void bfs(int s, int n) {
    vector<bool> visited(n, false);
    queue<int> q;
    visited[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

// DFS traversal (recursive)
vector<bool> visited;
void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

// Check if graph is connected (undirected)
bool isConnected(int n) {
    visited.assign(n, false);
    dfs(0);
    for (bool v : visited) if (!v) return false;
    return true;
}

int main() {
    int n = 5; // number of vertices
    adj.resize(n);
    // Example usage
    addEdgeUndirected(0, 1);
    addEdgeUndirected(1, 2);
    addEdgeDirected(2, 3);
    bfs(0, n);
    return 0;
}