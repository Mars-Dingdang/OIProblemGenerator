#include <bits/stdc++.h>
using namespace std;

// Longest Common Subsequence (LCS)
int lcs(const vector<int>& A, const vector<int>& B) {
    int n = A.size(), m = B.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

// Longest Increasing Subsequence (LIS) O(n log n)
int lis(const vector<int>& a) {
    vector<int> d; // d[i]: smallest ending value of LIS of length i+1
    for (int x : a) {
        auto it = lower_bound(d.begin(), d.end(), x); // use upper_bound for non-decreasing
        if (it == d.end()) d.push_back(x);
        else *it = x;
    }
    return d.size();
}

// Number Triangle (example)
int maxPathSum(const vector<vector<int>>& tri) {
    int r = tri.size();
    vector<vector<int>> dp = tri; // copy
    for (int i = r - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            dp[i][j] += max(dp[i + 1][j], dp[i + 1][j + 1]);
        }
    }
    return dp[0][0];
}

int main() {
    // Example usage
    vector<int> A = {1, 2, 3, 4, 5};
    vector<int> B = {2, 4, 5, 3, 1};
    cout << "LCS length: " << lcs(A, B) << endl;
    cout << "LIS length: " << lis(A) << endl;
    return 0;
}