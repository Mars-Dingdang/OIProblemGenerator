#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 10;
const int mod = 1e9 + 7;

ll global_n;
int lim;
vector<int> primes;
bool is_prime[N];
vector<ll> values;
vector<int> idx1, idx2;
vector<ll> g0, g1;
vector<ll> fprime_sum;

void sieve(int n) {
    fill(is_prime, is_prime + n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i + i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

void init(ll n) {
    lim = sqrt(n);
    sieve(lim + 1000);
    values.clear();
    idx1.resize(lim + 1);
    idx2.resize(lim + 1);
    for (ll i = 1, la; i <= n; i = la + 1) {
        la = n / (n / i);
        values.push_back(n / i);
    }
    reverse(values.begin(), values.end());
    int m = values.size();
    g0.resize(m);
    g1.resize(m);
    for (int i = 0; i < m; ++i) {
        ll v = values[i];
        g0[i] = v - 1;
        g1[i] = (v % mod) * ((v + 1) % mod) % mod * ((mod + 1) / 2) % mod - 1;
    }
    for (int p : primes) {
        if ((ll)p * p > n) break;
        for (int i = 0; i < m; ++i) {
            ll v = values[i];
            if ((ll)p * p > v) break;
            int j = (v / p <= lim) ? idx1[v / p] : idx2[n / (v / p)];
            g0[i] -= (g0[j] - (lower_bound(primes.begin(), primes.end(), p) - primes.begin()));
            g1[i] = (g1[i] - (ll)p * (g1[j] - fprime_sum[p - 1]) % mod + mod) % mod;
        }
    }
}

void calcFprime() {
    fprime_sum.resize(primes.back() + 1);
    fprime_sum[0] = 0;
    for (int i = 0; i < primes.size(); ++i) {
        int p = primes[i];
        fprime_sum[p] = (fprime_sum[primes[i - 1]] + p) % mod;
    }
}

ll F(int t, ll l) {
    if (l == 0) return 0;
    int idx = (l <= lim) ? idx1[l] : idx2[global_n / l];
    ll res = (g1[idx] - g0[idx] + mod) % mod;
    for (int i = t; i < primes.size(); ++i) {
        int p = primes[i];
        if ((ll)p * p > l) break;
        for (ll pc = p, c = 1; pc <= l; pc *= p, ++c) {
            res = (res + (pc % mod) * F(i + 1, l / pc) % mod) % mod;
            if (c > 1) res = (res + (pc % mod)) % mod;
        }
    }
    return res;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> global_n;
    lim = sqrt(global_n);
    sieve(lim + 1000);
    init(global_n);
    calcFprime();
    cout << (F(1, global_n) + 1ll + mod) % mod << '\n';
    return 0;
}