#include <vector>
#include <iostream>
using namespace std;

const int MAXN = 1e5 + 5;
vector<pair<int, int>> G[MAXN]; // to, weight
int n;

double f[MAXN]; // f[u]: expected distance from u to parent
double g[MAXN]; // g[u]: expected distance from parent to u

double w(int u, int v) {
    for (auto &e : G[u]) {
        if (e.first == v) return e.second;
    }
    return 0;
}

void dfs_f(int u, int parent) {
    f[u] = 0;
    double sum = 0;
    int deg = G[u].size();
    for (auto &e : G[u]) {
        int v = e.first;
        if (v == parent) continue;
        dfs_f(v, u);
        sum += e.second + f[v];
    }
    f[u] = (w(u, parent) * deg + sum) / deg;
    // Actually simplified version: f[u] = w(u, parent) + sum, but only if derived correctly
    // Correct derivation in unit weight: f[u] = 1 + sum over children f[v]
}

void dfs_g(int u, int parent) {
    if (parent != -1) {
        double sibling_sum = 0;
        int p_deg = G[parent].size();
        for (auto &e : G[parent]) {
            int s = e.first;
            if (s == u || s == parent) continue; // skip self and grandparent
            sibling_sum += e.second + f[s];
        }
        double parent_edge = (parent == 1 ? 0 : w(parent, parent));
        g[u] = (w(parent, u) + 
                (parent == 1 ? 0 : (parent_edge + g[parent])) + 
                sibling_sum) / p_deg;
        // Simplified known form: g[u] = g[parent] + f[parent] - f[u];
        // But this requires proper base derivation
    }
    for (auto &e : G[u]) {
        int v = e.first;
        if (v != parent) {
            dfs_g(v, u);
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, weight = 1;
        cin >> u >> v;
        G[u].push_back({v, weight});
        G[v].push_back({u, weight});
    }
    dfs_f(1, 0);
    g[1] = 0;
    dfs_g(1, 0);
    // Example: print expected distance from node 2 to its parent
    cout << "f[2] = " << f[2] << '\n';
    return 0;
}