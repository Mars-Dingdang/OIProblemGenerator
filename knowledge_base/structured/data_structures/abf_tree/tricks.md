# 《基础圆方树练习题》命题报告

**Author:** 范致远

### Key Ideas and Observations

- **k-Cactus Structure**: In a k-cactus, any edge lies in at most k simple cycles. This implies that each biconnected component has limited complexity — specifically, there are at most k+1 chains connecting vertices of degree ≥3.

- **Round-Square Tree (Palm Tree)**: The problem reduces to maintaining a round-square tree representation of the k-desert, where biconnected components (cycles or more complex subgraphs) are represented as square nodes, and articulation points as round nodes. This allows decomposition of the graph into a tree-like structure.

- **AAA Tree as Base**: The AAA tree is a variant of Link-Cut Tree (LCT), enhanced with auxiliary trees on each node to manage subtree information and edge children. It supports:
  - `compress` nodes for original vertices,
  - `rake` nodes for directed edges,
  - Extra pointers (`p`, `s`) to track parent and solid child edges.
  - Lazy propagation for path and subtree updates via `tagr` (path tag) and `tagv` (subtree tag).

- **ABF Tree Extension**: The ABF tree extends the AAA tree by introducing a third type of node:
  - `twist` nodes represent biconnected components (square nodes in the round-square tree),
  - Each `twist` node maintains lists `v` (key vertices) and `e` (chains between them),
  - All `twist` nodes remain leaves in the compress tree to preserve complexity.

- **Efficient Splice Operation**: The core operation in expose is `splice`. By analyzing its amortized cost using a logarithmic potential function, the paper shows that each splice costs $ O(\log n + k \log k) $, leading to an overall expose cost of $ O(k \log k \log n) $.

- **Handling Dynamic Changes**:
  - When adding/removing edges within a biconnected component, the affected part is extracted, rebuilt (possibly splitting or merging biconnected components), and reinserted.
  - Tarjan's algorithm is used after deletion to recompute biconnected components.
  - Chains of degree-2 nodes are contracted into single edges during processing.

- **Amortized Analysis Trick**: A refined potential function includes terms not only from subtree sizes but also virtual adjustments when converting nodes to/from key status in twist nodes. This ensures that even structural changes (like promoting a degree-2 node to a key point) have constant amortized overhead.

- **Reverse Handling**: Flip operations affect pointer roles (`p` ↔ `s`), which must be swapped lazily without affecting structural integrity.

- **Edge Information Support**: Since raw AAA trees don't handle edge weights directly, auxiliary nodes are inserted on edges to convert edge data into vertex data.

- **Reduction to Known Problems**: For special cases (e.g., forests, 1-cacti), known solutions like Self-adjusting Top Trees or Dynamic Cactus III/IV apply, providing partial credit paths.

Overall, the ABF tree achieves lower complexity than previous methods for general k-cacti by tightly coupling round-square decomposition with advanced LCT techniques and careful amortization.