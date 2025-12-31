# 浅谈一类基于线段树分治的信息维护算法

**Author:** 黄佳旭

### Key Ideas and Observations

- **Segment Tree Over Time**: Instead of handling dynamic deletions, represent each edge's lifetime as an interval in time and insert it into a segment tree where leaves are time points. Traverse the tree DFS-style, applying edges at nodes and rolling back upon exit.

- **Rollback DSU (Disjoint Set Union)**: Use a DSU that supports union with undo (stack-based). Only union by size/rank (not path compression) is used to allow rollbacks. Each merge is recorded so it can be reverted after processing a subtree.

- **Maintaining Aggregate Information per Component**:
  - For operations like `max` or `add`, maintain a stack-like structure per component root.
  - When merging set `y` into `x`, push `y`'s info onto `x`’s stack. On rollback, pop and propagate lazy tags appropriately.
  - Lazy propagation works without requiring inverses by storing prefix-style metadata (e.g., prefix max, lazy tag at time of merge).

- **Binary Grouping + Segment Trees for Arbitrary Access**:
  - To support single-point updates/queries within components (not just whole-component ops), use binary grouping: maintain $ O(\log n) $ segment trees over the sequence of merges.
  - Insertion/deletion happens only at the end → amortized efficient.
  - Each operation (update/query) affects $ O(\log n) $ trees, each taking $ O(\log n) $, leading to $ O(\log^2 n) $ per query.

- **Path-Based Updates for Point Queries**:
  - To query/update a single node’s value, traverse from node to root in DSU, propagating all pending lazy tags along the way ($ O(\log n) $ depth), then update bottom-up.

- **Space Optimization via Linear Simulation**:
  - Avoid storing $ O(m \log q) $ intervals explicitly by simulating segment tree traversal while passing active edges down recursively, reusing memory. Achieves linear space $ O(n + m + q) $.

- **Persistent Version Handling with HLD & Virtual Trees**:
  - Model version dependencies as a tree. Use Heavy-Light Decomposition (HLD) to build segment trees over DFS order of versions.
  - Break edge modifications using a virtual tree of modification points.
  - Classify edges as:
    - *Node edges*: affect only one version.
    - *Light interval edges*: affect entire subtrees of light children.
    - *Heavy interval edges*: affect parts of heavy chains.
  - This ensures disjoint scopes for operations, enabling stack-based rollback even in versioned settings.

- **Efficient Coverage via Interval Splitting**:
  - Each edge update gets decomposed into $ O(\log q) $ segment tree nodes due to virtual tree edges, resulting in $ O((m + q \log q) \log q) $ total edge applications.

- **Offline Processing Order**:
  - Process the version tree in DFS order, apply relevant edges via segment trees, answer queries, then rollback all changes — ensuring clean state for next branch.