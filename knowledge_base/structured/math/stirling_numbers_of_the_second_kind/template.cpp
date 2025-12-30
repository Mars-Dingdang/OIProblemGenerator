#include <vector>
#include <iostream>
using namespace std;
using ll = long long;

// DP for S(n,k) mod MOD, O(n^2)
vector<vector<ll>> stirling2_dp(int n, int k, ll MOD = 1e9+7) {
    vector<vector<ll>> dp(n+1, vector<ll>(k+1, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= min(i, k); ++j) {
            dp[i][j] = (dp[i-1][j-1] + j * dp[i-1][j]) % MOD;
        }
    }
    return dp;
}

// Single row S(n,0..n) via convolution O(n log n) (requires NTT/FFT)
// Using formula: S(n,m) = (1/m!) Σ_{i=0}^{m} (-1)^{m-i} C(m,i) i^n
// Let A[i] = (-1)^i / i!, B[i] = i^n / i!, then S row = convolution(A,B)
// Implementation depends on polynomial library with NTT.

// Quick access for small n (precomputed)
ll stirling2(int n, int k) {
    if (k > n) return 0;
    if (k == 0) return (n == 0) ? 1 : 0;
    if (k == 1 || k == n) return 1;
    // Use DP or formula
    static vector<vector<ll>> dp;
    if ((int)dp.size() <= n) dp.resize(n+1);
    if (dp[n].empty()) dp[n].resize(n+1, -1);
    if (dp[n][k] != -1) return dp[n][k];
    return dp[n][k] = stirling2(n-1, k-1) + k * stirling2(n-1, k);
}

int main() {
    // Example usage
    int n = 5, k = 2;
    auto dp = stirling2_dp(n, k);
    cout << "S(" << n << "," << k << ") = " << dp[n][k] << endl;
    return 0;
}