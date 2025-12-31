# 浅谈信息学竞赛中的弦图问题

**Author:** 郭城志

### Key Ideas and Observations

- **Perfect Elimination Ordering (PEO)**: A vertex sequence where each vertex forms a clique with its neighbors that come later in the sequence. Every chordal graph has at least one PEO.

- **Maximum Cardinality Search (MCS)**: An algorithm to compute a PEO. It assigns labels to vertices (initially 0), then repeatedly selects the unvisited vertex with the highest label, adds it to the front of the sequence, and increments the labels of its unvisited neighbors. Runs in O(n + m).

- **Chordal Graph Recognition**: After running MCS, verify the result is a valid PEO by checking for each vertex `v`, whether its neighbor set in the future (C(v)) forms a clique. This can be optimized to O(n + m) by only checking if the first neighbor in C(v) connects to all others.

- **Simplicial Vertex**: A vertex whose neighborhood is a clique. Chordal graphs always have at least one simplicial vertex; non-complete chordal graphs have two non-adjacent ones.

- **Minimal Vertex Separator**: In chordal graphs, any minimal separator between two non-adjacent vertices is a clique.

- **Coloring and Clique Number**: Using PEO from back to front and greedy coloring gives optimal coloring. The chromatic number χ(G) equals the clique number ω(G).

- **Maximum Independent Set and Minimum Clique Cover**: Greedily select vertices in PEO order if not adjacent to any already selected. The size α(G) equals κ(G), and the sets C(v) for selected v form a minimum clique cover.

- **Clique Tree**: A tree whose nodes are maximal cliques of G, such that for each vertex v, the set of cliques containing v forms a connected subtree. Every chordal graph has a clique tree, constructible incrementally in O(n + m).

- **Subtree Representation**: Chordal graphs are exactly the intersection graphs of subtrees in a tree — this provides a powerful structural characterization.

- **Equivalence Theorem**: For a graph G, the following are equivalent:
  1. G is a chordal graph.
  2. G is a subtree graph (intersection graph of subtrees on a tree).
  3. G has a clique tree.

- **Applications**:
  - Counting valid colorings under equality/inequality constraints derived from KMP-like structures reduces to chordal graph coloring.
  - Game theory problems reduce to tree traversal via clique tree transformation.
  - Feedback vertex set on chordal graphs reduces to limiting clique sizes to ≤2, solvable via tree DP on clique tree.

- **Structural Insight**: The clique tree transforms hard graph problems into easier tree problems, leveraging subtree intersection properties.