#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1e4 + 5;

int n, m;
vector<int> G[MAXN];
int deg[MAXN], rnk[MAXN], p[MAXN];
int h[MAXN], nxt[MAXN], lst[MAXN];
bool tf[MAXN];

// 最大势搜索求完美消除序列
void mcs() {
    memset(h, 0, sizeof(h));
    memset(deg, 0, sizeof(deg));
    memset(tf, false, sizeof(tf));
    int cur = n, nww = 0;
    for (int i = 1; i <= n; ++i) {
        deg[i] = 0;
        nxt[i] = lst[i] = 0;
        h[0] = i;
        lst[i] = i - 1;
        nxt[i - 1] = i;
    }
    lst[n] = n - 1;
    nxt[n] = 0;

    while (cur) {
        p[cur] = h[nww];
        rnk[p[cur]] = cur;
        h[nww] = nxt[h[nww]];
        if (h[nww]) lst[h[nww]] = 0;
        lst[p[cur]] = nxt[p[cur]] = 0;
        tf[p[cur]] = true;
        for (int v : G[p[cur]]) {
            if (!tf[v]) {
                if (h[deg[v]] == v) h[deg[v]] = nxt[v];
                if (nxt[v]) lst[nxt[v]] = lst[v];
                if (lst[v]) nxt[lst[v]] = nxt[v];
                lst[v] = nxt[v] = 0;
                deg[v]++;
                nxt[v] = h[deg[v]];
                if (h[deg[v]]) lst[h[deg[v]]] = v;
                h[deg[v]] = v;
            }
        }
        cur--;
        if (h[nww + 1]) nww++;
        while (nww && !h[nww]) nww--;
    }
}

// 判断序列是否为完美消除序列
bool is_perfect_elimination() {
    vector<int> s;
    bool jud = true;
    for (int i = 1; i <= n; ++i) {
        s.clear();
        int u = p[i];
        for (int v : G[u]) {
            if (rnk[u] < rnk[v]) {
                s.push_back(v);
            }
        }
        if (s.empty()) continue;
        // 找到 rnk 最小的邻居
        int first = *min_element(s.begin(), s.end(), [&](int a, int b) { return rnk[a] < rnk[b]; });
        for (int v : s) {
            if (v == first) continue;
            // 检查 first 是否与 v 相邻
            if (find(G[first].begin(), G[first].end(), v) == G[first].end()) {
                jud = false;
                break;
            }
        }
        if (!jud) break;
    }
    return jud;
}

// 求弦图的色数/团数
int chromatic_number() {
    int max_clique = 0;
    for (int i = 1; i <= n; ++i) {
        int cnt = 0;
        for (int v : G[p[i]]) {
            if (rnk[p[i]] < rnk[v]) cnt++;
        }
        max_clique = max(max_clique, cnt + 1);
    }
    return max_clique;
}