#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct BipartiteGraph {
  int n1, n2;
  std::vector<std::vector<int>> g;
  std::vector<int> ma, mb;
  std::vector<int> dist;

  BipartiteGraph(int n1, int n2) : n1(n1), n2(n2), g(n1), ma(n1, -1), mb(n2, -1) {}

  void add_edge(int u, int v) {
    g[u].emplace_back(v);
  }

  bool bfs() {
    dist.assign(n1, -1);
    std::queue<int> q;
    for (int u = 0; u < n1; ++u) {
      if (ma[u] == -1) {
        dist[u] = 0;
        q.emplace(u);
      }
    }
    bool found = false;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v : g[u]) {
        if (mb[v] == -1) {
          found = true;
        } else if (dist[mb[v]] == -1) {
          dist[mb[v]] = dist[u] + 1;
          q.emplace(mb[v]);
        }
      }
    }
    return found;
  }

  bool dfs(int u) {
    for (int v : g[u]) {
      if (mb[v] == -1 || (dist[mb[v]] == dist[u] + 1 && dfs(mb[v]))) {
        ma[u] = v;
        mb[v] = u;
        return true;
      }
    }
    dist[u] = -1;
    return false;
  }

  std::vector<std::pair<int, int>> maximum_matching() {
    while (bfs()) {
      for (int u = 0; u < n1; ++u) {
        if (ma[u] == -1) {
          dfs(u);
        }
      }
    }
    std::vector<std::pair<int, int>> matches;
    for (int u = 0; u < n1; ++u) {
      if (ma[u] != -1) {
        matches.emplace_back(u, ma[u]);
      }
    }
    return matches;
  }
};