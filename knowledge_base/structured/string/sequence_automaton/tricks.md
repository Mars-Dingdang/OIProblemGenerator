## Key Observations

1. **Greedy Selection**: When checking if a string is a subsequence, always choose the earliest possible occurrence of each character. This is why `next[i][c]` stores the minimum position `j > i` where `s[j] = c`.

2. **State Interpretation**: State `i` represents that we have matched up to position `i` in the original string. State `0` is the start state (before reading any characters).

3. **Efficient Construction**: Build the automaton from right to left while maintaining the earliest occurrence of each character seen so far.

## Common Problem Transformations

1. **Shortest Non-Common Subsequence**: Given strings A and B, find the shortest subsequence of A that is NOT a subsequence of B. This can be solved using DP on both automata:
   - `dp[i][j]` = minimum length of subsequence starting from state `i` in A's automaton and state `j` in B's automaton
   - Transition: `dp[i][j] = min(dp[next_A[i][c]][next_B[j][c]] + 1)` for all characters `c`
   - Base case: `dp[i][j] = 0` when `j` is a terminal (non-accepting) state in B's automaton

2. **Counting Distinct Subsequences**: Can be combined with DP to count distinct subsequences, though careful handling is needed to avoid overcounting.

3. **Combined with Suffix Automaton**: Problems like "shortest non-common substring/subsequence" often require using both sequence automaton and suffix automaton together.

## Optimization Notes

- For small alphabets (like 26 lowercase letters), the O(n|Σ|) construction is efficient.
- The automaton can be built in O(n) time for constant alphabet size.
- Memory can be optimized using `next` array of size `(n+1) × |Σ|`.
- For multiple queries about whether strings are subsequences, building the automaton once and then answering each query in O(|t|) time is optimal.