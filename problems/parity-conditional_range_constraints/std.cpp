#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<vector<int>> graph_t;
vector<bool> visited;
vector<int> order;
vector<int> comp;

void dfs1(int u) {
    visited[u] = true;
    for (int v : graph[u]) {
        if (!visited[v]) dfs1(v);
    }
    order.push_back(u);
}

void dfs2(int u, int cid) {
    comp[u] = cid;
    for (int v : graph_t[u]) {
        if (comp[v] == -1) dfs2(v, cid);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    int n, m;
    cin >> n >> m;
    
    int size = 1;
    while (size < n) size <<= 1;
    int total_base = 2 * n;
    int seg_even_base = total_base;
    int seg_odd_base = total_base + 2 * size;
    int total_nodes = seg_odd_base + 2 * size;
    
    graph.resize(total_nodes);
    
    for (int i = 0; i < n; i++) {
        int leaf = size + i;
        graph[seg_even_base + leaf].push_back(2 * i + 1);
        graph[seg_odd_base + leaf].push_back(2 * i);
    }
    
    for (int i = size - 1; i >= 1; i--) {
        graph[seg_even_base + i].push_back(seg_even_base + (i << 1));
        graph[seg_even_base + i].push_back(seg_even_base + (i << 1 | 1));
        graph[seg_odd_base + i].push_back(seg_odd_base + (i << 1));
        graph[seg_odd_base + i].push_back(seg_odd_base + (i << 1 | 1));
    }
    
    function<void(int, int, int, int, int, int)> add_seg_even;
    function<void(int, int, int, int, int, int)> add_seg_odd;
    
    add_seg_even = [&](int source, int l, int r, int node, int segl, int segr) {
        if (r < segl || segr < l) return;
        if (l <= segl && segr <= r) {
            graph[source].push_back(seg_even_base + node);
            return;
        }
        int mid = (segl + segr) >> 1;
        add_seg_even(source, l, r, node << 1, segl, mid);
        add_seg_even(source, l, r, node << 1 | 1, mid + 1, segr);
    };
    
    add_seg_odd = [&](int source, int l, int r, int node, int segl, int segr) {
        if (r < segl || segr < l) return;
        if (l <= segl && segr <= r) {
            graph[source].push_back(seg_odd_base + node);
            return;
        }
        int mid = (segl + segr) >> 1;
        add_seg_odd(source, l, r, node << 1, segl, mid);
        add_seg_odd(source, l, r, node << 1 | 1, mid + 1, segr);
    };
    
    for (int k = 0; k < m; k++) {
        int type, l, r, j;
        cin >> type >> l >> r >> j;
        l--; r--; j--;
        int len = r - l + 1;
        
        if ((type == 0 && len % 2 == 0) || (type == 1 && len % 2 == 1)) {
            if (type == 0) {
                add_seg_even(2 * j, l, r, 1, 0, size - 1);
            } else {
                add_seg_odd(2 * j + 1, l, r, 1, 0, size - 1);
            }
        }
    }
    
    graph_t.resize(total_nodes);
    for (int u = 0; u < total_nodes; u++) {
        for (int v : graph[u]) {
            graph_t[v].push_back(u);
        }
    }
    
    visited.assign(total_nodes, false);
    order.clear();
    for (int i = 0; i < total_nodes; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }
    
    comp.assign(total_nodes, -1);
    int cid = 0;
    reverse(order.begin(), order.end());
    for (int u : order) {
        if (comp[u] == -1) {
            dfs2(u, cid++);
        }
    }
    
    bool sat = true;
    for (int i = 0; i < n; i++) {
        if (comp[2 * i] == comp[2 * i + 1]) {
            sat = false;
            break;
        }
    }
    
    cout << (sat ? "YES" : "NO") << '\n';
    
    return 0;
}