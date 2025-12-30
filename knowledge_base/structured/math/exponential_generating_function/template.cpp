#include <bits/stdc++.h>
using namespace std;

// Example: Compute the number of permutations of n labeled elements
// using EGF: P(x) = 1/(1-x) = sum_{n>=0} n! * x^n / n!
// This is trivial, but demonstrates EGF concept.
// For more complex applications (e.g., set partitions, forests),
// polynomial exponentiation via FFT/NTT is typically required.

const int MOD = 998244353;
const int G = 3; // primitive root for NTT

// NTT implementation for polynomial multiplication (simplified)
// In practice, use a full polynomial library for exp, ln, etc.

// Example: Compute exponential generating function for permutations
long long factorial(int n) {
    long long res = 1;
    for (int i = 2; i <= n; i++) res *= i;
    return res;
}

// Compute [x^n] exp(F(x)) where F(x) is given by its first (n+1) coefficients f[0..n]
// using polynomial exponentiation (O(n log n) via Newton's method).
// This is a placeholder; actual implementation requires full polynomial toolkit.
vector<long long> poly_exp(const vector<long long>& f, int n) {
    // f[0] must be 0 for combinatorial exp (no empty set).
    // Returns g = exp(f) mod x^{n+1}
    vector<long long> g(n+1, 0);
    g[0] = 1; // exp(0) = 1
    // ... iterative Newton method ...
    // (Omitted for brevity; see polynomial template library)
    return g;
}

int main() {
    // Example: Number of permutations of size n via EGF
    int n = 5;
    // EGF for permutations: P(x) = 1/(1-x)
    // Coefficient of x^n/n! is n!, so [x^n] P(x) = 1 (since EGF uses x^n/n! factor)
    // But ordinary generating function for n! is 1/(1-x).
    // This illustrates the shift in perspective.
    cout << "Permutations of " << n << " labeled elements: " << factorial(n) << endl;
    
    // More advanced: Set partitions (Bell numbers) via exp(exp(x)-1)
    // EGF for nonempty sets: S(x) = exp(x) - 1
    // EGF for set partitions: B(x) = exp(S(x)) = exp(exp(x)-1)
    // Compute Bell numbers via polynomial exp.
    // (Implementation requires poly_exp and poly_exp of exp(x)-1)
    return 0;
}