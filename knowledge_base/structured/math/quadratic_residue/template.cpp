#include <iostream>
#include <random>
#include <cassert>
using namespace std;

long long modpow(long long a, long long b, long long p) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

// Legendre symbol: (a/p) = 1 if quadratic residue, -1 if non-residue, 0 if p|a
int legendre(long long a, long long p) {
    long long res = modpow(a % p, (p - 1) / 2, p);
    if (res == p - 1) return -1;
    return (int)res;
}

// Cipolla algorithm for square root modulo prime p
// Returns -1 if no solution (a is non-residue)
// Returns one solution x, the other is p-x
long long cipolla_sqrt(long long a, long long p) {
    a %= p;
    if (a == 0) return 0;
    if (legendre(a, p) == -1) return -1;
    
    mt19937 rng(random_device{}());
    long long r;
    do {
        r = rng() % p;
    } while (legendre((r * r - a + p) % p, p) != -1);
    
    long long w2 = (r * r - a + p) % p;
    
    // Multiplication in F_p[sqrt(w)]
    auto mul = [&](pair<long long, long long> x, pair<long long, long long> y) -> pair<long long, long long> {
        return {
            (x.first * y.first + w2 * (x.second * y.second % p)) % p,
            (x.first * y.second + x.second * y.first) % p
        };
    };
    
    // Fast exponentiation in F_p[sqrt(w)]
    pair<long long, long long> res_poly = {1, 0};
    pair<long long, long long> base = {r, 1};
    long long exp = (p + 1) / 2;
    while (exp) {
        if (exp & 1) res_poly = mul(res_poly, base);
        base = mul(base, base);
        exp >>= 1;
    }
    
    assert(res_poly.second == 0); // Coefficient of sqrt(w) must be 0
    return res_poly.first;
}

// Tonelli-Shanks algorithm (alternative)
long long tonelli_shanks(long long a, long long p) {
    a %= p;
    if (a == 0) return 0;
    if (legendre(a, p) == -1) return -1;
    
    // Factor p-1 = Q * 2^S
    long long Q = p - 1;
    long long S = 0;
    while (Q % 2 == 0) {
        Q /= 2;
        S++;
    }
    
    // Find quadratic non-residue z
    mt19937 rng(random_device{}());
    long long z;
    do {
        z = rng() % p;
    } while (legendre(z, p) != -1);
    
    long long c = modpow(z, Q, p);
    long long t = modpow(a, Q, p);
    long long R = modpow(a, (Q + 1) / 2, p);
    long long M = S;
    
    while (t != 1) {
        long long i = 0;
        long long tt = t;
        while (tt != 1) {
            tt = tt * tt % p;
            i++;
        }
        long long b = modpow(c, 1LL << (M - i - 1), p);
        R = R * b % p;
        t = t * b % p * b % p;
        c = b * b % p;
        M = i;
    }
    return R;
}

int main() {
    // Example usage
    long long a = 5, p = 13;
    long long x = cipolla_sqrt(a, p);
    if (x == -1) {
        cout << "No solution" << endl;
    } else {
        cout << "Solutions: " << x << " and " << p - x << endl;
        cout << "Check: " << (x * x) % p << " ≡ " << a << " (mod " << p << ")" << endl;
    }
    return 0;
}