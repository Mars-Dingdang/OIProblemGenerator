The provided problem asks to compute the **total cosmic resonance** of a binary string $s$, which is defined as the sum of the number of *diverse substrings* for all valid parameters $k \ge 1$. A substring $t$ is diverse for parameter $k$ if all contiguous substrings of length $k$ in $t$ are pairwise distinct. This condition is equivalent to saying that no substring of length $k$ appears twice in $t$.

Let $max\_repeat(t)$ be the length of the longest substring that appears at least twice in $t$. The substring $t$ is diverse for parameter $k$ if and only if $k > max\_repeat(t)$ and $k \le |t|$. Thus, the contribution of a substring $t$ to the total resonance is $|t| - max\_repeat(t)$ (if positive, otherwise 0). Since $max\_repeat(t) < |t|$ for any string with length $\ge 1$, the total resonance is simply:
$$ \sum_{t \subseteq s} (|t| - max\_repeat(t)) = \sum_{t \subseteq s} |t| - \sum_{t \subseteq s} max\_repeat(t) $$
The first part, $\sum_{t \subseteq s} |t|$, is the sum of lengths of all substrings of $s$, which is $\frac{n(n+1)(n+2)}{6}$ for a string of length $n$. The core of the problem is to compute the second part: the sum of the length of the longest repeating substring over all substrings of $s$.

This problem can be efficiently solved using the **Suffix Automaton (SAM)** of the reversed string $s^R$ (which corresponds to the Suffix Tree of $s$) combined with a **sweep-line algorithm** and a **Segment Tree Beats** data structure. The approach leverages the fact that the set of all repeating substrings can be characterized by pairs of positions $(p, q)$ in $s$ (representing two occurrences of a substring) that are adjacent in the suffix structure.

### Algorithm

1.  **Construct the Suffix Automaton (SAM)** for the reversed string $s^R$. The parent tree of this SAM corresponds to the Suffix Tree of the original string $s$. Each node $u$ in the parent tree represents a set of substrings that appear in the same right-end positions in $s^R$ (left-end positions in $s$). Let $len(u)$ be the length of the longest string represented by node $u$.

2.  **Collect "Repetition Pairs"**: We are interested in pairs of starting positions $(p, q)$ in $s$ (with $p < q$) such that the longest common prefix starting at $p$ and $q$ has some length $L$. Specifically, we only need to consider pairs that are "adjacent" in the set of occurrences of some node in the Suffix Tree.
    *   Traverse the parent tree. For each node $u$, maintain the set of starting positions of occurrences in $s$ (which are $n - \text{endpos}_{s^R} + 1$).
    *   Use **Small-to-Large Merging** (DSU on Tree) to merge position sets from children to parents.
    *   When merging a smaller set into a larger set, for each position $x$ in the smaller set, find its predecessor $y$ and successor $z$ in the larger set. These pairs $(y, x)$ and $(x, z)$ represent a potential longest repeating substring of length $len(u)$ starting at these positions.
    *   Store these significant pairs as events: `events[p].push_back({q, len(u)})` where $p < q$. There are $O(n \log n)$ such pairs.

3.  **Sweep-Line with Segment Tree**:
    *   We want to compute $\sum_{l=1}^n \sum_{r=l}^n F(l, r)$, where $F(l, r) = \max \{ \min(len, r-q+1) \mid (p, q, len) \text{ is a pair}, p \ge l, q \le r \}$.
    *   Iterate $l$ from $n$ down to $1$.
    *   Maintain a Segment Tree over the index $r$ ($1 \le r \le n$). The tree will maintain the current value of $V_r = \max_{(p, q, len), p \ge l} (\min(len, r-q+1))$ for each $r$, and allow querying the sum $\sum_{r=l}^n V_r$.
    *   When moving from $l+1$ to $l$, activate all pairs with starting position $p=l$. For a pair $(q, len)$, we perform a range update on the Segment Tree:
        *   For $r \in [q, q+len-1]$, update $V_r \leftarrow \max(V_r, r - q + 1)$. This is an update with a linear function of slope 1.
        *   For $r \in [q+len, n]$, update $V_r \leftarrow \max(V_r, len)$. This is an update with a constant.
    *   These updates can be handled using a **Segment Tree Beats** approach (specifically designed for `chmax` with arithmetic progressions). Since the values are non-decreasing and we only take maximums, a simplified version or a standard implementation supporting "Range Chmax with Line" suffices.
    *   After updates, add the sum of $V_r$ for $r \in [l, n]$ to the total sum of `max_repeat`.

