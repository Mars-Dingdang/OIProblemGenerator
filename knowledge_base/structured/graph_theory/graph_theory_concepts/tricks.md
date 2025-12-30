## Key Observations

1. **Graph Representation**:
   - **Adjacency List**: O(V+E) space, efficient for sparse graphs.
   - **Adjacency Matrix**: O(V²) space, fast edge queries, good for dense graphs.
   - **Edge List**: Simple storage, useful for Kruskal's algorithm.

2. **Degree Properties**:
   - **Handshaking Lemma**: Σ deg(v) = 2|E| for undirected graphs.
   - **Directed Graphs**: Σ in-degree = Σ out-degree = |E|.
   - **Odd Degree Vertices**: Always appear in even numbers.

3. **Connectivity**:
   - **Undirected**: Use DFS/BFS to find connected components.
   - **Directed**: Strongly Connected Components (SCC) via Kosaraju/Tarjan.
   - **Weak Connectivity**: Replace directed edges with undirected edges.

4. **Special Graphs**:
   - **Tree**: Connected acyclic graph with |E| = |V| - 1.
   - **Bipartite Graph**: No odd cycles, check via BFS coloring.
   - **Complete Graph Kₙ**: n(n-1)/2 edges, clique problems.
   - **Planar Graph**: |E| ≤ 3|V| - 6 for |V| ≥ 3.

5. **Path vs Cycle**:
   - **Simple Path**: No repeated vertices.
   - **Simple Cycle**: Start/end same vertex, no other repeats.
   - **Eulerian Path**: Visits every edge exactly once.
   - **Hamiltonian Path**: Visits every vertex exactly once (NP-hard).

6. **Graph Operations**:
   - **Complement Graph**: Edge (u,v) exists iff not in original.
   - **Transpose Graph**: Reverse all directed edges.
   - **Subgraphs**: Induced subgraphs preserve all edges between selected vertices.

7. **Cut Properties**:
   - **Vertex Cut**: Minimum vertices whose removal disconnects graph.
   - **Edge Cut**: Minimum edges whose removal disconnects graph.
   - **Menger's Theorem**: Relates cuts to disjoint paths.

8. **Matching & Covering**:
   - **König's Theorem**: In bipartite graphs, size of max matching = min vertex cover.
   - **Hall's Marriage Theorem**: Condition for perfect matching in bipartite graphs.
   - **Tutte's Theorem**: Condition for perfect matching in general graphs.

9. **Algorithm Selection**:
   - **Sparse Graphs**: Prefer adjacency list, O(E) algorithms.
   - **Dense Graphs**: Adjacency matrix may be better, O(V²) algorithms.
   - **Weighted Edges**: Store pairs (neighbor, weight) in adjacency list.

10. **Common Pitfalls**:
    - Self-loops and parallel edges may need special handling.
    - Directed vs undirected edges in algorithms.
    - Zero-based vs one-based indexing.
    - Graph may be disconnected; need to check all components.