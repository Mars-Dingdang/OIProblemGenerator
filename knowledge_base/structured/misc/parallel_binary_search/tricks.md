## Key Observations
1. **Offline Requirement**: All queries and updates must be known in advance.
2. **Monotonic Answer**: The answer to each query must be monotonic with respect to the binary search criterion (e.g., "is the k-th element ≤ x?").
3. **Independent Contributions**: Updates must have independent, additive contributions to the predicate.

## Optimizations
- **Global Array + Pointer Tracking**: For static problems, sort values and maintain a pointer `pos` to track the current mid. Update BIT only when `pos` moves, drastically reducing BIT operations from O(n log² n) to O(n log n).
- **In-place Partition**: Use temporary arrays `q1`, `q2` for partitioning, then merge back into the original array to avoid extra copying.
- **Rollback BIT Changes**: After processing a layer, revert BIT updates made by left-partition updates by adding `-val`. This avoids full BIT clears.
- **Discretization**: Always discretize value range to [1, cnt] to reduce binary search range.

## Problem Transformations
- **Range k-th Smallest**: Classic application; use BIT to count numbers ≤ mid in a range.
- **Dynamic Updates**: Treat updates as deletions (+1) and insertions (-1) with type=0.
- **Range Predecessor/Successor**: First use CDQ to compute rank (count of numbers < k), then use overall binary search to find the k-th smallest.
- **Monotonic Sequence Construction**: For making sequence non-decreasing with min +1/-1 ops, binary search on final values and greedily choose split points.

## Implementation Notes
- Use `type` field to distinguish queries (1) from updates (0).
- For updates, `k` field can store the value for comparison, and `r` field can store +1/-1 for BIT update magnitude.
- Ensure BIT range matches sequence length (n), not value range.
- When partitioning queries, adjust `k` for right partition by subtracting count from left partition.
- Base case `l == r` assigns answer to all queries in current batch.