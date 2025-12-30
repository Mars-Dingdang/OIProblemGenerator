#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Poly = vector<ll>; // coefficients modulo MOD
const ll MOD = 998244353; // common NTT-friendly prime
const ll G = 3;          // primitive root for MOD

// Fast Fourier Transform (NTT) for polynomial multiplication
void ntt(Poly& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll wlen = powmod(G, (MOD - 1) / len, MOD);
        if (invert) wlen = powmod(wlen, MOD - 2, MOD);
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < len / 2; ++j) {
                ll u = a[i + j], v = a[i + j + len / 2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                w = w * wlen % MOD;
            }
        }
    }
    if (invert) {
        ll inv_n = powmod(n, MOD - 2, MOD);
        for (ll& x : a) x = x * inv_n % MOD;
    }
}

Poly multiply(Poly a, Poly b) {
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, false); ntt(b, false);
    for (int i = 0; i < n; ++i) a[i] = a[i] * b[i] % MOD;
    ntt(a, true);
    a.resize(a.size() + b.size() - 1);
    return a;
}

// Polynomial inversion (Newton's method)
Poly inverse(Poly a, int m) {
    Poly inv = {powmod(a[0], MOD - 2, MOD)};
    int k = 1;
    while (k < m) {
        k <<= 1;
        Poly tmp(a.begin(), a.begin() + min((int)a.size(), k));
        Poly res = multiply(multiply(inv, inv), tmp);
        inv.resize(k);
        for (int i = 0; i < k; ++i) {
            inv[i] = (2 * inv[i] - res[i] + MOD) % MOD;
        }
    }
    inv.resize(m);
    return inv;
}

// Helper: modular exponentiation
ll powmod(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    // Example: multiply (1 + 2x) * (3 + 4x) = 3 + 10x + 8x^2
    Poly a = {1, 2};
    Poly b = {3, 4};
    Poly c = multiply(a, b);
    for (ll coeff : c) cout << coeff << " "; // Output: 3 10 8
    return 0;
}