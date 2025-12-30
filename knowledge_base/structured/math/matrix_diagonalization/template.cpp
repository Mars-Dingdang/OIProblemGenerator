#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld EPS = 1e-9;

// Solve eigenvalue problem A*x = lambda*x for real symmetric matrix A.
// Returns eigenvalues and eigenvectors (columns).
// For simplicity, this is a naive power iteration example for largest eigenvalue.
// Real diagonalization requires specialized libraries (e.g., LAPACK).
pair<vector<ld>, vector<vector<ld>>> power_iteration(const vector<vector<ld>>& A, int max_iter = 1000) {
    int n = A.size();
    vector<ld> x(n, 1.0 / sqrt(n)); // initial guess
    for (int iter = 0; iter < max_iter; ++iter) {
        vector<ld> y(n, 0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                y[i] += A[i][j] * x[j];
        ld norm = 0;
        for (ld v : y) norm += v * v;
        norm = sqrt(norm);
        for (ld& v : y) v /= norm;
        if (inner_product(x.begin(), x.end(), y.begin(), 0.0) > 1 - EPS) {
            x = y;
            break;
        }
        x = y;
    }
    // Compute Rayleigh quotient for eigenvalue
    ld lambda = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            lambda += x[i] * A[i][j] * x[j];
    // In practice, use full eigendecomposition (e.g., via Jacobi, QR).
    return {{lambda}, {x}};
}

// Example: check if matrix is diagonalizable via characteristic polynomial.
// Not full implementation; symbolic computation needed.
bool is_diagonalizable(const vector<vector<ld>>& A) {
    // Condition: geometric multiplicity = algebraic multiplicity for each eigenvalue.
    // In practice, compute eigenvalues and eigenvectors.
    // This is a placeholder.
    return false;
}

int main() {
    // Example: 2x2 symmetric matrix
    vector<vector<ld>> A = {{4, 1}, {1, 3}};
    auto [vals, vecs] = power_iteration(A);
    cout << "Dominant eigenvalue: " << vals[0] << endl;
    cout << "Eigenvector: ";
    for (ld v : vecs[0]) cout << v << ' ';
    cout << endl;
    return 0;
}