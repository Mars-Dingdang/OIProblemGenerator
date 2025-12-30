#include <iostream>
using ll = long long;

// Basic form: f(a, b, c, n) = sum_{i=0}^{n} floor((a*i + b) / c)
ll euclidean_like_f(ll a, ll b, ll c, ll n) {
    if (a == 0) return (b / c) * (n + 1);
    if (a >= c || b >= c) {
        return euclidean_like_f(a % c, b % c, c, n)
               + (a / c) * n * (n + 1) / 2
               + (b / c) * (n + 1);
    }
    ll m = (a * n + b) / c;
    if (m == 0) return 0;
    return n * m - euclidean_like_f(c, c - b - 1, a, m - 1);
}

// Extended version computing f, g, h simultaneously (mod version)
#include <tuple>
using Data = std::tuple<ll, ll, ll>; // f, g, h
constexpr ll MOD = 998244353;
constexpr ll inv2 = (MOD + 1) / 2;
constexpr ll inv6 = (MOD + 1) / 6;

Data euclidean_like_all(ll a, ll b, ll c, ll n) {
    if (a == 0) {
        ll p = (b / c) % MOD;
        ll f = p * (n + 1) % MOD;
        ll g = p * n % MOD * (n + 1) % MOD * inv2 % MOD;
        ll h = p * p % MOD * (n + 1) % MOD;
        return {f, g, h};
    }
    if (a >= c || b >= c) {
        auto [f0, g0, h0] = euclidean_like_all(a % c, b % c, c, n);
        ll p = a / c % MOD, q = b / c % MOD;
        ll n1 = n % MOD, n2 = n1 * (n1 + 1) % MOD * inv2 % MOD;
        ll n3 = n2 * (2 * n1 + 1) % MOD * inv6 % MOD;
        ll f = (f0 + p * n2 + q * (n1 + 1)) % MOD;
        ll g = (g0 + p * n3 + q * n2) % MOD;
        ll h = (h0 + 2 * q * f0 + 2 * p * g0 + p * p % MOD * n3 + q * q % MOD * (n1 + 1) + 2 * p * q % MOD * n2) % MOD;
        return {f, g, h};
    }
    ll m = (a * n + b) / c;
    if (m == 0) return {0, 0, 0};
    auto [f0, g0, h0] = euclidean_like_all(c, c - b - 1, a, m - 1);
    ll n1 = n % MOD, m1 = m % MOD;
    ll n2 = n1 * (n1 + 1) % MOD * inv2 % MOD;
    ll f = (n1 * m1 - f0) % MOD;
    ll g = (m1 * n2 - f0 * inv2 - h0 * inv2) % MOD;
    ll h = (n1 * m1 % MOD * m1 - f0 - 2 * g0) % MOD;
    f = (f + MOD) % MOD; g = (g + MOD) % MOD; h = (h + MOD) % MOD;
    return {f, g, h};
}