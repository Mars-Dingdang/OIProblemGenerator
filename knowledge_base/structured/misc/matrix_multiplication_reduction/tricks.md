# 浅谈矩阵乘法与归约

**Author:** 陈诺

### Key Ideas and Observations

- **Reduction Framework**: Two problems A and B are related via A ≤ B if solving B allows solving A with little overhead. Bidirectional reduction implies equivalent difficulty.

- **Matrix Multiplication Variants**:
  - Integer, Boolean, and 01 matrix multiplications are inter-reducible under certain conditions.
  - The current best exponent ω ≈ 2.371339 gives theoretical speedups even if not practical in OI due to constants.

- **Block-based Construction for Static Problems**:
  - Divide sequences into blocks of size ~√N.
  - Encode block membership or contributions as matrices A and B such that their product C = A × B captures pairwise interactions (e.g., set intersections, equal pairs).
  - This enables reducing problems like interval distinct values or pair counting to matrix multiplication.

- **Handling Dynamic Queries via Reduction**:
  - Use block decomposition and construct query sets as vectors.
  - Matrix multiplication computes aggregated information across subsets efficiently.
  - Example: For 'range add, global zero count', simulate subset queries using +∞ modifications and repeated decrements.

- **Bidirectional Equivalences Between Query Types**:
  - Interval query problems involving functions like [x=y], [x>y], max(x,y), |x−y| can be expressed as non-orthogonal half-plane polynomials.
  - These are mutually reducible to *bipartite interval equality queries* using functional decompositions (via hashing or polynomial representations).

- **Triangle Counting ↔ Bipartite Equality Queries**:
  - Each edge’s common neighbors = intersection of neighbor lists → bipartite equality query.
  - Conversely, use segment tree decomposition to convert equality queries into a weighted tripartite graph; then reduce to triangle counting.

- **Speeding Up Classical Algorithms Using Matrix Multiplication**:
  - Apply thresholding: split elements into heavy/light contributors.
  - Handle heavy parts via matrix multiplication (size B), light parts via brute-force (cost O(N²/B)).
  - Balance B so that B^ω ≈ N²/B ⇒ B = N^{2/(ω+1)}, leading to total time O(N^{2ω/(ω+1)}).

- **Tree Path Queries (e.g., colors on path)**:
  - Use tree clustering (Top Clusters) via recursive partitioning to get O(B) clusters and O(B) boundary points.
  - Any path splits into O(N/B) scattered nodes and boundary-to-boundary segments.
  - Precompute color appearances among boundaries using divide-and-conquer with matrix multiplication over frequent colors.
  - Rare colors handled via virtual trees and 2D prefix sums after discretization.

- **General Optimization Paradigm**:
  - Let B be a parameter (block size).
  - Preprocessing cost: O(B^ω) via matrix multiplication.
  - Per-query cost: O(N/B).
  - Optimize total: O(B^ω + N²/B) minimized when B = Θ(N^{2/(ω+1)}), giving final complexity O(N^{2ω/(ω+1)}).