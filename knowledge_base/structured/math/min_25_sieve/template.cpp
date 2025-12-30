/* Min_25 Sieve for multiplicative function prefix sum */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXS = 200000; // 2*sqrt(n)

ll n;
int lim, pcnt;
int pri[MAXS / 7], lpf[MAXS + 1];
ll spri[MAXS + 1]; // prefix sum of g(p) for primes
vector<ll> lis;
int le[MAXS + 1], ge[MAXS + 1];
vector<ll> G0, G1; // G values for each term of polynomial
vector<ll> Fprime;

inline int idx(ll v) {
    return v <= lim ? le[v] : ge[n / v];
}

void sieve(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!lpf[i]) {
            lpf[i] = ++pcnt;
            pri[pcnt] = i;
            spri[pcnt] = spri[pcnt - 1] + i; // example for g(p)=p
        }
        for (int j = 1; j <= lpf[i] && i * pri[j] <= n; ++j)
            lpf[i * pri[j]] = j;
    }
}

void init(ll n) {
    lim = sqrt(n);
    sieve(lim);
    lis.clear();
    for (ll i = 1, v; i <= n; i = n / v + 1) {
        v = n / i;
        lis.push_back(v);
        if (v <= lim) le[v] = lis.size() - 1;
        else ge[n / v] = lis.size() - 1;
    }
    int m = lis.size();
    G0.resize(m); G1.resize(m);
    for (int i = 0; i < m; ++i) {
        ll v = lis[i];
        G0[i] = v - 1;                     // sum of 1 for composite part
        G1[i] = (v + 2) * (v - 1) / 2;     // sum of p (example)
    }
    for (int k = 1; k <= pcnt; ++k) {
        ll p = pri[k], sqp = p * p;
        for (int i = 0; i < m && lis[i] >= sqp; ++i) {
            ll v = lis[i] / p;
            int id = idx(v);
            G0[i] -= (G0[id] - (k - 1));
            G1[i] -= p * (G1[id] - spri[k - 1]);
        }
    }
    Fprime.resize(m);
    for (int i = 0; i < m; ++i)
        Fprime[i] = G1[i] - G0[i]; // example for f(p)=p-1
}

ll f_pc(ll p, int c) {
    // implement f(p^c), e.g., for Euler totient: return p^c - p^(c-1);
    return pow(p, c) - pow(p, c - 1);
}

ll F(int k, ll n) {
    if (n < pri[k] || n <= 1) return 0;
    int id = idx(n);
    ll ans = Fprime[id] - (spri[k - 1] - (k - 1)); // adjust for f(p)=p-1
    for (int i = k; i <= pcnt && (ll)pri[i] * pri[i] <= n; ++i) {
        ll pw = pri[i], pw2 = pw * pw;
        for (int c = 1; pw2 <= n; ++c, pw = pw2, pw2 *= pri[i]) {
            ans += f_pc(pri[i], c) * F(i + 1, n / pw) + f_pc(pri[i], c + 1);
        }
    }
    return ans;
}

ll solve(ll n) {
    init(n);
    return F(1, n) + 1; // + f(1)
}

int main() {
    cin >> n;
    cout << solve(n) << '\n';
    return 0;
}