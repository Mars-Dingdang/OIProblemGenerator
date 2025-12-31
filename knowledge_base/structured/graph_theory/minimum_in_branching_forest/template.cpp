/*
 * Priority In-Tree Expansion Algorithm for Minimum In-Branching Forest
 * Time Complexity: O(E log E)
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 200005; // Adjust based on constraints

struct Edge {
    int u, v;
    ll w;
    bool operator<(const Edge& e) const { return w > e.w; } // Max-heap by default
};

// Mergeable min-heap for outgoing edges (using priority_queue + lazy)
class Node {
public:
    ll lazy = 0;
    priority_queue<Edge> edges; // Min-heap via reversed comparison

    void push(Edge e) {
        e.w -= lazy; // Normalize before storing
        edges.push(e);
    }

    void add(ll delta) {
        lazy += delta;
    }

    Edge top() {
        Edge e = edges.top();
        e.w += lazy; // Restore actual weight
        return e;
    }

    void pop() {
        edges.pop();
    }

    bool empty() {
        return edges.empty();
    }

    void merge(Node& other) {
        // Heuristic: merge smaller into larger
        if (edges.size() < other.edges.size()) {
            swap(lazy, other.lazy);
            swap(edges, other.edges);
        }
        while (!other.edges.empty()) {
            Edge e = other.edges.top(); other.edges.pop();
            e.w += (other.lazy - lazy); // Adjust to new lazy base
            edges.push(e);
        }
    }
};

int n, m, k;
vector<Node> node; // One per original vertex initially
vector<int> parent, root_id;
ll ans[MAXN]; // ans[i] = MDF(i)

int find_root(int x) {
    return parent[x] == x ? x : parent[x] = find_root(parent[x]);
}

void merge_trees(int u, int v) { // Merge u into v
    u = find_root(u), v = find_root(v);
    if (u == v) return;
    parent[u] = v;
    node[v].merge(node[u]);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m >> k;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        --edges[i].u; --edges[i].v;
    }

    // Initialize
    node.resize(n);
    parent.resize(n);
    root_id.resize(n);
    iota(parent.begin(), parent.end(), 0);
    for (int i = 0; i < n; ++i) root_id[i] = i;

    // Build initial edge lists
    for (auto& e : edges) {
        node[e.u].push(e);
    }

    // Global heap: select tree with minimum expansion cost
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq; // (cost, root)
    vector<ll> dec(n, 0); // Pre-decrement for each root

    auto update = [&](int u) {
        u = find_root(u);
        while (!node[u].empty()) {
            Edge e = node[u].top();
            if (find_root(e.v) == u) { // Self-loop in contracted graph
                node[u].pop();
                continue;
            }
            ll cost = dec[u] + e.w; // Actual expansion cost
            pq.emplace(cost, u);
            break;
        }
    };

    for (int i = 0; i < n; ++i) update(i);

    int cnt_edges = 0;
    ans[0] = 0;

    while (!pq.empty() && cnt_edges < k) {
        auto [cost, u] = pq.top(); pq.pop();
        u = find_root(u);
        if (cost != dec[u] + (node[u].empty() ? LLONG_MAX : node[u].top().w)) {
            // Outdated entry
            if (!node[u].empty()) update(u);
            continue;
        }

        Edge e = node[u].top(); node[u].pop();
        int v = find_root(e.v);

        if (u == v) {
            // Need to expand further within same component? Not possible.
            update(u);
            continue;
        }

        // Add edge e
        ans[++cnt_edges] = ans[cnt_edges - 1] + e.w + dec[u];

        // Perform contraction if necessary (simulate Edmonds)
        node[u].add(dec[u]); // Apply accumulated decrement
        node[v].add(dec[v]);

        // Merge u into v
        merge_trees(u, v);
        dec[v] = max(dec[v], dec[u] + e.w); // New pre-decrement

        update(v);
    }

    // Output answer for k edges
    cout << ans[k] << '\n';

    return 0;
}