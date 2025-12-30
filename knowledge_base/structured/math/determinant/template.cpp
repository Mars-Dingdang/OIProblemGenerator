#include <bits/stdc++.h>
using namespace std;

// Compute determinant of a square matrix using Gaussian elimination
// Returns determinant as a double (or long double for better precision)
// For modular arithmetic, modify to use modular inverses

template<typename T>
T determinant(vector<vector<T>> a) {
    int n = a.size();
    T det = 1;
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int j = i + 1; j < n; ++j)
            if (abs(a[j][i]) > abs(a[pivot][i]))
                pivot = j;
        if (abs(a[pivot][i]) < 1e-12) // or epsilon for floating point
            return 0;
        if (pivot != i) {
            swap(a[i], a[pivot]);
            det = -det;
        }
        det *= a[i][i];
        for (int j = i + 1; j < n; ++j) {
            T factor = a[j][i] / a[i][i];
            for (int k = i + 1; k < n; ++k)
                a[j][k] -= factor * a[i][k];
        }
    }
    return det;
}

// Example usage for double:
// vector<vector<double>> mat = {{1,2},{3,4}};
// cout << determinant(mat) << endl; // -2

// For integer/modular determinant (mod prime):
/*
template<typename T>
T mod_det(vector<vector<T>> a, T mod) {
    int n = a.size();
    T det = 1;
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int j = i + 1; j < n; ++j)
            if (a[j][i] != 0) { pivot = j; break; }
        if (a[pivot][i] == 0) return 0;
        if (pivot != i) {
            swap(a[i], a[pivot]);
            det = (mod - det) % mod;
        }
        det = det * a[i][i] % mod;
        T inv = mod_inv(a[i][i], mod);
        for (int j = i + 1; j < n; ++j) {
            T factor = a[j][i] * inv % mod;
            for (int k = i + 1; k < n; ++k) {
                a[j][k] = (a[j][k] - factor * a[i][k]) % mod;
                if (a[j][k] < 0) a[j][k] += mod;
            }
        }
    }
    return det;
}
*/