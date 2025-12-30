## Key Observations
- **Linear States**: A string of length n has at most n distinct palindromic substrings.
- **Incremental Construction**: The tree is built character by character, maintaining the longest palindromic suffix for each prefix.
- **Two Roots**: Use odd root (len = -1) and even root (len = 0) to handle odd/even length palindromes without separators.

## Optimizations
- **Fail Pointer Jumps**: The total number of fail jumps during construction is O(n).
- **Occurrence Counting**: Propagate counts from nodes to their fail pointers in reverse topological order.
- **Arithmetic Progression (AP) Decomposition**: All palindromic suffixes can be partitioned into O(log n) arithmetic progressions. This enables O(n log n) DP for problems like minimum palindromic partitioning.
  - Maintain `diff[u] = len[u] - len[fail[u]]` and `slink[u]` (the first node in the AP chain where diff changes).
  - Use `g[v]` to store DP sum for the entire AP, updating efficiently via `g[fail[x]]`.

## Common Transformations
- **Palindrome Partitioning**: For problems like dividing a string into palindromes, transform by interleaving characters (e.g., `t = s[0]s[n-1]s[1]s[n-2]...`) to reduce to even palindromic partitioning.
- **Double-ended Operations**: Extend the tree to support insertions at both ends (e.g., HDU 5421).
- **Border Properties**: Leverage relationships between borders, periods, and palindromes for combinatorial proofs and optimizations.

## Implementation Notes
- Initialize with `s[0] = '$'` to simplify boundary checks.
- The `getfail` function finds the longest palindromic suffix that can be extended by the new character.
- New node creation ensures the fail pointer points to the longest proper palindromic suffix.
- For AP optimization, compute `dif` and `slink` during node creation.