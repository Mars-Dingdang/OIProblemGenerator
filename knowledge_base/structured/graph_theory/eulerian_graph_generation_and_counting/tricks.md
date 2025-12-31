# 欧拉图相关的生成与计数问题探究

**Author:** 陈通

## Key Ideas and Tricks

### 1. **Eulerian Graph Characterization**
- **Undirected**: A graph is Eulerian iff it's connected and all vertices have even degree.
- **Semi-Eulerian**: Exactly two vertices have odd degree (start and end of Euler path).
- **Directed**: Weakly connected and `in-degree == out-degree` for all vertices.

### 2. **Hierholzer Algorithm (Preferred over Fleury)**
- Uses DFS-style stack-based traversal.
- Time complexity: `O(m)` vs Fleury’s `O(m^2)` due to bridge-checking overhead.
- Works by forming cycles and merging them during backtracking.
- Can be adapted for lexicographically smallest Eulerian circuit by sorting adjacency lists.

### 3. **Model Transformation: From Hamiltonian to Eulerian**
- When a problem seems to require visiting every *vertex* once (Hamiltonian), consider modeling edges as vertices.
- Example: De Bruijn sequence — instead of tracking strings as nodes, model overlaps as nodes and transitions as edges → reduces to Eulerian circuit in a directed graph.

### 4. **Reduction via Edge Addition**
- For semi-Eulerian graphs: Add an edge from sink to source to make it Eulerian. Count Eulerian circuits in new graph → corresponds to Eulerian paths in original.
- Used in BEST theorem extension to paths.

### 5. **Network Flow Modeling**
- **Mixed Graph Eulerian Circuit**: Fix arbitrary directions for undirected edges, compute imbalance `s(v) = out_degree - in_degree`. Use max-flow to adjust orientations: each reversal changes imbalance by ±2.
  - Source connects to nodes with `s(v) > 0`, capacity `|s(v)|/2`.
  - Nodes with `s(v) < 0` connect to sink.
  - Undirected edges become directed with capacity 1.
  - Full flow ⇒ valid Eulerian orientation exists.

- **Chinese Postman Problem (CPP)**:
  - Directed version: Min-cost flow where demand/supply based on `in_degree - out_degree`.
  - Undirected version: Find minimum-weight perfect matching among odd-degree vertices using shortest paths.

### 6. **Counting Techniques**
- **Even-Degree Graphs (Labeled, Simple, Undirected)**:
  - Any subset of edges on first `n−1` vertices determines parity; last vertex must connect to odd-degree nodes to fix parity.
  - Number of such graphs: `2^{C(n−1,2)}`.

- **Connected Eulerian Graphs**:
  - Use inclusion-exclusion: `f_n = s_n − Σ C(n−1,i−1) * f_i * s_{n−i}`.
  - Solvable in `O(n^2)` or faster with FFT/polynomial inversion.

- **Eulerian Subgraphs (Even Degree Spanning Subgraphs)**:
  - Equivalent to cycle space dimension: `m − n + c` ⇒ count = `2^{m−n+c}`.
  - Proven via linear algebra (mod 2 system) or combinatorially using spanning trees and fundamental cycles.

- **BEST Theorem (Directed Eulerian Circuits)**:
  - Number of Eulerian circuits = `T_1 × ∏_{i=1}^n (deg^+(i) − 1)!`
    - `T_1`: number of arborescences rooted at node 1 (computed via Matrix-Tree Theorem: determinant of Laplacian minor).
  - Invariant: `T_1 = T_2 = ... = T_n` in Eulerian digraphs.

### 7. **Lexicographic Optimization**
- To find lex-smallest Euler tour: sort adjacency lists, use greedy Hierholzer.
- Ensures earliest possible choice at each step while maintaining correctness.

### 8. **Important Observations**
- Every edge appears exactly twice in some closed walk ⇔ double every edge → becomes Eulerian.
- Circle decomposition: All degrees even ⇔ edge-disjoint union of cycles.
- Minimum path cover (edge coverage): equals number of added edges needed to make Eulerian ⇒ equal to `k = (#odd_vertices)/2` for undirected.

These transformations and dualities between structure, connectivity, and counting are central to solving advanced Euler-related problems.