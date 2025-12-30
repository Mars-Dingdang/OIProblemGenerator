## Key Observations & Optimizations

1. **State Representation**: Use an integer bitmask where the i-th bit represents the state of the i-th element (e.g., selected/not selected, color, etc.).

2. **Precomputation**: Often you can precompute all valid single-row/column states and their properties (like number of set bits) to speed up transitions.

3. **Subset Enumeration**:
   - To iterate over all subsets of a mask `S`: `for (int sub = S; sub; sub = (sub - 1) & S)`.
   - To iterate over all subsets of size `n`: `for (int mask = 0; mask < (1 << n); ++mask)`.
   - Complexity of iterating over all subsets of all masks is O(3^n), not O(4^n).

4. **Memory Optimization**:
   - Use rolling arrays (only keep previous row) when DP depends only on the previous state.
   - Use `int` or `long long` arrays indexed by bitmask directly (size 2^n).

5. **Common Problem Transformations**:
   - **Traveling Salesman Problem (TSP)**: `dp[mask][i]` = minimum cost to visit set `mask` ending at city `i`.
   - **Assignment Problems**: Matching `n` items to `n` slots where each item has a cost per slot.
   - **Dominating Set / Vertex Cover** on small graphs.
   - **Grouping Problems**: Partition a set into groups satisfying constraints (like the bridge problem PRZ).

6. **Bit Operations for Checks**:
   - No two adjacent bits set: `(mask & (mask >> 1)) == 0`.
   - Subset check: `(sub & mask) == sub`.
   - Complement of mask within `n` bits: `((1 << n) - 1) ^ mask`.

7. **SOS DP (Sum Over Subsets)**:
   - Used to compute `f[mask] = sum of g[sub] for all sub ⊆ mask` in O(n * 2^n).
   - Iterate over bits: `for (int i = 0; i < n; ++i) for (int mask = 0; mask < (1 << n); ++mask) if (mask & (1 << i)) f[mask] += f[mask ^ (1 << i)];`

8. **Symmetry & Pruning**:
   - Many states are symmetric; you can canonicalize states (e.g., sort bits) to reduce state space.
   - Prune invalid states early in DFS generation.

9. **Meet-in-the-Middle**:
   - For n up to ~40, split into two halves, compute DP for each half, and combine results.

10. **Using __builtin Functions (GCC)**:
    - `__builtin_popcount(mask)`: count set bits.
    - `__builtin_ctz(mask)`: count trailing zeros.
    - Useful for fast iteration over set bits: `while (mask) { int i = __builtin_ctz(mask); ... mask &= mask - 1; }`