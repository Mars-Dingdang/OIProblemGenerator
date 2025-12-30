// Euclidean Algorithm (recursive)
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Euclidean Algorithm (iterative)
int gcd_iterative(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// Extended Euclidean Algorithm (recursive)
// Returns gcd(a, b) and finds x, y such that a*x + b*y = gcd(a, b)
int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, x, y);
    int t = x;
    x = y;
    y = t - (a / b) * y;
    return d;
}

// Compute lcm using gcd
long long lcm(int a, int b) {
    return 1LL * a / gcd(a, b) * b;  // Divide first to avoid overflow
}

// C++17 standard library (if available)
#include <numeric>
// std::gcd(a, b)
// std::lcm(a, b)