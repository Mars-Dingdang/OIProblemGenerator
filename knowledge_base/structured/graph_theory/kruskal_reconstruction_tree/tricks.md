# Kruskal Reconstruction Tree Tricks

1.  **Core Property**:
    *   The Kruskal Reconstruction Tree is a binary tree with $2N-1$ nodes.
    *   Leaves are original nodes. Internal nodes represent edges.
    *   The value of an internal node is the weight of the edge it represents.
    *   **Key Property**: The LCA of $u$ and $v$ in the reconstruction tree represents the "bottleneck" (maximum weight edge) on the MST path between $u$ and $v$.
    *   Actually, it represents the bottleneck on *any* path between $u$ and $v$ that minimizes the maximum edge weight (minimax path).

2.  **Subtree Property**:
    *   For a fixed node $u$ and a weight limit $W$, the set of nodes reachable from $u$ using only edges with weight $\le W$ corresponds to the subtree of the highest ancestor of $u$ whose value is $\le W$.
    *   This transforms a "reachability on graph" problem into a "subtree query" problem.

3.  **Combination with Data Structures**:
    *   Since it becomes a subtree problem, we can use **DFS Order (DFS Sequence)** to map the subtree to a continuous range.
    *   Then use **Segment Tree** or **Persistent Segment Tree** to query information about the nodes in that range.
    *   *Example*: "Find the $k$-th smallest node value reachable from $u$ using edges $\le W$." -> Find ancestor, get range, query Persistent Segment Tree on that range.