4.  **Final Calculation**:
    *   Calculate Total Length Sum: $S_{len} = \frac{n(n+1)(n+2)}{6}$.
    *   Calculate Result: $S_{len} - \text{Total Sum of Max Repeats}$.

### C++ Solution

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

typedef long long ll;

const int MAXN = 200005;

// Suffix Automaton
struct State {
    int len, link;
    int next[2]; // 0 and 1
    int first_pos = -1;
} st[MAXN * 2];
int sz, last;

void sam_init() {
    st[0].len = 0;
    st[0].link = -1;
    st[0].next[0] = st[0].next[1] = -1;
    sz = 1;
    last = 0;
}

void sam_extend(int c, int pos) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].next[0] = st[cur].next[1] = -1;
    st[cur].first_pos = pos;
    int p = last;
    while (p != -1 && st[p].next[c] == -1) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next[0] = st[q].next[0];
            st[clone].next[1] = st[q].next[1];
            st[clone].link = st[q].link;
            st[clone].first_pos = st[q].first_pos; 
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

vector<int> adj[MAXN * 2];
vector<pair<int, int>> pairs[MAXN]; // pairs[p] contains {q, len}
set<int> pos_set[MAXN * 2];

// DSU on Tree to collect pairs
void dfs_pos(int u, int n) {
    // If leaf (original string position)
    if (st[u].first_pos != -1) {
        // SAM of reverse string: first_pos is end in reverse, so start in original is n - 1 - first_pos + 1 = n - first_pos
        // Let's use 1-based indexing for the problem logic
        // String s indices 1..n. 
        // s^R indices 0..n-1. 
        // pos in s^R is k. Corresponds to s[n-1-k]. 1-based index: n-k.
        // Wait, not exactly leaves. We need to identify which nodes correspond to original positions.
        // In SAM, states created by `extend` (not clones) correspond to prefixes of s^R, i.e., suffixes of s.
        // We can just track the `first_pos` which is a valid end position in s^R.
        // However, `first_pos` is just one occurrence. We need all.
        // Standard way: initialize sets at "real" nodes and merge up.
        // "Real" nodes are those not cloned.
        // But clones also have positions.
        // Actually, we can just initialize pos_set[u] = {n - st[u].first_pos} for non-clones?
        // No, we need to pass sets up.
    }
    
    // Proper initialization: Only nodes created in `sam_extend` (not clones) contribute a position initially.
    // However, `first_pos` is maintained for all. But clones don't represent a unique endpos class size=1 initially.
    // Clones represent a class that is a union.
    // Actually simpler: Build tree, find which node corresponds to the prefix s^R[0...i].
    // That node has an occurrence ending at i in s^R => starting at n-i in s.
}

// Better approach for DSU:
// Map each prefix of s^R to its node.
// node_of_prefix[i] is the state after processing s^R[0...i].
// This state has an occurrence ending at i.
// So we insert (n - i) into pos_set[node_of_prefix[i]].
// Then merge sets up the link tree.

int node_map[MAXN]; 

void dfs_merge(int u) {
    for (int v : adj[u]) {
        dfs_merge(v);
        // Merge v into u (small to large)
        if (pos_set[u].size() < pos_set[v].size()) {
            swap(pos_set[u], pos_set[v]);
        }
        for (int x : pos_set[v]) {
            // Check predecessor
            auto it = pos_set[u].lower_bound(x);
            if (it != pos_set[u].begin()) {
                int y = *prev(it);
                // Pair y, x (y < x). Len = st[u].len
                pairs[y].push_back({x, st[u].len});
            }
            // Check successor
            if (it != pos_set[u].end()) {
                int z = *it;
                // Pair x, z (x < z). Len = st[u].len
                pairs[x].push_back({z, st[u].len});
            }
            pos_set[u].insert(x);
        }
        pos_set[v].clear();
    }
}

