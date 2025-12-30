## Key Observations & Optimizations

1. **Doubling with Radix Sort**: The standard O(n log n) construction uses doubling and two-pass radix sort (by second key then first key).
2. **Second Keyword Optimization**: Instead of sorting the second keyword, we can directly construct the order: positions `i` where `i + w > n` come first, followed by `sa[i] - w` for `sa[i] > w`.
3. **Value Domain Optimization**: After each doubling step, the rank value domain shrinks to the number of distinct ranks `p`. Use `m = p` to limit counting sort range.
4. **Early Termination**: If after a step all ranks are distinct (`p == n`), the suffix array is fully sorted and we can stop.
5. **Height Array in O(n)**: Use the property `height[rk[i]] >= height[rk[i-1]] - 1` to compute LCP between adjacent suffixes in SA.

## Common Problem Transformations

- **Pattern Matching**: Binary search on SA with O(|pattern| log n) time.
- **Distinct Substrings**: Total substrings minus sum of `height` array.
- **Longest Repeated Substring**: Maximum value in `height` array.
- **Lexicographically Minimal String from Ends**: Append reversed string with separator, build SA, compare ranks of left and right pointers.
- **LCP of Any Two Suffixes**: Minimum in `height[l+1..r]` via RMQ.
- **At Least k Occurrences**: Sliding window minimum over `height` of size k-1.
- **Non‑overlapping Repeated Substrings**: Binary search length, group by `height >= len`, check index ranges.
- **Combining with Data Structures**: Use monotonic stack for sum of LCPs (e.g., "差异"), union‑find for decreasing thresholds (e.g., "品酒大会"), segment tree for merging information.