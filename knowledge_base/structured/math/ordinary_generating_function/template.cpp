#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 998244353; // Or other modulus
const int G = 3;          // Primitive root for NTT

// Example: Compute OGF for sequence a and b, return convolution (a * b)
vector<ll> multiply_ogf(const vector<ll>& a, const vector<ll>& b) {
    // Using NTT for convolution (assuming MOD is NTT-friendly)
    int n = 1;
    while (n < (int)a.size() + (int)b.size() - 1) n <<= 1;
    vector<ll> fa(n), fb(n);
    copy(a.begin(), a.end(), fa.begin());
    copy(b.begin(), b.end(), fb.begin());
    // NTT(fa, n, 1); NTT(fb, n, 1); // Forward NTT
    for (int i = 0; i < n; i++) fa[i] = fa[i] * fb[i] % MOD;
    // NTT(fa, n, -1); // Inverse NTT
    fa.resize(a.size() + b.size() - 1);
    return fa;
}

// Example: Compute closed form for geometric series ∑ p^n x^n = 1/(1 - p x)
ll geometric_ogf(ll p, ll x, int n) {
    // Evaluate coefficient of x^n in 1/(1 - p x) = p^n
    ll res = 1;
    while (n--) res = res * p % MOD;
    return res;
}

// Example: Fibonacci OGF: F(x) = x / (1 - x - x^2)
ll fibonacci_ogf(int n) {
    // Using closed form: a_n = (φ^n - ψ^n)/√5
    const ll phi = (1 + sqrt(5)) / 2; // Approximate, use modular sqrt for exact
    const ll psi = (1 - sqrt(5)) / 2;
    ll res = (pow_mod(phi, n) - pow_mod(psi, n)) * inv_mod(sqrt(5)) % MOD;
    return (res + MOD) % MOD;
}

int main() {
    // Example usage: compute convolution of two sequences
    vector<ll> a = {1, 2, 3}; // OGF: 1 + 2x + 3x^2
    vector<ll> b = {1, 1};    // OGF: 1 + x
    vector<ll> c = multiply_ogf(a, b); // OGF: 1 + 3x + 5x^2 + 3x^3
    for (ll x : c) cout << x << ' ';
    cout << endl;
    return 0;
}