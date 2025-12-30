#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// 计算阶 δ_m(a)
ll order(ll a, ll m, const vector<ll>& factors_phi) {
    // 要求 gcd(a, m) = 1
    ll phi_m = m; // 假设 m 是质数或已计算 φ(m)
    ll ord = phi_m;
    for (ll p : factors_phi) {
        while (ord % p == 0 && qpow(a, ord / p, m) == 1) {
            ord /= p;
        }
    }
    return ord;
}

// 判断 g 是否是模 m 的原根
bool is_primitive_root(ll g, ll m, ll phi_m, const vector<ll>& factors_phi) {
    if (gcd(g, m) != 1) return false;
    for (ll p : factors_phi) {
        if (qpow(g, phi_m / p, m) == 1) {
            return false;
        }
    }
    return true;
}

// 寻找模 m 的最小原根 (m 需有原根)
ll find_min_primitive_root(ll m, ll phi_m, const vector<ll>& factors_phi) {
    for (ll g = 1; g <= m; ++g) {
        if (gcd(g, m) == 1 && is_primitive_root(g, m, phi_m, factors_phi)) {
            return g;
        }
    }
    return -1; // 理论上不会到达
}

int main() {
    // 示例: 求模质数 p 的原根
    ll p = 998244353;
    ll phi = p - 1;
    // 需要先对 φ(p) 进行质因数分解
    vector<ll> factors = {2, 7, 17, 23, ...}; // 实际应根据 φ(p) 计算
    ll g = find_min_primitive_root(p, phi, factors);
    cout << "Primitive root of " << p << " is " << g << endl;
    return 0;
}