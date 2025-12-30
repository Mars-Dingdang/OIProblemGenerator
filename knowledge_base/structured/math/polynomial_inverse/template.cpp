#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 998244353, G = 3; // NTT prime

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void ntt(vector<ll>& a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll wlen = qpow(G, (MOD - 1) / len);
        if (inv) wlen = qpow(wlen, MOD - 2);
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i + j], v = a[i + j + len / 2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                w = w * wlen % MOD;
            }
        }
    }
    if (inv) {
        ll inv_n = qpow(n, MOD - 2);
        for (ll& x : a) x = x * inv_n % MOD;
    }
}

vector<ll> poly_inv(const vector<ll>& a, int n) {
    if (n == 1) return {qpow(a[0], MOD - 2)};
    int m = (n + 1) / 2;
    vector<ll> b = poly_inv(a, m);
    int len = 1;
    while (len < n * 2) len <<= 1;
    vector<ll> fa(len, 0), fb(len, 0);
    copy(a.begin(), a.begin() + n, fa.begin());
    copy(b.begin(), b.end(), fb.begin());
    ntt(fa, false); ntt(fb, false);
    for (int i = 0; i < len; i++) {
        fa[i] = fb[i] * (2 - fa[i] * fb[i] % MOD + MOD) % MOD;
    }
    ntt(fa, true);
    fa.resize(n);
    return fa;
}

int main() {
    // Example: find inverse of polynomial A(x) modulo x^n
    int n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<ll> inv = poly_inv(a, n);
    for (ll x : inv) cout << x << ' ';
    cout << endl;
    return 0;
}