#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

// 高斯消元求解线性方程组 Ax = b
// 返回解向量，空向量表示无解或无穷多解
vector<double> gauss(vector<vector<double>> A, vector<double> b) {
    int n = A.size();
    // 构造增广矩阵
    vector<vector<double>> aug(n, vector<double>(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aug[i][j] = A[i][j];
        }
        aug[i][n] = b[i];
    }
    
    vector<int> where(n, -1); // 记录每列主元所在行
    
    for (int col = 0, row = 0; col < n && row < n; col++) {
        // 寻找主元
        int sel = row;
        for (int i = row; i < n; i++) {
            if (abs(aug[i][col]) > abs(aug[sel][col])) {
                sel = i;
            }
        }
        if (abs(aug[sel][col]) < EPS) continue;
        
        // 交换行
        for (int j = col; j <= n; j++) {
            swap(aug[sel][j], aug[row][j]);
        }
        where[col] = row;
        
        // 归一化
        for (int j = n; j >= col; j--) {
            aug[row][j] /= aug[row][col];
        }
        
        // 消元
        for (int i = 0; i < n; i++) {
            if (i != row && abs(aug[i][col]) > EPS) {
                double factor = aug[i][col];
                for (int j = col; j <= n; j++) {
                    aug[i][j] -= factor * aug[row][j];
                }
            }
        }
        row++;
    }
    
    // 构造解
    vector<double> x(n, 0);
    for (int i = 0; i < n; i++) {
        if (where[i] != -1) {
            x[i] = aug[where[i]][n];
        }
    }
    
    // 验证解是否正确
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        if (abs(sum - b[i]) > EPS) {
            return vector<double>(); // 无解
        }
    }
    
    return x;
}

// 计算行列式
double determinant(vector<vector<double>> A) {
    int n = A.size();
    double det = 1;
    for (int i = 0; i < n; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(A[j][i]) > abs(A[k][i])) k = j;
        }
        if (abs(A[k][i]) < EPS) return 0;
        swap(A[i], A[k]);
        if (i != k) det = -det;
        det *= A[i][i];
        for (int j = i + 1; j < n; j++) A[i][j] /= A[i][i];
        for (int j = 0; j < n; j++) {
            if (j != i && abs(A[j][i]) > EPS) {
                for (int k = i + 1; k < n; k++) {
                    A[j][k] -= A[i][k] * A[j][i];
                }
            }
        }
    }
    return det;
}

int main() {
    // 示例：求解线性方程组
    // 2x + y = 5
    // x - y = 1
    vector<vector<double>> A = {{2, 1}, {1, -1}};
    vector<double> b = {5, 1};
    
    vector<double> x = gauss(A, b);
    if (x.empty()) {
        cout << "No solution or infinite solutions" << endl;
    } else {
        cout << "Solution: x = " << x[0] << ", y = " << x[1] << endl;
    }
    
    // 计算行列式
    double det = determinant(A);
    cout << "Determinant: " << det << endl;
    
    return 0;
}