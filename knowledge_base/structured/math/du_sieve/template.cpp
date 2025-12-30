#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e6 + 10; // Precompute up to ~n^{2/3}
vector<int> primes;
bool is_composite[MAXN];
int mu[MAXN];
ll phi[MAXN];
ll sum_mu[MAXN];
ll sum_phi[MAXN];
unordered_map<ll, ll> mp_mu, mp_phi;

void linear_sieve(int n) {
    mu[1] = 1;
    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!is_composite[i]) {
            primes.push_back(i);
            mu[i] = -1;
            phi[i] = i - 1;
        }
        for (int p : primes) {
            if (i * p > n) break;
            is_composite[i * p] = true;
            if (i % p == 0) {
                mu[i * p] = 0;
                phi[i * p] = phi[i] * p;
                break;
            } else {
                mu[i * p] = -mu[i];
                phi[i * p] = phi[i] * phi[p];
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        sum_mu[i] = sum_mu[i - 1] + mu[i];
        sum_phi[i] = sum_phi[i - 1] + phi[i];
    }
}

ll du_sieve_mu(ll n) {
    if (n < MAXN) return sum_mu[n];
    if (mp_mu.count(n)) return mp_mu[n];
    ll res = 1; // ∑_{i=1}^{n} ε(i) = 1
    for (ll l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        res -= (r - l + 1) * du_sieve_mu(n / l);
    }
    return mp_mu[n] = res;
}

ll du_sieve_phi(ll n) {
    if (n < MAXN) return sum_phi[n];
    if (mp_phi.count(n)) return mp_phi[n];
    ll res = n * (n + 1) / 2; // ∑_{i=1}^{n} id(i)
    for (ll l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        res -= (r - l + 1) * du_sieve_phi(n / l);
    }
    return mp_phi[n] = res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    linear_sieve(MAXN - 1);
    int T;
    cin >> T;
    while (T--) {
        ll n;
        cin >> n;
        cout << du_sieve_phi(n) << ' ' << du_sieve_mu(n) << '\n';
    }
    return 0;
}