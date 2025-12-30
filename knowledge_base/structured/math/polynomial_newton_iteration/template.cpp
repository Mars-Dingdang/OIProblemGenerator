#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 998244353;
const int G = 3;

// 快速幂
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// NTT 相关函数 (省略具体实现)
void ntt(vector<int>& a, int inv) { /* ... */ }
vector<int> poly_mul(vector<int> a, vector<int> b) { /* ... */ }
vector<int> poly_inv(vector<int> a, int n) { /* ... */ }
vector<int> poly_sqrt(vector<int> a, int n) { /* ... */ }
vector<int> poly_exp(vector<int> a, int n) { /* ... */ }

// 通用牛顿迭代求解 G(x, f(x)) ≡ 0 (mod x^n)
// 需要提供函数: G(f) 和 dG(f) (偏导数)
typedef function<vector<int>(vector<int>)> PolyFunc;
vector<int> newton_iteration(int n, PolyFunc G, PolyFunc dG, int f1) {
    vector<int> f = {f1}; // 初始解 f1
    for (int len = 1; len < n; len <<= 1) {
        int m = min(n, len << 1);
        vector<int> g_val = G(f); // 计算 G(f)
        vector<int> dg_val = dG(f); // 计算 dG/df
        // 倍增公式: f_new = f - G(f) / dG(f) (mod x^m)
        vector<int> inv_dg = poly_inv(dg_val, m);
        vector<int> delta = poly_mul(g_val, inv_dg);
        delta.resize(m);
        // f = f - delta
        f.resize(m);
        for (int i = 0; i < m; i++) {
            f[i] = (f[i] - delta[i] + MOD) % MOD;
        }
    }
    f.resize(n);
    return f;
}

// 示例: 多项式求逆 (h(x) 给定)
vector<int> poly_inv_newton(vector<int> h, int n) {
    // G(f) = 1/f - h, dG(f) = -1/f^2
    PolyFunc G = [&](vector<int> f) -> vector<int> {
        vector<int> inv_f = poly_inv(f, n);
        vector<int> res = poly_mul(inv_f, h);
        // 1/f - h
        for (int i = 0; i < n; i++) res[i] = (inv_f[i] - res[i] + MOD) % MOD;
        return res;
    };
    PolyFunc dG = [&](vector<int> f) -> vector<int> {
        vector<int> inv_f2 = poly_inv(f, n);
        inv_f2 = poly_mul(inv_f2, inv_f2);
        // -1/f^2
        for (int i = 0; i < n; i++) inv_f2[i] = (MOD - inv_f2[i]) % MOD;
        return inv_f2;
    };
    int f1 = qpow(h[0], MOD - 2); // 初始解: 常数项逆元
    return newton_iteration(n, G, dG, f1);
}

int main() {
    // 示例用法
    vector<int> h = {1, 2, 3}; // h(x) = 1 + 2x + 3x^2
    int n = 4;
    vector<int> inv_h = poly_inv_newton(h, n);
    // 输出结果
    for (int i = 0; i < n; i++) cout << inv_h[i] << " ";
    return 0;
}