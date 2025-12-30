#include <iostream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

using ll = long long;
const int MOD = 1e9 + 7;

int add(int x, int y) { return (x + y >= MOD) ? x + y - MOD : x + y; }
int sub(int x, int y) { return (x < y) ? x - y + MOD : x - y; }
int mul(int x, int y) { return (ll)x * y % MOD; }
int qpow(int x, ll y) {
    int res = 1;
    for (; y; y >>= 1, x = mul(x, x))
        if (y & 1) res = mul(res, x);
    return res;
}

namespace PN_Sieve {
    const int N = 2e6 + 5, M = 35;
    ll global_n;
    int pcnt, prime[N], phi[N];
    bool isp[N];
    int g[N], sg[N];
    int h[N][M];
    bool vis_h[N][M];
    map<ll, int> mp_g;
    int inv2, inv6;

    void sieve(int n) {
        pcnt = 0;
        fill(isp + 2, isp + n + 1, true);
        phi[1] = 1;
        for (int i = 2; i <= n; ++i) {
            if (isp[i]) prime[++pcnt] = i, phi[i] = i - 1;
            for (int j = 1; j <= pcnt && (ll)i * prime[j] <= n; ++j) {
                isp[i * prime[j]] = false;
                if (i % prime[j] == 0) {
                    phi[i * prime[j]] = phi[i] * prime[j];
                    break;
                }
                phi[i * prime[j]] = phi[i] * phi[prime[j]];
            }
        }
        for (int i = 1; i <= n; ++i) g[i] = mul(i, phi[i]);
        for (int i = 1; i <= n; ++i) sg[i] = add(sg[i - 1], g[i]);
    }

    int S1(ll n) { return mul(mul(n % MOD, (n + 1) % MOD), inv2); }
    int S2(ll n) {
        n %= MOD;
        return mul(mul(n, mul((n + 1) % MOD, (2 * n + 1) % MOD)), inv6);
    }

    int G(ll n) {
        if (n < N) return sg[n];
        if (mp_g.count(n)) return mp_g[n];
        int res = S2(n);
        for (ll l = 2, r; l <= n; l = r + 1) {
            r = n / (n / l);
            res = sub(res, mul(sub(S1(r), S1(l - 1)), G(n / l)));
        }
        return mp_g[n] = res;
    }

    void dfs(ll d, int hd, int pid, int &ans) {
        ans = add(ans, mul(hd, G(global_n / d)));
        for (int i = pid; i <= pcnt; ++i) {
            if (i > 1 && d > global_n / prime[i] / prime[i]) break;
            int c = 2;
            for (ll x = d * prime[i] * prime[i]; x <= global_n; x *= prime[i], ++c) {
                if (!vis_h[i][c]) {
                    int f = qpow(prime[i], c);
                    f = mul(f, sub(f, 1));
                    int g_val = mul(prime[i], prime[i] - 1);
                    int t = mul(prime[i], prime[i]);
                    for (int j = 1; j <= c; ++j) {
                        f = sub(f, mul(g_val, h[i][c - j]));
                        g_val = mul(g_val, t);
                    }
                    h[i][c] = f;
                    vis_h[i][c] = true;
                }
                if (h[i][c]) dfs(x, mul(hd, h[i][c]), i + 1, ans);
            }
        }
    }

    int solve(ll n) {
        global_n = n;
        int ans = 0;
        dfs(1, 1, 1, ans);
        return ans;
    }

    void init() {
        sieve(N - 1);
        for (int i = 1; i <= pcnt; ++i) h[i][0] = 1, h[i][1] = 0, vis_h[i][0] = vis_h[i][1] = true;
        inv2 = qpow(2, MOD - 2);
        inv6 = qpow(6, MOD - 2);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    PN_Sieve::init();
    ll n;
    cin >> n;
    cout << PN_Sieve::solve(n) << '\n';
    return 0;
}