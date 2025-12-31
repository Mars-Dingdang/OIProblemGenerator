# 信息学竞赛中构造题的常用解题方法

**Author:** 蒋凌宇

## Key Ideas and Tricks

### Pigeonhole Principle (抽屉原理)
- When multiple feasible solutions exist with a fixed total cost, the pigeonhole principle guarantees that at least one solution has cost ≤ ⌊total/k⌋ and one with cost ≥ ⌈total/k⌉.
- **Application in Errich-Tac-Toe**: Divide the grid into 3 classes based on (r + c) mod 3. Each consecutive triple in a row/column contains one cell from each class. Three different flipping strategies are considered, each eliminating monochromatic triples. The sum of operations across all three is exactly k (number of non-empty cells), so the best uses ≤ ⌊k/3⌋ operations.
- **Application in Mine Sweeper II**: Flipping all cells (mine ↔ empty) preserves the sum of numbers on empty cells because it preserves the number of adjacent (mine, non-mine) pairs. Thus, either transform A → B or A → complement(B); one requires ≤ ⌊nm/2⌋ changes since their total is nm.

### DFS Tree Techniques
- In an undirected graph, a DFS tree ensures all non-tree edges are back edges (from a node to its ancestor).
- **Ehab’s Last Corollary**: Build DFS tree. For any back edge (u, v), if |dep[u] - dep[v]| < k, then the cycle formed by the back edge and tree path has length ≤ k. Otherwise, if depth ≥ k, pick every other ancestor up to ⌈k/2⌉ nodes to form an independent set. If no such long path exists (i.e., tree), partition by parity of depth — one side has size ≥ ⌈n/2⌉ ≥ ⌈k/2⌉.
- **Scenic Walkway Partition (景点划分)**: Use DFS tree and focus on the centroid. If some subtree (including upward part T) has size ≥ a, use it to build connected component A; else greedily merge subtrees connected to T until reaching size ≥ a. Remaining nodes suffice for B due to bounds (a ≤ b ≤ c, a + b + c = n).

### Recursion and Structural Induction
- Exploit self-similar structure across input sizes.
- **Baggage**: Prove minimum n moves via counting adjacent same-type pairs (initially 0, finally 2n−2; each move increases count by at most 2). Construct recursively: for n ≥ 8, perform 4 moves to create a subproblem of size n−4 in shifted positions, then call `solve(n−4, x+4)`.
- **Strange Housing**: Prove existence iff graph is connected using induction. Remove a non-articulation point, solve recursively, then decide whether to include it based on neighbors in partial solution. Efficiently simulate via DFS order inclusion: add nodes in DFS preorder, maintaining connectivity and independence (no two selected neighbors). This avoids explicit articulation point detection while ensuring correctness.