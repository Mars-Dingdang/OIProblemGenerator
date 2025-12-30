#include <bits/stdc++.h>
using namespace std;

// Example: Count the number of ways to partition n into k positive integers (order matters).
// dp[n][k] = number of ordered partitions of n into k positive integers.
long long countOrderedPartitions(int n, int k) {
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));
    // Base case: partition 0 into 0 parts is 1 (empty tuple).
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            // dp[i][j] = sum_{x=1}^{i-j+1} dp[i-x][j-1]
            for (int x = 1; x <= i - j + 1; ++x) {
                dp[i][j] += dp[i - x][j - 1];
            }
        }
    }
    return dp[n][k];
}

// Example: Count the number of ways to partition n into positive integers (order does NOT matter).
// dp[n][m] = number of unordered partitions of n using numbers <= m.
long long countUnorderedPartitions(int n) {
    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
    for (int m = 0; m <= n; ++m) dp[0][m] = 1; // base: sum 0 can be formed by empty set.
    for (int i = 1; i <= n; ++i) {
        for (int m = 1; m <= n; ++m) {
            dp[i][m] = dp[i][m - 1]; // partitions without using m
            if (i >= m) {
                // partitions using m: can use m multiple times, so recurse on i-m with same m
                dp[i][m] += dp[i - m][m];
            }
        }
    }
    return dp[n][n];
}

int main() {
    int n = 5, k = 3;
    cout << "Ordered partitions of " << n << " into " << k << " parts: " << countOrderedPartitions(n, k) << endl;
    cout << "Unordered partitions of " << n << ": " << countUnorderedPartitions(n) << endl;
    return 0;
}