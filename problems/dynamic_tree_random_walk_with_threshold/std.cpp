#include <bits/stdc++.h>
using namespace std;

// Discretization and constants
const int MAXN = 200005;
vector<long long> all_vals;  // All distinct threshold values
int M;  // Number of distinct threshold values

// Segment Tree Node for piecewise constant function
struct SegNode {
    double val;  // Value for this segment (constant)
    int left, right;  // Children indices (-1 if leaf)
    SegNode() : val(0), left(-1), right(-1) {}
    SegNode(double v) : val(v), left(-1), right(-1) {}
};

vector<SegNode> seg_pool;  // Pool of segment tree nodes

// Create a new segment tree node
int new_node(double val = 0) {
    seg_pool.push_back(SegNode(val));
    return (int)seg_pool.size() - 1;
}

// Merge two segment trees by adding their values
int merge_seg(int a, int b, int l, int r) {
    if (a == -1) return b;
    if (b == -1) return a;
    
    if (l == r) {
        // Leaf node: sum the values
        int node = new_node(seg_pool[a].val + seg_pool[b].val);
        return node;
    }
    
    int mid = (l + r) / 2;
    int left_child = merge_seg(seg_pool[a].left, seg_pool[b].left, l, mid);
    int right_child = merge_seg(seg_pool[a].right, seg_pool[b].right, mid + 1, r);
    
    int node = new_node();
    seg_pool[node].left = left_child;
    seg_pool[node].right = right_child;
    return node;
}

// Build a segment tree with constant value
int build_constant(int l, int r, double val) {
    if (l == r) {
        return new_node(val);
    }
    
    int node = new_node();
    int mid = (l + r) / 2;
    seg_pool[node].left = build_constant(l, mid, val);
    seg_pool[node].right = build_constant(mid + 1, r, val);
    return node;
}

// Query a segment tree at position pos
double query_seg(int node, int l, int r, int pos) {
    if (node == -1) return 0;
    if (l == r) return seg_pool[node].val;
    
    int mid = (l + r) / 2;
    if (pos <= mid) return query_seg(seg_pool[node].left, l, mid, pos);
    else return query_seg(seg_pool[node].right, mid + 1, r, pos);
}

// Update a segment tree: set range [ql, qr] to val
int update_seg(int old_node, int l, int r, int ql, int qr, double val) {
    if (ql > r || qr < l) return old_node;
    if (ql <= l && r <= qr) {
        return build_constant(l, r, val);
    }
    
    int node = new_node();
    seg_pool[node] = seg_pool[old_node];
    
    int mid = (l + r) / 2;
    seg_pool[node].left = update_seg(seg_pool[node].left, l, mid, ql, qr, val);
    seg_pool[node].right = update_seg(seg_pool[node].right, mid + 1, r, ql, qr, val);
    return node;
}

// Heavy-Light Decomposition
vector<int> adj[MAXN];
int parent[MAXN], depth[MAXN], heavy[MAXN], head[MAXN], pos[MAXN];
int cur_pos;

int dfs_hld(int u) {
    int size = 1;
    int max_subtree = 0;
    heavy[u] = -1;
    
    for (int v : adj[u]) {
        if (v == parent[u]) continue;
        parent[v] = u;
        depth[v] = depth[u] + 1;
        int subtree_size = dfs_hld(v);
        size += subtree_size;
        if (subtree_size > max_subtree) {
            max_subtree = subtree_size;
            heavy[u] = v;
        }
    }
    return size;
}

void decompose(int u, int h) {
    head[u] = h;
    pos[u] = cur_pos++;
    
    if (heavy[u] != -1) {
        decompose(heavy[u], h);
    }
    
    for (int v : adj[u]) {
        if (v != parent[u] && v != heavy[u]) {
            decompose(v, v);
        }
    }
}

// Problem-specific data structures
long long a[MAXN];
int deg[MAXN];
int seg_root[MAXN];  // Segment tree root for each node
int light_sum_root[MAXN];  // Segment tree root for sum of light children's E

