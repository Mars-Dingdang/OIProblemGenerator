## Key Observations
- **Generalized Matrix Multiplication**: Use max-plus algebra (replace multiplication with addition, addition with max) to represent DP transitions as matrix multiplication, which is associative.
- **Heavy-Light Decomposition (HLD)**: Decompose the tree into heavy paths to support efficient updates/queries. Each path is managed with a segment tree storing matrices.
- **Separate Light/Heavy Contributions**: Define `g[i][0/1]` as DP values considering only light children, then combine with heavy child via matrix multiplication.

## Optimizations
- **O(log² n) Updates**: Each update climbs O(log n) heavy paths, each requiring O(log n) segment tree operations.
- **Lazy Propagation Not Needed**: Since updates affect only ancestors along heavy paths, recompute matrices directly.
- **Precompute Initial Matrices**: Compute `g` matrices during HLD preprocessing to avoid redundant calculations.

## Common Problem Transformations
- **Maximum Weighted Independent Set (MWIS)**: Classic example; DP is `f[i][0]` (not take i) and `f[i][1]` (take i).
- **Edge Weight Updates**: Convert to point weights by associating edges with child nodes.
- **Other DP Formulations**: Any DP with linear recurrences on trees (e.g., maximum matching, minimum vertex cover) can be adapted using appropriate matrix definitions.

## Implementation Tricks
- **Matrix Structure**: Use 2x2 matrices for MWIS; adjust size for other DPs.
- **Segment Tree on HLD**: Build segment tree over HLD order; query product from node to end of its heavy path.
- **Update Propagation**: When updating a node, recalc its matrix, then propagate changes to parent's `g` matrix using difference between old and new query results.
- **Initialization**: DFS to compute `f` and `g`; second DFS for HLD and matrix building.

## Pitfalls
- **Infinite Values**: Use `-INF` carefully in matrices to avoid overflow.
- **Matrix Multiplication Order**: Ensure correct order (child matrix on right).
- **Heavy Child Selection**: Standard HLD; ensure `son[u]` is initialized.
- **1‑Based Indexing**: Common in HLD implementations; adjust if needed.