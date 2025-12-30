#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Baby-step Giant-step (BSGS) for a^x ≡ b (mod m), a ⟂ m
// Returns minimal x >= 0, or -1 if no solution
ll bsgs(ll a, ll b, ll m) {
    a %= m; b %= m;
    if (m == 1) return 0;
    if (b == 1) return 0;
    ll k = 0, ak = 1;
    while (true) {
        ll g = __gcd(a, m);
        if (g == 1) break;
        if (b % g) return -1;
        b /= g; m /= g;
        ak = ak * (a / g) % m;
        k++;
        if (ak == b) return k;
    }
    // Now a ⟂ m
    ll n = sqrt(m) + 1;
    ll an = 1;
    for (int i = 0; i < n; i++) an = an * a % m;
    unordered_map<ll, ll> vals;
    for (ll q = 0, cur = b; q <= n; q++) {
        vals[cur] = q;
        cur = cur * a % m;
    }
    for (ll p = 1, cur = ak; p <= n; p++) {
        cur = cur * an % m;
        if (vals.count(cur)) {
            return n * p - vals[cur] + k;
        }
    }
    return -1;
}

// Example usage
int main() {
    ll a, b, m;
    cin >> a >> b >> m;
    ll res = bsgs(a, b, m);
    if (res == -1) cout << "No solution\n";
    else cout << res << "\n";
    return 0;
}