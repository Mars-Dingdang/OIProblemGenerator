#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;

ll fact[MAXN], inv_fact[MAXN];

ll mod_pow(ll a, ll e) {
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
    inv_fact[n] = mod_pow(fact[n], MOD-2);
    for (int i = n-1; i >= 0; i--) inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
}

ll C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n-k] % MOD;
}

ll P(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv_fact[n-k] % MOD;
}

ll stars_and_bars(int n, int k, bool positive = true) {
    // number of solutions to x1 + x2 + ... + xk = n
    // if positive = true, each xi >= 1
    // if positive = false, each xi >= 0
    if (positive) {
        if (n < k) return 0;
        return C(n-1, k-1);
    } else {
        return C(n + k - 1, k - 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    precompute(MAXN-1);
    
    // Example usage
    int n = 10, k = 3;
    cout << "C(" << n << ", " << k << ") = " << C(n, k) << endl;
    cout << "P(" << n << ", " << k << ") = " << P(n, k) << endl;
    cout << "Stars and bars (positive) for n=" << n << " k=" << k << ": " << stars_and_bars(n, k, true) << endl;
    cout << "Stars and bars (non‑negative) for n=" << n << " k=" << k << ": " << stars_and_bars(n, k, false) << endl;
    
    return 0;
}