# 动态传递闭包问题的探究

**Author:** 孙耀峰

### Key Ideas and Observations

#### Static Case
- **Floyd-Warshall with bitset optimization**: Use bitwise OR and AND to simulate logical operations over paths, reducing time from $O(n^3)$ to $O(n^3 / w)$ via word-level parallelism.
- **Topological sorting on DAGs**: Process nodes in reverse topological order and propagate descendant sets using union operations.
- **Strongly Connected Components (SCC)**: Compress each SCC into a single node to form a DAG, then apply topological methods. This reduces complexity to $O(nm / w)$.

#### Partially Dynamic (Only Insertions)
- **Incremental propagation via 'mid-edge' updates**: When adding edge $(u, v)$, if $v \notin \text{desc}(u)$, update all ancestors of $u$ that are not already ancestors of $v$. Specifically, for every $x \in (\text{anc}(u) \setminus \text{anc}(v))$, set $\text{desc}(x) = \text{desc}(x) \cup \text{desc}(v)$.
- **Maintain reverse graph** to efficiently compute ancestor sets by symmetry.
- **Tree-merging algorithm**: For each node $x$, maintain a tree-like structure $T_x$ representing its reachable descendants. On inserting $(u, v)$, merge subtree $T_v$ into $T_u$ recursively while avoiding cycles. Each node is inserted at most once per tree, leading to amortized $O(n)$ per operation.

#### Fully Dynamic
- **Offline Time Segment Tree (TimeLine SegTree)**:
  - Assign each edge an existence interval across operations.
  - Build a segment tree over time (operation indices), storing edges active during intervals.
  - Traverse the tree DFS-style, applying local updates and rolling back state after recursion. Uses incremental algorithms within segments.
  - Complexity: $O((m + q) \log q \cdot n^2 / w)$.

- **Randomized Linear Algebra Approach**:
  - Represent graph as symbolic adjacency matrix $A$, where entries are random values.
  - Reachability from $i$ to $j$ is equivalent to non-zero determinant of modified matrix $A_E(j,i)$ (after connecting $j \to i$, removing self-loops at $i,j$).
  - By Schur complement and matrix identities: $\det(A_E(j,i)) = (\text{adj}~A)_{ij}$, and $\text{adj}~A = \det(A) \cdot A^{-1}$.
  - Maintain $\det(A)$ and $A^{-1}$ dynamically using rank-1 update formulas:
    - After column change $\delta$, express $A' = A + \delta e_i^T$.
    - Then $A'^{-1} = (I + b e_i^T)^{-1} A^{-1}$, computable in $O(n^2)$ due to sparsity.
    - Determinant updated as $\det(A') = \det(A) \cdot (1 + b_i)$.
  - Query $i \to j$ by checking whether $(A^{-1})_{ji} \neq 0$ (scaled by determinant).
  - Error probability bounded by Schwartz-Zippel lemma when using large finite field (e.g., $10^9+7$).
  - Achieves $O(n^2)$ worst-case time per update.

#### Optimization Techniques
- **Bitset packing**: Represent sets like $\text{desc}(u)$ as bitmasks, enabling $O(n/w)$ set unions and membership checks.
- **Amortization argument**: In insertion-only case, total number of distinct reachability relations is bounded by $n^2$, so expensive updates happen at most $n^2$ times.
- **Symmetry between desc and anc**: Maintain both forward and backward graphs to allow efficient ancestor queries.