#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
const int MAXM = 2e5 + 5;

struct Edge {
    int to, nxt;
} e[MAXM];
int head[MAXN], cnt;
int dist[MAXN], pre[MAXN];
bool vis[MAXN];

void addEdge(int u, int v) {
    e[++cnt].to = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}

void bfs(int s) {
    queue<int> q;
    q.push(s);
    vis[s] = true;
    dist[s] = 0;
    pre[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (!vis[v]) {
                vis[v] = true;
                dist[v] = dist[u] + 1;
                pre[v] = u;
                q.push(v);
            }
        }
    }
}

void restorePath(int t) {
    vector<int> path;
    for (int v = t; v != -1; v = pre[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    for (int x : path) cout << x << " ";
    cout << endl;
}

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u); // undirected graph
    }
    bfs(s);
    for (int i = 1; i <= n; ++i) {
        cout << "dist[" << i << "] = " << dist[i] << endl;
    }
    return 0;
}