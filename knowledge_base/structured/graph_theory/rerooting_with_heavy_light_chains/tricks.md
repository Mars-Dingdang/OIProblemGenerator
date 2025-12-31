# 浅谈一类树上换根问题

**Author:** 赵海鲲

### Key Ideas and Tricks

- **Tree Rerooting Challenge**: When changing the root, maintaining global properties (e.g., distances, sums, maxima) is hard because the 'complement' of a subtree has no guaranteed structure.

- **Heavy-Light Decomposition (HLD)**:
  - Heavy son = child with largest subtree size.
  - Any path from node to root passes through at most $ O(\log n) $ light edges.
  - Total size of all light subtrees is $ O(n \log n) $.
  - Useful for bounding complexity when processing light children individually.

- **Long-Chain Decomposition**:
  - Long son = child with maximum height (depth in subtree).
  - A node’s path to root goes through at most $ O(\sqrt{n}) $ short (non-long) nodes.
  - The sum of heights of short nodes is exactly $ n $, since each node belongs to exactly one long chain.
  - Enables efficient maintenance of depth-limited DP arrays by only storing $ \min(L+1, \text{height}_x) $ values per node.

- **Efficient State Transfer During Rerooting**:
  - For functions like $ f_{x,i} $ (e.g., count of nodes within distance $ i $), inherit from heavy/long son and update with light sons via:
    - Prefix updates: brute-force modify for small indices.
    - Suffix updates: use lazy tags (multiplicative or matrix) for large indices where recurrence stabilizes.

- **Recovering Parent States**:
  - To compute outside-information $ F_x $, temporarily remove contributions of each light child $ y $, derive $ F_y $ from parent's state, recurse into $ y $, then restore.
  - Use reversible operations (like division in multiplicative DPs) or store intermediate states.

- **Handling Multiple Data Structures (Multi-Tree Binary Search)**:
  - When combining $ O(\log n) $ structures (e.g., segment trees from light children), avoid naive binary search over each.
  - Simultaneous binary search across identical structures (e.g., weight-balanced trees) reduces time.
  - Advanced method (Algorithm 4): Use WBLT to split trees around quantiles and eliminate a constant fraction of elements in $ O(n) $ time.

- **Convex Hull Maintenance**:
  - In averaging maximization problems, optimal average lies on the upper convex hull of (size, sum) points.
  - Minkowski sum of hulls corresponds to merging subtrees.
  - During rerooting, maintain convex hulls from light ancestors using heap-managed balanced trees.
  - Use value scaling ($ \times n^2 $) and floor to discretize slopes for segment tree storage.
  - Alternatively, simulate multi-tree binary search on slope comparisons using heap to track min/max root slopes.

- **Amortized Efficiency**:
  - Exploit that total number of short/light nodes processed across all rerooting steps is bounded (e.g., $ O(n \log \log n) $, $ O(n) $).
  - Trade-off between decomposition type: HLD better for general cases due to $ O(\log n) $ path length; long-chain better for depth-bounded DPs.

- **Observation**: $ \log \log n \approx \text{constant} $ for $ n \leq 10^6 $, making some complex bounds effectively constant in practice.