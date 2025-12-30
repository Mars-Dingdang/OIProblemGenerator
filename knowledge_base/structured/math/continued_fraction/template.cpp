// Find continued fraction representation of p/q
vector<int> fraction(int p, int q) {
    vector<int> a;
    while (q) {
        a.push_back(p / q);
        tie(p, q) = make_pair(q, p % q);
    }
    return a;
}

// Compute convergents from coefficients a0, a1, ..., an
pair<vector<int>, vector<int>> convergents(const vector<int>& a) {
    vector<int> p = {0, 1};
    vector<int> q = {1, 0};
    for (int ak : a) {
        p.push_back(p.back() * ak + p.end()[-2]);
        q.push_back(q.back() * ak + q.end()[-2]);
    }
    return {p, q};
}

// Solve Ax + By = C using continued fractions
pair<int, int> dio(int A, int B, int C) {
    auto a = fraction(A, B);
    auto [p, q] = convergents(a);
    int g = A / p.back(); // gcd(A, B)
    if (C % g != 0) return {0, 0}; // No solution
    C /= g;
    int t = (p.size() % 2) ? -1 : 1;
    return {t * C * q.end()[-2], -t * C * p.end()[-2]};
}