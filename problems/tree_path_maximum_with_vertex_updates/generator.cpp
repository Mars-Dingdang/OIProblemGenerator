```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    // Initialize random seed
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    mt19937_64 rng(seed);

    // Generate n and q (use max constraints for a strong test)
    int n = 200000;
    int q = 200000;
    
    // Output n and q
    cout << n << " " << q << endl;
    
    // Generate initial vertex values
    uniform_int_distribution<long long> val_dist(-1e9, 1e9);
    for (int i = 0; i < n; i++) {
        cout << val_dist(rng);
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    // Generate random tree edges (connected graph)
    // Use simple method: connect vertex i to random previous vertex
    for (int i = 2; i <= n; i++) {
        uniform_int_distribution<int> parent_dist(1, i - 1);
        int parent = parent_dist(rng);
        cout << parent << " " << i << endl;
    }
    
    // Generate queries
    uniform_int_distribution<int> type_dist(1, 2);
    uniform_int_distribution<int> vertex_dist(1, n);
    
    for (int i = 0; i < q; i++) {
        int type = type_dist(rng);
        
        if (type == 1) {
            // Type 1: update query
            int v = vertex_dist(rng);
            long long x = val_dist(rng);
            cout << "1 " << v << " " << x << endl;
        } else {
            // Type 2: path query
            int u = vertex_dist(rng);
            int v = vertex_dist(rng);
            cout << "2 " << u << " " << v << endl;
        }
    }
    
    return 0;
}
```