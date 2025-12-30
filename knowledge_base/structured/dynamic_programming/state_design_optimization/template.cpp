#include <bits/stdc++.h>
using namespace std;

// Example: LCS with n up to 1e6, m up to 1e3
int lcs_optimized(const string& A, const string& B) {
    int n = A.size(), m = B.size();
    // dp[j] stores the length of LCS for current prefix of A and prefix of B up to j
    vector<int> dp(m + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int prev = 0; // dp[i-1][j-1] from previous row
        for (int j = 1; j <= m; ++j) {
            int temp = dp[j]; // store current dp[j] before update
            if (A[i-1] == B[j-1]) {
                dp[j] = prev + 1;
            } else {
                dp[j] = max(dp[j], dp[j-1]);
            }
            prev = temp; // update prev for next iteration
        }
    }
    return dp[m];
}

int main() {
    string A, B;
    cin >> A >> B;
    cout << lcs_optimized(A, B) << endl;
    return 0;
}