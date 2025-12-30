#include <vector>
#include <cstring>
using namespace std;

const int MOD = 1000007;

// Compute partition number p(n) using pentagonal number theorem O(n sqrt(n))
vector<long long> partition_numbers(int n) {
    vector<long long> p(n + 1, 0);
    p[0] = 1;
    if (n >= 1) p[1] = 1;
    if (n >= 2) p[2] = 2;
    
    // Precompute pentagonal numbers
    vector<int> pent;
    for (int k = 1; k * (3 * k - 1) / 2 <= n; k++) {
        pent.push_back(k * (3 * k - 1) / 2);
        pent.push_back(k * (3 * k + 1) / 2);
    }
    
    for (int i = 3; i <= n; i++) {
        long long sum = 0;
        for (int j = 0; j < pent.size() && pent[j] <= i; j++) {
            if ((j / 2) % 2 == 0) {  // Even index (positive sign)
                sum = (sum + p[i - pent[j]]) % MOD;
            } else {  // Odd index (negative sign)
                sum = (sum - p[i - pent[j]] + MOD) % MOD;
            }
        }
        p[i] = sum;
    }
    return p;
}

// Compute k-partition numbers p(n, k) using DP O(nk)
vector<vector<int>> k_partition_numbers(int max_n, int max_k) {
    vector<vector<int>> p(max_n + 1, vector<int>(max_k + 1, 0));
    p[0][0] = 1;
    
    for (int i = 1; i <= max_n; i++) {
        for (int j = 1; j <= max_k; j++) {
            if (i - j >= 0) {
                p[i][j] = (p[i - j][j] + p[i - 1][j - 1]) % MOD;
            }
        }
    }
    return p;
}

// Compute distinct partition numbers pd(n) using DP O(n sqrt(n))
vector<int> distinct_partition_numbers(int n) {
    vector<vector<int>> pd(n + 1, vector<int>(2, 0));
    pd[0][0] = 1;
    int ans = 0;
    
    for (int j = 1; j * (j + 1) / 2 <= n; j++) {  // At most O(sqrt(n)) parts
        int cur = j & 1;
        int prev = cur ^ 1;
        
        for (int i = 0; i <= n; i++) {
            pd[i][cur] = 0;
        }
        
        for (int i = 0; i <= n; i++) {
            if (i - j >= 0) {
                pd[i][cur] = (pd[i - j][cur] + pd[i - j][prev]) % MOD;
            }
        }
        ans = (ans + pd[n][cur]) % MOD;
    }
    
    vector<int> result(n + 1, 0);
    // For full distinct partition numbers, need to compute for all n
    // This returns just the value for input n
    result[n] = ans;
    return result;
}