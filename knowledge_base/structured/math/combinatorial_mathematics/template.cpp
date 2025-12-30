#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;

// Example: Counting labeled trees with Cayley's formula: n^{n-2}
ll count_labeled_trees(int n) {
    if (n <= 1) return 1;
    ll ans = 1;
    for (int i = 0; i < n - 2; ++i) {
        ans = (ans * n) % MOD;
    }
    return ans;
}

// Example: Binomial coefficient with precomputed factorials
vector<ll> fact, inv_fact;
ll mod_pow(ll a, ll e) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}
void precompute_factorials(int n) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = fact[i-1] * i % MOD;
    inv_fact[n] = mod_pow(fact[n], MOD - 2);
    for (int i = n-1; i >= 0; --i) inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
}
ll C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

int main() {
    int n = 5;
    precompute_factorials(n);
    cout << "Labeled trees for n=" << n << ": " << count_labeled_trees(n) << endl;
    cout << "C(5,2) = " << C(5, 2) << endl;
    return 0;
}