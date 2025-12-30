#include <bits/stdc++.h>
using namespace std;

// Example: Represent vectors as arrays (for ℝ^n).
// In practice, linear space operations are abstract.
// Here we demonstrate vector addition and scalar multiplication.

struct Vector {
    vector<double> coords;
    Vector(int n = 0) : coords(n, 0.0) {}
    Vector operator+(const Vector& other) const {
        assert(coords.size() == other.coords.size());
        Vector res(coords.size());
        for (size_t i = 0; i < coords.size(); ++i)
            res.coords[i] = coords[i] + other.coords[i];
        return res;
    }
    Vector operator*(double scalar) const {
        Vector res(coords.size());
        for (size_t i = 0; i < coords.size(); ++i)
            res.coords[i] = coords[i] * scalar;
        return res;
    }
};

// Gaussian elimination to compute rank (dimension of column space).
int matrixRank(vector<vector<double>> A) {
    int n = A.size();
    if (n == 0) return 0;
    int m = A[0].size();
    int rank = 0;
    vector<bool> row_used(n, false);
    for (int col = 0; col < m; ++col) {
        int pivot = -1;
        for (int row = 0; row < n; ++row) {
            if (!row_used[row] && abs(A[row][col]) > 1e-9) {
                pivot = row;
                break;
            }
        }
        if (pivot == -1) continue;
        ++rank;
        row_used[pivot] = true;
        double div = A[pivot][col];
        for (int j = col; j < m; ++j)
            A[pivot][j] /= div;
        for (int row = 0; row < n; ++row) {
            if (row != pivot && abs(A[row][col]) > 1e-9) {
                double factor = A[row][col];
                for (int j = col; j < m; ++j)
                    A[row][j] -= factor * A[pivot][j];
            }
        }
    }
    return rank;
}

int main() {
    // Example: vectors in ℝ^3
    Vector v1(3), v2(3);
    v1.coords = {1, 2, 3};
    v2.coords = {4, 5, 6};
    Vector sum = v1 + v2;
    Vector scaled = v1 * 2.5;
    // Rank example
    vector<vector<double>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int r = matrixRank(mat);
    cout << "Rank: " << r << endl; // Should be 2
    return 0;
}