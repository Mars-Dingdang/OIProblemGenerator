#include <bits/stdc++.h>
using namespace std;

// Example template for DP over DP (DP on automaton states).
// This is a generic skeleton. The actual states and transitions are problem-specific.
// Typically, we first build an automaton for the inner DP condition.

const int MOD = 1e9 + 7;

// Suppose inner DP has S states after minimization.
// dp_outer[i][s] = number of ways for first i elements, ending at automaton state s.
// Transitions depend on the next element and the automaton's transition function.

int main() {
    int n; // length of sequence
    cin >> n;
    // Build automaton (problem-specific, often via BFS/DP on inner states).
    // Let 'next_state[s][c]' give new state from state s on input c.
    // Initialize dp_outer[0][initial_state] = 1.
    // for (int i = 0; i < n; i++) {
    //     for (int s = 0; s < num_states; s++) {
    //         for (int c : possible_inputs) {
    //             int ns = next_state[s][c];
    //             dp_outer[i+1][ns] = (dp_outer[i+1][ns] + dp_outer[i][s]) % MOD;
    //         }
    //     }
    // }
    // Sum over accepting states for answer.
    return 0;
}