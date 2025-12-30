#include <bits/stdc++.h>
using namespace std;

// 初等行变换类型
enum RowOpType {
    MULTIPLY,   // 倍乘
    SWAP,       // 对换
    ADD         // 倍加
};

// 矩阵结构体
struct Matrix {
    int n, m;
    vector<vector<double>> mat;
    
    Matrix(int n, int m) : n(n), m(m), mat(n, vector<double>(m, 0)) {}
    
    // 倍乘操作：第i行乘以k
    void row_multiply(int i, double k) {
        for (int j = 0; j < m; j++) {
            mat[i][j] *= k;
        }
    }
    
    // 对换操作：交换第i行和第j行
    void row_swap(int i, int j) {
        swap(mat[i], mat[j]);
    }
    
    // 倍加操作：第j行的k倍加到第i行
    void row_add(int i, int j, double k) {
        for (int col = 0; col < m; col++) {
            mat[i][col] += k * mat[j][col];
        }
    }
    
    // 打印矩阵
    void print() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// 生成倍乘矩阵 D_i(k)
Matrix generate_multiply_matrix(int n, int i, double k) {
    Matrix D(n, n);
    for (int j = 0; j < n; j++) {
        D.mat[j][j] = 1.0;
    }
    D.mat[i][i] = k;
    return D;
}

// 生成对换矩阵 P_ij
Matrix generate_swap_matrix(int n, int i, int j) {
    Matrix P(n, n);
    for (int k = 0; k < n; k++) {
        P.mat[k][k] = 1.0;
    }
    P.mat[i][i] = 0.0;
    P.mat[j][j] = 0.0;
    P.mat[i][j] = 1.0;
    P.mat[j][i] = 1.0;
    return P;
}

// 生成倍加矩阵 T_ij(k)
Matrix generate_add_matrix(int n, int i, int j, double k) {
    Matrix T(n, n);
    for (int r = 0; r < n; r++) {
        T.mat[r][r] = 1.0;
    }
    T.mat[i][j] = k;
    return T;
}

// 矩阵乘法
Matrix matrix_multiply(const Matrix& A, const Matrix& B) {
    assert(A.m == B.n);
    Matrix C(A.n, B.m);
    for (int i = 0; i < A.n; i++) {
        for (int j = 0; j < B.m; j++) {
            for (int k = 0; k < A.m; k++) {
                C.mat[i][j] += A.mat[i][k] * B.mat[k][j];
            }
        }
    }
    return C;
}

int main() {
    // 示例：使用初等变换将矩阵化为行阶梯形
    Matrix A(3, 3);
    A.mat = {{2, 1, 1}, {4, -6, 0}, {-2, 7, 2}};
    
    cout << "原始矩阵：" << endl;
    A.print();
    
    // 倍乘：第一行乘以0.5
    A.row_multiply(0, 0.5);
    
    // 倍加：第二行减去第一行的4倍
    A.row_add(1, 0, -4);
    
    // 倍加：第三行加上第一行的2倍
    A.row_add(2, 0, 2);
    
    // 倍乘：第二行乘以-0.125
    A.row_multiply(1, -0.125);
    
    // 倍加：第三行减去第二行的8倍
    A.row_add(2, 1, -8);
    
    cout << "\n行阶梯形矩阵：" << endl;
    A.print();
    
    return 0;
}