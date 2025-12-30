#include <bits/stdc++.h>
using namespace std;

// 0/1 knapsack - standard version
int knapsack_01(vector<int>& weights, vector<int>& values, int capacity) {
    int n = weights.size();
    vector<int> dp(capacity + 1, 0);
    
    for (int i = 0; i < n; i++) {
        for (int j = capacity; j >= weights[i]; j--) {
            dp[j] = max(dp[j], dp[j - weights[i]] + values[i]);
        }
    }
    return dp[capacity];
}

// K-th best knapsack (as shown in the text)
int kth_best_knapsack(vector<int>& weights, vector<int>& values, int capacity, int K) {
    int n = weights.size();
    vector<vector<int>> dp(capacity + 1, vector<int>(K + 1, 0));
    vector<int> a(K + 2), b(K + 2);
    
    for (int i = 0; i < n; i++) {
        for (int j = capacity; j >= weights[i]; j--) {
            for (int p = 1; p <= K; p++) {
                a[p] = dp[j - weights[i]][p] + values[i];
                b[p] = dp[j][p];
            }
            a[K + 1] = b[K + 1] = -1;
            
            int x = 1, y = 1, z = 1;
            while (z <= K && (a[x] != -1 || b[y] != -1)) {
                if (a[x] > b[y]) {
                    dp[j][z] = a[x++];
                } else {
                    dp[j][z] = b[y++];
                }
                if (dp[j][z] != dp[j][z - 1]) z++;
            }
        }
    }
    return dp[capacity][K];
}

int main() {
    // Example usage
    vector<int> weights = {2, 3, 4, 5};
    vector<int> values = {3, 4, 5, 6};
    int capacity = 5;
    
    cout << "0/1 Knapsack result: " << knapsack_01(weights, values, capacity) << endl;
    
    int K = 3;
    cout << "K-th best (K=" << K << "): " << kth_best_knapsack(weights, values, capacity, K) << endl;
    
    return 0;
}