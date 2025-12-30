#include <bits/stdc++.h>
using namespace std;

int main() {
    // Example: Count ways to place K kings on N x N board (SCOI2005)
    int n, k;
    cin >> n >> k;
    
    // Precompute all valid states for a single row and their king counts
    vector<int> states;   // list of bitmasks
    vector<int> cnt_ones; // number of kings in each state
    
    // DFS to generate states where no two adjacent bits are 1
    function<void(int, int, int)> dfs = [&](int mask, int count, int pos) {
        if (pos >= n) {
            states.push_back(mask);
            cnt_ones.push_back(count);
            return;
        }
        // Option 1: don't place king at pos
        dfs(mask, count, pos + 1);
        // Option 2: place king at pos (skip next position to avoid adjacent)
        dfs(mask | (1 << pos), count + 1, pos + 2);
    };
    dfs(0, 0, 0);
    
    int m = states.size();
    // dp[row][state_index][kings_used]
    vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(m, vector<long long>(k + 1, 0)));
    
    // Initialize first row
    for (int i = 0; i < m; ++i) {
        if (cnt_ones[i] <= k) {
            dp[1][i][cnt_ones[i]] = 1;
        }
    }
    
    // Transition
    for (int row = 2; row <= n; ++row) {
        for (int cur = 0; cur < m; ++cur) {
            for (int prev = 0; prev < m; ++prev) {
                // Check vertical and diagonal attacks
                if ((states[cur] & states[prev]) || ((states[cur] << 1) & states[prev]) || (states[cur] & (states[prev] << 1))) {
                    continue;
                }
                for (int used = cnt_ones[cur]; used <= k; ++used) {
                    dp[row][cur][used] += dp[row - 1][prev][used - cnt_ones[cur]];
                }
            }
        }
    }
    
    // Sum over all states in last row with exactly k kings
    long long ans = 0;
    for (int i = 0; i < m; ++i) {
        ans += dp[n][i][k];
    }
    cout << ans << endl;
    
    return 0;
}