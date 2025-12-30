#include <bits/stdc++.h>
using namespace std;

// Gaussian integer structure
struct GaussianInteger {
    long long a, b; // a + bi
    GaussianInteger(long long a = 0, long long b = 0) : a(a), b(b) {}
    long long norm() const { return a * a + b * b; }
    GaussianInteger conjugate() const { return GaussianInteger(a, -b); }
    bool operator==(const GaussianInteger& other) const { return a == other.a && b == other.b; }
    GaussianInteger operator+(const GaussianInteger& other) const { return GaussianInteger(a + other.a, b + other.b); }
    GaussianInteger operator-(const GaussianInteger& other) const { return GaussianInteger(a - other.a, b - other.b); }
    GaussianInteger operator*(const GaussianInteger& other) const {
        return GaussianInteger(a * other.a - b * other.b, a * other.b + b * other.a);
    }
    GaussianInteger operator/(const GaussianInteger& other) const {
        long long n = other.norm();
        long long x = a * other.a + b * other.b;
        long long y = b * other.a - a * other.b;
        return GaussianInteger(round((double)x / n), round((double)y / n));
    }
    GaussianInteger operator%(const GaussianInteger& other) const {
        GaussianInteger q = (*this) / other;
        return (*this) - q * other;
    }
};

// Eisenstein integer structure (using ω = (-1 + sqrt(-3))/2)
struct EisensteinInteger {
    long long a, b; // a + bω
    EisensteinInteger(long long a = 0, long long b = 0) : a(a), b(b) {}
    long long norm() const { return a * a - a * b + b * b; }
    EisensteinInteger conjugate() const { return EisensteinInteger(a - b, -b); }
    bool operator==(const EisensteinInteger& other) const { return a == other.a && b == other.b; }
    EisensteinInteger operator+(const EisensteinInteger& other) const { return EisensteinInteger(a + other.a, b + other.b); }
    EisensteinInteger operator-(const EisensteinInteger& other) const { return EisensteinInteger(a - other.a, b - other.b); }
    EisensteinInteger operator*(const EisensteinInteger& other) const {
        return EisensteinInteger(a * other.a - b * other.b, a * other.b + b * other.a - b * other.b);
    }
};

// Count integer solutions to x² + y² = n using Gaussian integers
int count_circle_points(int n) {
    int res = 0;
    for (int d = 1; d * d <= n; ++d) {
        if (n % d == 0) {
            res += (d % 4 == 1) ? 1 : (d % 4 == 3) ? -1 : 0;
            if (d * d != n) {
                int e = n / d;
                res += (e % 4 == 1) ? 1 : (e % 4 == 3) ? -1 : 0;
            }
        }
    }
    return 4 * res;
}

// Generate primitive Pythagorean triples (x, y, z) with x² + y² = z²
vector<tuple<int, int, int>> generate_primitive_triples(int limit) {
    vector<tuple<int, int, int>> triples;
    for (int m = 1; m * m <= limit; ++m) {
        for (int n = 1; n < m; ++n) {
            if ((m - n) % 2 == 1 && gcd(m, n) == 1) {
                int x = m * m - n * n;
                int y = 2 * m * n;
                int z = m * m + n * n;
                if (z <= limit) {
                    triples.emplace_back(x, y, z);
                }
            }
        }
    }
    return triples;
}

int main() {
    // Example usage
    int n = 25;
    cout << "Number of integer solutions to x² + y² = " << n << ": " << count_circle_points(n) << endl;
    auto triples = generate_primitive_triples(50);
    cout << "Primitive Pythagorean triples with z ≤ 50:" << endl;
    for (auto [x, y, z] : triples) {
        cout << x << " " << y << " " << z << endl;
    }
    return 0;
}