// Simplex method for solving linear programming problems.
// Solves: minimize c^T x, subject to Ax = b, x >= 0.
// Returns: optimal value, and solution vector x (if feasible and bounded).
// Usage: set A, b, c, then call simplex().
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-8;
const double INF = 1e20;

struct Simplex {
    int m, n; // constraints, variables (including slacks)
    vector<vector<double>> tab; // simplex tableau
    vector<int> B, N; // basic and nonbasic indices

    Simplex(const vector<vector<double>> &A, const vector<double> &b, const vector<double> &c) {
        m = b.size();
        n = c.size();
        // Build initial tableau for slack form: min c^T x, s.t. Ax <= b, x >= 0.
        // Convert to: Ax + s = b, x >= 0, s >= 0.
        tab = vector<vector<double>>(m + 1, vector<double>(n + m + 1, 0.0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                tab[i][j] = A[i][j];
            }
            tab[i][n + i] = 1.0; // slack variable
            tab[i][n + m] = b[i]; // RHS
        }
        for (int j = 0; j < n; ++j) {
            tab[m][j] = c[j]; // objective row
        }
        B.resize(m);
        N.resize(n);
        for (int i = 0; i < m; ++i) B[i] = n + i; // slacks are basic initially
        for (int j = 0; j < n; ++j) N[j] = j;
    }

    void pivot(int x, int y) {
        // Pivot on (N[x], B[y])
        swap(N[x], B[y]);
        double v = -1.0 / tab[x][y];
        for (int j = 0; j <= m; ++j) {
            tab[x][j] = (j == y) ? -v : v * tab[x][j];
        }
        for (int i = 0; i <= m; ++i) {
            if (i == x) continue;
            v = tab[i][y];
            tab[i][y] = 0.0;
            for (int j = 0; j <= m; ++j) {
                tab[i][j] += v * tab[x][j];
            }
        }
    }

    bool simplex() {
        while (true) {
            // Find entering variable (most negative reduced cost)
            int e = -1;
            for (int j = 0; j < n; ++j) {
                if (tab[m][j] < -eps && (e == -1 || tab[m][j] < tab[m][e])) {
                    e = j;
                }
            }
            if (e == -1) break; // optimal
            // Find leaving variable (minimum ratio test)
            int l = -1;
            double min_ratio = INF;
            for (int i = 0; i < m; ++i) {
                if (tab[i][e] > eps) {
                    double ratio = tab[i][m] / tab[i][e];
                    if (ratio < min_ratio - eps) {
                        min_ratio = ratio;
                        l = i;
                    }
                }
            }
            if (l == -1) return false; // unbounded
            pivot(l, e);
        }
        return true;
    }

    pair<double, vector<double>> solve() {
        if (!simplex()) return {INF, {}}; // unbounded or infeasible
        double opt = -tab[m][m]; // optimal value
        vector<double> x(n, 0.0);
        for (int i = 0; i < m; ++i) {
            if (B[i] < n) x[B[i]] = tab[i][m];
        }
        return {opt, x};
    }
};

// Example usage:
// vector<vector<double>> A = {{1,2,2},{2,1,2},{2,2,1}};
// vector<double> b = {20,20,20};
// vector<double> c = {-10,-12,-12}; // min -10x1-12x2-12x3
// Simplex smp(A, b, c);
// auto [opt, sol] = smp.solve(); // opt = -136, sol = {4,4,4}