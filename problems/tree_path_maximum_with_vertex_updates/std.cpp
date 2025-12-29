// ```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005;
const int LOGN = 20;            // 2^20 > 200000
const ll INF = 1e18;            // large enough for -infinity

// ---------- Matrix for a segment ----------
struct Matrix {
    ll dp[2][2];                // dp[left_state][right_state]
    Matrix() {
        dp[0][0] = dp[0][1] = dp[1][0] = dp[1][1] = -INF;
    }
};

// Merge two adjacent segments A (left) and B (right)
Matrix merge(const Matrix& A, const Matrix& B) {
    Matrix C;
    for (int l = 0; l < 2; ++l) {               // left state of A
        for (int r = 0; r < 2; ++r) {           // right state of B
            ll best = -INF;
            for (int m1 = 0; m1 < 2; ++m1) {    // right state of A / left state of B
                for (int m2 = 0; m2 < 2; ++m2) {
                    if (m1 + m2 > 1) continue;  // adjacent vertices cannot both be taken
                    if (A.dp[l][m1] <= -INF/2 || B.dp[m2][r] <= -INF/2) continue;
                    best = max(best, A.dp[l][m1] + B.dp[m2][r]);
                }
            }
            C.dp[l][r] = best;
        }
    }
    return C;
}

// Reverse a segment (swap left and right endpoints)
Matrix reverse(const Matrix& A) {
    Matrix B;
    B.dp[0][0] = A.dp[0][0];
    B.dp[0][1] = A.dp[1][0];
    B.dp[1][0] = A.dp[0][1];
    B.dp[1][1] = A.dp[1][1];
    return B;
}

// Matrix for a single vertex
Matrix single(ll val) {
    Matrix M;
    M.dp[0][0] = 0;            // do not take the vertex
    M.dp[1][1] = val;          // take the vertex
    // dp[0][1] and dp[1][0] remain -INF (impossible)
    return M;
}

// ---------- Heavy‑Light Decomposition ----------
int n, q;
vector<int> adj[MAXN];
ll a[MAXN];

// tree information
int up[MAXN][LOGN];
int depth[MAXN];

// HLD information
int sz[MAXN], heavy[MAXN];
int chain_id[MAXN], chain_pos[MAXN], chain_head[MAXN];
vector<vector<int>> chains;            // vertices in each chain (top‑down order)
vector<vector<Matrix>> segtrees;       // segment tree for each chain

// first DFS: compute subtree sizes and heavy child
void dfs_size(int u, int p) {
    sz[u] = 1;
    heavy[u] = -1;
    int max_size = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        up[v][0] = u;
        dfs_size(v, u);
        sz[u] += sz[v];
        if (sz[v] > max_size) {
            max_size = sz[v];
            heavy[u] = v;
        }
    }
}

// second DFS: decompose into heavy paths
void decompose(int u, int h, int& pos, int cid) {
    chain_head[u] = h;
    chain_id[u] = cid;
    chain_pos[u] = pos;
    chains[cid].push_back(u);
    pos++;
    if (heavy[u] != -1) {
        decompose(heavy[u], h, pos, cid);
    }
    for (int v : adj[u]) {
        if (v == up[u][0] || v == heavy[u]) continue;
        int new_cid = chains.size();
        chains.push_back(vector<int>());
        segtrees.push_back(vector<Matrix>());
        decompose(v, v, pos, new_cid);
    }
}

// ---------- Segment tree on a heavy chain ----------
void build_segtree(int cid, int idx, int l, int r) {
    if (l == r) {
        int v = chains[cid][l];
        segtrees[cid][idx] = single(a[v]);
        return;
    }
    int mid = (l + r) >> 1;
    build_segtree(cid, idx * 2, l, mid);
    build_segtree(cid, idx * 2 + 1, mid + 1, r);
    segtrees[cid][idx] = merge(segtrees[cid][idx * 2], segtrees[cid][idx * 2 + 1]);
}

