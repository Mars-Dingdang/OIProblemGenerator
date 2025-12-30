#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;

// Example: Counting labeled connected graphs via polynomial ln (EGF)
// G(x) = exp(C(x)) => C(x) = ln(G(x))
// g_n = 2^{C(n,2)}, c_n derived via polynomial ln.

vector<ll> polynomial_ln(const vector<ll>& G) {
    // G[0] = 1, returns C = ln(G) mod x^{n+1}
    int n = (int)G.size() - 1;
    vector<ll> deriv(n);
    for (int i = 1; i <= n; ++i) deriv[i-1] = G[i] * i % MOD;
    // Compute inverse of G
    vector<ll> invG(n+1);
    invG[0] = 1;
    for (int i = 1; i <= n; ++i) {
        invG[i] = 0;
        for (int j = 1; j <= i; ++j) {
            invG[i] = (invG[i] - G[j] * invG[i-j]) % MOD;
        }
        invG[i] = (invG[i] + MOD) % MOD;
    }
    // Multiply deriv * invG
    vector<ll> C(n+1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            C[i+1] = (C[i+1] + deriv[j] * invG[i-j]) % MOD;
        }
        C[i+1] = C[i+1] * inv(i+1, MOD) % MOD; // modular inverse
    }
    C[0] = 0;
    return C;
}

// Example: Counting unlabeled trees via Euler transform
// F(x) = x * E(F(x)) where E is Euler transform.
vector<ll> euler_transform(const vector<ll>& a, int n) {
    vector<ll> b(n+1), c(n+1);
    b[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int d = 1; d <= i; ++d) {
            if (i % d == 0) c[i] = (c[i] + d * a[d]) % MOD;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            b[i] = (b[i] + c[j] * b[i-j]) % MOD;
        }
        b[i] = b[i] * inv(i, MOD) % MOD;
    }
    return b;
}

int main() {
    // Example usage for labeled connected graphs up to n=5
    int n = 5;
    vector<ll> G(n+1);
    G[0] = 1;
    for (int i = 1; i <= n; ++i) {
        G[i] = modpow(2, i*(i-1)/2, MOD); // 2^{C(i,2)}
    }
    vector<ll> C = polynomial_ln(G);
    // C[i] now is number of labeled connected graphs on i vertices
    return 0;
}