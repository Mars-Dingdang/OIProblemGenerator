#include <vector>
#include <cstdint>
using namespace std;
using Matrix = vector<vector<int>>;
using i64 = int64_t;

// 将矩阵转换为上 Hessenberg 形式（相似变换）
Matrix to_upper_Hessenberg(const Matrix &M, int mod) {
    Matrix H = M;
    int n = H.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if ((H[i][j] %= mod) < 0) H[i][j] += mod;
    for (int i = 0; i < n - 1; ++i) {
        int pivot = i + 1;
        for (; pivot < n; ++pivot)
            if (H[pivot][i] != 0) break;
        if (pivot == n) continue;
        if (pivot != i + 1) {
            for (int j = i; j < n; ++j) swap(H[i + 1][j], H[pivot][j]);
            for (int j = 0; j < n; ++j) swap(H[j][i + 1], H[j][pivot]);
        }
        for (int j = i + 2; j < n; ++j) {
            for (;;) {
                if (H[j][i] == 0) break;
                if (H[i + 1][i] == 0) {
                    for (int k = i; k < n; ++k) swap(H[i + 1][k], H[j][k]);
                    for (int k = 0; k < n; ++k) swap(H[k][i + 1], H[k][j]);
                    break;
                }
                if (H[j][i] >= H[i + 1][i]) {
                    int q = H[j][i] / H[i + 1][i], mq = mod - q;
                    for (int k = i; k < n; ++k)
                        H[j][k] = (H[j][k] + i64(mq) * H[i + 1][k]) % mod;
                    for (int k = 0; k < n; ++k)
                        H[k][i + 1] = (H[k][i + 1] + i64(q) * H[k][j]) % mod;
                } else {
                    int q = H[i + 1][i] / H[j][i], mq = mod - q;
                    for (int k = i; k < n; ++k)
                        H[i + 1][k] = (H[i + 1][k] + i64(mq) * H[j][k]) % mod;
                    for (int k = 0; k < n; ++k)
                        H[k][j] = (H[k][j] + i64(q) * H[k][i + 1]) % mod;
                }
            }
        }
    }
    return H;
}

// 计算特征多项式，返回系数向量（从常数项到最高次项）
vector<int> get_charpoly(const Matrix &M, int mod) {
    Matrix H = to_upper_Hessenberg(M, mod);
    int n = H.size();
    vector<vector<int>> p(n + 1);
    p[0] = {1 % mod};
    for (int i = 1; i <= n; ++i) {
        const vector<int> &pi_1 = p[i - 1];
        vector<int> &pi = p[i];
        pi.resize(i + 1, 0);
        int v = mod - H[i - 1][i - 1];
        if (v == mod) v -= mod;
        for (int j = 0; j < i; ++j) {
            pi[j] = (pi[j] + i64(v) * pi_1[j]) % mod;
            if ((pi[j + 1] += pi_1[j]) >= mod) pi[j + 1] -= mod;
        }
        int t = 1;
        for (int j = 1; j < i; ++j) {
            t = i64(t) * H[i - j][i - j - 1] % mod;
            int prod = i64(t) * H[i - j - 1][i - 1] % mod;
            if (prod == 0) continue;
            prod = mod - prod;
            for (int k = 0; k <= i - j - 1; ++k)
                pi[k] = (pi[k] + i64(prod) * p[i - j - 1][k]) % mod;
        }
    }
    return p[n];
}