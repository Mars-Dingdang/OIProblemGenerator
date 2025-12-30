#include <bits/stdc++.h>
using namespace std;

// 快速幂: a^b mod mod
long long qpow(long long a, long long b, long long mod) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// 欧拉函数 phi(n)
long long phi(long long n) {
    long long ans = n;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) ans = ans / n * (n - 1);
    return ans;
}

// 旋转对称群 C_n（仅旋转）的 Polya 计数
// n 个珠子，m 种颜色，模 mod
long long polya_rotate(long long n, long long m, long long mod) {
    long long ans = 0;
    // 枚举旋转步长 k（即旋转 k 个位置）
    for (long long k = 0; k < n; ++k) {
        // gcd(k, n) 是置换的轮换数
        long long g = __gcd(k, n);
        ans = (ans + qpow(m, g, mod)) % mod;
    }
    ans = ans * qpow(n, mod - 2, mod) % mod; // 乘上 1/n
    return ans;
}

// 二面体群 D_{2n}（旋转 + 翻转）的 Polya 计数
long long polya_dihedral(long long n, long long m, long long mod) {
    long long ans = 0;
    // 旋转部分（与 C_n 相同）
    for (long long k = 0; k < n; ++k) {
        long long g = __gcd(k, n);
        ans = (ans + qpow(m, g, mod)) % mod;
    }
    // 翻转部分
    if (n & 1) { // n 为奇数
        // 对称轴过一顶点及其对边中点，有 n 条对称轴，每个置换有 1 个 1‑轮换和 (n-1)/2 个 2‑轮换
        ans = (ans + n * qpow(m, (n + 1) / 2, mod)) % mod;
    } else { // n 为偶数
        // 对称轴过相对顶点：n/2 条，每个置换有 2 个 1‑轮换和 (n-2)/2 个 2‑轮换
        ans = (ans + (n / 2) * qpow(m, n / 2 + 1, mod)) % mod;
        // 对称轴过相对边中点：n/2 条，每个置换有 n/2 个 2‑轮换
        ans = (ans + (n / 2) * qpow(m, n / 2, mod)) % mod;
    }
    ans = ans * qpow(2 * n, mod - 2, mod) % mod; // 乘上 1/(2n)
    return ans;
}

int main() {
    // 示例：n 个珠子，m 种颜色，模 1e9+7
    long long n = 4, m = 3, mod = 1e9 + 7;
    cout << "旋转对称 (C_n): " << polya_rotate(n, m, mod) << endl;
    cout << "二面体群 (D_{2n}): " << polya_dihedral(n, m, mod) << endl;
    return 0;
}