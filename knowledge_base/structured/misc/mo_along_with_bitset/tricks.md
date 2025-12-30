- **Avoid negative indices in bitset**: When using Mo's algorithm with `bitset`, ensure that the movement of pointers does not result in negative counts being used as indices. Always move outward pointers (extending the interval) before inward ones (shrinking), especially when inserting elements like `x + cnt[x]` into the bitset.

- **Use occurrence-augmented indexing**: To handle multiple occurrences of the same value, insert `x + cnt[x]` instead of just `x` into the bitset. This way, each occurrence maps to a unique position, allowing correct tracking of multiplicities across intervals.

- **Reduce space via batch processing**: Due to high memory usage of `bitset<N>` (e.g., 10^5 × 10^5 bits ≈ 1.25 GB), split queries into blocks of constant size (e.g., 3–5 queries per group) and process each block separately to reuse the same `bitset` storage, reducing peak memory usage significantly.

- **Combine results using bitwise operations**: For problems asking for union sizes over multiple intervals, use `&=` (intersection) during Mo’s to accumulate common elements, then compute final answer as total length minus intersection count multiplied appropriately.

- **Discretize input values**: Always discretize the original array values to compress the range into `[1, n]`, which makes indexing into `bitset` safe and efficient.