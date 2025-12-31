# 浅谈一类有界树宽问题

**Author:** 吴畅

## Key Ideas and Observations

### Tree Decomposition Basics
- A **tree decomposition** of a graph $ G = (V, E) $ is a tree $ T $ where each node represents a subset of vertices $ X_i \subseteq V $, satisfying:
  1. The union of all $ X_i $ covers $ V $.
  2. Every edge $ (u,v) \in E $ is contained in at least one bag $ X_i $.
  3. For any vertex $ v \in V $, the nodes $ \{i \mid v \in X_i\} $ form a connected subtree (the *connectedness condition*).
- The **width** of a decomposition is $ \max |X_i| - 1 $. The **tree width** $ \text{tw}(G) $ is the minimum width over all valid decompositions.

### Equivalence to Partial k-Trees
- A graph has tree width at most $ k $ if and only if it is a **partial k-tree**, i.e., a subgraph of a k-tree.
- This gives structural insight: many real-world graphs (e.g., series-parallel, outerplanar) have small tree width.

### Reduction Techniques for Small Tree Width
- **Reduction rules** (e.g., removing degree-0/1 nodes, contracting degree-2 nodes, merging multi-edges) preserve tree width and allow simplification of graphs like series-parallel graphs (which are exactly connected partial 2-trees).
- These reductions naturally induce a **series-parallel tree**, enabling bottom-up dynamic programming.

### Dynamic Programming on Tree Decompositions
- Many NP-hard problems become tractable via DP on tree decompositions when tree width $ w $ is bounded.
- **Courcelle’s Theorem**: Any graph property expressible in monadic second-order logic can be decided in linear time on graphs of bounded tree width.

### Perfect and Smooth Tree Decompositions
- A **perfect tree decomposition** structures the tree as a rooted binary tree with four types of nodes:
  - **Leaf**: singleton bag.
  - **Introduce node**: adds one vertex.
  - **Forget node**: removes one vertex.
  - **Join node**: merges two identical bags.
- Any tree decomposition of bounded width can be converted into a perfect one in linear time.
- Similarly, a **smooth decomposition** ensures all bags have size $ k+1 $ and adjacent bags differ by one element — useful for uniform processing.

### Efficient Algorithms via Problem Size Reduction
- **Bodlaender’s Algorithm (Key Insight)**:
  - Uses divide-and-conquer based on identifying abundant structures:
    - If there are many **green vertices** (low-degree vertices adjacent to other low-degree ones), find a large matching, contract edges, recurse, then lift the decomposition.
    - Otherwise, many **I-simplex vertices** exist — low-degree non-green vertices whose neighbors form a clique in the *augmented graph* (with edges added between vertices sharing >k common neighbors). Remove them, recurse, and reintroduce.
  - In both cases, the problem size shrinks by a constant factor, leading to overall **linear-time complexity** for fixed $ k $.

### Applications Demonstrated
- **Maximum Independent Set**:
  - On a perfect decomposition, use DP state $ dp[i][S] $: maximum independent set in subtree rooted at $ i $, with selected subset $ S \subseteq X_i $.
  - Transition depends on node type (introduce, forget, join).
  - Complexity: $ O(2^w w^2 n) $, feasible for small $ w $.

- **Shortest Path Queries**:
  - Preprocess distances from every vertex to all ancestors in the decomposition tree.
  - Use LCA in decomposition: $ \text{dist}(s,t) = \min_{v \in X_{\text{lca}(\text{top}_s, \text{top}_t)}} \text{dist}(s,v) + \text{dist}(v,t) $.
  - Query time: $ O(w) $ after $ O(hn) $ BFS preprocessing ($ h $: height of decomposition tree).

### Structural Lemmas
- **Lemma (Connected Neighbors)**: For an edge $ (u,v) $, if $ \text{lev}_u \geq \text{lev}_v $, then $ v \in X_{\text{top}_u} $.
- **Edge Bound**: In a partial k-tree, $ |E| \leq k|V| - \binom{k+1}{2} $.
- **Contraction Preserves Tree Width**: Contracting an edge does not increase tree width.
- **Augmentation Lemma**: Adding an edge $ (u,v) $ doesn’t change tree width bound if $ |N(u) \cap N(v)| > k $.

These tricks enable efficient preprocessing and reduction strategies crucial for handling bounded tree width graphs in practice.