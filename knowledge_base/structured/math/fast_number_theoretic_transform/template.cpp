#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;          // 常见模数
const int G = 3;                    // 模数的原根

int qpow(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1) res = 1LL * res * x % MOD;
        x = 1LL * x * x % MOD;
        y >>= 1;
    }
    return res;
}

void ntt(vector<int> &a, int opt) {
    int n = a.size();
    vector<int> r(n);
    for (int i = 0; i < n; ++i) {
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
    }
    for (int i = 0; i < n; ++i) {
        if (i < r[i]) swap(a[i], a[r[i]]);
    }
    for (int k = 2; k <= n; k <<= 1) {
        int m = k >> 1;
        int gn = qpow(G, (MOD - 1) / k);
        for (int i = 0; i < n; i += k) {
            int g = 1;
            for (int j = 0; j < m; ++j, g = 1LL * g * gn % MOD) {
                int tmp = 1LL * a[i + j + m] * g % MOD;
                a[i + j + m] = (a[i + j] - tmp + MOD) % MOD;
                a[i + j] = (a[i + j] + tmp) % MOD;
            }
        }
    }
    if (opt == -1) {
        reverse(a.begin() + 1, a.end());
        int inv = qpow(n, MOD - 2);
        for (int &x : a) x = 1LL * x * inv % MOD;
    }
}

vector<int> multiply(vector<int> a, vector<int> b) {
    int n = 1;
    while (n < (int)a.size() + (int)b.size() - 1) n <<= 1;
    a.resize(n);
    b.resize(n);
    ntt(a, 1);
    ntt(b, 1);
    for (int i = 0; i < n; ++i) a[i] = 1LL * a[i] * b[i] % MOD;
    ntt(a, -1);
    a.resize((int)a.size() + (int)b.size() - 1);
    return a;
}