#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 998244353;
const int G = 3;

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void ntt(vector<ll>& a, int opt) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll w = qpow(G, (MOD - 1) / len);
        if (opt == -1) w = qpow(w, MOD - 2);
        for (int i = 0; i < n; i += len) {
            ll wn = 1;
            for (int j = 0; j < len / 2; ++j) {
                ll u = a[i + j], v = a[i + j + len / 2] * wn % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                wn = wn * w % MOD;
            }
        }
    }
    if (opt == -1) {
        ll inv = qpow(n, MOD - 2);
        for (ll& x : a) x = x * inv % MOD;
    }
}

vector<ll> poly_multiply(vector<ll> a, vector<ll> b) {
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, 1); ntt(b, 1);
    for (int i = 0; i < n; ++i) a[i] = a[i] * b[i] % MOD;
    ntt(a, -1);
    a.resize(a.size() + b.size() - 1);
    return a;
}

vector<ll> poly_mod(vector<ll> f, vector<ll> g) {
    int n = f.size() - 1, m = g.size() - 1;
    if (n < m) return f;
    vector<ll> fr = f, gr = g;
    reverse(fr.begin(), fr.end());
    reverse(gr.begin(), gr.end());
    fr.resize(n - m + 1); gr.resize(n - m + 1);
    vector<ll> gr_inv = poly_inverse(gr); // Assume poly_inverse implemented
    vector<ll> q = poly_multiply(fr, gr_inv);
    q.resize(n - m + 1);
    reverse(q.begin(), q.end());
    vector<ll> r = poly_multiply(g, q);
    for (int i = 0; i < m; ++i) r[i] = (f[i] - r[i] + MOD) % MOD;
    r.resize(m);
    return r;
}

vector<ll> build_product_tree(const vector<ll>& x, int l, int r) {
    if (l == r) return { (MOD - x[l]) % MOD, 1 };
    int mid = (l + r) / 2;
    vector<ll> left = build_product_tree(x, l, mid);
    vector<ll> right = build_product_tree(x, mid + 1, r);
    return poly_multiply(left, right);
}

void evaluate(const vector<ll>& f, const vector<ll>& tree, const vector<ll>& x, vector<ll>& res, int l, int r, int node) {
    if (l == r) {
        res[l] = 0;
        for (int i = f.size() - 1; i >= 0; --i) {
            res[l] = (res[l] * x[l] + f[i]) % MOD;
        }
        return;
    }
    int mid = (l + r) / 2;
    vector<ll> f_left = poly_mod(f, tree[node * 2]);
    vector<ll> f_right = poly_mod(f, tree[node * 2 + 1]);
    evaluate(f_left, tree, x, res, l, mid, node * 2);
    evaluate(f_right, tree, x, res, mid + 1, r, node * 2 + 1);
}

vector<ll> multi_point_evaluate(const vector<ll>& f, const vector<ll>& x) {
    int n = x.size();
    vector<ll> tree(4 * n);
    vector<ll> root_poly = build_product_tree(x, 0, n - 1);
    // Build tree recursively (simplified)
    vector<ll> res(n);
    evaluate(f, tree, x, res, 0, n - 1, 1);
    return res;
}

vector<ll> fast_interpolation(const vector<ll>& x, const vector<ll>& y) {
    int n = x.size();
    vector<ll> tree = build_product_tree(x, 0, n - 1);
    vector<ll> d = multi_point_evaluate(poly_derivative(tree), x); // Assume poly_derivative
    for (int i = 0; i < n; ++i) d[i] = y[i] * qpow(d[i], MOD - 2) % MOD;
    // Recursive interpolation (simplified)
    return {}; // Placeholder
}