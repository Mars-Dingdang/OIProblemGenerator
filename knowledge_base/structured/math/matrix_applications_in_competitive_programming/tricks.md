# 浅谈矩阵在信息学竞赛中的应用

**Author:** 杨宁远

### Key Ideas and Tricks

- **LGV Lemma (Lindström–Gessel–Viennot)**:
  - Used to count tuples of non-intersecting paths in DAGs.
  - Construct a matrix $ M $ where $ M_{i,j} = e(a_i, b_j) $, the sum of weights over all paths from $ a_i $ to $ b_j $.
  - The determinant $ |M| $ gives the signed sum over all vertex-disjoint path systems, with intersecting paths canceling out due to sign reversal upon swapping at first intersection.
  - Applied in problems involving constrained grid walks or layered structures.

- **Cofactor and Matrix-Tree Theorem**:
  - The number of spanning trees in an undirected graph is the determinant of any cofactor of the Laplacian matrix (degree minus adjacency).
  - For directed graphs, use in-degree or out-degree matrices accordingly for arborescences.
  - The adjugate matrix $ A^* $ satisfies $ AA^* = |A|I $. When $ \text{rank}(A) = n-1 $, there's a rank-one structure in the adjugate: $ A_{i,j} \propto q_i p_j $, derived from left/right null vectors.

- **Efficient Matrix Power via Cayley-Hamilton**:
  - Use $ A^k \mod p_A(x) $, where $ p_A(x) $ is the characteristic polynomial.
  - Compute $ x^k \mod p_A(x) $ using polynomial exponentiation in $ O(n^2 \log k) $.
  - Then express $ A^k $ as linear combination of $ I, A, ..., A^{n-1} $.

- **Fast Characteristic Polynomial Computation**:
  - **Hessenberg Reduction**: Transform matrix into upper Hessenberg form via similarity transformations preserving eigenvalues; allows $ O(n^2) $ determinant evaluation per point.
  - Combine with interpolation at $ \lambda = 0,1,...,n $ to recover coefficients in $ O(n^3) $.
  - **Berlekamp–Massey Optimization**: Instead of full matrix recurrence, pick random vectors $ \vec{a}, \vec{b} $, compute sequence $ s_k = \vec{a} A^k \vec{b} $, then apply BM to find recurrence. Recovers minimal annihilating polynomial with high probability via Schwartz-Zippel.

- **Diagonalization for Fast Exponentiation**:
  - If $ A = PDP^{-1} $, then $ A^k = PD^kP^{-1} $, reducing matrix power to scalar exponentiation on diagonal.
  - Useful when eigenvalues/vectors can be found analytically (e.g., structured transition matrices).

- **Numerical Eigenvalue Algorithms**:
  - **Power Iteration**: Finds dominant eigenvalue/vector by repeatedly applying $ A $ and normalizing.
  - **Inverse Iteration**: Applies $ (A - \sigma I)^{-1} $ to find eigenvalues near $ \sigma $.
  - **Jacobi Method**: For symmetric matrices, iteratively zero off-diagonal elements using Givens rotations. Converges quadratically.
  - **QR Iteration**: Repeatedly factor $ A_k = Q_kR_k $, set $ A_{k+1} = R_kQ_k $. Converges to Schur form (upper triangular), whose diagonal contains eigenvalues.

- **Modular Root Finding for Eigenvalues**:
  - In finite fields, compute characteristic polynomial, then use randomized splitting via $ \gcd(f(x+d), x^{(p-1)/2} - 1) $ to extract roots efficiently.

- **Generating Function Insights**:
  - Some matrix transitions correspond to generating functions (e.g., $ (1+x)^i(1-x)^{n-i} $); NTT-based convolution enables $ O(n \log n) $ transforms.

- **Practical Tips**:
  - When stuck on DP optimization, try writing the transition matrix and computing small cases to observe patterns in eigenvalues.
  - Randomized algorithms (like BM with vector probing) offer practical speedups with controllable error probabilities.