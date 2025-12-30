#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    
    // Generate n, m, q within [1, 200000] but n at least 2 to avoid m=0 conflict
    int n = uniform_int_distribution<int>(2, 200000)(rng);
    int m_original = uniform_int_distribution<int>(1, 200000)(rng);
    int q = uniform_int_distribution<int>(1, 200000)(rng);
    
    // Adjust m to not exceed max possible edges
    ll max_edges = (ll)n * (n-1) / 2;
    int m = min((ll)m_original, max_edges);
    
    // Generate initial colors for n towns (each in [1, 10^9])
    vector<int> colors(n);
    uniform_int_distribution<int> color_dist(1, 1000000000);
    for (int i = 0; i < n; ++i) {
        colors[i] = color_dist(rng);
    }
    
    // Pre-generate distinct edge weights for m edges
    set<ll> weight_set;
    uniform_int_distribution<ll> weight_dist(1, 1000000000);
    while (weight_set.size() < m) {
        ll w = weight_dist(rng);
        weight_set.insert(w);
    }
    vector<ll> distinct_weights(weight_set.begin(), weight_set.end());
    shuffle(distinct_weights.begin(), distinct_weights.end(), rng);
    
    // Generate edges (avoiding self-loops and duplicate edges)
    set<pair<int, int>> edge_set;
    vector<tuple<int, int, ll>> edges;
    uniform_int_distribution<int> node_dist(0, n-1);
    
    for (int i = 0; i < m; ) {
        int u = node_dist(rng);
        int v = node_dist(rng);
        if (u == v) continue;
        if (u > v) swap(u, v);
        if (edge_set.count({u, v})) continue;
        
        edge_set.insert({u, v});
        edges.emplace_back(u+1, v+1, distinct_weights[i]);
        ++i;
    }
    
    // Generate queries: update town u to color x
    vector<pair<int, int>> queries;
    uniform_int_distribution<int> node_dist2(1, n);
    for (int i = 0; i < q; ++i) {
        int u = node_dist2(rng);
        int x = color_dist(rng);
        queries.emplace_back(u, x);
    }
    
    // Output the test case
    cout << n << " " << m << " " << q << "\n";
    for (int i = 0; i < n; ++i) {
        if (i > 0) cout << " ";
        cout << colors[i];
    }
    cout << "\n";
    
    for (const auto& e : edges) {
        cout << get<0>(e) << " " << get<1>(e) << " " << get<2>(e) << "\n";
    }
    
    for (const auto& qry : queries) {
        cout << qry.first << " " << qry.second << "\n";
    }
    
    return 0;
}