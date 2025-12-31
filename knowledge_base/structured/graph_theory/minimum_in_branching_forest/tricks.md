# 最小内向森林问题

**Author:** 张哲宇

## Key Ideas and Observations

### 1. **Problem Modeling via Matroids**
- The problem is modeled as the intersection of two matroids:
  - $ M_1 $: Graphic matroid ensuring no undirected cycles (i.e., forest structure).
  - $ M_2 $: Partition matroid enforcing that each vertex has out-degree at most 1.
- A set of edges forms an in-branching forest if and only if it belongs to $ I_1 \cap I_2 $.

### 2. **Convexity of the Objective Function**
- Let $ \text{MDF}(k) $ be the minimum weight of an in-branching forest with $ k $ edges.
- Using linear programming and matroid intersection theory, it's proven that $ \text{MDF}(k) $ is a convex function in $ k $. This key insight enables the use of dual techniques like convex optimization (also known as *slope trick* or *Lagrange optimization* in competitive programming).

### 3. **Connection to Minimum Arborescence (Edmonds' Algorithm)**
- When $ k = |V| - 1 $, the problem reduces to finding a minimum arborescence (rooted in-tree) over all possible roots.
- Edmonds’ algorithm (Zhu-Liu algorithm) solves this in $ O(E \log E) $ using edge contraction and greedy selection.
- By adding a dummy root node $ t $ connected to all vertices with edge weight $ \alpha $, one can transform the $ k $-edge problem into a minimum arborescence instance whose solution depends on $ \alpha $.

### 4. **Convex Optimization Framework**
- Define $ T(\alpha) = \min_x \left[ \text{MDF}(x) + (|V| - x)\alpha \right] $, which corresponds to solving the arborescence problem with penalty $ \alpha $ for connecting to the dummy root.
- Since $ \text{MDF}(k) $ is convex, binary searching on $ \alpha $ allows recovering individual values of $ \text{MDF}(k) $ via duality.
- However, this approach has complexity $ O(E \log E \log \frac{1}{\varepsilon}) $ due to binary search precision.

### 5. **Priority In-Tree Expansion Algorithm (Main Contribution)**
- Instead of binary searching over $ \alpha $, simulate the process greedily by always expanding the in-tree with the smallest *expansion cost*.
- Each current weakly connected component (in-tree) maintains a *potential value* (called pre-decrement, `dec`) representing how much its outgoing edges have been effectively reduced during processing.
- The expansion cost of an in-tree is equal to the `dec` value of its root when attempting to add an outgoing edge.
- Use a priority queue to always pick the tree with minimal expansion cost.
- Upon selecting a root $ u $, perform standard Edmonds-style steps:
  - Select the cheapest outgoing edge (already adjusted so min edge is zero).
  - If a cycle is formed, contract it (using union-find or linked structure).
  - Maintain global lazy updates on edge weights via heap merging (e.g., using Fibonacci-like heaps or binary heaps with lazy tags).

### 6. **Avoiding Dummy Node and Binary Search**
- Crucially, because the expansion costs are non-decreasing throughout the algorithm (due to monotonicity induced by matroid properties), there's no need for binary search — the natural greedy order recovers $ \text{MDF}(k) $ for all $ k $ simultaneously.
- This eliminates the $ \log \frac{1}{\varepsilon} $ factor and yields a clean $ O(E \log E) $ solution.

### 7. **Correctness via Weighted Matroid Intersection**
- The correctness follows from the fact that the greedy step satisfies the exchange property required by weighted matroid intersection.
- Specifically, given an optimal solution of size $ k-1 $, there exists an extension to size $ k $ by adding one edge corresponding to the minimum expansion cost among valid candidates.

### 8. **Efficient Implementation Techniques**
- Use **mergeable heaps** (e.g., leftist heap or pairing heap) for each node/tree to maintain outgoing edges and support:
  - Global addition on edge weights.
  - Extract-min and merge operations.
- Maintain a global priority queue (heap) of trees keyed by their current expansion cost (i.e., root’s `dec`).
- Lazy propagation ensures efficient adjustment of edge costs across contractions.

### 9. **Applications**
- Applied to problems involving partitioning elements into sequences under dependency constraints (e.g., maximizing accumulated rewards based on relative ordering).
- Transformed into maximizing a reward sum → equivalent to minimizing negative weights in an in-forest with fixed number of components (hence fixed $ k $).