// Segment Tree Beats (Simplified for max updates with lines)
// We need to support:
// 1. Range chmax with y = x + C (slope 1)
// 2. Range chmax with y = C (slope 0)
// 3. Range sum query
// Given the specific nature (increasing updates), we use a heuristic beats approach or a specialized tag.
// Since time is tight and implementation complex, we use a standard Segment Tree with "max" tags.
// But we have slope.
// Tag type: {slope, intercept}. Maximize current val with slope*idx + intercept.
// Merging tags: We only add lines. We keep the max line? No, max of lines is convex.
// BUT, note that for a fixed l, as r increases, the optimal pair might change.
// However, N is small enough that maybe we can just use the "K-D Tree" or "Li Chao" idea on SegTree.
// Actually, we can just use a Fenwick tree if we process offline? No, range max.
// Let's use a Segment Tree that stores the current maximum value at each point.
// Since we only query sum, we maintain sum.
// Lazy tag: The line (k, b) to max with. k \in {0, 1}.
// If we have existing tag, we merge.
// Since lines can intersect, a single line tag isn't enough for exact maintenance unless we use Beats.
// BEATS condition:
// Node stores min_val. If new_line(l) <= min_val && new_line(r) <= min_val, return.
// Else if new_line(l) >= max_val && new_line(r) >= max_val, update fully.
// Else push down.
// Since updates are monotonic increasing, this is fast.

struct Node {
    ll sum;
    ll min_val, max_val;
    ll lazy_k, lazy_b; // y = k*x + b. -1e18 if empty.
    bool has_lazy;
} tree[MAXN * 4];

void push_up(int node) {
    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
    tree[node].min_val = min(tree[2 * node].min_val, tree[2 * node + 1].min_val);
    tree[node].max_val = max(tree[2 * node].max_val, tree[2 * node + 1].max_val);
}

// Apply line y = k*x + b to a node
// Assumption: this line dominates the current values in the node (for Beats)
// OR used for pushing down tags.
// Actually for Beats, we need to handle "partial" dominance.
// Simplification: We only support "replace if larger".
// If we apply a line to a range, and we know it's larger than ALL values, we can update sum arithmetic.
// If not, we recurse.
void apply(int node, int l, int r, ll k, ll b) {
    // Calculate values at ends
    ll val_l = k * l + b;
    ll val_r = k * r + b;
    // Check if update is useful
    if (val_l <= tree[node].min_val && val_r <= tree[node].min_val) return; // Optimization
    
    // If this is a leaf, update
    if (l == r) {
        ll val = k * l + b;
        if (val > tree[node].max_val) {
            tree[node].sum = val;
            tree[node].min_val = val;
            tree[node].max_val = val;
        }
        return;
    }
    
    // Beats Logic:
    // If the new line is completely above current max, we can replace? 
    // No, we need to keep max(old, new).
    // If new line is above max, then new becomes the value.
    // If val_l >= tree[node].max_val && val_r >= tree[node].max_val:
    //    We can update sum using arithmetic series formula.
    //    Update min/max.
    //    Set lazy tag to override? No, we need to merge with existing "max" history.
    //    This suggests we essentially replace the values.
    if (val_l >= tree[node].max_val && val_r >= tree[node].max_val) {
        tree[node].sum = (val_l + val_r) * (r - l + 1) / 2;
        tree[node].min_val = min(val_l, val_r); // Should be val_l if k=1, val_r if k=0
        tree[node].max_val = max(val_l, val_r);
        tree[node].lazy_k = k;
        tree[node].lazy_b = b;
        tree[node].has_lazy = true;
        return;
    }
    
    // If we have a lazy tag, we might need to push it before recursing?
    // Yes.
    int mid = (l + r) / 2;
    if (tree[node].has_lazy) {
        apply(2 * node, l, mid, tree[node].lazy_k, tree[node].lazy_b);
        apply(2 * node + 1, mid + 1, r, tree[node].lazy_k, tree[node].lazy_b);
        tree[node].has_lazy = false;
    }
    
    apply(2 * node, l, mid, k, b);
    apply(2 * node + 1, mid + 1, r, k, b);
    push_up(node);
}

