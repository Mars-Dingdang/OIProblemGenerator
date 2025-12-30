## Key Observations & Optimizations

### 1. **Path Compression**
- During `find(x)`, directly link all visited nodes to the root.
- Reduces tree height dramatically.
- Amortized complexity becomes nearly constant.

### 2. **Union by Size/Rank**
- Always attach the smaller tree under the larger tree's root.
- Prevents degenerate trees (chains).
- Can maintain either:
  - **Size**: Number of nodes in subtree.
  - **Rank**: Upper bound of tree height.

### 3. **Combined Optimization**
- Using both path compression and union by size gives **O(α(n))** per operation.
- α(n) is inverse Ackermann function (extremely slow growing).

## Common Problem Transformations

### 4. **Virtual Nodes for Deletion/Movement**
- Create a virtual parent for each real node.
- Only virtual nodes have children.
- Enables:
  - **Deletion**: Detach real node without affecting others.
  - **Movement**: Move single element between sets.
- Used in UVa11987 and SPOJ JMFILTER.

### 5. **Weighted DSU (带权并查集)**
- Store additional information on edges.
- Maintain relation between node and its parent.
- During path compression, accumulate weights.
- Applications:
  - Modular arithmetic (e.g., food chain problem).
  - Distance/offset maintenance.
  - Potential differences.

### 6. **Types/Extended Domain DSU (种类并查集)**
- Split each element into multiple states.
- Example: For 3 types (A,B,C), create 3 nodes per element.
- Union operations connect corresponding states.
- Alternative to weighted DSU for small moduli.

## Implementation Notes
- **Initialization**: Each node is its own parent.
- **Find with path compression**: One-line recursive/iterative.
- **Union**: Always find roots first, check if already connected.
- **Size tracking**: Update only when merging different components.

## When to Use Which Variant
- **Standard DSU**: General connectivity, Kruskal's MST.
- **Weighted DSU**: Relations with mod arithmetic, offsets.
- **Virtual node DSU**: Need to delete/move individual elements.
- **Persistent DSU**: Time travel queries, undo operations.

## Common Pitfalls
- Forgetting to initialize parent array.
- Not using both optimizations for best performance.
- Incorrect weight updates during path compression.
- Assuming DSU can efficiently split sets (it cannot).