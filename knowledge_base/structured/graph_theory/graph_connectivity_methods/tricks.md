# 综述图论中连通性及相关问题的一些处理方法

**Author:** 万成章

## Key Ideas and Tricks

### **DFS Tree Fundamentals**
- In an undirected graph, a DFS tree has the key property that all non-tree edges are back edges (connecting a descendant to an ancestor).
- This structure allows efficient computation of `low` values: `low[u] = min(dfn[u], min(low[v]), min(df[w]))`, where `v` is a child and `(u,w)` is a back edge.
- Used to detect bridges (`low[v] > dfn[u]` for tree edge `u→v`) and cut vertices (`low[v] >= dfn[u]` for non-root node `u`).

### **Biconnectivity and Round-Square Tree (圆方树)**
- **Edge-Biconnected Components**: Remove all bridges. Each remaining connected component is an edge-biconnected component. Computed via DFS with `low` array.
- **Vertex-Biconnected Components**: Defined as maximal sets such that any two edges lie on a common simple cycle. Not a partition of vertices, but of edges.
- **Round-Square Tree Construction**:
  - One round node per original vertex.
  - One square node per vertex-biconnected component.
  - An edge between a round node `v` and a square node `C` iff `v ∈ C`.
- Properties:
  - The round-square tree is a bipartite tree.
  - A vertex is a cut point iff its degree in the round-square tree > 1.
  - Path queries between `u` and `v` pass through exactly the biconnected components corresponding to the square nodes on the unique path in the round-square tree.

### **Ear Decomposition**
- **Undirected Graphs**:
  - A graph is edge-biconnected iff it admits an ear decomposition starting from a cycle.
  - A graph is vertex-biconnected iff it admits an open ear decomposition (ears are paths, not cycles).
- **Directed Graphs**:
  - A digraph is strongly connected iff it admits an ear decomposition.
- Useful for dynamic programming over biconnected/strongly connected graphs (e.g., minimum weight edge-biconnected subgraph).

### **Cut Space and Cycle Space (F2 Linear Algebra)**
- Represent edge sets as vectors in $\mathbb{F}_2^m$.
- **Cycle Space**: Spanned by fundamental cycles formed by adding each non-tree edge to a spanning tree. Dimension: $m - n + c$.
- **Cut Space**: Spanned by fundamental cuts defined by each tree edge. Dimension: $n - c$.
- **Orthogonality**: Cycle space and cut space are orthogonal complements: $E_1 \cdot E_2 = 0$ mod 2 for any cycle $E_1$ and cut $E_2$.
- **Application — Randomized Cut Detection**:
  - Assign random weights to non-tree edges.
  - Define tree edge weight as XOR of weights of non-tree edges whose fundamental cycle contains it.
  - A set of edges is a cut iff total XOR is zero (with high probability).
  - Used in problems like DZY Loves Chinese II.

### **Strong Connectivity and Tarjan’s Algorithm**
- Use DFS stack and `low` array to find SCCs.
- Maintain a stack of active nodes. When `low[u] == dfn[u]`, pop the stack until `u` is reached — this forms an SCC.
- After finding all SCCs, contract them to form a DAG (condensation).

### **Tournament Graphs**
- Every pair has exactly one directed edge.
- Always has a Hamiltonian path (constructible by insertion).
- Strongly connected tournaments have a Hamiltonian cycle.
- SCCs form a total order (a chain after condensation).
- **Landau’s Theorem**: Sort nodes by in-degree. Node `k` is the end of an SCC iff $\sum_{i=1}^k d_i = \binom{k}{2}$.

### **Directed Cycle Weights and Modular Arithmetic**
- For strongly connected graphs, the set of achievable cycle weights modulo `m` depends on the GCD of all cycle lengths.
- Using a DFS tree, define potential `dep[u]` as distance from root.
- For a non-tree edge `u → v` with weight `w`, the fundamental cycle weight is $w + dep[v] - dep[u]$.
- The GCD of all such values gives the generator of the cycle weight subgroup.
- Can be extended to XOR and k-ary carry-less addition by building linear bases.

### **Bitset Optimization for Reachability**
- For DAGs, compute transitive closure by processing nodes in reverse topological order.
- Use bitset `f[u]` to represent all nodes reachable from `u`.
- Then: `f[u] = OR(f[v])` for all `u → v`, plus self-reachability.
- Complexity: $O(nm / w)$ using bit-level parallelism.

### **Query/Update Batching with Bitsets**
- For dynamic reachability with edge flips, use batch processing (block size `B`).
- Precompute static reachability among critical points (those involved in the block).
- Answer queries via BFS enhanced with bitset operations over the reduced graph.
- Total complexity: $O(q(n+m)/w + qB^2/w)$.

### **Key Observations**
- Menger’s Theorem links connectivity to disjoint paths (vertex/edge).
- Ear decompositions provide constructive proofs and algorithmic frameworks.
- Round-square tree transforms vertex-biconnectivity into tree path problems.
- F2 linear algebra unifies global structural properties (cuts vs cycles).
- Landau’s theorem enables simple SCC characterization in tournaments without DFS.