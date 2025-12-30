#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 求解 Pell 方程 x^2 - D y^2 = 1 的基本解 (x1, y1)
// 返回 (x1, y1)
pair<ll, ll> pell_fundamental(int D) {
    int sqrtD = sqrt(D);
    if (sqrtD * sqrtD == D) {
        // D 是完全平方数，只有平凡解
        return {1, 0};
    }
    // 连分数展开 √D
    vector<int> a;
    int m = 0, d = 1, a0 = sqrtD;
    int p0 = a0, q0 = 1;
    a.push_back(a0);
    map<pair<int, int>, int> seen;
    seen[{p0, q0}] = 0;
    int k = 0;
    while (true) {
        m = d * a.back() - m;
        d = (D - m * m) / d;
        a.push_back((a0 + m) / d);
        if (seen.count({m, d})) {
            break;
        }
        seen[{m, d}] = ++k;
    }
    // 计算渐近分数
    int l = a.size() - 2; // 循环节长度（去掉第一个 a0 和最后一个重复的）
    vector<ll> A = {1, (ll)a[0]}, B = {0, 1};
    for (int i = 1; i <= 2 * l; ++i) {
        int idx = (i <= l ? i : (i - 1) % l + 1);
        A.push_back(a[idx] * A.back() + A[A.size() - 2]);
        B.push_back(a[idx] * B.back() + B[B.size() - 2]);
    }
    if (l % 2 == 0) {
        return {A[l], B[l]};
    } else {
        return {A[2 * l], B[2 * l]};
    }
}

// 生成 Pell 方程的第 k 个解 (x_k, y_k)，其中 (x1, y1) 是基本解
pair<ll, ll> pell_solution(ll x1, ll y1, int k) {
    if (k == 0) return {1, 0};
    if (k < 0) {
        auto [x, y] = pell_solution(x1, y1, -k);
        return {x, -y};
    }
    // 使用快速幂计算 (x1 + y1√D)^k
    ll xk = 1, yk = 0; // 对应 1 + 0√D
    ll X = x1, Y = y1;
    while (k) {
        if (k & 1) {
            // 乘法: (xk + yk√D) * (X + Y√D)
            ll nx = xk * X + D * yk * Y;
            ll ny = xk * Y + yk * X;
            xk = nx;
            yk = ny;
        }
        // 平方: (X + Y√D)^2
        ll nx = X * X + D * Y * Y;
        ll ny = 2 * X * Y;
        X = nx;
        Y = ny;
        k >>= 1;
    }
    return {xk, yk};
}

// 示例：求解 x^2 - 41 y^2 = 1
int main() {
    int D = 41;
    auto [x1, y1] = pell_fundamental(D);
    cout << "Fundamental solution: (" << x1 << ", " << y1 << ")" << endl;
    for (int k = 1; k <= 5; ++k) {
        auto [x, y] = pell_solution(x1, y1, k);
        cout << "k=" << k << ": (" << x << ", " << y << ")" << endl;
    }
    return 0;
}