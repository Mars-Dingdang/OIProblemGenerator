#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;

ll fact[MAXN], invfact[MAXN];

ll modpow(ll a, ll e) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

void precompute(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % MOD;
    invfact[n] = modpow(fact[n], MOD-2);
    for (int i = n-1; i >= 0; i--) invfact[i] = invfact[i+1] * (i+1) % MOD;
}

ll C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invfact[k] % MOD * invfact[n-k] % MOD;
}

// Vandermonde convolution: sum_{i=0}^{k} C(n, i) * C(m, k-i) = C(n+m, k)
ll vandermonde(int n, int m, int k) {
    return C(n + m, k);
}

int main() {
    precompute(MAXN - 1);
    // Example usage
    int n = 5, m = 3, k = 4;
    ll direct = 0;
    for (int i = 0; i <= k; i++) {
        direct = (direct + C(n, i) * C(m, k-i)) % MOD;
    }
    ll conv = vandermonde(n, m, k);
    cout << "Direct sum: " << direct << endl;
    cout << "Vandermonde: " << conv << endl;
    return 0;
}