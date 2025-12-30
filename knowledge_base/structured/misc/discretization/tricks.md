## Key Observations
- **Preserves order**: If `a < b` in original values, then their compressed indices satisfy `compressed(a) < compressed(b)`. If `a == b`, they get the same index.
- **Space reduction**: Enables using array-based data structures (Fenwick Tree, Segment Tree) when original value range is huge (e.g., up to 1e9) but count of distinct values is moderate (e.g., up to 2e5).
- **Stable sorting**: When values are equal, sorting by original index ensures deterministic mapping; useful if order among equal values matters.

## Common Patterns
1. **Coordinate compression for intervals**: When dealing with intervals on a line (e.g., posters, meetings), compress all endpoints, then process on compressed coordinates.
2. **Union-Find with large indices**: Problems like "NOI2015 程序自动分析" require union-find on variables with large IDs; compress all appearing values first.
3. **Counting with Fenwick/Segment Tree**: After compression, you can maintain frequency arrays or prefix sums efficiently.

## Optimization Notes
- **Using `std::pair` or custom struct**: The example uses a struct to store `(value, index)`. `std::pair<int,int>` works similarly; default comparison sorts by `first` then `second`.
- **Alternative with `unique` and `lower_bound`**: Another common method: sort a copy, remove duplicates with `unique`, then map each original value via `lower_bound`. This yields 0‑based ranks and is often shorter.
- **Memory**: The auxiliary array size is O(n). If original array can be modified in‑place, you can store compressed values back into it.

## Edge Cases
- **Negative numbers**: Works fine; sorting handles them.
- **Duplicate values**: Ensure duplicates map to the same index.
- **1‑based vs 0‑based indexing**: Adjust loops and indices according to problem conventions. The template above uses 0‑based for C++ standard containers.

## Related Techniques
- **Two‑pointer after discretization**: After compression, two‑pointer sliding window can be applied on the compressed range.
- **Offline queries with Mo's algorithm**: Discretization is often a preprocessing step before Mo's algorithm to map values to indices.