#include <vector>
#include <iostream>
using namespace std;

// Compute Entringer numbers E(n, k) for 0 <= k <= n <= N
vector<vector<long long>> compute_entringer(int N) {
    vector<vector<long long>> E(N + 1, vector<long long>(N + 1, 0));
    E[0][0] = 1;
    for (int n = 1; n <= N; ++n) {
        E[n][0] = 0;  // base case
        for (int k = 1; k <= n; ++k) {
            E[n][k] = E[n][k-1] + E[n-1][n-k];
        }
    }
    return E;
}

// Compute Euler zigzag numbers A_n (also known as up/down numbers)
// A_n = E(n, n) = total alternating permutations of size n
vector<long long> compute_zigzag(int N) {
    auto E = compute_entringer(N);
    vector<long long> A(N + 1);
    for (int n = 0; n <= N; ++n) {
        A[n] = E[n][n];
    }
    return A;
}

int main() {
    int N = 10;
    auto E = compute_entringer(N);
    auto A = compute_zigzag(N);
    // Example: print E(5, k)
    for (int k = 0; k <= 5; ++k) {
        cout << "E(5," << k << ") = " << E[5][k] << endl;
    }
    // Example: print A_n for n=0..5
    for (int n = 0; n <= 5; ++n) {
        cout << "A_" << n << " = " << A[n] << endl;
    }
    return 0;
}