## Key Observations

1. **Matrix Representation**: Every linear map between finite-dimensional spaces can be represented by a matrix once bases are chosen. The matrix acts on coordinate vectors.

2. **Kernel-Image Dimension Theorem**: dim(Ker(T)) + dim(Im(T)) = dim(V). This is fundamental for understanding the structure of linear maps.

3. **Basis Change**: If A is the matrix of T in bases (α_i) and (β_j), and we change bases via transition matrices P (for codomain) and Q (for domain), the new matrix is P⁻¹AQ.

4. **Coordinate Transformation**: When changing basis in V via transition matrix Q, coordinates transform as x' = Q⁻¹x.

## Common Patterns

1. **Composition as Matrix Multiplication**: If S: U→V with matrix A, T: V→W with matrix B, then T∘S has matrix BA (note the order!).

2. **Isomorphism with Matrices**: L(V,W) ≅ M_{m×n}(F) when dim V=n, dim W=m. This allows using matrix techniques.

3. **Rank-Nullity Applications**: 
   - If dim V > dim W, T cannot be injective.
   - If dim V < dim W, T cannot be surjective.
   - For square matrices: T is invertible iff rank = n.

4. **Transition Matrix Trick**: To find the transition matrix from basis B to basis C, express each vector of C as linear combination of B and take coefficients as columns.

## Optimization Notes

1. **Sparse Matrices**: When dealing with high-dimensional but sparse linear maps (e.g., in graph theory), use sparse matrix representations.

2. **Modular Arithmetic**: In competitive programming, linear maps over finite fields (especially F₂) allow bitmask optimizations.

3. **Gaussian Elimination**: For finding kernel basis, image basis, or solving linear systems arising from linear maps.

## Problem Transformation Patterns

1. **Basis Reduction**: Many problems become easier after choosing an appropriate basis (e.g., eigenbasis for diagonalization).

2. **Dual Space Interpretation**: Sometimes it's easier to work with the dual map T*: W*→V*.

3. **Block Matrix Decomposition**: For maps with special structure (e.g., direct sums), use block matrices.

4. **Coordinate-Free Approach**: Some proofs are cleaner without coordinates - use linearity properties directly.

## Common Pitfalls

1. **Basis Dependency**: Remember that matrix representation depends on the chosen basis.

2. **Order of Composition**: Matrix multiplication order is opposite to function composition order.

3. **Field Characteristics**: Properties may differ in characteristic 2 or other finite fields.

4. **Infinite Dimensions**: Many theorems (like rank-nullity) require finite-dimensional spaces.