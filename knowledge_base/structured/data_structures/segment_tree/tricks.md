# Segment Tree Tricks & Observations

1.  **Segment Tree Optimized Graph Construction**:
    *   **Observation**: When adding edges from a node $u$ to a range $[L, R]$, or from a range $[L, R]$ to a node $u$, we can use the segment tree structure to reduce the number of edges from $O(N)$ to $O(\log N)$.
    *   **Construction**: Build a segment tree where leaf nodes represent the actual vertices.
        *   For "Node to Range": Create a virtual "Out-Tree". Edges go from parent to children (0 weight). Link $u$ to the $O(\log N)$ nodes covering $[L, R]$.
        *   For "Range to Node": Create a virtual "In-Tree". Edges go from children to parent (0 weight). Link the $O(\log N)$ nodes covering $[L, R]$ to $u$.
    *   **Application**: Shortest path problems involving range constraints, 2-SAT with range implications.

2.  **Segment Tree Beats (Jiyang Li)**:
    *   **Observation**: For operations like $A_i = \min(A_i, x)$, we can maintain the maximum and strictly second maximum value in each node.
    *   **Complexity**: Amortized $O(N \log N)$ or $O(N \log^2 N)$ depending on the variant.

3.  **Scanning Line + Segment Tree**:
    *   **Pattern**: Convert 2D geometric problems or range problems into a 1D problem by sorting queries/objects by one coordinate and maintaining the other dimension in a segment tree.
