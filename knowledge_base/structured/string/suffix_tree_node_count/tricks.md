# 《后缀树结点数》命题报告及一类区间问题的优化

**Author:** 陈江伦

### Key Ideas and Observations

- **Suffix Tree Node Count Composition**: The total number of nodes in a suffix tree equals:
  - Number of suffix nodes: exactly `r - l + 1` (one per suffix).
  - Plus the number of internal nodes (non-suffix nodes) with at least two children in the suffix trie.
  - However, nodes that are both suffixes and have ≥2 children are double-counted; subtract these.

- **Characterization of Internal Nodes**: A node corresponding to substring `t` becomes an internal node (i.e., not compressed) if `t` has at least two distinct successor characters in the string (i.e., `tc₁` and `tc₂` are both substrings).

- **Contribution on Left Expansion**: When extending the current substring from `P[l+1, r]` to `P[l, r]`, new contributions arise when a prefix `t = P[l, v]` now has two different successors, but previously had only one.

- **Real Son and Dynamic Tree Analogy**:
  - Define the 'real son' of a node as the child whose string appears latest.
  - Adding a new left character corresponds to an `access` operation in a link-cut tree.
  - Real son switches occur only when the successor character differs from the last occurrence — this happens at most O(log n) times amortized per operation.

- **Last and Diff Tracking**:
  - Let `last[t]` be the last occurrence position of string `t`.
  - Let `diff[t]` be the last position where `t` appeared with a different successor than its most recent appearance.
  - Then, `t` starts contributing to answers in intervals `[l, r]` where `r ∈ [last[t] + |t|, diff[t] + |t|)`.
  - This enables range-update (e.g., via segment tree) when moving `l` leftward.

- **Double-Counting Adjustment**:
  - Nodes that are both suffixes and branching (≥2 children) are counted twice.
  - Such strings `t = P[v, r]` must satisfy that `t` appears again in `[l, r]` with different successors.
  - Crucially, if a string `t` has multiple successors, so do all its suffixes → monotonicity in length.
  - Thus, binary search the maximum length `L` such that `P[r-L+1, r]` has multiple successors in `[l, r]`. Adjust answer by `-L`.

- **Efficient Check Using Hashing**:
  - Precompute hash values for all substrings to enable O(1) comparison.
  - Use hash table to map substring → node in suffix structure → access `last` and `diff` in O(1).
  - This reduces binary search cost from O(log n) per check to O(1), leading to O(log n) total per query after preprocessing.

- **Replacing Dynamic Trees with Heuristic Merging**:
  - Instead of using complex dynamic trees (LCT), maintain for each node the sorted list of occurrence positions (by right endpoint).
  - Use **启发式合并 (small-to-large merging)**: merge lighter child lists into heavier ones.
  - Each time a position is inserted, it may create at most 2 new 'breakpoints' (adjacent pairs with different successors).
  - Since each node participates in O(log n) merges, total events = O(n log n).
  - From these breakpoints, directly extract `last` and `diff` without LCT.
  - This simplifies code and avoids heavy data structures while preserving complexity.

- **General Applicability**:
  - This method applies to any problem involving interval queries over substrings where contributions depend on predecessor/successor behavior of repeated patterns.
  - Examples include counting distinct substrings in intervals or constructing virtual trees over node ranges in labeled trees.