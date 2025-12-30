#include <iostream>
#include <vector>
using namespace std;

const int MOD = 998244353;
using ll = long long;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % MOD;
        a = (ll)a * a % MOD;
        b >>= 1;
    }
    return res;
}

// 拉格朗日插值求 f(k) mod MOD
// x, y 为点对，n 为点数，k 为待求点
int lagrange(const vector<int>& x, const vector<int>& y, int k) {
    int n = x.size();
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int num = 1, den = 1;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            num = (ll)num * (k - x[j] + MOD) % MOD;
            den = (ll)den * (x[i] - x[j] + MOD) % MOD;
        }
        ans = (ans + (ll)y[i] * num % MOD * qpow(den, MOD - 2)) % MOD;
    }
    return ans;
}

// 横坐标为连续整数 1..n 时的 O(n) 插值
// 已知 f(1), f(2), ..., f(n)，求 f(k)
int lagrange_continuous(const vector<int>& f, int k) {
    int n = f.size(); // f[0] = f(1), f[1] = f(2), ...
    if (k <= n) return f[k - 1];
    vector<int> pre(n + 2, 1), suf(n + 2, 1);
    for (int i = 1; i <= n; ++i) pre[i] = (ll)pre[i - 1] * (k - i) % MOD;
    for (int i = n; i >= 1; --i) suf[i] = (ll)suf[i + 1] * (k - i) % MOD;
    vector<int> fac(n + 2, 1), invfac(n + 2, 1);
    for (int i = 2; i <= n; ++i) fac[i] = (ll)fac[i - 1] * i % MOD;
    invfac[n] = qpow(fac[n], MOD - 2);
    for (int i = n - 1; i >= 0; --i) invfac[i] = (ll)invfac[i + 1] * (i + 1) % MOD;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int num = (ll)pre[i - 1] * suf[i + 1] % MOD;
        int den = (ll)invfac[i - 1] * invfac[n - i] % MOD;
        if ((n - i) & 1) den = MOD - den;
        ans = (ans + (ll)f[i - 1] * num % MOD * den) % MOD;
    }
    return ans;
}

int main() {
    // 示例：已知三点 (1,1), (2,4), (3,9)，求 f(4)
    vector<int> x = {1, 2, 3};
    vector<int> y = {1, 4, 9};
    cout << lagrange(x, y, 4) << endl; // 输出 16
    
    // 连续整数示例：已知 f(1)=1, f(2)=5, f(3)=14, f(4)=30，求 f(5)
    vector<int> f = {1, 5, 14, 30};
    cout << lagrange_continuous(f, 5) << endl; // 输出 55
    return 0;
}