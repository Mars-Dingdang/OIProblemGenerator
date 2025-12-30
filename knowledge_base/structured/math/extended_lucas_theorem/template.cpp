#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

long long power(long long a, long long b, long long mod) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) { x = 1; y = 0; return a; }
    long long d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

long long inv(long long a, long long mod) {
    long long x, y;
    exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}

pair<long long, long long> factorize_p(long long n, long long p) {
    long long cnt = 0;
    while (n) {
        cnt += n / p;
        n /= p;
    }
    return {cnt, 0};
}

long long factorial_mod(long long n, long long p, long long pk) {
    if (!n) return 1;
    long long res = 1;
    for (long long i = 1; i <= pk; ++i)
        if (i % p) res = res * i % pk;
    res = power(res, n / pk, pk);
    for (long long i = 1; i <= n % pk; ++i)
        if (i % p) res = res * i % pk;
    return res * factorial_mod(n / p, p, pk) % pk;
}

long long C_mod_pk(long long n, long long k, long long p, long long pk) {
    if (k > n) return 0;
    auto [cnt1, _] = factorize_p(n, p);
    auto [cnt2, __] = factorize_p(k, p);
    auto [cnt3, ___] = factorize_p(n - k, p);
    long long cnt = cnt1 - cnt2 - cnt3;
    long long a = factorial_mod(n, p, pk);
    long long b = factorial_mod(k, p, pk);
    long long c = factorial_mod(n - k, p, pk);
    return power(p, cnt, pk) * a % pk * inv(b, pk) % pk * inv(c, pk) % pk;
}

long long crt(const vector<long long> &r, const vector<long long> &m) {
    long long M = 1, ans = 0;
    for (auto mi : m) M *= mi;
    for (size_t i = 0; i < r.size(); ++i) {
        long long Mi = M / m[i];
        long long invMi = inv(Mi, m[i]);
        ans = (ans + r[i] * Mi % M * invMi) % M;
    }
    return ans;
}

long long extended_lucas(long long n, long long k, long long mod) {
    long long m = mod;
    vector<long long> r, fac;
    for (long long i = 2; i * i <= m; ++i) {
        if (m % i == 0) {
            long long pk = 1;
            while (m % i == 0) { m /= i; pk *= i; }
            r.push_back(C_mod_pk(n, k, i, pk));
            fac.push_back(pk);
        }
    }
    if (m > 1) {
        r.push_back(C_mod_pk(n, k, m, m));
        fac.push_back(m);
    }
    return crt(r, fac);
}

int main() {
    long long n, k, m;
    cin >> n >> k >> m;
    cout << extended_lucas(n, k, m) << endl;
    return 0;
}