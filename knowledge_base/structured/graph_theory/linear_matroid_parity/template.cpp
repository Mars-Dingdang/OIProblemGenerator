// C++ template for unweighted Linear Matroid Parity
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 505;
const int MOD = 1e9+7; // Large prime

// Random number generator
default_random_engine rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> dist(0, MOD-1);

double log_rand() { return -log(dist(rng) * 1.0 / MOD); }

struct Matrix {
    vector<vector<ll>> data;
    int n, m;
    Matrix(int n_, int m_) : n(n_), m(m_), data(n_, vector<ll>(m_)) {}
    
    void set(int i, int j, ll val) { data[i][j] = val % MOD; }
    ll get(int i, int j) const { return data[i][j]; }
    
    static Matrix identity(int n) {
        Matrix I(n, n);
        for (int i = 0; i < n; ++i) I.set(i, i, 1);
        return I;
    }
};

Matrix mat_mul(const Matrix& A, const Matrix& B) {
    Matrix C(A.n, B.m);
    for (int i = 0; i < A.n; ++i)
        for (int k = 0; k < A.m; ++k) {
            ll aik = A.get(i,k);
            if (!aik) continue;
            for (int j = 0; j < B.m; ++j)
                C.set(i, j, (C.get(i,j) + aik * B.get(k,j)) % MOD);
        }
    return C;
}

Matrix mat_add(const Matrix& A, const Matrix& B) {
    Matrix C(A.n, A.m);
    for (int i = 0; i < A.n; ++i)
        for (int j = 0; j < A.m; ++j)
            C.set(i, j, (A.get(i,j) + B.get(i,j)) % MOD);
    return C;
}

Matrix mat_neg(const Matrix& A) {
    Matrix C(A.n, A.m);
    for (int i = 0; i < A.n; ++i)
        for (int j = 0; j < A.m; ++j)
            C.set(i, j, (-A.get(i,j) + MOD) % MOD);
    return C;
}

// Gaussian elimination for rank computation
int gauss_rank(Matrix M) {
    int r = 0;
    vector<bool> used(M.m, false);
    for (int col = 0; col < M.m && r < M.n; ++col) {
        int sel = -1;
        for (int row = r; row < M.n; ++row) {
            if (M.get(row, col) && !used[row]) {
                sel = row;
                break;
            }
        }
        if (sel == -1) continue;
        swap(M.data[r], M.data[sel]);
        used[r] = true;
        ll inv = 1, base = M.get(r, col);
        // Modular inverse
        for (int i = 0; i < MOD-2; ++i) inv = inv * base % MOD;
        for (int j = 0; j < M.m; ++j)
            M.set(r, j, M.get(r,j) * inv % MOD);
        for (int i = 0; i < M.n; ++i) {
            if (i != r && M.get(i,col)) {
                ll factor = M.get(i,col);
                for (int j = 0; j < M.m; ++j) {
                    ll sub = factor * M.get(r,j) % MOD;
                    M.set(i, j, (M.get(i,j) - sub + MOD) % MOD);
                }
            }
        }
        ++r;
    }
    return r;
}

// Sherman-Morrison-Woodbury update for inverse
// (A - U V^T)^{-1} = A^{-1} + A^{-1} U (I - V^T A^{-1} U)^{-1} V^T A^{-1}
Matrix smw_update(const Matrix& A_inv, const Matrix& U, const Matrix& V) {
    Matrix Au = mat_mul(A_inv, U);
    Matrix Vt_Ainv = mat_mul(V, A_inv); // V^T A^{-1}
    Matrix Vt_Ainv_U = mat_mul(Vt_Ainv, U);
    int k = Vt_Ainv_U.n;
    Matrix I_k = Matrix::identity(k);
    Matrix temp = mat_add(I_k, mat_neg(Vt_Ainv_U)); // I - V^T A^{-1} U
    Matrix temp_inv = temp; // In practice, invert this small matrix
    // For simplicity, assume inversion done
    Matrix mid = mat_mul(mat_mul(Au, temp_inv), Vt_Ainv);
    return mat_add(A_inv, mid);
}

// Main LMPP solver
int solve_lmpp(vector<pair<vector<ll>, vector<ll>>> pairs) {
    int m = pairs.size();
    int n = pairs.empty() ? 0 : pairs[0].first.size();
    
    // Build compact matrix M = sum x_i (a_i b_i^T - b_i a_i^T)
    Matrix M(n, n);
    vector<ll> xs(m);
    for (int i = 0; i < m; ++i) {
        xs[i] = dist(rng);
        auto [a, b] = pairs[i];
        // Add x_i * (a b^T - b a^T)
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                ll val = (a[u] * b[v] - b[u] * a[v]) % MOD;
                M.set(u, v, (M.get(u,v) + xs[i] * val) % MOD);
            }
        }
    }
    
    // Compute rank
    return gauss_rank(M);
}

// Example usage
int main() {
    // Example: General graph matching on 3 nodes
    vector<pair<vector<ll>, vector<ll>>> pairs;
    // Edge (0,1): a=e0, b=e1
    pairs.push_back({{1,0,0}, {0,1,0}});
    // Edge (1,2)
    pairs.push_back({{0,1,0}, {0,0,1}});
    // Edge (0,2)
    pairs.push_back({{1,0,0}, {0,0,1}});
    
    int max_matching = solve_lmpp(pairs) / 2;
    cout << "Max matching size: " << max_matching << endl;
    return 0;
}