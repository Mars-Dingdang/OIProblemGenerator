## Key Observations
- **Optimization from O(n²) to O(n)**: When `S[i+k] > S[j+k]`, all starting positions `l` in `[i, i+k]` can be skipped because for each `S_{i+p}` (p in [0,k]), there exists a better string `S_{j+p}`.
- **Pointer Jump**: Instead of incrementing by 1, jump `i` or `j` to `i+k+1` or `j+k+1` respectively.
- **Avoid Self-Comparison**: If `i == j` after a jump, increment one pointer to ensure comparing two different strings.

## Common Patterns
- **Problem Transformation**: Many problems about cyclic strings can be reduced to finding the minimum rotation.
- **Duplicate Strings**: The algorithm handles strings with repeated patterns efficiently, unlike the naive version which degrades to O(n²) on strings like `aaa...aab`.
- **Two-Pointer Technique**: The algorithm is essentially a two-pointer comparison with smart skips.

## Implementation Notes
- Use modulo arithmetic to handle cyclic indexing.
- The final answer is `min(i, j)` as both pointers may advance beyond `n`.
- Works for both even and odd length strings.

## Related Problems
- Find lexicographically smallest cyclic shift of a string.
- Check if two strings are cyclic rotations of each other (compare their minimum rotations).
- String matching in cyclic texts.