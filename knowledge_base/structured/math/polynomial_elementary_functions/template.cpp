#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int G = 3;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

void ntt(vector<int>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = qpow(G, (MOD - 1) / len);
        if (invert) wlen = qpow(wlen, MOD - 2);
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i + j], v = 1LL * a[i + j + len / 2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                w = 1LL * w * wlen % MOD;
            }
        }
    }
    if (invert) {
        int inv_n = qpow(n, MOD - 2);
        for (int& x : a) x = 1LL * x * inv_n % MOD;
    }
}

vector<int> multiply(vector<int> a, vector<int> b) {
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, false); ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * b[i] % MOD;
    ntt(a, true);
    while (a.size() > 1 && a.back() == 0) a.pop_back();
    return a;
}

vector<int> inverse(vector<int> a, int m) {
    vector<int> inv = {qpow(a[0], MOD - 2)};
    int k = 1;
    while (k < m) {
        k <<= 1;
        vector<int> tmp(a.begin(), a.begin() + min((int)a.size(), k));
        tmp = multiply(multiply(inv, inv), tmp);
        inv.resize(k);
        for (int i = 0; i < k; i++) {
            inv[i] = (2LL * inv[i] - tmp[i] + MOD) % MOD;
        }
    }
    inv.resize(m);
    return inv;
}

vector<int> derivative(vector<int> a) {
    for (int i = 1; i < a.size(); i++) a[i - 1] = 1LL * i * a[i] % MOD;
    a.pop_back();
    if (a.empty()) a.push_back(0);
    return a;
}

vector<int> integral(vector<int> a) {
    a.push_back(0);
    for (int i = a.size() - 1; i > 0; i--) a[i] = 1LL * a[i - 1] * qpow(i, MOD - 2) % MOD;
    a[0] = 0;
    return a;
}

vector<int> logarithm(vector<int> a, int m) {
    assert(a[0] == 1);
    vector<int> inv_a = inverse(a, m);
    vector<int> der_a = derivative(a);
    vector<int> tmp = multiply(der_a, inv_a);
    tmp.resize(m - 1);
    vector<int> res = integral(tmp);
    res.resize(m);
    return res;
}

vector<int> exponential(vector<int> a, int m) {
    assert(a[0] == 0);
    vector<int> res = {1};
    int k = 1;
    while (k < m) {
        k <<= 1;
        vector<int> tmp = logarithm(res, k);
        for (int i = 0; i < k; i++) tmp[i] = (a[i] - tmp[i] + MOD) % MOD;
        tmp[0] = (tmp[0] + 1) % MOD;
        res = multiply(res, tmp);
        res.resize(k);
    }
    res.resize(m);
    return res;
}

vector<int> sqrt(vector<int> a, int m) {
    assert(a[0] == 1);
    vector<int> res = {1};
    int k = 1;
    int inv2 = qpow(2, MOD - 2);
    while (k < m) {
        k <<= 1;
        vector<int> tmp(a.begin(), a.begin() + min((int)a.size(), k));
        vector<int> inv_res = inverse(res, k);
        tmp = multiply(tmp, inv_res);
        tmp.resize(k);
        for (int i = 0; i < k; i++) {
            res[i] = 1LL * inv2 * (res[i] + tmp[i]) % MOD;
        }
    }
    res.resize(m);
    return res;
}

int main() {
    // Example usage
    vector<int> poly = {1, 1}; // 1 + x
    int n = 5;
    vector<int> inv = inverse(poly, n);
    vector<int> log_poly = logarithm(poly, n);
    vector<int> exp_poly = exponential(poly, n);
    vector<int> sqrt_poly = sqrt(poly, n);
    
    return 0;
}