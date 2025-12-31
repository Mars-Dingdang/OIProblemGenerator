# 浅谈静态Top Tree 在树和广义串并联图上的应用

**Author:** 程思元

### Key Ideas and Observations

- **Cluster Definition**: A cluster is a triple (V, E, B), where B ⊆ V are boundary points (|B| ≤ 2). Clusters abstract subgraphs as edges between boundary points, enabling modular composition.

- **Operations**:
  - **Compress**: Merges two clusters sharing one boundary point into a new cluster with the other two endpoints as boundaries. Models edge merging in a path.
  - **Rake**: Attaches a cluster as a side branch (leaf-like) onto another; preserves the base cluster’s boundary. Used for combining subtrees under a common parent.
  - **Twist**: Combines two clusters with identical boundaries (parallel edges), essential for handling cycles in generalized series-parallel graphs.

- **Top Tree Construction**:
  - Built as an expression tree over cluster operations.
  - For trees, using heavy-path decomposition yields O(log² n) depth; using global-balanced binary trees (weighted by subtree size) reduces depth to Θ(log n).
  - Global balancing ensures that splits during compress/rake tree construction respect subtree sizes, leading to logarithmic depth.

- **Applications on Trees**:
  - **Pushup Information Maintenance**: Maintain DP states (e.g., f[0/1][0/1]) at each cluster representing costs based on boundary node states. Enables dynamic tree problems like weighted independent set with O(log n) update time.
  - **Top Tree Point Divide**: Perform divide-and-conquer on the Top Tree itself. Choose split edges to balance component sizes. Total edge occurrences across all recursive levels is O(n log n), suitable for path counting.
  - **Tree Blocking**: Select clusters in Top Tree whose size ≤ √n but parent > √n. Yields Θ(√n) blocks, each of size Θ(√n), useful for localized processing.

- **Generalization to Generalized Series-Parallel Graphs (GSP)**:
  - GSP graphs are those without K₄-minor or K₄-homoeomorph subgraphs.
  - Standard Top Tree construction may have linear depth O(n), making direct pushup inefficient.
  - **Double Top Tree (Top Tree of Top Tree)**: Build a Top Tree on the original Top Tree. Transforms O(n)-depth updates into O(log n) via hierarchical aggregation. Each node stores k⁴ states if original has k per-node states.
  - **Modified Point Divide**: During recursion, external parts outside current subtree can be contracted into equivalent clusters (preserving shortest paths), allowing correct contribution calculation.
  - **GSP Graph Blocking**: Apply tree blocking on the Top Tree of a GSP graph. Each block corresponds to a contracted region with up to four interface points (two outer, two inner). Blocks have O(√n) size and number.

- **Efficient Query Handling**:
  - Use precomputed distances from boundary points.
  - Reduce multi-block shortest path queries to low-dimensional geometric problems (e.g., 4D dominance counting via offline processing and data structures like bitset or high-dimensional divide).

- **Handling Modifications**:
  - Only affected blocks need recomputation.
  - Auxiliary graphs (e.g., boundary-only graphs with inter-block shortest paths) are updated locally when edge weights change.

- **Design Insight**: By treating structural hierarchies as first-class objects (via Top Trees), complex dynamic graph problems reduce to simpler operations on bounded-size components or balanced trees.