## Key Observations & Tricks

### 1. **DP Principles**
- **Optimal Substructure**: Optimal solution can be constructed from optimal solutions of subproblems.
- **No Aftereffect**: Once a subproblem is solved, its solution remains valid regardless of future decisions.
- **Overlapping Subproblems**: Store solutions to avoid recomputation (memoization/tabulation).

### 2. **State Design Patterns**
- **Linear DP**: Often `dp[i]` represents answer for prefix up to `i`.
- **Two-sequence DP**: `dp[i][j]` for prefixes of two sequences (e.g., LCS).
- **Interval DP**: `dp[l][r]` for subarray/substring problems.

### 3. **LCS Optimizations**
- **Space Optimization**: Use rolling arrays to reduce `O(n*m)` space to `O(min(n,m))`.
- **Bit-Parallel LCS**: For small alphabets, use bitsets to achieve `O(n*m / w)` time (w = word size).

### 4. **LIS/LNDS Optimizations**
- **Greedy + Binary Search**: Maintain array `d` where `d[len]` = smallest possible ending value for LIS of length `len+1`. Use `lower_bound` for strictly increasing, `upper_bound` for non-decreasing.
- **Reconstruction**: Store predecessor indices to reconstruct the actual sequence.
- **Dilworth's Theorem**: For partially ordered sets, relates LIS to minimum chain decomposition.

### 5. **Problem Transformations**
- **Longest Common Substring**: Change LCS transition to reset on mismatch (`dp[i][j] = 0`).
- **Edit Distance**: Similar to LCS but with costs for insert/delete/replace.
- **Maximum Subarray (Kadane)**: Special case of DP with state `dp[i] = max(a[i], dp[i-1] + a[i])`.

### 6. **Implementation Tricks**
- **Bottom-up vs Top-down**: Top-down (memoized recursion) often easier to reason; bottom-up (iterative) usually faster and avoids recursion overhead.
- **Sentinel Values**: Use `-INF` or `0` appropriately to handle empty subsequences.
- **Loop Order**: Critical for dependency DAG; ensure subproblems are solved before they are needed.

### 7. **Common Pitfalls**
- **Off-by-one errors**: Carefully define whether indices are 0-based or 1-based.
- **Integer overflow**: Use `long long` if sums can exceed `int`.
- **TLE on large `n`**: Always consider `O(n log n)` alternatives for LIS-like problems.