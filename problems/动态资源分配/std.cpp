#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1e9;          // 足够大的值代替无穷大

struct Edge {
    int to, rev;            // 目标节点，反向边在邻接表中的下标
    ll cap;                 // 剩余容量
};

vector<vector<Edge>> g;     // 残量网络
vector<int> heights, current;
vector<ll> excess;
int V;                      // 总节点数

// 添加一条有向边及其反向边
void add_edge(int u, int v, ll cap) {
    g[u].push_back({v, (int)g[v].size(), cap});
    g[v].push_back({u, (int)g[u].size() - 1, 0});
}

// 重标记节点 u 的高度
void relabel(int u) {
    int min_h = INT_MAX;
    for (auto &e : g[u]) {
        if (e.cap > 0) {
            min_h = min(min_h, heights[e.to]);
        }
    }
    if (min_h < INT_MAX) {
        heights[u] = min_h + 1;
    }
}

// 从节点 u 通过边 e 推送流
void push(Edge &e, int u) {
    ll flow = min(excess[u], e.cap);
    if (flow == 0) return;
    e.cap -= flow;
    g[e.to][e.rev].cap += flow;
    excess[u] -= flow;
    excess[e.to] += flow;
}

// 释放节点 u 的超额流
void discharge(int u) {
    while (excess[u] > 0) {
        if (current[u] == g[u].size()) {
            relabel(u);
            current[u] = 0;
        } else {
            Edge &e = g[u][current[u]];
            if (e.cap > 0 && heights[u] == heights[e.to] + 1) {
                push(e, u);
            } else {
                current[u]++;
            }
        }
    }
}

// 计算从 s 到 t 的最大流（Push-Relabel 算法）
ll max_flow(int s, int t) {
    heights.assign(V, 0);
    excess.assign(V, 0);
    current.assign(V, 0);
    heights[s] = V;                 // 源点高度设为 V
    excess[s] = 0;

    // 初始化：从源点推流到所有相邻节点
    for (auto &e : g[s]) {
        if (e.cap > 0) {
            ll flow = e.cap;
            e.cap -= flow;
            g[e.to][e.rev].cap += flow;
            excess[s] -= flow;
            excess[e.to] += flow;
        }
    }

    queue<int> active;
    for (int i = 0; i < V; ++i) {
        if (excess[i] > 0 && i != s && i != t) {
            active.push(i);
        }
    }

    while (!active.empty()) {
        int u = active.front();
        active.pop();
        discharge(u);
        if (excess[u] > 0 && u != s && u != t) {
            active.push(u);
        }
    }

    return -excess[s];              // 最大流即为源点超额流的相反数
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, q;
    cin >> n >> m >> q;

    vector<ll> C(m);
    for (int j = 0; j < m; ++j) {
        cin >> C[j];
    }

    vector<string> need(n);          // 项目与资源的依赖关系
    for (int i = 0; i < n; ++i) {
        cin >> need[i];
    }

    vector<vector<ll>> D(q, vector<ll>(n));
    for (int t = 0; t < q; ++t) {
        for (int i = 0; i < n; ++i) {
            cin >> D[t][i];
        }
    }

    // 节点编号
    const int S = 0;
    const int R_start = 1;               // 资源节点起始：1 .. m
    const int P_start = R_start + m;     // 项目节点起始：R_start+m .. R_start+m+n-1
    const int T = P_start + n;           // 汇点
    V = T + 1;

    // 对每个时刻独立计算
    for (int t = 0; t < q; ++t) {
        g.clear();
        g.resize(V);

        // 源点 -> 资源节点
        for (int j = 0; j < m; ++j) {
            add_edge(S, R_start + j, C[j]);
        }

        // 资源节点 -> 项目节点（如果需要）
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (need[i][j] == '1') {
                    add_edge(R_start + j, P_start + i, INF);
                }
            }
        }

        // 项目节点 -> 汇点，容量为当前时刻的需求量
        ll total_demand = 0;
        for (int i = 0; i < n; ++i) {
            add_edge(P_start + i, T, D[t][i]);
            total_demand += D[t][i];
        }

        ll flow = max_flow(S, T);
        cout << (flow == total_demand ? "Yes" : "No") << '\n';
    }

    return 0;
}