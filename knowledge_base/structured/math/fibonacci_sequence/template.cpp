#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;

// 矩阵快速幂法 O(log n)
struct Matrix {
    ll a[2][2];
    Matrix() { a[0][0] = a[0][1] = a[1][0] = a[1][1] = 0; }
    Matrix operator*(const Matrix& other) const {
        Matrix res;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j]) % MOD;
                }
            }
        }
        return res;
    }
};

Matrix mat_pow(Matrix base, ll exp) {
    Matrix res;
    res.a[0][0] = res.a[1][1] = 1; // 单位矩阵
    while (exp > 0) {
        if (exp & 1) res = res * base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}

ll fibonacci_matrix(ll n) {
    if (n <= 1) return n;
    Matrix base;
    base.a[0][0] = 0; base.a[0][1] = 1;
    base.a[1][0] = 1; base.a[1][1] = 1;
    Matrix res = mat_pow(base, n - 1);
    return res.a[1][1];
}

// 快速倍增法 O(log n) - 返回 {F_n, F_{n+1}}
pair<ll, ll> fibonacci_fast_doubling(ll n) {
    if (n == 0) return {0, 1};
    auto [a, b] = fibonacci_fast_doubling(n >> 1);
    ll c = a * ((2 * b - a) % MOD + MOD) % MOD;
    ll d = (a * a % MOD + b * b % MOD) % MOD;
    if (n & 1) return {d, (c + d) % MOD};
    else return {c, d};
}

// 计算斐波那契数模 m 的周期（皮萨诺周期）
ll pisano_period(ll m) {
    ll a = 0, b = 1, period = 0;
    do {
        ll c = (a + b) % m;
        a = b;
        b = c;
        period++;
    } while (!(a == 0 && b == 1));
    return period;
}

int main() {
    ll n;
    cin >> n;
    cout << "Matrix method: " << fibonacci_matrix(n) << endl;
    auto [fn, fn1] = fibonacci_fast_doubling(n);
    cout << "Fast doubling: " << fn << endl;
    return 0;
}