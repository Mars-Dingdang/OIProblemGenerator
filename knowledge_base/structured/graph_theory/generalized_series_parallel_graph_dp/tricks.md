# 《公园》命题报告

**Author:** 吴作同

### Key Ideas and Observations

- **Generalized Series-Parallel Graphs**: Defined as graphs where no four vertices are connected by six edge-disjoint paths. These graphs can be reduced to a single node using three operations:
  - **Remove degree-1 node**: Eliminate a leaf and fold its contribution into its neighbor’s node weight.
  - **Contract degree-2 node**: Replace a node of degree 2 with a new edge combining the two incident edges and the node’s weight, storing contributions based on endpoint colors.
  - **Merge parallel edges**: Combine two edges between same endpoints by summing their respective weights.

- **Reduction Implies Structure**: Any generalized series-parallel graph can be fully reduced via these operations in O(n) steps. This allows building an *expression tree* representing how the final answer is computed from initial parameters.

- **Expression Tree Construction**:
  - Each original edge and node becomes a leaf.
  - Internal nodes represent operations: `+` (merge edges), `*` (contract degree-2), `⊕` (remove degree-1), and `R` (reverse edge direction).
  - The root holds the final result.

- **Dynamic Updates via HLD + Segment Tree**:
  - Use heavy-light decomposition on the expression tree.
  - Maintain a segment tree over each heavy path to support fast updates.
  - Transfer functions are represented as matrices under (max, +) semiring:
    - Vector state: `[f(0), f(1)]` — best value if node is black or white.
    - Transition: `f_u = g_uv ⊗ f_v`, where `⊗` is matrix multiplication with `+` replaced by `max` and `×` replaced by `+`.
  - Matrices depend on operation type (`+`, `*`, `⊕`, `R`) and which child is heavy.

- **Matrix Representation Details**:
  - For `+` (edge merging): additive combination → diagonal matrix.
  - For `*` (degree-2 contraction): max-plus combination over four cases → dense 4×4 matrix.
  - For `⊕` (leaf removal): combines node and edge weights depending on color choices.
  - For `R` (reversal): swaps cross terms (w01 ↔ w10) → permutation matrix.

- **Efficient Update Process**:
  - On update, trace affected path up to root through HLD chains.
  - At each level, recompute local `g` matrix and update segment tree.
  - Propagate changes upward until root value stabilizes.

- **Why It Works**:
  - Generalized series-parallel graphs exclude K₄ minors (in a broad sense), enabling full reduction.
  - The expression tree captures all dependencies in a hierarchical way amenable to divide-and-conquer.
  - Matrix representation ensures associative composition along paths.

- **Handling Non-commutativity**:
  - Operations like `*` and `⊕` are not commutative; order of operands matters.
  - Expression tree preserves operand order explicitly.
  - During contraction, correct argument ordering (e.g., left edge, node, right edge) must be maintained.

- **Edge Direction Handling**:
  - Edge reversal (`R`) is needed when merging edges inconsistently oriented.
  - Represented as a linear transformation in the weight space.

- **Complexity Justification**:
  - Preprocessing: O(n) reduction to build expression tree.
  - Each query affects O(log n) nodes due to HLD chain decomposition.
  - Segment tree update per chain: O(log n).
  - Total: O(Q log² n)? But paper claims O(Q log n), likely due to optimized implementation or amortization.

- **Optimization Insight**:
  - Instead of recomputing entire DP after each update, maintain incremental structure.
  - Chain decomposition limits propagation scope.

- **Extensibility**:
  - Can count number of optimal solutions by augmenting values with counts modulo prime, using tropical-like algebra with pairs `(value, count)`.