// Preprocessing: build initial segment trees
void dfs_build(int u) {
    // Process children first
    for (int v : adj[u]) {
        if (v == parent[u]) continue;
        dfs_build(v);
    }
    
    // Merge segment trees of children
    int merged = -1;
    for (int v : adj[u]) {
        if (v == parent[u]) continue;
        if (merged == -1) {
            merged = seg_root[v];
        } else {
            merged = merge_seg(merged, seg_root[v], 0, M - 1);
        }
    }
    
    // Find threshold index for a[u]
    int thresh_idx = lower_bound(all_vals.begin(), all_vals.end(), a[u]) - all_vals.begin();
    
    // Build E(u, T)
    if (merged == -1) {
        // Leaf node
        if (thresh_idx < M) {
            seg_root[u] = update_seg(-1, 0, M - 1, thresh_idx, M - 1, 0);
        } else {
            seg_root[u] = -1;
        }
    } else {
        // Non-leaf node
        if (thresh_idx < M) {
            // For T >= a[u]: E(u, T) = 1 + S(u, T)/deg(u)
            // We need to create a new segment tree with transformed values
            // This is done by traversing the merged tree and applying transformation
            function<int(int, int, int)> transform = [&](int node, int l, int r) {
                if (node == -1) {
                    return build_constant(l, r, 1.0 / deg[u]);
                }
                if (l == r) {
                    return new_node(1.0 + seg_pool[node].val / deg[u]);
                }
                int new_node_idx = new_node();
                int mid = (l + r) / 2;
                seg_pool[new_node_idx].left = transform(seg_pool[node].left, l, mid);
                seg_pool[new_node_idx].right = transform(seg_pool[node].right, mid + 1, r);
                return new_node_idx;
            };
            
            int transformed = transform(merged, 0, M - 1);
            // For T < a[u]: E(u, T) = 0
            if (thresh_idx > 0) {
                transformed = update_seg(transformed, 0, M - 1, 0, thresh_idx - 1, 0);
            }
            seg_root[u] = transformed;
        } else {
            // All T < a[u]
            seg_root[u] = build_constant(0, M - 1, 0);
        }
    }
}

