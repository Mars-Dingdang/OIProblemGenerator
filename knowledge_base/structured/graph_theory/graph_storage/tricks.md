## Key Observations
- **Direct Edge Storage**:
  - Use when edges need to be sorted (e.g., Kruskal's algorithm).
  - Can rebuild graphs efficiently by storing raw edges.
  - Avoid for traversal-heavy tasks due to O(m) per operation.

- **Adjacency Matrix**:
  - O(1) edge queries are its main advantage.
  - Only feasible for small n (typically n ≤ 1000) due to O(n²) space.
  - Not suitable for graphs with multiple edges between same vertices.

- **Adjacency List**:
  - Most balanced: O(n + m) traversal, O(m) space.
  - Sorting adjacency lists enables binary search for edge existence in O(log d⁺(u)).
  - Easy to modify dynamically (add/remove edges).

- **Linked Forward Star**:
  - Memory-efficient static representation; common in competitive programming.
  - Slightly faster iteration than vector-based adjacency list due to cache locality.
  - Harder to modify after construction; best for pre-built graphs.

## Optimization Patterns
1. **Hybrid Approaches**:
   - Use adjacency list for general traversal, but keep a hash map (or bitset for small n) for O(1) edge queries if needed.
2. **Reverse Graph**:
   - Store both original and reverse adjacency lists for algorithms needing in-edge traversal (e.g., Kosaraju's SCC).
3. **Edge Compression**:
   - For weighted graphs, store `vector<vector<pair<int, int>>>` where pair = (neighbor, weight).
4. **Memory Reduction**:
   - Use `vector<int>` for unweighted graphs; for weighted, store weights in separate array parallel to `to[]` in linked forward star.

## Common Transformations
- **Undirected to Directed**:
  - Store each undirected edge as two directed edges in adjacency list.
- **Dense to Sparse**:
  - If m ≈ n², consider adjacency matrix; otherwise, adjacency list is better.
- **Multiple Graphs**:
  - When building several related graphs (e.g., residual network), store edges once and use different adjacency lists referencing the same edge pool.

## Pitfalls
- **Indexing**: Always decide on 0-based or 1-based indexing and be consistent.
- **Visited Array**: Reset `vis` array between traversals if needed.
- **Parallel Edges**: Adjacency matrix cannot handle them; use adjacency list with counts or multiset if duplicates matter.