#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 300;
const double eps = 1e-9;

double mat[MAXN][MAXN];

// 高斯消元求行列式（实数）
double gauss_det(int n) {
    double res = 1;
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i + 1; j < n; j++)
            if (fabs(mat[j][i]) > fabs(mat[pivot][i]))
                pivot = j;
        if (fabs(mat[pivot][i]) < eps) return 0;
        if (pivot != i) {
            for (int j = i; j < n; j++)
                swap(mat[i][j], mat[pivot][j]);
            res = -res;
        }
        res *= mat[i][i];
        for (int j = i + 1; j < n; j++) {
            double ratio = mat[j][i] / mat[i][i];
            for (int k = i; k < n; k++)
                mat[j][k] -= mat[i][k] * ratio;
        }
    }
    return fabs(res);
}

// 构建无向图的Laplace矩阵
void build_laplace(int n, const vector<pair<int, int>>& edges) {
    memset(mat, 0, sizeof(mat));
    for (auto& e : edges) {
        int u = e.first, v = e.second;
        mat[u][u] += 1;
        mat[v][v] += 1;
        mat[u][v] -= 1;
        mat[v][u] -= 1;
    }
}

// 示例：计算删去第k行第k列后的行列式
double solve(int n, int k, const vector<pair<int, int>>& edges) {
    build_laplace(n, edges);
    // 删除第k行第k列
    for (int i = k; i < n - 1; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = mat[i + 1][j];
    for (int j = k; j < n - 1; j++)
        for (int i = 0; i < n - 1; i++)
            mat[i][j] = mat[i][j + 1];
    return gauss_det(n - 1);
}