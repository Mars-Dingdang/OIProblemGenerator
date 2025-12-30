#include <bits/stdc++.h>
using namespace std;

int main() {
    // Seed random number generator
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    
    // Random n between 1 and 200000
    int n = uniform_int_distribution<int>(1, 200000)(rng);
    cout << n << "\n";
    
    // Generate n random a_i values between 1 and 1e9
    for (int i = 0; i < n; i++) {
        cout << uniform_int_distribution<long long>(1, 1000000000)(rng);
        if (i < n - 1) cout << " ";
    }
    cout << "\n";
    
    // Generate a valid tree rooted at 1
    // We'll create a random permutation of nodes 2..n and assign each a random parent from earlier nodes
    vector<int> nodes(n - 1);
    iota(nodes.begin(), nodes.end(), 2);
    shuffle(nodes.begin(), nodes.end(), rng);
    
    vector<int> parent(n + 1, 0);
    parent[1] = -1;  // root has no parent
    
    // For each node, choose a random parent from already processed nodes (including 1)
    for (int node : nodes) {
        // Choose parent from [1, node-1]
        int p = uniform_int_distribution<int>(1, node - 1)(rng);
        
        // Ensure we don't create cycles by checking if p is already in the tree
        // Since we process nodes in increasing order, p will always be processed before node
        parent[node] = p;
        cout << p << " " << node << "\n";
    }
    
    // Random q between 1 and 200000
    int q = uniform_int_distribution<int>(1, 200000)(rng);
    cout << q << "\n";
    
    // Generate q random operations
    for (int i = 0; i < q; i++) {
        int type = uniform_int_distribution<int>(1, 2)(rng);
        
        if (type == 1) {
            // Update operation: 1 x v
            int x = uniform_int_distribution<int>(1, n)(rng);
            int v = uniform_int_distribution<long long>(1, 1000000000)(rng);
            cout << "1 " << x << " " << v << "\n";
        } else {
            // Query operation: 2 s T
            int s = uniform_int_distribution<int>(1, n)(rng);
            int T = uniform_int_distribution<long long>(1, 1000000000)(rng);
            cout << "2 " << s << " " << T << "\n";
        }
    }
    
    return 0;
}