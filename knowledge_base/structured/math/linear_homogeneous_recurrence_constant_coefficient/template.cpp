#include <bits/stdc++.h>
using namespace std;
using poly = vector<int>;
const int MOD = 998244353; // Example modulus

// Polynomial multiplication (naive O(n^2) for simplicity)
poly mul(const poly &a, const poly &b) {
    poly res(a.size() + b.size() - 1, 0);
    for (size_t i = 0; i < a.size(); ++i)
        for (size_t j = 0; j < b.size(); ++j)
            res[i + j] = (res[i + j] + 1LL * a[i] * b[j]) % MOD;
    return res;
}

// Polynomial modulo (a mod b, assuming b is monic)
poly mod(const poly &a, const poly &b) {
    poly r = a;
    while (r.size() >= b.size()) {
        int coef = r.back();
        int shift = r.size() - b.size();
        for (size_t i = 0; i < b.size(); ++i)
            r[i + shift] = (r[i + shift] - 1LL * coef * b[i] % MOD + MOD) % MOD;
        while (!r.empty() && r.back() == 0) r.pop_back();
    }
    return r;
}

// Polynomial exponentiation x^k mod Gamma
poly poly_pow_mod(int k, const poly &Gamma) {
    poly res = {1}; // x^0
    poly base = {0, 1}; // x
    while (k) {
        if (k & 1) res = mod(mul(res, base), Gamma);
        base = mod(mul(base, base), Gamma);
        k >>= 1;
    }
    return res;
}

// Compute a_k using Fiduccia algorithm
int linear_recurrence(const vector<int> &a, const vector<int> &c, int k) {
    int d = c.size();
    if (k < d) return a[k];
    // Build Gamma(x) = x^d - c_d x^{d-1} - ... - c_1
    poly Gamma(d + 1, 0);
    Gamma[d] = 1;
    for (int i = 1; i <= d; ++i)
        Gamma[d - i] = (MOD - c[i - 1]) % MOD;
    // Build A(x) = a_0 + a_1 x + ... + a_{d-1} x^{d-1}
    poly A(a.begin(), a.begin() + d);
    // Compute x^k mod Gamma
    poly xk_mod = poly_pow_mod(k, Gamma);
    // Inner product <xk_mod, A>
    int ans = 0;
    for (size_t i = 0; i < xk_mod.size(); ++i)
        ans = (ans + 1LL * xk_mod[i] * A[i]) % MOD;
    return ans;
}

int main() {
    // Example: Fibonacci: a_n = a_{n-1} + a_{n-2}
    vector<int> a = {0, 1}; // a0, a1
    vector<int> c = {1, 1}; // c1, c2 (a_n = c1*a_{n-1} + c2*a_{n-2})
    int k = 10;
    cout << linear_recurrence(a, c, k) << endl; // Output: 55
    return 0;
}