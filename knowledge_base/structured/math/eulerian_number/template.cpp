#include <vector>
using namespace std;

// Compute Eulerian numbers A(n, m) for 0 <= m < n
// Returns a 2D vector dp where dp[n][m] = A(n, m)
vector<vector<long long>> eulerian_numbers(int max_n) {
    vector<vector<long long>> dp(max_n + 1, vector<long long>(max_n + 1, 0));
    dp[0][0] = 1; // Base case
    for (int n = 1; n <= max_n; ++n) {
        for (int m = 0; m < n; ++m) {
            if (m == 0) {
                dp[n][m] = 1; // Only descending permutation
            } else {
                // Recurrence: A(n, m) = (n - m) * A(n-1, m-1) + (m + 1) * A(n-1, m)
                dp[n][m] = (n - m) * dp[n-1][m-1] + (m + 1) * dp[n-1][m];
            }
        }
    }
    return dp;
}

// Example usage: get A(n, m)
long long eulerian_number(int n, int m) {
    if (m >= n || n == 0) return 0;
    auto dp = eulerian_numbers(n);
    return dp[n][m];
}