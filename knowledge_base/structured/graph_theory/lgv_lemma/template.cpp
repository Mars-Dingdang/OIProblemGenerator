#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

using ll = long long;
constexpr int MOD = 1e9 + 7;

ll modpow(ll base, ll exp, ll mod) {
    ll res = 1;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

ll inv(ll x, ll mod) { return modpow(x, mod - 2, mod); }

// 计算组合数 C(n, k) mod MOD，预处理阶乘
const int MAX = 200000;
ll fact[MAX + 1];

void precompute_factorials() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
}

ll C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv(fact[k], MOD) % MOD * inv(fact[n - k], MOD) % MOD;
}

// 高斯消元求行列式 (mod p)
ll det(vector<vector<ll>>& mat) {
    int n = mat.size();
    ll res = 1;
    for (int i = 0; i < n; ++i) {
        int pivot = -1;
        for (int j = i; j < n; ++j) {
            if (mat[j][i] != 0) {
                pivot = j;
                break;
            }
        }
        if (pivot == -1) return 0;
        if (pivot != i) {
            swap(mat[i], mat[pivot]);
            res = (MOD - res) % MOD; // 行交换改变符号
        }
        res = (res * mat[i][i]) % MOD;
        ll inv_val = inv(mat[i][i], MOD);
        for (int j = i + 1; j < n; ++j) {
            ll mul = (mat[j][i] * inv_val) % MOD;
            for (int k = i; k < n; ++k) {
                mat[j][k] = (mat[j][k] - mul * mat[i][k] % MOD + MOD) % MOD;
            }
        }
    }
    return res;
}

// 示例：构建 e(A_i, B_j) 矩阵并计算 LGV 行列式
// 对于网格图从 (1, a_i) 到 (n, b_j)，路径数为 C(n-1 + b_j - a_i, n-1)
ll lgv_lemma_example(vector<int>& a, vector<int>& b, int n) {
    int k = a.size();
    vector<vector<ll>> mat(k, vector<ll>(k));
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            if (a[i] <= b[j]) {
                mat[i][j] = C(n - 1 + b[j] - a[i], n - 1);
            } else {
                mat[i][j] = 0;
            }
        }
    }
    return det(mat);
}