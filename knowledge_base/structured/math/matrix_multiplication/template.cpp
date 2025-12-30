struct Matrix {
    int n, m;
    vector<vector<long long>> a;
    Matrix(int n = 0, int m = 0) : n(n), m(m), a(n, vector<long long>(m, 0)) {}
    Matrix operator*(const Matrix &b) const {
        assert(m == b.n);
        Matrix res(n, b.m);
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < m; ++k) {
                long long r = a[i][k];
                for (int j = 0; j < b.m; ++j)
                    res.a[i][j] += r * b.a[k][j];
            }
        return res;
    }
    Matrix operator^(long long k) const {
        assert(n == m);
        Matrix res(n, n), base = *this;
        for (int i = 0; i < n; ++i) res.a[i][i] = 1;
        while (k) {
            if (k & 1) res = res * base;
            base = base * base;
            k >>= 1;
        }
        return res;
    }
};