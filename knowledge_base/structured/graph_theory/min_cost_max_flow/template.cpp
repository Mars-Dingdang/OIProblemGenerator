#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

const int INF = 0x3f3f3f3f;

struct Edge {
    int v, f, c, next;
};

Edge e[100005];
int head[5005], dis[5005], vis[5005], h[5005];
int p[5005][2]; // parent vertex and edge index
int n, m, s, t, cnt = 1, maxf, minc;

void addedge(int u, int v, int f, int c) {
    e[++cnt].v = v;
    e[cnt].f = f;
    e[cnt].c = c;
    e[cnt].next = head[u];
    head[u] = cnt;
}

bool dijkstra() {
    std::priority_queue<std::pair<int, int>> q;
    for (int i = 1; i <= n; ++i) dis[i] = INF;
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    q.push({0, s});

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].v;
            int nc = e[i].c + h[u] - h[v];
            if (e[i].f && dis[v] > dis[u] + nc) {
                dis[v] = dis[u] + nc;
                p[v][0] = u;
                p[v][1] = i;
                if (!vis[v]) q.push({-dis[v], v});
            }
        }
    }
    return dis[t] != INF;
}

void spfa() {
    std::queue<int> q;
    memset(h, 0x3f, sizeof(h));
    h[s] = 0;
    vis[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = 0;
        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].v;
            if (e[i].f && h[v] > h[u] + e[i].c) {
                h[v] = h[u] + e[i].c;
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= m; ++i) {
        int u, v, f, c;
        scanf("%d%d%d%d", &u, &v, &f, &c);
        addedge(u, v, f, c);
        addedge(v, u, 0, -c);
    }

    spfa();
    while (dijkstra()) {
        for (int i = 1; i <= n; ++i) h[i] += dis[i];
        int minf = INF;
        for (int u = t; u != s; u = p[u][0]) {
            minf = std::min(minf, e[p[u][1]].f);
        }
        for (int u = t; u != s; u = p[u][0]) {
            e[p[u][1]].f -= minf;
            e[p[u][1] ^ 1].f += minf;
        }
        maxf += minf;
        minc += minf * h[t];
    }
    printf("%d %d\n", maxf, minc);
    return 0;
}