#include <cstdlib>
#include <ctime>
#include <algorithm>
using ll = long long;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll mul_mod(ll a, ll b, ll m) {
    return (__int128)a * b % m;
}

ll f(ll x, ll c, ll mod) {
    return (mul_mod(x, x, mod) + c) % mod;
}

ll pollard_rho(ll n) {
    if (n == 4) return 2;
    ll c = rand() % (n - 1) + 1;
    ll t = f(0, c, n);
    ll r = f(t, c, n);
    while (t != r) {
        ll d = gcd(abs(t - r), n);
        if (d > 1) return d;
        t = f(t, c, n);
        r = f(f(r, c, n), c, n);
    }
    return n;
}

// 倍增优化版本（Brent 判环）
ll pollard_rho_optimized(ll n) {
    if (n % 2 == 0) return 2;
    ll c = rand() % (n - 1) + 1;
    ll t = 0, r = 0;
    ll goal = 1, val = 1;
    for (goal = 1; ; goal <<= 1) {
        r = t;
        val = 1;
        for (ll step = 1; step <= goal; ++step) {
            t = f(t, c, n);
            val = mul_mod(val, abs(t - r), n);
            if (step % 127 == 0) {
                ll d = gcd(val, n);
                if (d > 1) return d;
            }
        }
        ll d = gcd(val, n);
        if (d > 1) return d;
    }
}

// 完整分解框架（需要 Miller-Rabin 素性测试）
#include <vector>
std::vector<ll> factorize(ll n) {
    std::vector<ll> factors;
    if (n < 2) return factors;
    // 先用小素数试除（可选）
    // 再用 Miller-Rabin 判断素数
    // 最后用 Pollard-Rho 递归分解
    return factors;
}