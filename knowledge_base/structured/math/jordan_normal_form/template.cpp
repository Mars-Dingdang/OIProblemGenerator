#include <bits/stdc++.h>
using namespace std;
using Matrix = vector<vector<double>>;
using Complex = complex<double>;

// 注意：这是一个简化的概念性框架。
// 完整的 Jordan 标准型算法涉及计算特征值、特征向量、广义特征向量和 Smith 标准型，
// 在竞赛编程中很少需要完整实现。
// 这里提供一个用于幂零 Jordan 块生成的辅助函数。

// 生成一个大小为 r 的幂零 Jordan 块（特征值为 0）
Matrix nilpotent_jordan_block(int r) {
    Matrix J(r, vector<double>(r, 0.0));
    for (int i = 0; i < r - 1; ++i) {
        J[i][i+1] = 1.0;
    }
    return J;
}

// 生成一个大小为 r，特征值为 lambda 的 Jordan 块
Matrix jordan_block(int r, double lambda) {
    Matrix J = nilpotent_jordan_block(r);
    for (int i = 0; i < r; ++i) {
        J[i][i] = lambda;
    }
    return J;
}

// 将 Jordan 块列表组装成块对角矩阵（Jordan 标准型）
Matrix assemble_jordan_form(const vector<pair<int, double>>& blocks) {
    // blocks: 每个元素是 (块大小, 特征值)
    int total_n = 0;
    for (auto& [sz, _] : blocks) total_n += sz;
    Matrix J(total_n, vector<double>(total_n, 0.0));
    int row_offset = 0;
    for (auto& [sz, lambda] : blocks) {
        Matrix blk = jordan_block(sz, lambda);
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                J[row_offset + i][row_offset + j] = blk[i][j];
            }
        }
        row_offset += sz;
    }
    return J;
}

int main() {
    // 示例：构建一个由两个 Jordan 块组成的矩阵
    // 块1: 大小3，特征值2.0
    // 块2: 大小2，特征值2.0（另一个块）
    // 块3: 大小1，特征值5.0
    vector<pair<int, double>> blocks = {{3, 2.0}, {2, 2.0}, {1, 5.0}};
    Matrix J = assemble_jordan_form(blocks);
    // 输出矩阵（示例）
    for (int i = 0; i < J.size(); ++i) {
        for (int j = 0; j < J[i].size(); ++j) {
            cout << J[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}