void update_segtree(int cid, int idx, int l, int r, int pos, ll val) {
    if (l == r) {
        segtrees[cid][idx] = single(val);
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update_segtree(cid, idx * 2, l, mid, pos, val);
    else
        update_segtree(cid, idx * 2 + 1, mid + 1, r, pos, val);
    segtrees[cid][idx] = merge(segtrees[cid][idx * 2], segtrees[cid][idx * 2 + 1]);
}

Matrix query_segtree(int cid, int idx, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return segtrees[cid][idx];
    int mid = (l + r) >> 1;
    if (qr <= mid)
        return query_segtree(cid, idx * 2, l, mid, ql, qr);
    if (ql > mid)
        return query_segtree(cid, idx * 2 + 1, mid + 1, r, ql, qr);
    return merge(query_segtree(cid, idx * 2, l, mid, ql, qr),
                 query_segtree(cid, idx * 2 + 1, mid + 1, r, ql, qr));
}

// Query a chain segment from ancestor a to descendant b (a is shallower)
Matrix query_chain(int a, int b) {
    int cid = chain_id[a];
    int l = chain_pos[a];
    int r = chain_pos[b];
    return query_segtree(cid, 1, 0, chains[cid].size() - 1, l, r);
}

// Get matrix for a segment from deeper to shallower (deeper is descendant of shallower)
Matrix get_upward_segment(int deeper, int shallower) {
    Matrix M = query_chain(shallower, deeper);   // order shallower -> deeper
    return reverse(M);                           // order deeper -> shallower
}

// ---------- LCA and lifting ----------
void preprocess_lca() {
    for (int j = 1; j < LOGN; ++j) {
        for (int i = 1; i <= n; ++i) {
            if (up[i][j - 1] != -1)
                up[i][j] = up[up[i][j - 1]][j - 1];
            else
                up[i][j] = -1;
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int j = 0; j < LOGN; ++j)
        if (diff & (1 << j))
            u = up[u][j];
    if (u == v) return u;
    for (int j = LOGN - 1; j >= 0; --j)
        if (up[u][j] != up[v][j])
            u = up[u][j], v = up[v][j];
    return up[u][0];
}

// Lift u up by k steps
int lift(int u, int k) {
    for (int j = 0; j < LOGN; ++j)
        if (k & (1 << j))
            u = up[u][j];
    return u;
}

// ---------- Main ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // root the tree at 1
    depth[1] = 0;
    up[1][0] = -1;
    dfs_size(1, -1);

    // HLD decomposition
    chains.push_back(vector<int>());
    segtrees.push_back(vector<Matrix>());
    int pos = 0;
    decompose(1, 1, pos, 0);

    // build segment trees for all chains
    for (int i = 0; i < (int)chains.size(); ++i) {
        int m = chains[i].size();
        segtrees[i].resize(4 * m);
        build_segtree(i, 1, 0, m - 1);
    }

    preprocess_lca();

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {               // update
            int x; ll y;
            cin >> x >> y;
            a[x] = y;
            int cid = chain_id[x];
            int p = chain_pos[x];
            update_segtree(cid, 1, 0, chains[cid].size() - 1, p, y);
        } else {                       // query path
            int u, v;
            cin >> u >> v;
            int w = lca(u, v);

            // ---- collect segments from u to w (including w) ----
            vector<Matrix> left_segments;
            int current = u;
            while (chain_id[current] != chain_id[w]) {
                int h = chain_head[current];
                left_segments.push_back(get_upward_segment(current, h));
                current = up[h][0];
            }
            if (current != w)
                left_segments.push_back(get_upward_segment(current, w));
            else
                left_segments.push_back(single(a[w]));

            // ---- collect segments from w to v (excluding w) ----
            vector<Matrix> right_segments;
            if (v != w) {
                int wv = lift(v, depth[v] - depth[w] - 1);   // child of w on the path to v
                vector<Matrix> temp;
                current = v;
                while (chain_id[current] != chain_id[wv]) {
                    int h = chain_head[current];
                    temp.push_back(query_chain(h, current));
                    current = up[h][0];
                }
                if (current != wv)
                    temp.push_back(query_chain(wv, current));
                else
                    temp.push_back(single(a[wv]));
                reverse(temp.begin(), temp.end());
                right_segments = temp;
            }

            // ---- combine all segments in order ----
            Matrix total = left_segments[0];
            for (size_t i = 1; i < left_segments.size(); ++i)
                total = merge(total, left_segments[i]);
            for (size_t i = 0; i < right_segments.size(); ++i)
                total = merge(total, right_segments[i]);

            ll ans = max({total.dp[0][0], total.dp[0][1],
                          total.dp[1][0], total.dp[1][1]});
            cout << ans << '\n';
        }
    }

    return 0;
}
// ```