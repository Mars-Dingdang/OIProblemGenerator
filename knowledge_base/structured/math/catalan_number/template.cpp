#include <iostream>
#include <vector>
using namespace std;

// Precompute Catalan numbers up to n using recurrence C_n = (4n-2)/(n+1) * C_{n-1}
vector<long long> catalan(int n) {
    vector<long long> C(n + 1, 0);
    C[0] = 1;
    for (int i = 1; i <= n; ++i) {
        C[i] = C[i - 1] * (4 * i - 2) / (i + 1);
    }
    return C;
}

// Compute single Catalan number using binomial coefficient (beware overflow)
long long catalan_binom(int n) {
    long long res = 1;
    for (int i = 1; i <= n; ++i) {
        res *= (n + i);
        res /= i;
    }
    return res / (n + 1);
}

int main() {
    int n = 10;
    vector<long long> C = catalan(n);
    for (int i = 0; i <= n; ++i) {
        cout << "C_" << i << " = " << C[i] << endl;
    }
    // Alternative
    cout << "C_5 via binomial = " << catalan_binom(5) << endl;
    return 0;
}