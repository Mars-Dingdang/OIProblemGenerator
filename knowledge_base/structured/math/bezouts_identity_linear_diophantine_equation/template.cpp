#include <bits/stdc++.h>
using namespace std;

// Extended Euclidean Algorithm
// Returns gcd(a, b) and finds x, y such that a*x + b*y = gcd(a, b)
int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// Solves a*x + b*y = c
// Returns true if solution exists, false otherwise
// Stores one particular solution in x0, y0
// General solution: x = x0 + (b/d)*t, y = y0 - (a/d)*t, t ∈ Z
bool solve_linear_diophantine(int a, int b, int c, int &x0, int &y0, int &g) {
    g = exgcd(abs(a), abs(b), x0, y0);
    if (c % g != 0) return false;
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

// Frobenius coin problem (Sylvester's theorem)
// For coprime a, b, largest unrepresentable integer is a*b - a - b
long long frobenius(int a, int b) {
    return 1LL * a * b - a - b;
}

int main() {
    // Example: Solve 35x + 21y = 14
    int a = 35, b = 21, c = 14;
    int x, y, g;
    if (solve_linear_diophantine(a, b, c, x, y, g)) {
        cout << "Particular solution: x = " << x << ", y = " << y << endl;
        cout << "General solution: x = " << x << " + " << (b/g) << "*t, y = " << y << " - " << (a/g) << "*t" << endl;
    } else {
        cout << "No solution" << endl;
    }
    
    // Example: Frobenius problem for coprime 3 and 5
    cout << "Largest unrepresentable: " << frobenius(3, 5) << endl; // 7
    return 0;
}