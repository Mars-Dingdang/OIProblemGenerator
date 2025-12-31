# 浅谈一类图上邻域相关问题

**Author:** 焦思源

### Key Ideas and Observations

- **Rooted on Graph Density**: The core insight is that for a graph with maximum subgraph density $ \rho_{\text{max}}(G) $, there always exists a vertex of degree at most $ 2\rho_{\text{max}}(G) $ in any non-empty subgraph. This allows iterative removal of low-degree vertices.

- **Vertex Deletion Order & Edge Orientation**: By repeatedly removing vertices with degree ≤ $ d_{\text{min}}(G) $ (which is bounded by $ 2\rho_{\text{max}}(G) $), we obtain a deletion order. Direct each undirected edge from the earlier-removed endpoint to the later one. Then, every vertex has out-degree ≤ $ d_{\text{min}}(G) \leq 2\rho_{\text{max}}(G) $.

- **Efficient Maintenance Using In-Degree Sum**: For each vertex $ x $, maintain $ s_x = \sum_{y \to x} a_y $, i.e., the sum of weights from all in-neighbors. 
  - On updating $ a_x $, propagate the change to $ s_y $ for all out-neighbors $ y $ of $ x $. Since out-degree is small ($ \leq 2\rho_{\text{max}} $), this takes $ O(\rho_{\text{max}}) $ per update.
  - On querying neighbor sum of $ x $, return $ s_x + \sum_{x \to y} a_y $. Again, summing over out-neighbors is cheap.

- **Tight Complexity Bound**: This yields total complexity $ O(n + m + q \cdot \rho_{\text{max}}(G)) $, which is never worse than the classical $ O(q\sqrt{m}) $ method since $ \rho_{\text{max}} \leq \sqrt{2m} $.

- **Offline Optimization via Cost-Aware Edge Direction**: When operations are known offline, assign cost $ c_x $ = total number of operations on node $ x $. Orient each edge from lower $ c $ to higher $ c $. The total work becomes $ \sum_{(x,y)} \min(c_x, c_y) $, maximized when the active set forms a max-density subgraph with uniform $ c $, again leading to $ O(n + m + q\rho_{\text{max}}) $ bound.

- **Extension to Range Queries via Sequence Transformation**: For problems involving range-based neighborhood updates/queries, transform the graph into a *neighborhood sequence* $ \text{seq}(G) $: concatenate $ R(1), R(2), ..., R(n) $. Now, operations become interval operations on this sequence.

- **Block-Based Processing on Neighborhood Sequence**: Divide $ \text{seq}(G) $ into blocks of size $ B = \sqrt{2m} $. Use precomputed 2D arrays:
  - $ f[i][j] $: total contribution to first $ j $ elements if block $ i $ is fully updated.
  - $ g[i][j] $: total contribution to block $ j $ if first $ i $ elements are updated.
  Handle full blocks using tags and prefix differences, scatter parts directly. Achieves $ O((m + q)\sqrt{m}) $.

- **Connection to Matrix Multiplication**: Shows the block method is near-optimal by reducing Boolean matrix multiplication to the extended problem, proving it cannot be significantly improved without breaking matrix multiply barriers.

- **Application to Path Counting with Mo’s Algorithm**: For counting paths of length $ k \in [2,4] $ within intervals:
  - $ k=2 $: reduce to counting edges inside $[l,r]$ — standard 2D point counting.
  - $ k=3 $: use Mo’s algorithm on the neighborhood sequence to avoid high-degree node penalties.
  - $ k=4 $: apply *secondary offline Mo*, decomposing contributions into prefixes; combine with degree thresholding ($ B = m^{1/4} $) to achieve $ O(m^{7/4}) $.

- **Generalization to Directed Graphs**: Treat directed edges as undirected during preprocessing, but filter direction during query/update propagation.