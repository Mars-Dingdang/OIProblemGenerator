#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 10005;
const long long INF = 0x3f3f3f3f3f3f3f3f;

struct Edge {
    int v, w;
    Edge(int _v, int _w) : v(_v), w(_w) {}
};

vector<Edge> graph[MAXN];
int dist[MAXN], cnt[MAXN], vis[MAXN];
int n, m;

bool spfa(int start) {
    queue<int> q;
    memset(dist, 0x3f, sizeof(dist));
    dist[start] = 0;
    vis[start] = 1;
    q.push(start);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = 0;
        for (auto &e : graph[u]) {
            int v = e.v, w = e.w;
            if (dist[u] + w > dist[v]) { // 注意这里是 '>': 我们在跑最长路
                dist[v] = dist[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) return false; // 存在正环 -> 无解
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return true;
}

void add_edge(int u, int v, int w) {
    graph[u].push_back(Edge(v, w));
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int op, a, b, c;
        cin >> op;
        if (op == 1) {
            // x_a - x_b >= c  =>  x_b <= x_a - c  =>  x_b - x_a <= -c  => add_edge(a, b, -c)
            cin >> a >> b >> c;
            add_edge(a, b, -c);
        } else if (op == 2) {
            // x_a - x_b <= c  =>  x_a <= x_b + c  => add_edge(b, a, c)
            cin >> a >> b >> c;
            add_edge(b, a, c);
        } else if (op == 3) {
            // x_a == x_b  =>  x_a <= x_b && x_b <= x_a
            cin >> a >> b;
            add_edge(a, b, 0);
            add_edge(b, a, 0);
        }
    }

    // 超级源点 0 连向所有点，边权为 0
    for (int i = 1; i <= n; ++i) {
        add_edge(0, i, 0);
    }

    if (spfa(0)) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}