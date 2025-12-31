# 登顶计划

**Author:** 彭天翼

### Key Observations and Tricks

1. **Visibility Definition**: A point $A$ can see point $B$ if the line segment connecting them does not intersect any other part of the mountain profile below it. This geometric condition can be translated into computational checks.

2. **Left and Right Peak Preprocessing**:
   - For each point $i$, precompute $L[i]$ and $R[i]$, representing the nearest higher peak to the left and right respectively that $i$ can see.
   - This is done in $O(n)$ time per point naively, but optimizations exist.

3. **Path Construction Insight**:
   - When moving from a point $A$ toward the peak, the next significant step is always to jump to a point $B$ such that $T[B] \geq T[A]$, where $T[i]$ represents some measure (like height) at point $i$.
   - The total distance from $A$ to the summit equals the distance from $A$ to $B$ plus the distance from $B$ to the summit.

4. **Graph Transformation**:
   - Construct a directed graph where an edge $A \rightarrow B$ exists if $B$ is the first point to the right (or left) of $A$ such that $T[B] \geq T[A]$.
   - In this transformed graph, every node has out-degree at most 1, forming a forest of trees rooted at local maxima.

5. **Efficient Query Handling**:
   - After building the graph, perform a DFS or use dynamic programming to compute distances from each node to its root (the peak).
   - Answer queries directly via lookup once preprocessing is complete.

6. **Optimization with Data Structures**:
   - To avoid the $O(n^2)$ naive preprocessing, use techniques like stack-based monotonic traversal or binary search with RMQ (Range Maximum Query) to find $L[i]$ and $R[i]$ in $O(n \log n)$ or even $O(n)$ amortized time.
   - The final complexity hinges on how efficiently we can determine the next visible higher point.

7. **Geometric to Algebraic Translation**:
   - The visibility condition between two points $(x_i, y_i)$ and $(x_j, y_j)$ can be checked algebraically by ensuring no intermediate point lies above the line segment joining them.
   - This leads to inequalities involving slopes and coordinates which can be optimized during scanning.

8. **Divide and Conquer Framework**:
   - Split the set of points into halves.
   - Recursively solve within each half.
   - Combine results by handling cross-half interactions, particularly focusing on paths that go through the middle region.
   - Use the fact that only $O(n)$ candidate transitions need consideration due to geometric constraints.