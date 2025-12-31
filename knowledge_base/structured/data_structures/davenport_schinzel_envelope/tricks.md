# 浅谈函数最值的动态维护

**Author:** 李白天

## Key Ideas and Observations

- **Davenport-Schinzel (DS) Sequences**: These sequences model the alternation complexity between functions. For a family of functions where any two intersect at most s times, the upper envelope of n such functions has at most λ_s(n) segments, where λ_s(n) is the maximum length of a DS(n,s) sequence.

- **Upper Envelope Maintenance**: When maintaining max_j f_j(x), the structure of where each f_j dominates forms a piecewise function with at most λ_s(n) breakpoints. This allows efficient merging and querying if s is small (e.g., linear functions → s=1; piecewise linear → s=3).

- **Binary Grouping (for static insertions)**: Insert functions into groups sized like powers of two. Each group maintains its own upper envelope. On query, binary search within each group’s envelope. Using fractional cascading across layers reduces query time from O(log² n) to O(log n).

- **Fractional Cascading Optimization**: By pre-merging every third element from higher-level envelopes into lower ones, we can propagate lower_bound results in O(1) per level, reducing total query time to O(log n).

- **Kinetic Tournament Tree (KTT)**: A segment tree where each node tracks which child’s function currently achieves the maximum at current x. As x increases monotonically, events occur when dominance switches. Each node changes O(λ_s(size)) times, leading to O(λ_s(n) log² n) total update cost.

- **Amortized Analysis via Potential Functions**:
  - In KTT, define potential based on slope comparisons between children. If left child has smaller slope than right but currently dominates, it may be overtaken — this defines membership in set P.
  - Potential Φ = sum of depths of such nodes. Updates decrease potential significantly, making amortized cost low.
  - For special cases (e.g., slopes increasing), only one-way transitions happen (left → right), limiting switch count to O(n log n).

- **Application to DP Optimization**: Transforms DP of form `a_i = max_{j<i} a_j + w_{j,i}` into function maximization, where fj(xi) = aj + wj,i. If these functions are low-order alternating (e.g., due to quadrangle inequality), then DS-based structures apply.

- **Handling Range Updates**:
  - Supports operations like adding an arithmetic progression with positive common difference over intervals.
  - Uses lazy propagation in KTT-style trees, interpreting updates as advancing a virtual time parameter affecting linear functions.
  - Achieves O(log³ n) per update using potential analysis, improving over known √n block-based methods.

- **Generalization Beyond Lines**: While focused on linear/piecewise-linear functions, framework extends to higher-degree polynomials (with increased s), though efficiency depends on bounding intersection counts.