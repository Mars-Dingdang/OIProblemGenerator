# 一类基础子串数据结构

**Author:** 许庭强

### Key Ideas and Observations

- **Extension Function (ext)**: For any substring `t`, `ext(t)` is defined as the longest substring containing `t` with the same occurrence count. This function is idempotent (`ext(ext(t)) = ext(t)`) and partitions all substrings into equivalence classes.

- **Equivalence Classes and Representative Elements**: Each class has a unique representative `rep(a) = t` such that `ext(t) = t`. These representatives are the maximal substrings in their class and serve as anchors for the geometric structure.

- **Geometric Interpretation (Staircase Grids)**: In a 2D plane with axes `(l, r)` representing substring start and end, each equivalence class forms a *staircase-shaped grid* — left-aligned and top-aligned — where every point corresponds to a substring’s first occurrence. The shape arises because if two endpoints define valid substrings in the class, so do all points within the bounding rectangle.

- **Connection to SAM Parent Trees**:
  - Rows (fixed `r`) in a grid correspond to nodes in the forward SAM's parent tree (`T0`).
  - Columns (fixed `l`) correspond to nodes in the reverse SAM's parent tree (`T1`).
  - Thus, intersections of rows and columns represent individual substrings, linking both directional SAM structures.

- **Tree Edge Encoding**: Tree edges from parent decompositions are encoded as connections between boundaries of different blocks:
  - `T0` edges link upper boundary segments to lower aligned ones.
  - `T1` edges link left to right boundary segments.

- **Structural Isomorphism (Theorem 3.4)**: If two SAM nodes lie in the same block (same `l` for longest string), their entire parent subtrees (excluding root) are structurally isomorphic — including OCC counts and relative positioning in grids. This allows grouping of transitions.

- **Efficient Construction**:
  - Build forward and reverse SAMs in `O(n)`.
  - Identify representatives by checking whether a node’s longest string has only one outgoing edge in the automaton (indicating it's not extendable without changing OCC).
  - Use `posl`, `posr` of representatives to map all nodes to their equivalence classes.
  - Sort nodes by `l` or `r` (which naturally follows SAM insertion order) to reconstruct grid layouts.

- **Applications Relying on Geometry**:
  - **Query Intersections**: e.g., common substrings in a forward-SAM node and reverse-SAM node → intersect a row and column in the grid → `O(1)`.
  - **Weighted Sum Over Substrings**: Decompose total weight over blocks; use prefix sums across rows/columns due to rectangular structure.
  - **Pattern Matching Aggregation**: Perform prefix sums along `T1` then `T0` (i.e., horizontally then vertically in grid), optimized using block structure to avoid `O(n^2)` blowup.
  - **Dynamic Programming Optimization**: In problems like deletion sequences weighted by `occ(T_i)`, process equivalence classes in decreasing `occ` order. Within a class, use divide-and-conquer FFT leveraging the staircase contour to compute DP transitions efficiently (`O(per(a) log² n)` per block).

- **Tree Chain Decomposition on Basic Substring Structure**:
  - Define heavy-light decomposition on SAM parent trees using size and `posr` for tie-breaking.
  - Due to subtree isomorphism (Theorem 3.4), entire groups of edges (from block boundary) are either all heavy or all light.
  - Enables alignment of chain endpoints across occurrences of a block.
  - Chains can be indexed by leaf `posr`, making each node’s presence on chains form a contiguous interval → facilitates 2D range queries over `(chain_id, length)`.
  - Useful for border-related queries: a border is a common prefix-suffix → intersection of a path in `T0` (suffixes) and `T1` (prefixes). After HLD, this becomes `O(log n)` pairwise segment intersections.

- **Advantages Over Existing Structures**:
  - Surpasses symmetric compressed SAM by preserving internal grid structure instead of collapsing blocks.
  - Outperforms DAG-based methods (e.g., DAG partitioning) in multi-directional aggregation tasks.
  - Enables solving strengthened versions of problems (e.g., nested prefix-suffix statistics) that break traditional approaches.