// We need a specific "Range Chmax" function for Beats
void update(int node, int l, int r, int ql, int qr, ll k, ll b) {
    if (ql > r || qr < l) return;
    
    ll val_l = k * (max(l, ql)) + b;
    ll val_r = k * (min(r, qr)) + b;
    
    // Pruning: if new line is below min for the whole range, exit
    // Since k>=0, min is at left, max at right (for the line segment in [l, r])
    // Actually we check intersection of [l,r] and [ql,qr].
    // The line is defined on [ql, qr].
    
    // Simple recursive structure for Beats
    if (l >= ql && r <= qr) {
        ll v_l = k * l + b;
        ll v_r = k * r + b;
        if (v_l <= tree[node].min_val && v_r <= tree[node].min_val) return;
        if (v_l >= tree[node].max_val && v_r >= tree[node].max_val) {
            tree[node].sum = (v_l + v_r) * (r - l + 1) / 2;
            tree[node].min_val = v_l; // k>=0
            tree[node].max_val = v_r;
            tree[node].lazy_k = k;
            tree[node].lazy_b = b;
            tree[node].has_lazy = true;
            return;
        }
    }
    
    int mid = (l + r) / 2;
    if (tree[node].has_lazy) {
        // Push down current tag (which is a "set" tag effectively because it dominated)
        // Note: The tag stores the line that *replaced* the values.
        apply(2 * node, l, mid, tree[node].lazy_k, tree[node].lazy_b);
        apply(2 * node + 1, mid + 1, r, tree[node].lazy_k, tree[node].lazy_b);
        tree[node].has_lazy = false;
    }
    
    update(2 * node, l, mid, ql, qr, k, b);
    update(2 * node + 1, mid + 1, r, ql, qr, k, b);
    push_up(node);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    string s;
    cin >> s;
    
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    
    sam_init();
    // Keep track of which node corresponds to which prefix of rev_s (suffix of s)
    // node 0 is root.
    int curr = 0;
    for (int i = 0; i < n; i++) {
        sam_extend(rev_s[i] - '0', i);
        // After extending i-th char, 'last' is the node for prefix 0...i
        node_map[i] = last;
    }
    
    // Build Parent Tree
    for (int i = 1; i < sz; i++) {
        adj[st[i].link].push_back(i);
    }
    
    // Initialize pos sets
    // For each i in 0..n-1, node_map[i] has occurrence ending at i in rev_s
    // Which is pos n - 1 - i + 1 = n - i in s (1-based).
    for (int i = 0; i < n; i++) {
        pos_set[node_map[i]].insert(n - i);
    }
    
    // DFS to merge and collect pairs
    dfs_merge(0);
    
    // Sort pairs? No, store in events[p].
    // pairs[p] is already a vector.
    
    // Segment Tree Init
    // 1-based [1, n]. Initially 0.
    
    ll total_max_repeat_sum = 0;
    
    for (int l = n; l >= 1; l--) {
        for (auto& p : pairs[l]) {
            int q = p.first;
            int len = p.second;
            // Update [q, q+len-1] with val = r - q + 1
            // y = 1*r + (1-q)
            if (q <= n) {
                int r_end = min(n, q + len - 1);
                update(1, 1, n, q, r_end, 1, 1 - q);
            }
            // Update [q+len, n] with val = len
            // y = 0*r + len
            if (q + len <= n) {
                update(1, 1, n, q + len, n, 0, len);
            }
        }
        total_max_repeat_sum += tree[1].sum; // Query [1, n], but effectively [l, n] are the only relevant ones? 
        // No, we need sum_{r=l}^n max_repeat(s[l..r]).
        // The segment tree stores B[r] for the current l.
        // We need sum over r in [l, n].
        // But since we only add pairs with p >= l, B[r] is 0 for r < l?
        // Wait, pairs (p, q). q > p >= l. So q > l.
        // So B[r] is 0 for r <= l.
        // So tree[1].sum is exactly sum_{r=l}^n B[r].
    }
    
    ll total_substring_len = 0;
    for (ll i = 1; i <= n; i++) {
        total_substring_len += i * (n - i + 1);
    }
    
    cout << total_substring_len - total_max_repeat_sum << endl;
    
    return 0;
}
```