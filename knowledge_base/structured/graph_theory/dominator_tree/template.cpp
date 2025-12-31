struct DominatorTree {
    int n;
    vector<vector<int>> G, GT, bucket;
    vector<int> sdom, dom, dsu, label;
    vector<vector<int>> children;
    vector<int> dfs_order, parent, idom;
    int cur_time = 0;

    DominatorTree(int _n) : n(_n), G(n), GT(n), bucket(n),
        sdom(n), dom(n), dsu(n), label(n), children(n),
        dfs_order(n), parent(n, -1), idom(n, -1) {
        iota(dsu.begin(), dsu.end(), 0);
        iota(label.begin(), label.end(), 0);
    }

    void add_edge(int u, int v) {
        G[u].push_back(v);
        GT[v].push_back(u);
    }

    void dfs(int u) {
        dfs_order[cur_time] = u;
        sdom[u] = cur_time++;
        for (int v : G[u]) {
            if (sdom[v] == -1) {
                parent[v] = u;
                dfs(v);
            }
        }
    }

    int find_root(int u, const function<int(int)> &eval) {
        if (dsu[u] == u) return u;
        int r = find_root(dsu[u], eval);
        if (r != dsu[u]) {
            if (sdom[label[dsu[u]]] < sdom[label[u]])
                label[u] = label[dsu[u]];
            dsu[u] = r;
        }
        return dsu[u];
    }

    void unite(int u, int v) {
        dsu[v] = u;
    }

    vector<int> build(int root) {
        // Initialize
        fill(sdom.begin(), sdom.end(), -1);
        cur_time = 0;
        dfs(root);

        // Reverse DFS order processing
        for (int i = cur_time - 1; i >= 1; i--) {
            int w = dfs_order[i];
            // Case 1: direct edge (v, w)
            for (int v : GT[w]) {
                if (sdom[v] != -1) { // v already visited
                    int anc = find_root(v, [&](int x){return x;});
                    if (sdom[label[anc]] < sdom[w])
                        sdom[w] = sdom[label[anc]];
                }
            }

            bucket[dfs_order[sdom[w]]].push_back(w);

            if (i > 1) {
                // Resolve bucket of current node
                int pw = parent[w];
                for (int x : bucket[pw]) {
                    int anc = find_root(x, [&](int x){return x;});
                    int p = label[anc];
                    dom[x] = (sdom[p] == sdom[x]) ? p : p;
                }
                bucket[pw].clear();
                unite(parent[w], w);
            }
        }

        // Finalize idom
        idom[root] = root;
        for (int i = 1; i < cur_time; i++) {
            int w = dfs_order[i];
            if (dom[w] != dfs_order[sdom[w]])
                idom[w] = idom[dom[w]];
            else
                idom[w] = dfs_order[sdom[w]];
        }

        return idom;
    }
};