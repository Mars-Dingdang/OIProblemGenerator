#include <bits/stdc++.h>
using namespace std;

const long long INF = 1000000001;

int main() {
    cin.tie(0); 
    ios::sync_with_stdio(0);
    
    int n, m, q;
    cin >> n >> m >> q;
    int total_nodes = 2 * n + 10;
    vector<long long> val(total_nodes, 0);
    vector<int> dsu_rep(total_nodes);
    for (int i = 0; i < total_nodes; i++) {
        dsu_rep[i] = i;
    }
    vector<unordered_set<int>> sets(total_nodes);
    vector<int> distinct(total_nodes, 0);
    vector<int> parent_tree(total_nodes, -1);

    vector<int> color(n);
    for (int i = 0; i < n; i++) {
        cin >> color[i];
        sets[i].insert(color[i]);
        distinct[i] = 1;
    }

    vector<tuple<long long, int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--; v--;
        edges.push_back({w, u, v});
    }
    sort(edges.begin(), edges.end());

    int node_count = n;

    function<int(int)> find = [&](int u) {
        if (dsu_rep[u] != u) {
            dsu_rep[u] = find(dsu_rep[u]);
        }
        return dsu_rep[u];
    };

    for (auto &e : edges) {
        long long w = get<0>(e);
        int u = get<1>(e);
        int v = get<2>(e);
        int ru = find(u);
        int rv = find(v);
        if (ru == rv) continue;

        val[node_count] = w;
        parent_tree[ru] = node_count;
        parent_tree[rv] = node_count;

        if (sets[ru].size() < sets[rv].size()) {
            swap(ru, rv);
        }
        int cnt = sets[ru].size();
        for (int c : sets[rv]) {
            if (sets[ru].find(c) == sets[ru].end()) {
                cnt++;
                sets[ru].insert(c);
            }
        }
        sets[node_count] = move(sets[ru]);
        distinct[node_count] = cnt;

        dsu_rep[ru] = node_count;
        dsu_rep[rv] = node_count;
        dsu_rep[node_count] = node_count;
        node_count++;
    }

    int root_all = node_count;
    val[root_all] = INF;
    for (int i = 0; i < node_count; i++) {
        if (dsu_rep[i] == i) {
            parent_tree[i] = root_all;
        }
    }
    parent_tree[root_all] = -1;

    int total_nodes_used = root_all + 1;
    vector<vector<int>> children(total_nodes_used);
    for (int i = 0; i < total_nodes_used; i++) {
        if (parent_tree[i] != -1) {
            children[parent_tree[i]].push_back(i);
        }
    }

    vector<int> depth(total_nodes_used, -1);
    queue<int> q_bfs;
    depth[root_all] = 0;
    q_bfs.push(root_all);
    while (!q_bfs.empty()) {
        int u = q_bfs.front(); q_bfs.pop();
        for (int v : children[u]) {
            depth[v] = depth[u] + 1;
            q_bfs.push(v);
        }
    }

    int LOG = 20;
    vector<vector<int>> up(total_nodes_used, vector<int>(LOG, -1));
    for (int i = 0; i < total_nodes_used; i++) {
        up[i][0] = parent_tree[i];
    }
    for (int j = 1; j < LOG; j++) {
        for (int i = 0; i < total_nodes_used; i++) {
            if (up[i][j-1] != -1) {
                up[i][j] = up[up[i][j-1]][j-1];
            }
        }
    }

    while (q--) {
        int u;
        long long x;
        cin >> u >> x;
        u--;
        int cur = u;
        for (int j = LOG-1; j >= 0; j--) {
            if (up[cur][j] != -1) {
                int anc = up[cur][j];
                if (val[anc] <= x) {
                    cur = anc;
                }
            }
        }
        cout << distinct[cur] << '\n';
    }

    return 0;
}