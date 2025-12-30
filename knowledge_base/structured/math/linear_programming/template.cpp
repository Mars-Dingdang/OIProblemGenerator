#include <bits/stdc++.h>
using namespace std;

// 单纯形法求解标准线性规划:
// max c^T x
// s.t. Ax <= b, x >= 0
// 返回最优值，无解返回 -INF，无界返回 INF
const double EPS = 1e-8;
const double INF = 1e20;

struct Simplex {
    vector<vector<double>> a;
    vector<double> b, c;
    vector<int> basic, nonbasic;
    int m, n;
    
    Simplex(vector<vector<double>> A, vector<double> B, vector<double> C) {
        m = B.size();
        n = C.size();
        a = A;
        b = B;
        c = C;
        basic.resize(m);
        nonbasic.resize(n);
        for (int i = 0; i < m; i++) basic[i] = n + i;
        for (int i = 0; i < n; i++) nonbasic[i] = i;
    }
    
    void pivot(int r, int s) {
        double inv = 1.0 / a[r][s];
        for (int i = 0; i < m; i++) if (i != r) {
            double factor = a[i][s] * inv;
            for (int j = 0; j < n; j++) a[i][j] -= factor * a[r][j];
            b[i] -= factor * b[r];
        }
        for (int j = 0; j < n; j++) if (j != s) a[r][j] *= inv;
        b[r] *= inv;
        a[r][s] = inv;
        swap(basic[r], nonbasic[s]);
    }
    
    double solve() {
        while (true) {
            int s = -1;
            for (int j = 0; j < n; j++) {
                if (c[j] > EPS) { s = j; break; }
            }
            if (s == -1) break;
            int r = -1;
            double min_ratio = INF;
            for (int i = 0; i < m; i++) {
                if (a[i][s] > EPS) {
                    double ratio = b[i] / a[i][s];
                    if (ratio < min_ratio) {
                        min_ratio = ratio;
                        r = i;
                    }
                }
            }
            if (r == -1) return INF; // 无界
            pivot(r, s);
        }
        double res = 0;
        for (int i = 0; i < m; i++) {
            if (basic[i] < n) res += c[basic[i]] * b[i];
        }
        return res;
    }
};

int main() {
    // 示例: max 5x1 + 6x2
    // s.t. 4x1 + 7x2 <= 66
    //      7x1 + 3x2 <= 60
    //      8x1 + 6x2 <= 96
    //      x1, x2 >= 0
    vector<vector<double>> A = {{4, 7}, {7, 3}, {8, 6}};
    vector<double> B = {66, 60, 96};
    vector<double> C = {5, 6};
    Simplex simplex(A, B, C);
    double ans = simplex.solve();
    cout << "Maximum profit: " << ans << endl; // 输出 66
    return 0;
}