#include <bits/stdc++.h>
using namespace std;

// Matrix representation of a linear mapping
struct LinearMapping {
    int n, m; // dimension of domain V (n), codomain W (m)
    vector<vector<double>> A; // m x n matrix
    
    LinearMapping(int n, int m) : n(n), m(m), A(m, vector<double>(n, 0)) {}
    
    // Apply mapping to vector x (size n), result y (size m)
    vector<double> apply(const vector<double>& x) {
        vector<double> y(m, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                y[i] += A[i][j] * x[j];
            }
        }
        return y;
    }
    
    // Composition: this ∘ other (this applied after other)
    LinearMapping compose(const LinearMapping& other) {
        // other: V1 -> V2 (n2 x n1), this: V2 -> V3 (m x n2)
        // result: V1 -> V3 (m x n1)
        LinearMapping res(other.n, m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < other.n; j++) {
                for (int k = 0; k < other.m; k++) {
                    res.A[i][j] += A[i][k] * other.A[k][j];
                }
            }
        }
        return res;
    }
    
    // Change basis in domain and codomain
    // newA = P^{-1} * A * Q where P changes basis in codomain, Q in domain
    LinearMapping changeBasis(const vector<vector<double>>& P_inv,
                              const vector<vector<double>>& Q) {
        // P_inv: m x m, Q: n x n
        LinearMapping res(n, m);
        // res.A = P_inv * A * Q
        vector<vector<double>> temp(m, vector<double>(n, 0));
        // temp = A * Q
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    temp[i][j] += A[i][k] * Q[k][j];
                }
            }
        }
        // res.A = P_inv * temp
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < m; k++) {
                    res.A[i][j] += P_inv[i][k] * temp[k][j];
                }
            }
        }
        return res;
    }
};

// Example: identity transformation
LinearMapping identity(int n) {
    LinearMapping id(n, n);
    for (int i = 0; i < n; i++) id.A[i][i] = 1;
    return id;
}

// Example: zero transformation
LinearMapping zero(int n, int m) {
    return LinearMapping(n, m); // all zeros
}

int main() {
    // Example usage
    LinearMapping T(3, 2); // from R^3 to R^2
    // Set matrix representation
    T.A = {{1, 0, 1}, {0, 1, 1}}; // 2x3 matrix
    
    vector<double> x = {1, 2, 3};
    vector<double> y = T.apply(x);
    // y = {1*1 + 0*2 + 1*3, 0*1 + 1*2 + 1*3} = {4, 5}
    
    return 0;
}