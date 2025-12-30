#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

const int MAXN = 1005;
const int INF = 0x3f3f3f3f;

struct Dinic {
    struct Edge {
        int to, rev;
        long long cap;
        Edge(int t, long long c, int r) : to(t), cap(c), rev(r) {}
    };

    std::vector<std::vector<Edge>> graph;
    std::vector<int> level, iter;
    int n;

    Dinic(int nodes) : n(nodes) {
        graph.assign(n, std::vector<Edge>());
        level.resize(n);
        iter.resize(n);
    }

    void add_edge(int u, int v, long long cap) {
        graph[u].emplace_back(v, cap, (int)graph[v].size());
        graph[v].emplace_back(u, 0, (int)graph[u].size() - 1);
    }

    void bfs(int s) {
        level.assign(n, -1);
        std::queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto& e : graph[u]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
    }

    long long dfs(int u, int t, long long f) {
        if (u == t) return f;
        for (int& i = iter[u]; i < (int)graph[u].size(); ++i) {
            Edge& e = graph[u][i];
            if (e.cap > 0 && level[u] < level[e.to]) {
                long long d = dfs(e.to, t, std::min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
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
            iter.assign(n, 0);
            long long f;
            while ((f = dfs(s, t, INF)) > 0) flow += f;
        }
        return flow;
    }
};

// Example usage for edge connectivity
/*
int main() {
    int n, m;
    std::cin >> n >> m;
    Dinic dinic(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u; --v;
        dinic.add_edge(u, v, 1);
        dinic.add_edge(v, u, 1); // for undirected
    }
    long long min_edge_conn = LLONG_MAX;
    for (int s = 0; s < n; ++s) {
        for (int t = s+1; t < n; ++t) {
            min_edge_conn = std::min(min_edge_conn, dinic.max_flow(s, t));
            // Rebuild graph or use copy
        }
    }
    std::cout << min_edge_conn << '\n';
    return 0;
}
*/