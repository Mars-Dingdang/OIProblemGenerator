# 《遇到困难睡大觉》命题报告

**Author:** 魏衍芃

### Key Ideas and Observations

- **Reformulation via Relative Positioning**: Since only relative positions matter, we can shift the entire sequence so that one level is placed at index 0. This simplifies constraint handling.

- **Constraint Derivation from M = max(b_pi + i×k)**:
  For a fixed M, each level i has a rightmost valid position: `r_i = floor((M - b_i) / k)`. These r_i values are monotonic in -b_i, allowing preprocessing by sorting.

- **Left Constraint from Binary Search**:
  When binary searching on the answer `mid`, we require `min(a_i + pos×k) - M ≥ mid`, which implies `a_i + pos×k ≥ mid + M`, leading to a left constraint: `l_i = ceil((mid + M - a_i) / k)`.

- **Feasibility as Interval Matching Problem**:
  Each level must be assigned to a position in `[l_i, r_i]` within a contiguous block of n positions containing 0. This becomes a bipartite matching problem between levels and positions.

- **Hall’s Theorem Application**:
  A perfect matching exists iff for every interval [L, R], the number of levels whose allowed interval lies entirely inside [L, R] does not exceed R - L + 1.

- **Efficient Checking with Scanline + Segment Tree**:
  Use a scanline over R, adding constraints when `r_i = R`, then updating all L ≤ l_i with +1. Query min prefix sum to detect Hall violators.

- **Key Insight: Behavior under M → M + k**:
  Increasing M by k increases all `r_i` by 1 and decreases all `l_i` by 1. The structure changes predictably — each `l_i` and `r_i` shifts only once as M mod k varies.

- **Compressing k Checks into One**:
  Instead of checking all M in [0, k), precompute base values `l'_i`, `r'_i`, and their transition points (`tli`, `tri`). Then define `q(i,j) = r'_j - l'_i + 1 - s(l_i, r_j)`.

  Analyze how `r_j - l_i + 1 - s(l_i, r_j)` evolves with M:
  - If `q(i,j) < -1`: always invalid.
  - If `q(i,j) > 0`: always valid.
  - If `q(i,j) = 0`: invalid only when `tli ≤ M < trj`.
  - If `q(i,j) = -1`: valid only when `trj ≤ M < tli`.

- **Final Feasibility Check**:
  Maintain segment tree over q-values during scanline on `r'_j`. At each node, track minimum and second minimum q-values and corresponding minimal `tli`. Collect O(n) constraints on M mod k.

  Intersect intervals from `q = -1` cases, then sweep through this intersection to validate against `q = 0` constraints using greedy coverage.

- **Lemma 1 (Optimal t)**:
  For fixed constraints, choosing largest feasible starting index `t = min(r_i - i + 1)` maximizes outcome due to monotonicity of greedy assignment.

- **Greedy Assignment Equivalence**:
  Two equivalent strategies:
  1. From back to front, pick highest `a_i` available.
  2. Sort by increasing `a_i`, assign each to first free slot from `r_i` backward (using union-find).

These insights allow transforming a complex optimization into a binary-searchable decision problem with structural efficiency gains.