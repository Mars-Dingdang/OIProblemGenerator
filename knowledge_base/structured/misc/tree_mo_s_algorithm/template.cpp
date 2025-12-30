#include <algorithm>
#include <cmath>
#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

const int MAXN = 100002;
const int LOGN = 20;

int n, m, q, step, bls;
int head[MAXN], nxt[MAXN * 2], ver[MAXN * 2], tot = 0;
int bl[MAXN], fa[MAXN], dp[MAXN], sz[MAXN], hs[MAXN], top[MAXN], id[MAXN];
stack<int> sta;

void add_edge(int x, int y) {
    ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
    ver[++tot] = x, nxt[tot] = head[y], head[y] = tot;
}

void dfs1(int x) {
    sz[x] = 1;
    unsigned ss = sta.size();
    for (int i = head[x]; i; i = nxt[i]) {
        if (ver[i] != fa[x]) {
            fa[ver[i]] = x;
            dp[ver[i]] = dp[x] + 1;
            dfs1(ver[i]);
            sz[x] += sz[ver[i]];
            if (sz[ver[i]] > sz[hs[x]]) hs[x] = ver[i];
            if (sta.size() - ss >= step) {
                bls++;
                while (sta.size() != ss) {
                    bl[sta.top()] = bls;
                    sta.pop();
                }
            }
        }
    }
    sta.push(x);
}

int cnt = 0;
void dfs2(int x, int hf) {
    top[x] = hf;
    id[x] = ++cnt;
    if (!hs[x]) return;
    dfs2(hs[x], hf);
    for (int i = head[x]; i; i = nxt[i]) {
        if (ver[i] != fa[x] && ver[i] != hs[x]) {
            dfs2(ver[i], ver[i]);
        }
    }
}

int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (dp[top[x]] < dp[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dp[x] < dp[y] ? x : y;
}

struct Query {
    int x, y, t, id;
    bool operator<(const Query& a) const {
        return bl[x] == bl[a.x] ? (bl[y] == bl[a.y] ? t < a.t : bl[y] < bl[a.y]) : bl[x] < bl[a.x];
    }
} q[MAXN];

struct Update {
    int x, y, b;
} upd[MAXN];

long long ans[MAXN];
int color[MAXN], freq[MAXN];
long long val[MAXN], wgt[MAXN];
long long now = 0;
bool vis[MAXN];

void update_node(int x) {
    if (vis[x]) {
        now -= wgt[freq[color[x]]--] * val[color[x]];
    } else {
        now += wgt[++freq[color[x]]] * val[color[x]];
    }
    vis[x] ^= 1;
}

void move(int x, int y) {
    if (dp[x] < dp[y]) swap(x, y);
    while (dp[x] > dp[y]) {
        update_node(x);
        x = fa[x];
    }
    while (x != y) {
        update_node(x);
        update_node(y);
        x = fa[x];
        y = fa[y];
    }
}

void rollback(int t) {
    if (vis[upd[t].x]) {
        now -= wgt[freq[upd[t].y]--] * val[upd[t].y];
        now += wgt[++freq[upd[t].b]] * val[upd[t].b];
    }
    color[upd[t].x] = upd[t].b;
}

void apply_update(int t) {
    if (vis[upd[t].x]) {
        now -= wgt[freq[upd[t].b]--] * val[upd[t].b];
        now += wgt[++freq[upd[t].y]] * val[upd[t].y];
    }
    color[upd[t].x] = upd[t].y;
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    step = pow(n, 0.6);
    for (int i = 1; i <= m; i++) scanf("%lld", &val[i]);
    for (int i = 1; i <= n; i++) scanf("%lld", &wgt[i]);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }
    for (int i = 1; i <= n; i++) scanf("%d", &color[i]);
    
    dfs1(1);
    if (!sta.empty()) {
        bls++;
        while (!sta.empty()) bl[sta.top()] = bls, sta.pop();
    }
    dfs2(1, 1);
    
    int qc = 0, uc = 0;
    for (int i = 1; i <= q; i++) {
        int op = gi();
        if (op == 1) {
            int x = gi(), y = gi();
            if (id[x] > id[y]) swap(x, y);
            q[++qc] = {x, y, uc, qc};
        } else {
            int x = gi(), y = gi();
            upd[++uc] = {x, y, color[x]};
        }
    }
    
    sort(q + 1, q + qc + 1);
    
    int cx = 1, cy = 1; // current pointers
    vis[1] = true; freq[color[1]]++;
    
    for (int i = 1; i <= qc; i++) {
        while (uc < q[i].t) apply_update(++uc);
        while (uc > q[i].t) rollback(uc--);
        
        move(cx, q[i].x); cx = q[i].x;
        move(cy, q[i].y); cy = q[i].y;
        
        int l = lca(cx, cy);
        if (cx != l && cy != l) {
            update_node(l);
            ans[q[i].id] = now;
            update_node(l);
        } else {
            ans[q[i].id] = now;
        }
    }
    
    for (int i = 1; i <= qc; i++) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}