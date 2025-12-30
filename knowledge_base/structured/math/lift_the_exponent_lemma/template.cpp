#include <bits/stdc++.h>
using namespace std;

// Function to compute ν_p(n): exponent of prime p in factorization of n
int vp(int n, int p) {
    int cnt = 0;
    while (n % p == 0) {
        n /= p;
        cnt++;
    }
    return cnt;
}

// LTE Lemma for odd prime p, case p | (x - y)
int lte_odd_minus(int x, int y, int n, int p) {
    // Assumes p is odd prime, p | (x - y), and p does not divide x or y
    return vp(x - y, p) + vp(n, p);
}

// LTE Lemma for odd prime p, case p | (x + y) and n odd
int lte_odd_plus(int x, int y, int n, int p) {
    // Assumes p is odd prime, p | (x + y), n is odd, and p does not divide x or y
    return vp(x + y, p) + vp(n, p);
}

// LTE Lemma for p = 2, case 2 | (x - y)
int lte_two(int x, int y, int n) {
    // Assumes p = 2, 2 | (x - y), and x, y are odd
    if (n % 2 == 1) {
        return vp(x - y, 2);
    } else {
        return vp(x - y, 2) + vp(x + y, 2) + vp(n, 2) - 1;
    }
}

int main() {
    // Example usage
    int x = 10, y = 2, n = 6, p = 2;
    if (p == 2) {
        cout << "ν_2(" << x << "^" << n << " - " << y << "^" << n << ") = " << lte_two(x, y, n) << endl;
    } else {
        // For odd prime, check divisibility conditions
        if ((x - y) % p == 0) {
            cout << "ν_" << p << "(" << x << "^" << n << " - " << y << "^" << n << ") = " << lte_odd_minus(x, y, n, p) << endl;
        } else if ((x + y) % p == 0 && n % 2 == 1) {
            cout << "ν_" << p << "(" << x << "^" << n << " + " << y << "^" << n << ") = " << lte_odd_plus(x, y, n, p) << endl;
        }
    }
    return 0;
}