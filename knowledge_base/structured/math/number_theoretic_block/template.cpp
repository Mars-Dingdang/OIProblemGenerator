#include <iostream>
using ll = long long;

// 计算 ∑_{i=1}^{n} ⌊n/i⌋ 的示例
ll H(int n) {
    ll res = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        res += (ll)(r - l + 1) * (n / l);
    }
    return res;
}

// 通用数论分块模板（假设有前缀和函数 pre_f）
// ll pre_f(int x); // 返回 ∑_{i=1}^{x} f(i)
// ll g(int x); // 返回 g(x)
ll number_theoretic_block(int n) {
    ll res = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        // 假设 pre_f 和 g 已定义
        // res += (pre_f(r) - pre_f(l - 1)) * g(n / l);
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t, n;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        std::cout << H(n) << '\n';
    }
    return 0;
}