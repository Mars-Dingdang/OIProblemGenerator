## Key Observations

1. **Tag Method for O(1) Comparison**: Assign each node a real-valued tag within an interval (e.g., (0, INF)). The tag represents the node's position in the sorted order. Comparison between two suffixes reduces to comparing their tags after checking the first character.

2. **Reverse String for Tail Operations**: To support append/delete at the end efficiently, maintain the **reversed string** in the suffix balanced tree. This converts tail operations into head operations.

3. **Counting Occurrences**: The number of occurrences of a pattern `t` equals the number of suffixes that have `t` as a prefix. This can be computed as `rank(successor(t)) - rank(predecessor(t))`, where successor is constructed by appending a large character to `t`, and predecessor by decreasing `t`'s last character.

4. **Online Construction**: Build the tree by inserting suffixes in **reverse order** (from last to first). Each insertion corresponds to adding a new character at the beginning of the string.

## Optimizations

- **Scapegoat Tree for Simplicity**: Use a scapegoat tree (α=0.75) for amortized O(log n) operations without complex rotations.
- **Lazy Rebuilding**: Rebuild subtree only when imbalance factor exceeds α, ensuring O(n log n) total time.
- **Precision Handling**: Use double or long double for tags; the interval (0, 1e18) provides sufficient precision for practical n ≤ 1e6.

## Problem Transformation Patterns

- **Dynamic Suffix Array**: Suffix balanced tree's inorder traversal directly gives the suffix array.
- **Pattern Matching in Dynamic String**: Maintain reversed string's suffix balanced tree. For query pattern `t`, reverse `t` and query its rank range.
- **Persistent Suffix Queries**: Use a persistent balanced tree (e.g., persistent treap) to support versioned suffix queries.

## Implementation Notes

- **Node Representation**: Each node corresponds to a suffix starting at index `i`. Store `tag[i]` for O(1) comparison.
- **Comparison Function**: First compare `t[x]` vs `t[y]`. If equal, compare `tag[x+1]` vs `tag[y+1]` (for suffixes starting at x and y).
- **Deletion Handling**: Must physically delete nodes (no lazy deletion) to maintain correct tree structure for future comparisons.