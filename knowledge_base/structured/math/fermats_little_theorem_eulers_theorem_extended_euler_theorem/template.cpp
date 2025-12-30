#include <iostream>
using namespace std;

// Euler's Totient Function
int phi(int n) {
    int result = n;
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

// Fast modular exponentiation supporting extended Euler theorem
long long modpow(long long a, long long b, int m) {
    long long res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

// Helper for extended Euler: returns v mod m, but if v >= m returns v % m + m
long long mod(long long v, int m) {
    return v >= m ? v % m + m : v;
}

// Extended Euler theorem aware modular exponentiation
long long pow_ext(long long a, long long b, int m) {
    if (m == 1) return 0;
    if (b == 0) return 1 % m;
    if (gcd(a, m) == 1) {
        return modpow(a, b % phi(m), m);
    } else {
        if (b < phi(m)) {
            return modpow(a, b, m);
        } else {
            return modpow(a, b % phi(m) + phi(m), m);
        }
    }
}

// Example: Power tower (tetration) modulo m using recursion
long long tetra(long long a, long long b, int m) {
    if (m == 1) return 0;
    if (b == 0) return 1 % m;
    if (b == 1) return a % m;
    int p = phi(m);
    long long exp = tetra(a, b - 1, p); // recursive exponent
    return pow_ext(a, exp, m);
}

int main() {
    // Example usage
    long long a = 2, b = 3, m = 10;
    cout << "(2^3) mod 10 = " << modpow(a, b, m) << endl;
    cout << "phi(10) = " << phi(10) << endl;
    cout << "Extended Euler pow(2, 100, 10) = " << pow_ext(2, 100, 10) << endl;
    return 0;
}