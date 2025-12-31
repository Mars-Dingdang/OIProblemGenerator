# 浅谈信息学竞赛中的线图问题

**Author:** 翟锦程

## Key Ideas and Tricks

### Problem Definition
- **Linear Matroid Parity**: Given m pairs of n-dimensional vectors $(a_i, b_i)$, select the maximum number of pairs such that all selected vectors are linearly independent.
- This generalizes many combinatorial problems like maximum matching and network flow.

### Compact vs Sparse Constructions
- **Sparse Construction**: Creates a $2(n+m) \times 2(n+m)$ skew-symmetric matrix:
  $$
  \begin{bmatrix}
  0 & A \\
  -A^T & X
  \end{bmatrix}
  $$
  where $A = (a_1, b_1, \dots, a_m, b_m)$ and $X$ is block diagonal with $\begin{bmatrix}0 & x'_i \\ -x'_i & 0\end{bmatrix}$ blocks. The answer is $v = (\text{rank} - 2m)/2$.
  
- **Compact Construction**: More efficient approach creating an $n \times n$ matrix:
  $$
  M = \sum_{i=1}^m x_i(a_ib_i^T - b_ia_i^T)
  $$
  Then $\text{rank}(M) = 2v$. This reduces matrix size from $O((n+m)^2)$ to $O(n^2)$.

### Randomized Algorithm
- Use Schwartz-Zippel lemma: For non-zero polynomial $f$ of degree $d$, $\Pr[f(\alpha_1,\dots,\alpha_m)=0] \leq d/|S|$ when evaluating over finite field.
- Assign random values from large prime field $\mathbb{F}_p$ to variables $x_i$.
- Compute rank of resulting matrix $M'$ using Gaussian elimination in $O(n^3)$.
- With high probability ($\geq 1-r/p$), $\text{rank}(M') = \text{rank}(M)$.

### Low-Rank Update Optimization
For finding actual solution (not just size):
- Maintain $N = M^{-1}$ after initial $O(n^3)$ inversion
- For each pair $(a_i,b_i)$, check if removing it maintains independence
- Using Sherman-Morrison-Woodbury (SMW) formula:
  $$(M - UV)^{-1} = M^{-1} + M^{-1}U(I - VM^{-1}U)^{-1}VM^{-1}$$
  where $U = (a_i, -b_i)$, $V = (b_i, a_i)^T$
- Check invertibility by computing $I - VM^{-1}U$ (size $2\times2$) in $O(r^2)$
- Update inverse in $O(r^2)$ if kept
- Total complexity: $O(mr^2)$ instead of naive $O(mn^3)$

### Handling Single Vectors
For pairs with only one vector:
- Extend space by adding basis vectors $e_{n+i}$
- But this increases dimension; better to maintain column basis of single vectors, reducing effective dimension to $\min(m_1,n)$

### Weighted Version
- Introduce new variable $z$ where exponent tracks total weight
- Matrix becomes $M = Y + \sum_{i=1}^m x_i(a_ib_i^T - b_ia_i^T)z^{w_i}$
- Answer is $v = \deg_z(\det(M))/2$
- Use interpolation: evaluate determinant at $Vn+1$ points, then Lagrange interpolate
- Complexity dominated by $O(Vn^4)$ for determinant computations

### Applications
#### General Graph Maximum Matching
- For edge $(u,v)$, set $a_i = e_u, b_i = e_v$
- Linear dependence occurs iff vertices shared
- Connection to Tutte matrix: $M_{u,v} = \sum_{(u,v)\in E} x_e$ for $u<v$

#### Maximum mex Spanning Tree
- Find spanning tree maximizing mex of edge weights
- Equivalent to finding largest $k$ such that edges with weights $[0,k)$ form acyclic subgraph with exactly one edge per weight
- Reduce to matroid intersection: graphic matroid (acyclic) and partition matroid (distinct colors)
- Construct $a_i = e_u-e_v, b_i = e_{n+w_i}$
- Rank condition gives solution

#### Colored Spanning Forest
- Each color $i$ gets $\text{lim}_i$ dimensions
- Map edge of color $i$ to Vandermonde vector $(1^j, 2^j, \dots, k^j)$ for $j=1..\text{lim}_i$
- Ensures any $\text{lim}_i$ edges of same color are independent

### Proof Techniques
- **Schwartz-Zippel Lemma**: Proves randomized evaluation works with high probability
- **Sherman-Morrison-Woodbury**: Enables efficient low-rank updates
- **Matroid Intersection Theory**: Shows how LMPP generalizes other problems
- **Algebraic Reductions**: Transform combinatorial constraints into linear algebra conditions