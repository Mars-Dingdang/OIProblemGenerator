# 浅谈线性代数与图论的关系

**Author:** 潘佳奇

### Key Ideas and Tricks

#### **1. Lindström–Gessel–Viennot (LGV) Lemma**
- **Core Idea**: In a DAG, the determinant of matrix $ M_{ij} = \omega(S_i, T_j) $ counts weighted non-intersecting $ n $-paths with sign $ (-1)^{N(\sigma(P))} $. 
- **Sign Cancellation Trick**: Intersecting path tuples are paired via an involution $ f $ that swaps path tails at the first shared vertex. This pairs configurations with opposite signs, canceling their contributions.
- **Application to Grids**: On a grid with monotonic start/end points, only identity permutation yields non-intersecting paths → determinant directly gives count.
- **Maximum Flow via Randomization**:
  - Convert node-disjoint path problem into edge-disjoint by splitting nodes.
  - Assign random weights to edges to avoid cancellation due to negative signs.
  - Use Schwartz-Zippel lemma: if there exists a valid path set, the determinant is nonzero with high probability.
  - Maximum number of disjoint paths = rank of the path-count matrix.

#### **2. Cauchy-Binet Formula via LGV**
- Interpret $ |AB| $ as sum over intermediate vertex sets $ S $ of $ |A[:,S]| \cdot |B[S,:]| $.
- Construct bipartite DAG with left, middle, right layers; apply LGV to show determinant equals signed sum over non-intersecting paths through $ S $.

#### **3. Matrix-Tree Theorem (Kirchhoff)**
- **Laplacian Matrix $ L = D - A $**:
  - All cofactors equal; value equals total weight of spanning trees.
- **Proof via Incidence Matrix $ A $**:
  - Let $ A $ be oriented incidence matrix with $ \sqrt{w_e} $ entries.
  - Then $ L = A A^T $.
  - Apply Cauchy-Binet: $ \det(L_{1,1}) = \sum_{S \subseteq E, |S|=n-1} \det(A_{[2..n],S})^2 $.
  - Nonzero terms correspond to acyclic subgraphs where each node (except root) has one outgoing edge → rooted in-forest.
  - Only when no cycles and connected → spanning tree.
  - Cycle flipping argument cancels cyclic configurations.

#### **4. Generalized Matrix Tree Applications**
- **Directed Trees (In/Out-arborescences)**:
  - Use two different matrices $ A $ and $ B $: $ A $ ensures no cycles (like undirected), $ B $ enforces directionality.
  - $ M = A B^T $, compute cofactor $ C_{r,r} $ → counts in-trees rooted at $ r $.
  - BEST theorem: Eulerian circuits = $ T(r) \prod (\deg(v)-1)! $, where $ T(r) $ is number of out-trees.

- **Matroid Intersection (Linear Matroids)**:
  - Represent each matroid by a matrix (e.g., incidence-like).
  - Assign random weights to elements.
  - Build matrices $ A, B $ for two matroids.
  - Rank of $ AB^T $ gives size of largest common independent set.

- **Max Non-bipartite Subgraph**:
  - Modify incidence matrix: use $ +\alpha_e $ for both endpoints (no sign distinction).
  - Odd cycles contribute positively, even cycles cancel out (due to parity flip).
  - Compute $ \text{rank}(A A^T) $ → maximum number of edges in a subgraph with only odd-cycle components.

#### **5. Graph Products and Spectral Methods**
- **Tensor Product $ G_1 \times G_2 $**:
  - Adjacency matrix: $ A = A_1 \otimes A_2 $.
  - Eigenvalues: $ \lambda_i \mu_j $.
- **Cartesian Product $ G_1 \square G_2 $**:
  - Adjacency matrix: $ A = A_1 \otimes I + I \otimes A_2 $ (Kronecker sum).
  - Eigenvalues: $ \lambda_i + \mu_j $.
  - Laplacian follows same rule.
- **Applications**:
  - Number of closed walks of length $ L $: $ \mathrm{Tr}(A^L) = \sum (\lambda_i \mu_j)^L = (\sum \lambda_i^L)(\sum \mu_j^L) $.
  - Use generating functions and linear recurrence (via characteristic polynomial) to compute power sums efficiently.
  - Spanning tree count in $ G_1 \square G_2 $: $ \frac{1}{nm} \prod_{i,j} (\lambda_i + \mu_j) $ excluding zero eigenvalue term.
  - Use resultant of polynomials to compute product over roots without explicit factorization.