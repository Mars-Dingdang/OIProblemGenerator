# 《数据结构》解题报告

**Author:** 朱屹帆

### Key Ideas and Observations

- **Core Insight**: Traditional heavy-light decomposition allows path-to-logarithmic-chains reduction, but lacks locality for neighborhood operations. This work enhances HLD by redesigning the DFS labeling order to improve spatial locality of k-degree neighborhoods.

- **Relabeled HLD Construction**:
  - Traverse heavy chains top-down (by depth).
  - For each node in the chain, label its light children’s subtrees up to depth `i` during the `i-th` round (for `a` rounds, here `a=3`).
  - Once labeled, nodes retain their first assigned index — avoiding re-labeling.
  - This ensures that k-degree neighborhoods (especially along heavy chains) have mostly contiguous indices in the final array.

- **Segment Maintenance for Non-Contiguous Parts**:
  - Due to early labeling from ancestor chains, the top `a` layers of a heavy chain may not be contiguous with the rest.
  - To fix this, define two types of precomputed segments:
    - `s0{x, k}`: The set of contiguous intervals (segments) containing all nodes at exactly distance `k` from `x` **within** `x`'s subtree.
    - `s1{x, k}`: Same as above but restricted to nodes in the **light children subtrees** of `x`.
  - These are computed post-labeling via dynamic programming and stored for fast access.

- **Key Properties**:
  - **Property 6.1**: `s1{x, k}` has at most 2 segments due to continuity in labeling of light descendants; only broken possibly by one heavy successor.
  - **Property 6.2**: `s0{x, k}` has at most `a+1` segments because it aggregates contributions from multiple `s1` sets across levels.

- **Handling Operations**:
  - **Path-based update/query (ops 1,3,5)**: Decompose path into heavy chains. For each chain segment, use the min/max label in the k-neighborhood as interval bounds. Add corrections using `s0/s1` for non-contiguous top parts.
  - **Subtree-based (ops 2,4,6)**: Use standard subtree interval plus correction from `s0{x,k}` for top `a` layers.
  - **LCA Handling**: When processing a path `(x,y)`, split at LCA and apply inclusion-exclusion; however, **max queries cannot use subtraction**, so alternative methods are needed.

- **Max Query Fix (Algorithm 5)**:
  - Avoid inclusion-exclusion by using a **sweep-line method**.
  - Represent each contributing interval with +1 at start and -1 at end+1.
  - Sweep through events: positions with positive cumulative weight are active.
  - Then query max over union of these active intervals directly (since each point has unique ID).
  - This avoids decomposing max over subtracted regions.

- **Efficiency Justification**:
  - Each operation generates `O(a)` or `O(a²)` intervals due to bounded fragmentation in `s0/s1`.
  - Combined with segment tree / Fenwick tree operations (`O(log n)`), total complexity becomes `O(a² log a × n log² n)` naively, optimizable to `O(a × n log² n)` with care.