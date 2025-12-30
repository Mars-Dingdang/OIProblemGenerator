// Abstract Algebra is a theoretical framework, not a specific algorithm.
// No standard C++ implementation exists; instead, concepts are used in algorithm design.
// Example: Tropical semiring for dynamic DP (max-plus algebra)
#include <bits/stdc++.h>
using namespace std;

// Tropical semiring (max, +) with -∞ as additive identity
struct Tropical {
    long long val;
    static const long long neg_inf = -1e18;
    Tropical(long long x = neg_inf) : val(x) {}
    Tropical operator+(const Tropical& other) const { // max
        return Tropical(max(val, other.val));
    }
    Tropical operator*(const Tropical& other) const { // +
        if (val == neg_inf || other.val == neg_inf) return Tropical(neg_inf);
        return Tropical(val + other.val);
    }
};

// Matrix multiplication over tropical semiring
vector<vector<Tropical>> matMul(const vector<vector<Tropical>>& A,
                                const vector<vector<Tropical>>& B) {
    int n = A.size(), m = A[0].size(), p = B[0].size();
    vector<vector<Tropical>> C(n, vector<Tropical>(p, Tropical::neg_inf));
    for (int i = 0; i < n; ++i)
        for (int k = 0; k < m; ++k)
            if (A[i][k].val != Tropical::neg_inf)
                for (int j = 0; j < p; ++j)
                    C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
    return C;
}

// Example: DP for maximum weighted independent set on a chain using tropical matrices
// DP transition: f[i][1] = w[i] + f[i-1][0], f[i][0] = max(f[i-1][1], f[i-1][0])
// Represent as matrix multiplication over tropical semiring:
// [f[i][1]]   = [ -∞   w[i] ] [f[i-1][1]]
// [f[i][0]]     [  0     0  ] [f[i-1][0]]
// (where + is max, * is +)
int main() {
    // Example weights
    vector<long long> w = {0, 5, 3, 7, 2};
    int n = w.size() - 1;
    vector<vector<Tropical>> f(2, vector<Tropical>(1, Tropical::neg_inf));
    f[0][0] = Tropical(0); // f[0][0] = 0
    f[1][0] = Tropical(0); // f[0][1] = 0
    for (int i = 1; i <= n; ++i) {
        vector<vector<Tropical>> M = {
            {Tropical(Tropical::neg_inf), Tropical(w[i])},
            {Tropical(0), Tropical(0)}
        };
        f = matMul(M, f);
    }
    long long ans = max(f[0][0].val, f[1][0].val);
    cout << "Maximum weighted independent set value: " << ans << endl;
    return 0;
}