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

namespace Poly {
    vector<int> rev;
    void getRev(int n) {
        rev.resize(n);
        for (int i = 0; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1;
            if (i & 1) rev[i] |= n >> 1;
        }
    }
    void ntt(vector<int>& a, int op) {
        int n = a.size();
        for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int mid = 1; mid < n; mid <<= 1) {
            int gn = qpow(G, (MOD - 1) / (mid << 1));
            if (op == -1) gn = qpow(gn, MOD - 2);
            for (int i = 0; i < n; i += mid << 1) {
                int g = 1;
                for (int j = 0; j < mid; j++, g = 1LL * g * gn % MOD) {
                    int x = a[i + j], y = 1LL * g * a[i + j + mid] % MOD;
                    a[i + j] = (x + y) % MOD;
                    a[i + j + mid] = (x - y + MOD) % MOD;
                }
            }
        }
        if (op == -1) {
            int inv = qpow(n, MOD - 2);
            for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * inv % MOD;
        }
    }
    vector<int> multiply(vector<int> a, vector<int> b) {
        int n = 1, sz = a.size() + b.size() - 1;
        while (n < sz) n <<= 1;
        getRev(n);
        a.resize(n); b.resize(n);
        ntt(a, 1); ntt(b, 1);
        for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * b[i] % MOD;
        ntt(a, -1);
        a.resize(sz);
        return a;
    }
    vector<int> inverse(vector<int> a, int n) {
        if (n == 1) return {qpow(a[0], MOD - 2)};
        vector<int> b = inverse(a, (n + 1) >> 1);
        int len = 1;
        while (len < (n << 1)) len <<= 1;
        getRev(len);
        vector<int> c(a.begin(), a.begin() + n);
        c.resize(len); b.resize(len);
        ntt(c, 1); ntt(b, 1);
        for (int i = 0; i < len; i++) b[i] = 1LL * b[i] * (2 - 1LL * c[i] * b[i] % MOD + MOD) % MOD;
        ntt(b, -1);
        b.resize(n);
        return b;
    }
    vector<int> derivative(vector<int> a) {
        int n = a.size();
        vector<int> res(n - 1);
        for (int i = 1; i < n; i++) res[i - 1] = 1LL * a[i] * i % MOD;
        return res;
    }
    vector<int> integral(vector<int> a) {
        int n = a.size();
        vector<int> res(n + 1);
        for (int i = 0; i < n; i++) res[i + 1] = 1LL * a[i] * qpow(i + 1, MOD - 2) % MOD;
        return res;
    }
    vector<int> logarithm(vector<int> a, int n) {
        vector<int> inva = inverse(a, n);
        vector<int> der = derivative(a);
        vector<int> res = multiply(der, inva);
        res.resize(n - 1);
        res = integral(res);
        res.resize(n);
        return res;
    }
    vector<int> exponent(vector<int> a, int n) {
        if (n == 1) return {1};
        vector<int> b = exponent(a, (n + 1) >> 1);
        vector<int> lnb = logarithm(b, n);
        for (int i = 0; i < n; i++) lnb[i] = (a[i] - lnb[i] + MOD) % MOD;
        lnb[0] = (lnb[0] + 1) % MOD;
        b = multiply(b, lnb);
        b.resize(n);
        return b;
    }
}

vector<int> lagrange_inversion(vector<int> f, int n) {
    // f[0] = 0, f[1] != 0
    // compute g = f^{-1} up to x^n
    vector<int> g(n);
    g[0] = 0;
    g[1] = qpow(f[1], MOD - 2);
    for (int i = 2; i < n; i++) {
        vector<int> tmp = Poly::derivative(f);
        tmp.resize(n);
        vector<int> inv = Poly::inverse(tmp, n);
        vector<int> powg = Poly::exponent(g, n);
        vector<int> res = Poly::multiply(inv, powg);
        g[i] = 1LL * res[i - 1] * qpow(i, MOD - 2) % MOD;
    }
    return g;
}

int main() {
    // Example: solve for g where f(g(x)) = x, f(x) = x - x^2
    int n = 10;
    vector<int> f(n);
    f[0] = 0;
    f[1] = 1;
    f[2] = MOD - 1;
    vector<int> g = lagrange_inversion(f, n);
    for (int i = 0; i < n; i++) cout << g[i] << " ";
    cout << endl;
    return 0;
}