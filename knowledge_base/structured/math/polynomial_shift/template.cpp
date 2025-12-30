#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 998244353; // 常见模数
const int G = 3;          // 原根

ll modpow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
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
        ll wlen = modpow(G, (MOD - 1) / len);
        if (inv) wlen = modpow(wlen, MOD - 2);
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
        ll inv_n = modpow(n, MOD - 2);
        for (ll& x : a) x = x * inv_n % MOD;
    }
}

vector<ll> multiply(vector<ll> a, vector<ll> b) {
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, false); ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % MOD;
    ntt(a, true);
    while (a.size() > 1 && a.back() == 0) a.pop_back();
    return a;
}

// 多项式平移: 给定系数 f[0..n] 和常数 c, 返回 f(x+c) 的系数
vector<ll> polynomial_shift(vector<ll> f, ll c) {
    int n = f.size() - 1;
    vector<ll> fact(n + 1), inv_fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;
    inv_fact[n] = modpow(fact[n], MOD - 2);
    for (int i = n; i >= 1; i--) inv_fact[i - 1] = inv_fact[i] * i % MOD;
    
    // A0(x) = sum_{i=0..n} f[n-i] * (n-i)! * x^i
    // B0(x) = sum_{i=0..n} c^i / i! * x^i
    vector<ll> A0(n + 1), B0(n + 1);
    for (int i = 0; i <= n; i++) {
        A0[i] = f[n - i] * fact[n - i] % MOD;
        B0[i] = modpow(c, i) * inv_fact[i] % MOD;
    }
    vector<ll> C = multiply(A0, B0);
    C.resize(2 * n + 1);
    vector<ll> res(n + 1);
    for (int t = 0; t <= n; t++) {
        // t! * [x^t] f(x+c) = [x^{n-t}] C
        ll val = C[n - t] * inv_fact[t] % MOD;
        res[t] = val;
    }
    return res;
}

// 连续点值平移: 给定 f(0), f(1), ..., f(n), 计算 f(c), f(c+1), ..., f(c+n)
vector<ll> continuous_point_shift(vector<ll> f_val, ll c) {
    int n = f_val.size() - 1;
    vector<ll> fact(n + 1), inv_fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;
    inv_fact[n] = modpow(fact[n], MOD - 2);
    for (int i = n; i >= 1; i--) inv_fact[i - 1] = inv_fact[i] * i % MOD;
    
    // A0(x) = sum_{i=0..n} f(i) * (-1)^{n-i} / (i! (n-i)!) * x^i
    // B0(x) = sum_{i>=0} 1/(c - n + i) * x^i   (截断到足够长度)
    vector<ll> A0(n + 1), B0(2 * n + 1);
    for (int i = 0; i <= n; i++) {
        ll sign = ((n - i) & 1) ? MOD - 1 : 1;
        A0[i] = f_val[i] * sign % MOD * inv_fact[i] % MOD * inv_fact[n - i] % MOD;
    }
    for (int i = 0; i <= 2 * n; i++) {
        // 注意分母不能为0, 实际实现需处理 c > n 或其他情况
        ll denom = (c - n + i) % MOD;
        if (denom < 0) denom += MOD;
        B0[i] = modpow(denom, MOD - 2);
    }
    vector<ll> C = multiply(A0, B0);
    C.resize(2 * n + 1);
    vector<ll> res(n + 1);
    for (int t = 0; t <= n; t++) {
        // f(c+t) = (c+t)! / (c+t-n-1)! * [x^{n+t}] C
        ll num = 1;
        for (ll k = c + t - n; k <= c + t; k++) num = num * (k % MOD) % MOD;
        res[t] = num * C[n + t] % MOD;
    }
    return res;
}

int main() {
    // 示例: 多项式平移
    vector<ll> f = {1, 2, 3}; // 1 + 2x + 3x^2
    ll c = 5;
    vector<ll> shifted = polynomial_shift(f, c);
    // 输出 f(x+5) 的系数
    for (ll coeff : shifted) cout << coeff << ' ';
    cout << endl;
    return 0;
}