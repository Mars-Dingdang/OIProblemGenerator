#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;

// 错位排列数 D[n] = n! * sum_{k=0}^{n} (-1)^k / k!
// 递推式: D[0] = 1, D[1] = 0, D[n] = (n-1) * (D[n-1] + D[n-2]) for n >= 2

ll fact[MAXN], inv_fact[MAXN];
ll D[MAXN];

ll mod_pow(ll a, ll e) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

void precompute(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % MOD;
    inv_fact[n] = mod_pow(fact[n], MOD-2);
    for (int i = n-1; i >= 0; i--) inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
    // 使用容斥公式计算 D[n]
    D[0] = 1;
    for (int i = 1; i <= n; i++) {
        D[i] = 0;
        ll sign = 1;
        for (int k = 0; k <= i; k++) {
            D[i] = (D[i] + sign * inv_fact[k]) % MOD;
            sign = -sign;
        }
        D[i] = (D[i] * fact[i]) % MOD;
        if (D[i] < 0) D[i] += MOD;
    }
    // 或者使用递推式（更高效）
    // D[0] = 1; D[1] = 0;
    // for (int i = 2; i <= n; i++)
    //     D[i] = (i-1) * (D[i-1] + D[i-2]) % MOD;
}

int main() {
    int n = 10; // 示例
    precompute(n);
    for (int i = 0; i <= n; i++) {
        cout << "D[" << i << "] = " << D[i] << endl;
    }
    return 0;
}