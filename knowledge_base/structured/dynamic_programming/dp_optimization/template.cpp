#include <bits/stdc++.h>
using namespace std;

// Example: Knapsack with swapped dimensions (value as state)
// Problem: n items, volume v[i], value w[i], max capacity M
// Find: minimum volume to achieve value j
long long knapsack_swapped(const vector<long long>& v, const vector<int>& w, int n, int total_value) {
    const long long INF = 1e18;
    vector<long long> dp(total_value + 1, INF);
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = total_value; j >= w[i]; --j) {
            if (dp[j - w[i]] != INF) {
                dp[j] = min(dp[j], dp[j - w[i]] + v[i]);
            }
        }
    }
    // Find maximum value where volume <= M
    int ans = 0;
    for (int j = total_value; j >= 0; --j) {
        if (dp[j] <= M) {
            ans = j;
            break;
        }
    }
    return ans;
}

// Example: Hamiltonian cycle detection with bitmask compression
// n <= 20, graph adjacency matrix g
bool hamiltonian_cycle(const vector<vector<bool>>& g, int n) {
    vector<int> dp(1 << n, 0);
    dp[1] = 1; // start from node 0 (bit 0 set)
    for (int mask = 1; mask < (1 << n); ++mask) {
        if (!dp[mask]) continue;
        for (int i = 0; i < n; ++i) {
            if (!(mask >> i & 1)) continue;
            for (int j = 0; j < n; ++j) {
                if (mask >> j & 1) continue;
                if (g[i][j]) {
                    dp[mask | (1 << j)] |= dp[mask];
                }
            }
        }
    }
    // Check if we can return to start (node 0) from all nodes visited
    int full = (1 << n) - 1;
    if (!dp[full]) return false;
    for (int i = 0; i < n; ++i) {
        if (g[i][0] && (dp[full] >> i & 1)) {
            return true;
        }
    }
    return false;
}