# 浅谈一类树上统计相关问题

**Author:** 朱羿恺

## Key Ideas and Observations

- **Problem Transformation**: The original query — counting nodes within distance `d` from path `x → y` — is broken down via LCA (`z = lca(x, y)`), splitting the path into `z → x` and `z → y`. Using inclusion-exclusion, it reduces to computing counts along root-to-node paths.

- **Heavy-Light Decomposition (HLD)**: The tree is decomposed into heavy and light edges. Each node has at most one heavy child (the one with largest subtree), forming disjoint heavy chains. Light edges connect different chains.

- **Key HLD Properties Used**:
  - Any path from root to node crosses at most `O(log n)` light edges (since each light edge reduces subtree size by at least half).
  - Total size of all light subtrees across the tree is `O(n log n)`.

- **Contribution Splitting**:
  - Contributions to a query are split into two parts:
    1. From **heavy subtrees** of ancestors on the path (handled efficiently via preprocessing on heavy chains).
    2. From **light subtrees**, excluding the branch containing the query point.

- **Efficient Light Subtree Handling**:
  - A major optimization involves scanning down each heavy chain and incrementally adding light subtrees of nodes.
  - Maintain a global **prefix sum array** `P[i]`: total number of nodes in already processed light subtrees with depth ≤ `i` relative to their parent.
  - When processing a node `u`, add its light children’s subtree information to this prefix array in `O(depth)` time.

- **Query Answering**:
  - For a query `(x, y, d)`, after reducing to root-path differences, answer can be retrieved in `O(1)` from the prefix structure when traversing the chain containing `x`.

- **Handling Undercounted Parts**:
  - Naive prefix sum misses some contributions due to depth truncation.
  - Fix this by grouping light subtrees by depth intervals `[2^i, 2^(i+1))`.
  - Maintain two types of structures:
    - **Global group prefix arrays**: One per group, updated in `O(log n)` per insertion (total `O(n log n)`).
    - **Intra-group prefix arrays**: Updated in amortized `O(1)` per unit size due to geometric grouping; total cost remains `O(n log n)`.

- **Final Complexity**: All operations aggregate to `O(n log n)` total time due to logarithmic bounds on light edge traversals and amortized-efficient updates.

- **General Applicability**:
  - This framework applies broadly to tree path queries involving distances or subtree aggregations dependent on LCA.
  - Example applications include string problems via suffix trees (e.g., border queries, Z-function variants), where LCP corresponds to LCA depth.