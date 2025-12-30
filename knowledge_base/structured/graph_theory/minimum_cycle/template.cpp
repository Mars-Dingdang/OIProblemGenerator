#include <bits/stdc++.h>
using lint = long long;
const int MAXN = 110;
lint ans = 1e9;
int n, m, cnt, path[MAXN];
int g[MAXN][MAXN], dis[MAXN][MAXN], pos[MAXN][MAXN];

void get_path(int u, int v) {
    if (pos[u][v] == 0) return;
    int k = pos[u][v];
    get_path(u, k);
    path[++cnt] = k;
    get_path(k, v);
}

void Floyd() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i < k; ++i)
            for (int j = 1; j < i; ++j)
                if (ans > (long long)g[i][k] + g[k][j] + dis[i][j]) {
                    ans = g[i][k] + g[k][j] + dis[i][j];
                    cnt = 0;
                    path[++cnt] = i, path[++cnt] = k, path[++cnt] = j;
                    get_path(j, i);
                }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) {
                if (dis[i][j] > dis[i][k] + dis[k][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    pos[i][j] = k;
                }
            }
    }
}

int main() {
    std::cin >> n >> m;
    memset(g, 0x3f, sizeof(g));
    for (int i = 1; i <= n; ++i) g[i][i] = 0;
    for (int i = 0, u, v, w; i < m; ++i) {
        std::cin >> u >> v >> w;
        g[u][v] = g[v][u] = std::min(g[u][v], w);
    }
    memcpy(dis, g, sizeof(g));
    Floyd();
    if (ans == 1e9) {
        puts("No solution.");
    } else {
        for (int i = 1; i <= cnt; ++i)
            std::cout << path[i] << (i == cnt ? "" : " ");
        std::cout << std::endl;
    }
    return 0;
}