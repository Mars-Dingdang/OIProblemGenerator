#include <bits/stdc++.h>
using namespace std;

// Example template for a simple forward probability DP
// Problem: Bag of mice (CF 148D)
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int w, b;
    cin >> w >> b;
    vector<vector<double>> dp(w + 1, vector<double>(b + 1, 0.0));
    
    // Initialize boundaries
    for (int i = 1; i <= w; i++) dp[i][0] = 1.0;
    for (int j = 1; j <= b; j++) dp[0][j] = 0.0;
    
    // Forward DP for probability
    for (int i = 1; i <= w; i++) {
        for (int j = 1; j <= b; j++) {
            // Princess draws white
            dp[i][j] += (double)i / (i + j);
            
            // Both draw black, black escapes
            if (j >= 3) {
                dp[i][j] += (double)j / (i + j) * (j - 1) / (i + j - 1) * 
                           (j - 2) / (i + j - 2) * dp[i][j - 3];
            }
            
            // Both draw black, white escapes
            if (i >= 1 && j >= 2) {
                dp[i][j] += (double)j / (i + j) * (j - 1) / (i + j - 1) * 
                           i / (i + j - 2) * dp[i - 1][j - 2];
            }
        }
    }
    
    cout << fixed << setprecision(9) << dp[w][b] << '\n';
    return 0;
}