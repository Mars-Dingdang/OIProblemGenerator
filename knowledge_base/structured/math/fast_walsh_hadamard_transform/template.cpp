#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1 << 20;
const ll MOD = 998244353;
ll A[MAXN], B[MAXN], C[MAXN];
int n, lim;

void FWT_or(ll *a, int type) {
    for (int mid = 1; mid < lim; mid <<= 1)
        for (int block = mid << 1, j = 0; j < lim; j += block)
            for (int k = 0; k < mid; ++k)
                (a[j + k + mid] += a[j + k] * type) %= MOD;
}

void FWT_and(ll *a, int type) {
    for (int mid = 1; mid < lim; mid <<= 1)
        for (int block = mid << 1, j = 0; j < lim; j += block)
            for (int k = 0; k < mid; ++k)
                (a[j + k] += a[j + k + mid] * type) %= MOD;
}

void FWT_xor(ll *a, int type) {
    ll inv2 = (MOD + 1) / 2;
    for (int mid = 1; mid < lim; mid <<= 1)
        for (int block = mid << 1, j = 0; j < lim; j += block)
            for (int k = 0; k < mid; ++k) {
                ll x = a[j + k], y = a[j + k + mid];
                a[j + k] = (x + y) % MOD;
                a[j + k + mid] = (x - y + MOD) % MOD;
                if (type == -1) {
                    a[j + k] = a[j + k] * inv2 % MOD;
                    a[j + k + mid] = a[j + k + mid] * inv2 % MOD;
                }
            }
}

int main() {
    // Example: convolution for bitwise OR
    cin >> n;
    lim = 1 << n;
    for (int i = 0; i < lim; ++i) cin >> A[i];
    for (int i = 0; i < lim; ++i) cin >> B[i];
    FWT_or(A, 1);
    FWT_or(B, 1);
    for (int i = 0; i < lim; ++i) C[i] = A[i] * B[i] % MOD;
    FWT_or(C, -1);
    for (int i = 0; i < lim; ++i) cout << (C[i] + MOD) % MOD << " ";
    return 0;
}