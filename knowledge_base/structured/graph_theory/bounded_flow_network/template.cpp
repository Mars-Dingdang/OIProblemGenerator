#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205, MAXM = 1e4 + 5;
const long long INF = 1e18;

struct Edge {
    int to, rev;
    long long cap, flow;
    Edge(int t, int r, long long c) : to(t), rev(r), cap(c), flow(0) {}
};

vector<Edge> G[MAXN];
int level[MAXN], iter[MAXN];

void add_edge(int u, int v, long long cap) {
    G[u].emplace_back(v, (int)G[v].size(), cap);
    G[v].emplace_back(u, (int)G[u].size() - 1, 0);
}

void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &e : G[u]) {
            if (e.cap > e.flow && level[e.to] == -1) {
                level[e.to] = level[u] + 1;
                q.push(e.to);
            }
        }
    }
}

long long dfs(int u, int t, long long f) {
    if (u == t) return f;
    for (int &i = iter[u]; i < G[u].size(); ++i) {
        Edge &e = G[u][i];
        if (e.cap > e.flow && level[u] < level[e.to]) {
            long long d = dfs(e.to, t, min(f, e.cap - e.flow));
            if (d > 0) {
                e.flow += d;
                G[e.to][e.rev].flow -= d;
                return d;
            }
        }
    }
    return 0;
}

long long max_flow(int s, int t) {
    long long flow = 0;
    while (true) {
        bfs(s);
        if (level[t] == -1) break;
        memset(iter, 0, sizeof(iter));
        long long f;
        while ((f = dfs(s, t, INF)) > 0) flow += f;
    }
    return flow;
}

// Bounded Flow: 无源汇上下界可行流
// nodes: 0 ~ n-1, with given lower bounds and upper bounds
// returns whether feasible flow exists
bool bounded_flow_feasible(int n, vector<tuple<int, int, long long, long long>>& edges) {
    vector<long long> excess(n, 0);
    int S_prime = n, T_prime = n + 1;
    int N = n + 2;

    // Clear graph
    for (int i = 0; i < N; ++i) G[i].clear();

    for (auto &[u, v, b, c] : edges) { // b: lower, c: upper
        excess[v] += b;
        excess[u] -= b;
        add_edge(u, v, c - b);
    }

    long long total = 0;
    for (int i = 0; i < n; ++i) {
        if (excess[i] > 0) {
            add_edge(S_prime, i, excess[i]);
            total += excess[i];
        } else if (excess[i] < 0) {
            add_edge(i, T_prime, -excess[i]);
        }
    }

    long long flow = max_flow(S_prime, T_prime);
    return flow == total;
}

// 有源汇上下界可行流：S -> T，添加 T -> S 的边 [0, INF]
bool bounded_flow_feasible_with_source_sink(int n, int S, int T, vector<tuple<int, int, long long, long long>>& edges) {
    edges.emplace_back(T, S, 0, INF); // add back edge
    return bounded_flow_feasible(n, edges);
}