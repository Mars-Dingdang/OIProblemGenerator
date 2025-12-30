## Key Observations
- **Diagonalization Condition**: A matrix is diagonalizable iff it has n linearly independent eigenvectors (over the field), equivalently each eigenvalue's geometric multiplicity equals its algebraic multiplicity.
- **Minimal Polynomial**: A is diagonalizable iff its minimal polynomial has no repeated roots.
- **Symmetric/Hermitian Matrices**: Real symmetric/complex Hermitian matrices are always orthogonally/unitarily diagonalizable (Spectral Theorem).
- **Power Computation**: If A = PDP⁻¹, then Aᵏ = PDᵏP⁻¹, enabling fast matrix exponentiation.
- **Cayley–Hamilton**: p(A)=0 allows reducing high powers of A modulo the characteristic polynomial.

## Optimizations
- **Eigenvalue Algorithms**: Use QR algorithm for general matrices, Jacobi for symmetric, power iteration for dominant eigenvalue.
- **Avoid Numerical Instability**: Hessenberg reduction before eigenvalue computation; prefer stable libraries (LAPACK).
- **Block Diagonalization**: For structured matrices (e.g., block circulant), exploit symmetry to reduce dimension.
- **Krylov Subspace Methods**: For large sparse matrices, use Arnoldi/Lanczos to approximate extremal eigenvalues.

## Problem Transformations
- **Linear Recurrences**: Convert to matrix form (companion matrix) and diagonalize for closed-form solution.
- **Markov Chains**: Stationary distribution is eigenvector for eigenvalue 1.
- **Principal Component Analysis (PCA)**: Diagonalize covariance matrix to find principal axes.
- **Quantum Mechanics**: Hamiltonian diagonalization yields energy eigenvalues and states.
- **Graph Spectra**: Adjacency/Laplacian matrix eigenvalues reveal connectivity properties.

## Caveats
- Non-diagonalizable matrices require Jordan form.
- Complex eigenvalues appear in real matrices; use real Schur form.
- Ill-conditioned matrices cause numerical errors; use robust decompositions (SVD).