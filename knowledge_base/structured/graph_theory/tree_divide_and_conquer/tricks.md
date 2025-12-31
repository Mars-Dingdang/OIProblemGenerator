# 浅谈树上分治算法

**Author:** 张哲宇

### Key Ideas and Observations

- **Edge Divide and Conquer**:
  - Select an edge, process all paths passing through it, then remove the edge and recurse on the two resulting subtrees.
  - To maintain efficiency, ensure maximum degree is bounded by a constant. This can be achieved by introducing auxiliary nodes and edges when a node has high degree (e.g., splitting a star-shaped node into a binary-like structure).
  - After transformation, each recursion reduces problem size significantly, leading to O(n log n) time.
  - Useful for maximizing distances across two trees — after edge division, reduce to dynamic programming on virtual trees.
  - Drawback: introduces extra nodes/edges which may complicate implementation.

- **Point Divide and Conquer (Centroid Decomposition)**:
  - Choose a centroid (a node whose removal leaves no subtree larger than half the original), process all paths going through this node, then delete it and recurse on remaining components.
  - Guarantees depth of recursion is O(log n) since each subtree has size ≤ n/2.
  - Simplifies problems where connectivity must include a root (centroid), turning global queries into local ones.
  - Example application: finding k-th largest connected component via DAG modeling over DFS order (using entry/exit times).
  - When merging results from multiple subtrees, always merge the two smallest sets first — this mimics Huffman coding and ensures each set is merged only O(log n) times, preserving O(n log n) total complexity.
  - Interestingly, this merging strategy mirrors edge divide behavior, showing deep connection between both methods.
  - Can handle polynomial aggregation along paths using divide-and-conquer on centroids, achieving O(n log² n) via convolution of O(log n) segments of decreasing length.

- **Globally Balanced Binary Tree**:
  - A variant of heavy-light decomposition where each heavy chain is represented as a balanced binary tree based on subtree sizes, not just midpoint of the chain.
  - Ensures overall tree depth remains O(log n).
  - Each path in the original tree can be partitioned into O(log n) contiguous 'segments' corresponding to real paths in the decomposition.
  - Virtual children (light subtrees) can also be organized into balanced structures for efficient querying.
  - Enables fast range queries (e.g., maxima under exclusion constraints) by precomputing information in virtual parts.
  - Particularly useful for complex query problems involving forbidden paths or distance-bounded searches.
  - Achieves O((n + q) log n) for certain query types by combining segment lookup and subtree metadata.
  - Offers better integration with chain-based data than standard centroid decomposition, though with higher constant factors.

- **General Insight**:
  - The choice between edge, point, and global balance methods depends on problem constraints: negative weights break simple assumptions, high-degree nodes require restructuring, and query patterns dictate optimal decomposition.
  - Despite theoretical equivalence in complexity, practical performance varies due to constants and cache behavior.
  - Global balance excels in interactive problems where operation count matters more than raw speed.
  - Understanding the duality between different divide strategies helps design hybrid solutions.