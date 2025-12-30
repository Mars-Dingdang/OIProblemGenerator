#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using ll = long long;

constexpr int MAXN = 100010;

ll dis[MAXN];
bool vis[MAXN];
std::vector<std::pair<int, int>> adj[MAXN]; // to, weight

void add_edge(int u, int v, int w) {
    adj[u].emplace_back(v, w);
}

void spfa(int start, int mod) {
    std::fill(dis, dis + mod, LLONG_MAX);
    std::queue<int> q;
    dis[start] = 0;
    vis[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = false;
        for (auto &[v, w] : adj[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
}

// Example usage in main:
// int M = a[0];
// for (int i = 0; i < M; ++i) {
//     add_edge(i, (i + a[1]) % M, a[1]);
//     add_edge(i, (i + a[2]) % M, a[2]);
// }
// spfa(0, M);