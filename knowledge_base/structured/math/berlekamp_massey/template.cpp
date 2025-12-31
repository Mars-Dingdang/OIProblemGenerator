#include <vector>
#include <cstdint>

using ll = int64_t;
using vi = std::vector<ll>;
using vvi = std::vector<vi>;

// Berlekamp-Massey Algorithm (II): Computes shortest recurrence for prefix
// Assumes modular arithmetic (works in any field)
// Returns the shortest linear recurrence array r such that
// for all k >= len(r), a[k] = sum_{i} r[i] * a[k - i]

vi berlekamp_massey(const vi& a) {
    int n = a.size();
    vi r = {1}; // recurrence: r[0]*a[i] + r[1]*a[i-1] + ... = 0
    vi last = {1};
    ll v = 1; // last non-zero discrepancy value
    int s = 0; // shift counter

    for (int k = 1; k < n; ++k) {
        // Compute discrepancy u = sum_{i=0}^{len(r)-1} r[i] * a[k - i]
        ll u = 0;
        for (int i = 0; i < (int)r.size(); ++i) {
            u += r[i] * a[k - i];
            // Assuming mod arithmetic; uncomment next line if needed
            // u %= mod; if (u < 0) u += mod;
        }

        if (u == 0) {
            s++;
            continue;
        }

        // Make a copy of current r to potentially update
        vi new_r = r;
        if ((int)new_r.size() < last.size() + s) {
            new_r.resize(last.size() + s, 0);
        }

        // Subtract (u/v) * (shifted last) from new_r
        ll coef = u * mod_inv(v); // Requires modular inverse
        for (int i = 0; i < (int)last.size(); ++i) {
            new_r[i + s] -= coef * last[i];
            // Mod handling here too
        }

        if ((int)r.size() < (int)last.size() + s) {
            last = r;
            v = u;
            s = 0;
        }

        r = std::move(new_r);
        s = 0; // reset shift after correction
    }

    return r;
}

// Example helper: modular inverse (Fermat's little theorem, prime mod)
ll mod_inv(ll a, ll mod = 998244353) {
    ll res = 1, b = mod - 2;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}