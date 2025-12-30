#include <bits/stdc++.h>
using namespace std;

int main() {
    // Seed random generator
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    
    // Random parameters within constraints
    int n = uniform_int_distribution<int>(1, 50)(rng);
    int m = uniform_int_distribution<int>(1, 50)(rng);
    int q = uniform_int_distribution<int>(1, 1000)(rng);
    
    // Output first line
    cout << n << " " << m << " " << q << "\n";
    
    // Generate project resource requirements
    vector<string> projects(n);
    for (int i = 0; i < n; i++) {
        string req(m, '0');
        // Ensure at least one '1' per project
        int ones = uniform_int_distribution<int>(1, m)(rng);
        vector<int> positions(m);
        iota(positions.begin(), positions.end(), 0);
        shuffle(positions.begin(), positions.end(), rng);
        
        for (int j = 0; j < ones; j++) {
            req[positions[j]] = '1';
        }
        projects[i] = req;
        cout << req << "\n";
    }
    
    // Generate resource capacities
    for (int j = 0; j < m; j++) {
        cout << uniform_int_distribution<int>(1, 10000)(rng);
        if (j < m - 1) cout << " ";
    }
    cout << "\n";
    
    // Generate demands for each time point
    for (int t = 0; t < q; t++) {
        for (int i = 0; i < n; i++) {
            cout << uniform_int_distribution<int>(0, 10000)(rng);
            if (i < n - 1) cout << " ";
        }
        cout << "\n";
    }
    
    return 0;
}