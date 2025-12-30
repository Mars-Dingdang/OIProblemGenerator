#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

// Example: Longest path in DAG (UVa 437 variant)
const int MAXN = 100;
int dp[MAXN]; // dp[i] = longest path ending at node i
vector<pair<int, int>> adj[MAXN]; // adjacency list: (neighbor, weight)

int dfs(int u) {
    if (dp[u] != -1) return dp[u];
    int res = 0;
    for (auto &[v, w] : adj[u]) {
        res = max(res, dfs(v) + w);
    }
    return dp[u] = res;
}

int main() {
    int n, m;
    cin >> n >> m;
    // Build DAG edges (example: u -> v with weight w)
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    memset(dp, -1, sizeof(dp));
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, dfs(i));
    }
    cout << ans << endl;
    return 0;
}