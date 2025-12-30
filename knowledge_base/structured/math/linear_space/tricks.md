## Key Observations
- **Linear independence** is fundamental: vectors are linearly independent iff the only linear combination giving zero is trivial. This is equivalent to the matrix formed by them having full column rank.
- **Span** of a set of vectors is the smallest subspace containing them. The dimension of the span is the rank of the corresponding matrix.
- **Subspace criteria**: A non‑empty subset is a subspace iff closed under addition and scalar multiplication.
- **Direct sum** `V = U ⊕ W` means every vector in V decomposes uniquely as u + w with u∈U, w∈W. Equivalent to V = U + W and U ∩ W = {0}.
- **Rank‑nullity theorem**: For a linear map (matrix) A, dim(domain) = rank(A) + nullity(A). Nullity is dimension of kernel (solution space of Ax = 0).

## Common Problem Transformations
1. **Checking linear independence** → build matrix with vectors as columns (or rows) and compute rank via Gaussian elimination. If rank < number of vectors, they are dependent.
2. **Finding basis of span** → perform Gaussian elimination on the matrix formed by the vectors; the pivot rows/columns give a basis.
3. **Subspace intersection** → solve linear system combining basis vectors of both subspaces; the solution space gives intersection.
4. **Sum of subspaces** → take union of basis vectors and remove dependent ones (again via Gaussian elimination).
5. **Testing vector in span** → solve linear system Ax = b; if solution exists, b is in the span.

## Optimizations
- Use **double** with tolerance (e.g., 1e‑9) for floating‑point linear algebra.
- For integer/modular arithmetic, use Gaussian elimination with modular inverses (mod prime).
- **Basis maintenance** (linear basis) for XOR spaces or vector spaces over GF(2) can be done in O(n²) or O(n log MAX) with bit tricks.
- When only rank is needed, **Gaussian elimination** is O(n³) but can be optimized with bitsets for 0/1 matrices.

## Applications in Competitive Programming
- **Linear basis** for maximal XOR subset (see `linear_basis`).
- **Matrix rank** problems (e.g., counting linearly independent rows/columns).
- **Solving linear equations** modulo prime (e.g., using Gaussian elimination mod 1e9+7).
- **Graph theory**: incidence matrix, Kirchhoff's matrix‑tree theorem.
- **Polynomial interpolation** viewed as linear system.

## Pitfalls
- Over‑reliance on floating‑point precision; use modular arithmetic when possible.
- Confusing row space with column space; remember rank is same for both.
- Forgetting that zero vector is always linearly dependent with any set.