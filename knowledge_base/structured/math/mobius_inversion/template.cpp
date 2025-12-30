#include <vector>
#include <algorithm>
using namespace std;

// Compute mu[1..n] using linear sieve
vector<int> get_mu(int n) {
    vector<int> mu(n + 1, 0);
    vector<int> primes;
    vector<bool> not_prime(n + 1, false);
    mu[1] = 1;
    for (int x = 2; x <= n; ++x) {
        if (!not_prime[x]) {
            primes.push_back(x);
            mu[x] = -1;
        }
        for (int p : primes) {
            if (x * p > n) break;
            not_prime[x * p] = true;
            if (x % p == 0) {
                mu[x * p] = 0;
                break;
            } else {
                mu[x * p] = -mu[x];
            }
        }
    }
    return mu;
}

// Dirichlet prefix sum: f[n] = sum_{d|n} g[d]
vector<long long> dirichlet_presum(const vector<long long>& g) {
    int n = g.size() - 1;
    vector<long long> f(g);
    vector<bool> vis(n + 1, false);
    for (int x = 2; x <= n; ++x) {
        if (vis[x]) continue;
        for (int y = 1, xy = x; xy <= n; ++y, xy += x) {
            vis[xy] = true;
            f[xy] += f[y];
        }
    }
    return f;
}

// Dirichlet difference: g[n] = sum_{d|n} mu[n/d] * f[d]
vector<long long> dirichlet_diff(const vector<long long>& f) {
    int n = f.size() - 1;
    vector<long long> g(f);
    vector<bool> vis(n + 1, false);
    for (int x = 2; x <= n; ++x) {
        if (vis[x]) continue;
        for (int y = n / x, xy = x * y; y; --y, xy -= x) {
            vis[xy] = true;
            g[xy] -= g[y];
        }
    }
    return g;
}

// Example: count pairs (i,j) with 1<=i<=n, 1<=j<=m, gcd(i,j)=k
long long count_gcd_pairs(int n, int m, int k, const vector<int>& mu_prefix) {
    n /= k, m /= k;
    long long ans = 0;
    for (int l = 1, r; l <= min(n, m); l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        ans += (long long)(mu_prefix[r] - mu_prefix[l - 1]) * (n / l) * (m / l);
    }
    return ans;
}