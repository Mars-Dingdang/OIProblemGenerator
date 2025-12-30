#include <bits/stdc++.h>
using namespace std;

// Example template for DP over DP (general structure)
// This is a generic skeleton; actual implementation varies per problem.

const int MOD = 1e9 + 7;

// Suppose inner DP state is compressed into a mask of size M.
// Outer DP: f[i][mask] = number of sequences of length i leading to inner state 'mask'.
// Transition: f[i+1][new_mask] += f[i][mask] for each possible next character.

int main() {
    int n; // length of sequence
    int state_count; // number of possible inner states (e.g., 2^M)
    // Precompute transition: next_state[mask][char]
    // Initialize f[0][initial_mask] = 1
    // Run outer DP
    // Aggregate results from f[n][mask] for final states
    return 0;
}