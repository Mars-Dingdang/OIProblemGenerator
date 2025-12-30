#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

typedef long long ll;

const int MAXN = 1005;
const ll INF = LLONG_MAX;

struct Edge {
    int v;
    ll cap, flow;
    Edge(int _v, ll _cap) : v(_v), cap(_cap), flow(0) {}
};

vector<Edge> edges;
vector<vector<int>> adj(MAXN);
int level[MAXN], ptr[MAXN];

void add_edge(int u, int v, ll cap) {
    adj[u].push_back(edges.size());
    edges.emplace_back(v, cap);
    adj[v].push_back(edges.size());
    edges.emplace_back(u, 0); // reverse edge
}

bool bfs(int s, int t) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    q.push(s);
    level[s] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int idx : adj[u]) {
            Edge& e = edges[idx];
            if (level[e.v] == -1 && e.flow < e.cap) {
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
    }
    return level[t] != -1;
}

ll dfs(int u, int t, ll f) {
    if (u == t || f == 0) return f;
    for (int& i = ptr[u]; i < adj[u].size(); i++) {
        int idx = adj[u][i];
        Edge& e = edges[idx];
        if (level[e.v] == level[u] + 1) {
            ll pushed = dfs(e.v, t, min(f, e.cap - e.flow));
            if (pushed > 0) {
                e.flow += pushed;
                edges[idx ^ 1].flow -= pushed;
                return pushed;
            }
        }
    }
    return 0;
}

ll max_flow(int s, int t) {
    ll flow = 0;
    while (bfs(s, t)) {
        memset(ptr, 0, sizeof(ptr));
        while (ll pushed = dfs(s, t, INF)) {
            flow += pushed;
        }
    }
    return flow;
}