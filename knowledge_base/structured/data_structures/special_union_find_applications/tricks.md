# 浅谈并查集在OI 中的特殊应用

**Author:** 王相文

## Key Ideas and Tricks

### 1. **Linear Tree-Based Union-Find**
- Used when operations occur on a static tree and queries involve jumping up along merged edges.
- The tree is divided into blocks of size $ B = \lfloor \log n \rfloor $, enabling efficient intra-block queries via bit manipulation.
- Each block maintains:
  - A bitmask indicating which nodes are *not* merged with their parent.
  - Precomputed path masks from each node to the block root.
- Intra-block `Find` uses bitwise AND and `highbit` to find the highest unmerged ancestor in $ O(1) $ after preprocessing.
- Inter-block structure is compressed into a smaller tree of size $ O(n / \log n) $, where standard Union-Find with small-to-large merging achieves $ O(n) $ total time.
- Applied to problems like shortest path on colored strips, DP optimization with monotonic stacks, and offline LCA (Tarjan's algorithm).

### 2. **Weighted Union-Find**
- Maintains relative values (or relations) between elements in a set.
- Each node stores a `tag` representing the accumulated value from itself to its parent (lazy propagation on tree paths).
- When merging two sets:
  - If information is *invertible* (e.g., additive over integers), adjust one set’s tag relative to the other before linking (supports union in either direction).
  - Otherwise, create a new virtual root node and attach both roots to it to preserve correctness under path compression.
- Path compression updates node weights during `Find` to reflect true values.
- Example: Food chain problem where relations modulo 3 represent predator-prey relationships.
- Also used in tree path queries (e.g., max subarray sum on paths) by combining algebraic structures (quadruples: lmx, rmx, sum, ans) that support associative merging.

### 3. **Rollback (Undoable) Union-Find**
- Supports `Union`, `Find`, and `Back()` to undo the last operation.
- Uses **union by size (heuristic merging)** instead of path compression because path compression has amortized complexity and breaks undoability.
- Maintain a stack recording every parent change (`x -> y`) and subtree size changes.
- On `Back()`: pop the stack, restore the original parent of `x`, and revert the size of the old root.
- Enables DFS-based traversal over an "operation tree" for offline handling of versioned states.
- Applied to dynamic graphs with edge insertions/deletions:
  - Assign each edge a lifespan (time interval).
  - Insert edges into a segment tree over time.
  - Perform DFS on the segment tree, activating edges at nodes and rolling back upon exit.
  - Answer queries at leaves using current connectivity state.
- Total complexity: $ O(q \log q \log n) $ due to $ O(\log q) $ segment tree nodes per edge and $ O(\log n) $ per union.

### General Observations
- **Offline Processing**: Many advanced uses rely on processing queries or events in specific orders (e.g., reverse DFS order for LCA, increasing right endpoint for greedy jumps).
- **Combining Structures**: Union-Find often works alongside other techniques — segment trees, monotonic stacks, difference arrays, and Euler tours.
- **Linearity via Block Optimization**: Tree blocking allows reducing high-level DSU calls while solving local parts in constant time via bit operations.
- **Lazy Propagation on Trees**: Weighted DSU effectively implements lazy propagation along forest paths, similar to what might be done in segment trees but adapted to dynamic forests.