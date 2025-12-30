// Group theory is a theoretical concept; there is no standard C++ template for the entire field.
// However, common algorithms that use group theory concepts (e.g., Burnside's lemma) have implementations.
// Example: Burnside's lemma for counting distinct colorings under group actions.
#include <bits/stdc++.h>
using namespace std;

// Example: Count distinct colorings of n beads with m colors under rotations.
// Using Burnside's lemma for cyclic group C_n.
long long burnside_rotation(int n, int m) {
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        // For rotation by i positions, number of fixed colorings is m^{gcd(n, i)}
        ans += pow(m, __gcd(n, i));
    }
    ans /= n; // Divide by |G| = n
    return ans;
}

// Example: Count distinct colorings under dihedral group D_n (rotations and reflections).
long long burnside_dihedral(int n, int m) {
    long long ans = 0;
    // Rotations (same as cyclic group)
    for (int i = 0; i < n; ++i) {
        ans += pow(m, __gcd(n, i));
    }
    // Reflections
    if (n % 2 == 0) {
        // For even n: two types of reflections
        // Type 1: Reflection through vertices (n/2 axes) -> m^{n/2} fixed each
        ans += (n / 2) * pow(m, n / 2);
        // Type 2: Reflection through edges (n/2 axes) -> m^{n/2} fixed each
        ans += (n / 2) * pow(m, n / 2);
    } else {
        // For odd n: reflection through a vertex and opposite edge (n axes) -> m^{(n+1)/2} fixed each
        ans += n * pow(m, (n + 1) / 2);
    }
    ans /= (2 * n); // Divide by |G| = 2n
    return ans;
}

int main() {
    int n = 4, m = 3;
    cout << "Distinct colorings under rotations: " << burnside_rotation(n, m) << endl;
    cout << "Distinct colorings under dihedral group: " << burnside_dihedral(n, m) << endl;
    return 0;
}