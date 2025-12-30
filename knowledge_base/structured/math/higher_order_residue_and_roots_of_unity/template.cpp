#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 快速幂
ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// 扩展欧几里得
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) { x = 1; y = 0; return a; }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// BSGS 求离散对数 (a^x ≡ b mod p)
ll bsgs(ll a, ll b, ll p) {
    a %= p; b %= p;
    if (b == 1) return 0;
    ll m = ceil(sqrt(p));
    unordered_map<ll, ll> mp;
    ll now = b, am = qpow(a, m, p);
    for (ll i = 0; i < m; ++i) {
        mp[now] = i;
        now = now * a % p;
    }
    now = 1;
    for (ll i = 1; i <= m; ++i) {
        now = now * am % p;
        if (mp.count(now)) return i * m - mp[now];
    }
    return -1;
}

// 求原根 (模素数 p)
ll primitive_root(ll p) {
    vector<ll> factors;
    ll phi = p - 1, n = phi;
    for (ll i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) factors.push_back(n);
    for (ll g = 2; g <= p; ++g) {
        bool ok = true;
        for (ll factor : factors) {
            if (qpow(g, phi / factor, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
    return -1;
}

// 朴素算法求 k 次方根 (模素数 p, 假设原根存在)
ll kth_root_naive(ll k, ll a, ll p) {
    if (a == 0) return 0;
    ll g = primitive_root(p);
    ll ind = bsgs(g, a, p);
    if (ind == -1) return -1;
    // 解 k*y ≡ ind (mod p-1)
    ll x, y;
    ll d = exgcd(k, p - 1, x, y);
    if (ind % d) return -1;
    x = (x * (ind / d) % (p - 1) + (p - 1)) % (p - 1);
    return qpow(g, x, p);
}

int main() {
    // 示例: 求 x^3 ≡ 7 mod 13
    ll k = 3, a = 7, p = 13;
    ll root = kth_root_naive(k, a, p);
    if (root == -1) cout << "No solution\n";
    else cout << "One solution: " << root << endl;
    return 0;
}