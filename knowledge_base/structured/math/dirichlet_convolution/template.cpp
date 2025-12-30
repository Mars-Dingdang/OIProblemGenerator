#include <vector>
#include <iostream>

// 一般情形 Dirichlet 卷积，O(n log n)
std::vector<int> dirichlet_convolute(const std::vector<int>& f, const std::vector<int>& g) {
    int n = f.size() - 1;
    std::vector<int> h(n + 1, 0);
    for (int k = 1; k <= n; ++k) {
        for (int d = 1; k * d <= n; ++d) {
            h[k * d] += f[k] * g[d];
        }
    }
    return h;
}

// 若 g 为积性函数，O(n log log n)
std::vector<int> dirichlet_convolute_multiplicative(const std::vector<int>& f, const std::vector<int>& g) {
    int n = f.size() - 1;
    std::vector<int> h(f);
    std::vector<bool> vis(n + 1, false);
    for (int i = 2; i <= n; ++i) {
        if (vis[i]) continue;
        for (int k = n / i * i; k; k -= i) {
            vis[k] = true;
            int d = k;
            while (true) {
                d /= i;
                h[k] += h[d] * g[k / d];
                if (d % i) break;
            }
        }
    }
    return h;
}

// 若结果 h 为积性函数，O(n) 线性筛
std::vector<int> dirichlet_convolute_multiplicative_result(const std::vector<int>& f, const std::vector<int>& g, int n) {
    std::vector<int> h(n + 1, 0);
    std::vector<int> primes;
    std::vector<bool> is_composite(n + 1, false);
    h[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!is_composite[i]) {
            primes.push_back(i);
            // 计算 h(p^e) 暴力递推
            long long p_pow = i;
            int e = 1;
            while (p_pow <= n) {
                h[p_pow] = 0;
                for (int j = 0; j <= e; ++j) {
                    h[p_pow] += f[(int)std::pow(i, j)] * g[(int)std::pow(i, e - j)];
                }
                p_pow *= i;
                ++e;
            }
        }
        for (int p : primes) {
            if (i * p > n) break;
            is_composite[i * p] = true;
            if (i % p == 0) {
                // 利用积性 h(i * p) = h(i / p^e) * h(p^{e+1})
                int temp = i, e = 0;
                while (temp % p == 0) {
                    temp /= p;
                    ++e;
                }
                h[i * p] = h[temp] * h[(int)std::pow(p, e + 1)];
                break;
            } else {
                h[i * p] = h[i] * h[p];
            }
        }
    }
    return h;
}