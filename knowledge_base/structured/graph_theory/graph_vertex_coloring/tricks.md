# 浅谈图的点着色问题

**Author:** 高嘉煊

### Key Ideas and Tricks

#### 1. **Chromatic Number Bounds**
- $\chi(G) \geq \omega(G)$: The chromatic number is at least the size of the maximum clique.
- $\chi(G)(\chi(G)-1) \leq 2m$: Derived from the fact that in an optimal coloring, every pair of color classes must have at least one edge between them.
- **Brooks’ Theorem**: For any connected graph $G$ that is not a complete graph or an odd cycle, $\chi(G) \leq \Delta(G)$.

#### 2. **Greedy Coloring & Vertex Ordering**
- Greedily assign the smallest available color based on a vertex ordering.
- Using a reverse perfect elimination order on chordal graphs yields $\chi(G) = \omega(G)$.
- On planar graphs, iteratively removing degree-$\leq5$ vertices ensures a 6-coloring.

#### 3. **Set Power Series for k-Colorability**
- Define a set power series $f_S = [S \text{ is an independent set}]$.
- Compute its Möbius transform $\hat{f}_S = \sum_{T \subseteq S} f_T$.
- Then $\hat{g}_S = (\hat{f}_S)^k$, and after inverse Möbius transform, $g_V > 0$ iff $G$ is $k$-colorable.
- Time: $O(2^n n)$ per $k$, useful for small $n$.

#### 4. **Chromatic Polynomial via Deletion-Contraction**
- Fundamental recurrence: $P(G, x) = P(G - uv, x) - P(G / uv, x)$.
- Naive recursion leads to $O(1.62^{n+m})$ complexity due to Fibonacci-like branching.

#### 5. **Optimizations for Sparse Graphs**
- **Biconnected Component Decomposition**: If $G$ has $k$ biconnected components across $s$ connected components:
  $$
P(G, x) = \frac{1}{x^{k-s}} \prod_{i=1}^k P(C_i, x)
  $$
- **Degree-0/1 Nodes**:
  - Isolated node: $P(G, x) = x \cdot P(G-u, x)$
  - Leaf node: $P(G, x) = (x-1) \cdot P(G-u, x)$
- **Two-degree Paths (Key Optimization)**:
  - A path where internal nodes have degree 2.
  - Let $P = (p_1, ..., p_{k+1})$ be such a path of length $k$.
  - Let $G_1 = G$ with internal nodes removed, $G_2 = G$ with all edges of $P$ contracted.
  - Then:
    $$
    P(G, x) = \frac{(x-1)^k - (-1)^k}{x} \cdot P(G_1, x) + (-1)^k \cdot P(G_2, x)
    $$
  - This generalizes the base deletion-contraction when $k=1$.

#### 6. **Optimizations for Dense Graphs**
- Work on the complement graph.
- Use recurrence for independence partition polynomial $H(G,x)$:
  $$
  H(G, x) = H(G + uv, x) + H(G \setminus uv, x)
  $$
- Exploit cutpoints in the complement graph to decompose $H(G,x)$.
- Handle long paths in the complement (i.e., highly connected structures in original).
- For a chain $L_r$ in the complement (i.e., co-chain), its independence partition polynomial is:
  $$
  H(L_r, x) = \sum_{i=\lceil r/2 \rceil}^r \binom{i}{r-i} x^i
  $$

#### 7. **From Independence Partition to Chromatic Polynomial**
- Relationship:
  $$
  P(G, x) = \sum_{i} h_i \cdot x^{\underline{i}}, \quad \text{where } x^{\underline{i}} = x(x-1)\cdots(x-i+1)
  $$
- So once $h_i$ (number of $i$-independent set partitions) are known, convert via falling factorials.

#### 8. **Efficient Computation via Interpolation**
- Use set power series to compute $w(k) = P(G,k)$ for $k=1..n$.
- Since $P(G,x)$ is degree $n$, interpolate using Lagrange interpolation on points $(0,0),(1,w(1)),...,(n,w(n))$.

#### 9. **Practical Heuristics**
- Detect graph isomorphism during recursion to avoid recomputing same subgraphs.
- Precompute known forms: trees ($x(x-1)^{n-1}$), cycles ($(x-1)^n + (-1)^n(x-1)$), cliques ($x^{\underline{n}}$), chordal graphs via perfect elimination orders.

These tricks allow significant pruning and speedup over naive implementations, especially on structured inputs.