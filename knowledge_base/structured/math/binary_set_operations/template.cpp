#include <bits/stdc++.h>
using namespace std;

// Modulo power of two
int modPowerOfTwo(int x, int mod) {
    return x & (mod - 1);
}

// Check if a number is a power of two
bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

// Iterate over all non-empty subsets of a mask m in decreasing order
void iterateSubsets(int m) {
    for (int s = m; s; s = (s - 1) & m) {
        // s is a non-empty subset of m
        // Process s
    }
}

// Iterate over all subsets (including empty) of a mask m in decreasing order
void iterateSubsetsIncludingEmpty(int m) {
    int s = m;
    do {
        // s is a subset of m
        // Process s
        s = (s - 1) & m;
    } while (s != m); // Stops when s wraps to m after 0
}

// Iterate over all submasks of all masks of length n (O(3^n))
void iterateAllSubmasks(int n) {
    for (int m = 0; m < (1 << n); ++m) {
        for (int s = m; s; s = (s - 1) & m) {
            // s is a non-empty submask of m
            // Process (m, s)
        }
    }
}

int main() {
    // Example usage
    int mask = 0b1101; // {0, 2, 3}
    iterateSubsets(mask);
    return 0;
}