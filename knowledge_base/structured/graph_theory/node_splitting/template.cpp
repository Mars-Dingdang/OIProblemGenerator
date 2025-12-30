#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e4 + 5;
const int MAXK = 15;
const int INF = 0x3f3f3f3f;

struct State {
    int v, w, cnt;
    State() {}
    State(int v, int w, int cnt) : v(v), w(w), cnt(cnt) {}
    bool operator<(const State &rhs) const { return w > rhs.w; }
};

struct Edge {
    int v, w, next;
} edge[MAXN * 2];

int head[MAXN], dis[MAXN][MAXK], done[MAXN][MAXK];
int n, m, k, s, t, tot = 1;
priority_queue<State> pq;

void add(int u, int v, int w) {
    edge[++tot].v = v;
    edge[tot].w = w;
    edge[tot].next = head[u];
    head[u] = tot;
}

void dijkstra() {
    memset(dis, 0x3f, sizeof dis);
    dis[s][0] = 0;
    pq.push(State(s, 0, 0));
    while (!pq.empty()) {
        State top = pq.top(); pq.pop();
        int u = top.v, nowCnt = top.cnt;
        if (done[u][nowCnt]) continue;
        done[u][nowCnt] = true;
        for (int i = head[u]; i; i = edge[i].next) {
            int v = edge[i].v, w = edge[i].w;
            if (nowCnt < k && dis[v][nowCnt + 1] > dis[u][nowCnt]) {
                dis[v][nowCnt + 1] = dis[u][nowCnt];
                pq.push(State(v, dis[v][nowCnt + 1], nowCnt + 1));
            }
            if (dis[v][nowCnt] > dis[u][nowCnt] + w) {
                dis[v][nowCnt] = dis[u][nowCnt] + w;
                pq.push(State(v, dis[v][nowCnt], nowCnt));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> k >> s >> t;
    s++; t++;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u++; v++;
        add(u, v, w);
        add(v, u, w);
    }
    dijkstra();
    int ans = INF;
    for (int i = 0; i <= k; i++) ans = min(ans, dis[t][i]);
    cout << ans << endl;
    return 0;
}