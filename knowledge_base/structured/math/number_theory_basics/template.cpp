#include <bits/stdc++.h>
using namespace std;

// Greatest Common Divisor (Euclidean algorithm)
long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// Least Common Multiple
long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

// Check if a divides b
bool divides(long long a, long long b) {
    return b % a == 0;
}

// Modular arithmetic: (a + b) mod m
int add_mod(int a, int b, int m) {
    return (a + b) % m;
}

// Modular arithmetic: (a - b) mod m (non-negative result)
int sub_mod(int a, int b, int m) {
    return (a - b % m + m) % m;
}

// Modular arithmetic: (a * b) mod m
int mul_mod(int a, int b, int m) {
    return (1LL * a * b) % m;
}

// Check if n is prime (naive O(sqrt(n)))
bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Count number of divisors (naive O(sqrt(n)))
int count_divisors(int n) {
    int cnt = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            cnt++;
            if (i != n / i) cnt++;
        }
    }
    return cnt;
}

// Euler's totient function (phi) O(sqrt(n))
int euler_phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            result -= result / i;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

int main() {
    // Example usage
    cout << "gcd(12, 18) = " << gcd(12, 18) << endl;
    cout << "lcm(12, 18) = " << lcm(12, 18) << endl;
    cout << "is_prime(17) = " << is_prime(17) << endl;
    cout << "phi(12) = " << euler_phi(12) << endl;
    return 0;
}