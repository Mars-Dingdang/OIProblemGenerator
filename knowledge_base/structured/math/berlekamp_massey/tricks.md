# 关于数列递归式的一些研究

**Author:** 毛啸

### Key Ideas and Observations

- **Recursive Polynomial**: A novel abstraction where a polynomial $ R(x) $ is associated with a sequence $ a $ such that the convolution $ R(x) \cdot A(x) $ has zero coefficients from degree $ d $ to $ n-1 $. The minimal degree $ d_R $ characterizes how early the recurrence starts being satisfied.

- **Berlekamp-Massey via Basis Construction**: Instead of viewing the algorithm as correcting discrepancies, this paper frames it as constructing a basis $ \text{Base}_k(x) $ — the lowest-degree polynomial starting at $ x^k $ — enabling structural understanding through linear algebra.

- **Basis Update Insight**: When updating $ \text{Base}_k(x) $, consider $ x \cdot \text{Base}_{k+1}(x) $. If its product with $ A(x) $ has a nonzero coefficient at $ x^n $, use the most recent previously corrected discrepancy polynomial (tracked by `last`) to eliminate it. This maintains minimality.

- **Efficient Implementation Without Polynomials**: Track only the recurrence arrays $ r_k $, representing the shortest recurrence for the first $ k $ elements. Use lazy updates: extend $ r_k $ only when necessary using scaled shifts of previous correction vectors.

- **Minimal and Non-Trivial Second Minimal Polynomials ($ M(x), S(x) $)**: After full basis computation, all recursive polynomials can be uniquely expressed as linear combinations of $ M(x) $ and $ S(x) $, leading to exact counting formulas.

- **Counting Recurrence Relations**: Over a finite field of size $ q $, the number of $ k $-degree recursive polynomials is:
  $$
  \text{num}_k = q^{\max(k - d_M - 1, 0) + \max(k - d_S - 1, 0)} \left( [k \geq d_M] + [k \geq d_S] - 1 \right)
  $$
  Summing over lengths gives total recurrence count.

- **Characteristic Polynomial via Randomization**: For a sparse matrix $ A $ (with $ e $ nonzeros), if each eigenvalue corresponds to one Jordan block, then the minimal polynomial equals the characteristic polynomial. By choosing a random vector $ v $, compute the sequence $ s_i = \mathbf{h}(A^i v) $, where $ \mathbf{h} $ is a linear hash (e.g., dot product with another random vector). Apply Berlekamp–Massey on $ s_i $; with high probability, the result is the characteristic polynomial.

- **Determinant Computation**: Compute $ \det(A) $ as $ (-1)^n $ times the constant term of the characteristic polynomial. If $ A $ doesn’t satisfy the Jordan condition, perturb it with a random diagonal matrix $ B $, compute $ \det(AB)/\det(B) $, leveraging that $ AB $ will likely meet the requirement.

- **Spanning Tree Counting**: Via Kirchhoff’s Matrix-Tree Theorem, the number of spanning trees is the cofactor of the Laplacian matrix. For sparse graphs, apply the above determinant method efficiently in $ O(n(n + m)) $ time.

- **Monte Carlo Nature**: All matrix-related algorithms are probabilistic but succeed with high probability over large fields due to Schwartz-Zippel-type arguments.