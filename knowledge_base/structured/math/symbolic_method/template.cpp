#include <bits/stdc++.h>
using namespace std;

// Example: Generating function for ordered rooted trees (Catalan numbers)
// T(z) = z / (1 - T(z)) => T(z) = (1 - sqrt(1 - 4z)) / 2
// Returns nth Catalan number modulo MOD
const int MOD = 998244353;

long long mod_pow(long long a, long long e) {
    long long res = 1;
    while (e) {
        if (e & 1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

long long mod_inv(long long x) {
    return mod_pow(x, MOD - 2);
}

// Binomial coefficient for Catalan: C(2n, n) / (n + 1)
long long catalan(int n) {
    if (n == 0) return 1;
    long long num = 1, den = 1;
    for (int i = 1; i <= n; i++) {
        num = num * (2 * n - i + 1) % MOD;
        den = den * i % MOD;
    }
    den = den * (n + 1) % MOD;
    return num * mod_inv(den) % MOD;
}

// Example: Partition numbers (Euler transform) using OGF
// P(z) = exp(∑_{k≥1} σ(k) * z^k / k) where σ(k) = sum of divisors? Actually for partitions:
// P(z) = ∏_{k≥1} 1 / (1 - z^k)
vector<long long> partition_numbers(int n) {
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    for (int k = 1; k <= n; k++) {
        for (int i = k; i <= n; i++) {
            dp[i] = (dp[i] + dp[i - k]) % MOD;
        }
    }
    return dp;
}

int main() {
    // Example usage
    int n = 10;
    cout << "Catalan numbers:\n";
    for (int i = 0; i <= n; i++) {
        cout << catalan(i) << ' ';
    }
    cout << "\nPartition numbers:\n";
    auto parts = partition_numbers(n);
    for (int i = 0; i <= n; i++) {
        cout << parts[i] << ' ';
    }
    return 0;
}