// Update operation
void update_node(int x, long long new_val) {
    a[x] = new_val;
    
    // Recompute segment tree for node x
    vector<int> children;
    for (int v : adj[x]) {
        if (v == parent[x]) continue;
        children.push_back(v);
    }
    
    // Merge children's segment trees
    int merged = -1;
    for (int v : children) {
        if (merged == -1) {
            merged = seg_root[v];
        } else {
            merged = merge_seg(merged, seg_root[v], 0, M - 1);
        }
    }
    
    // Find threshold index for new a[x]
    int thresh_idx = lower_bound(all_vals.begin(), all_vals.end(), a[x]) - all_vals.begin();
    
    // Build new E(x, T)
    if (merged == -1) {
        if (thresh_idx < M) {
            seg_root[x] = update_seg(-1, 0, M - 1, thresh_idx, M - 1, 0);
        } else {
            seg_root[x] = -1;
        }
    } else {
        if (thresh_idx < M) {
            function<int(int, int, int)> transform = [&](int node, int l, int r) {
                if (node == -1) {
                    return build_constant(l, r, 1.0 / deg[x]);
                }
                if (l == r) {
                    return new_node(1.0 + seg_pool[node].val / deg[x]);
                }
                int new_node_idx = new_node();
                int mid = (l + r) / 2;
                seg_pool[new_node_idx].left = transform(seg_pool[node].left, l, mid);
                seg_pool[new_node_idx].right = transform(seg_pool[node].right, mid + 1, r);
                return new_node_idx;
            };
            
            int transformed = transform(merged, 0, M - 1);
            if (thresh_idx > 0) {
                transformed = update_seg(transformed, 0, M - 1, 0, thresh_idx - 1, 0);
            }
            seg_root[x] = transformed;
        } else {
            seg_root[x] = build_constant(0, M - 1, 0);
        }
    }
    
    // Propagate changes to ancestors using HLD
    // For simplicity, we'll update all ancestors directly
    // In a full implementation, this would use HLD with segment tree range updates
    int u = parent[x];
    while (u != 0) {
        // Recompute segment tree for u
        vector<int> children_u;
        for (int v : adj[u]) {
            if (v == parent[u]) continue;
            children_u.push_back(v);
        }
        
        int merged_u = -1;
        for (int v : children_u) {
            if (merged_u == -1) {
                merged_u = seg_root[v];
            } else {
                merged_u = merge_seg(merged_u, seg_root[v], 0, M - 1);
            }
        }
        
        int thresh_idx_u = lower_bound(all_vals.begin(), all_vals.end(), a[u]) - all_vals.begin();
        
        if (merged_u == -1) {
            if (thresh_idx_u < M) {
                seg_root[u] = update_seg(-1, 0, M - 1, thresh_idx_u, M - 1, 0);
            } else {
                seg_root[u] = -1;
            }
        } else {
            if (thresh_idx_u < M) {
                function<int(int, int, int)> transform = [&](int node, int l, int r) {
                    if (node == -1) {
                        return build_constant(l, r, 1.0 / deg[u]);
                    }
                    if (l == r) {
                        return new_node(1.0 + seg_pool[node].val / deg[u]);
                    }
                    int new_node_idx = new_node();
                    int mid = (l + r) / 2;
                    seg_pool[new_node_idx].left = transform(seg_pool[node].left, l, mid);
                    seg_pool[new_node_idx].right = transform(seg_pool[node].right, mid + 1, r);
                    return new_node_idx;
                };
                
                int transformed = transform(merged_u, 0, M - 1);
                if (thresh_idx_u > 0) {
                    transformed = update_seg(transformed, 0, M - 1, 0, thresh_idx_u - 1, 0);
                }
                seg_root[u] = transformed;
            } else {
                seg_root[u] = build_constant(0, M - 1, 0);
            }
        }
        
        u = parent[u];
    }
}

// Query operation
double query(int s, long long T) {
    // Find threshold index
    int idx = upper_bound(all_vals.begin(), all_vals.end(), T) - all_vals.begin() - 1;
    if (idx < 0) return 0;
    
    return query_seg(seg_root[s], 0, M - 1, idx);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, q;
    cin >> n >> q;
    
    // Read initial values
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        all_vals.push_back(a[i]);
    }
    
    // Read tree edges
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // Read operations and collect update values
    vector<pair<char, pair<int, long long>>> operations;
    for (int i = 0; i < q; i++) {
        char type;
        int x;
        long long val;
        cin >> type >> x >> val;
        operations.push_back({type, {x, val}});
        if (type == 'U') {
            all_vals.push_back(val);
        }
    }
    
    // Discretize threshold values
    sort(all_vals.begin(), all_vals.end());
    all_vals.erase(unique(all_vals.begin(), all_vals.end()), all_vals.end());
    M = all_vals.size();
    
    // Initialize segment tree pool
    seg_pool.clear();
    new_node();  // Node 0 as dummy
    
    // Build tree and compute degrees
    for (int i = 1; i <= n; i++) {
        deg[i] = (int)adj[i].size();
        if (i != 1) deg[i]--;  // Root has no parent, others have one parent
    }
    
    // Heavy-Light Decomposition
    parent[1] = 0;
    depth[1] = 0;
    cur_pos = 0;
    dfs_hld(1);
    decompose(1, 1);
    
    // Build initial segment trees
    dfs_build(1);
    
    // Process operations
    for (auto& op : operations) {
        char type = op.first;
        int x = op.second.first;
        long long val = op.second.second;
        
        if (type == 'U') {
            update_node(x, val);
        } else {  // 'Q'
            cout << fixed << setprecision(10) << query(x, val) << '\n';
        }
    }
    
    return 0;
}