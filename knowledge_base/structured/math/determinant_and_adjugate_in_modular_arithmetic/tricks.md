# 信息学竞赛中行列式的相关问题

**Author:** 王展鹏

### Key Ideas and Tricks

- **Problem Transformation via Möbius Inversion**: The original problem involving GCD over spanning trees is transformed using the identity $\gcd(a_1,\dots,a_k) = \sum_{d|\gcd} \phi(d)$, allowing enumeration over divisors and reducing to multiple determinant computations on subgraphs.

- **Adjugate Matrix via Rank Analysis (Mod Prime)**:
  - If $\text{rank}(A) = n$: Use $A^* = \det(A) A^{-1}$, compute via Gaussian elimination.
  - If $\text{rank}(A) \leq n-2$: All cofactors are 0.
  - If $\text{rank}(A) = n-1$: After Gaussian elimination, only one row/column of cofactors needs explicit computation; others are derived via recurrence from $AA^* = \det(A)I$.

- **Hessenberg Matrix Determinant Recurrence**:
  For a Hessenberg matrix (lower triangular with one superdiagonal), the determinant of the bottom-right $i \times i$ submatrix satisfies:
  $$
f_i = a_{i,i} f_{i+1} - a_{i+1,i} a_{i,i+1} f_{i+2} + \cdots
  $$
  This allows efficient DP in $O(n^2)$ per instance.

- **Divide-and-Conquer Elimination for Adjugate (Arbitrary Modulus)**:
  Use recursive elimination with GCD-like row operations (avoiding division) to handle non-invertible elements. Non-invertible pivot columns are moved to the end. Only $s^2$ entries (where $s \leq \log P$) need brute-force cofactor computation due to structural zeros modulo prime powers.

- **Polynomial Matrix Determinant (Linear Entries)**:
  When entries are linear polynomials $a_{ij}x + b_{ij}$, eliminate constant terms to upper-triangular form. The linear term of $\det$ comes from selecting exactly one $x$-term and taking its cofactor — which simplifies due to structure (e.g., product of diagonal constants).

- **Lagrange Interpolation for Polynomial Determinants**:
  Evaluate $\det(A(x))$ at $O(n)$ points, interpolate. Requires handling small moduli via CRT and high-precision arithmetic when necessary.

- **Chinese Remainder Theorem Approach**:
  Compute $\det$ modulo several large primes, reconstruct full integer result. Avoids precision issues but requires many runs.

- **Unified Algorithm over Arbitrary Commutative Rings**:
  Define $B(z) = I + z(A - I)$, so $B(0)=I$, $B(1)=A$. Perform symbolic Gaussian elimination on $B(z)$ as a polynomial matrix. Since diagonal entries have constant term 1, they are always invertible in any ring. Maintain matrices modulo $z^{n+1}$ since degree $\leq n$. Final answer is $\det(B(1))$.

- **Fast Determinant via Block Recursion**:
  Using block matrix identities:
  $$
  \det\begin{bmatrix}A & B \\ C & D\end{bmatrix} = \det(A)\det(D - CA^{-1}B)
  $$
  Combine with fast matrix multiplication ($O(n^\omega)$) and recursive inversion to achieve $O(n^\omega)$ field operations.

- **Optimization Insight**: Exploit symmetry in undirected graphs (e.g., Kirchhoff matrices) to avoid recomputing both rows and columns of adjugate.