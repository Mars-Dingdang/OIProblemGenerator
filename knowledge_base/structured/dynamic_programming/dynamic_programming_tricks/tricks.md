# 浅谈 OI 中动态规划问题的一些解题方法

**Author:** 曹立

### Key Ideas and Tricks

1. **State Compression and Optimization**:
   - The paper emphasizes compressing DP states using mathematical properties (e.g., Möbius function, Dirichlet convolution) to reduce state space.
   - For multiplicative functions, the sum $ S_f(n) = \sum_{i=1}^n f(i) $ can be computed efficiently using identities like $ \mu * I = \epsilon $, enabling recursive computation via:
     $$
     S_A(n) = S_C(n) - \sum_{k=2}^n B(k) S_A\left(\left\lfloor \frac{n}{k} \right\rfloor\right)
     $$
     where $ A * B = C $, reducing complexity to $ O(n^{2/3}) $.

2. **Powerful Number Method**:
   - Any powerful number (where all prime exponents ≥ 2) can be written as $ a^2 b^3 $. This allows factoring sums over such numbers into manageable parts.
   - Used to compute sums of multiplicative functions by separating contributions from square-free and non-square-free parts.

3. **Dirichlet Convolution and Möbius Inversion**:
   - Leverages $ f = g * h \Rightarrow S_f(n) = \sum_{d=1}^n g(d) S_h\left(\left\lfloor \frac{n}{d} \right\rfloor\right) $.
   - Enables fast computation of summatory functions when one component has sparse support (e.g., $ \mu $ is zero on non-square-free numbers).

4. **Exponential and Logarithmic Generating Functions**:
   - For multiplicative functions defined on prime powers, uses generating functions like $ \exp(q) $ and $ \log(f) $ to decompose complex functions.
   - Example: If $ f(p^k) = \frac{f(p)^k}{k!} $, then $ f = \exp(g) $ for some $ g $, allowing decomposition via logarithm.

5. **Optimized Computation via Thresholding**:
   - Precompute values up to $ n^{2/3} $, then use recursion for larger quotients $ \left\lfloor \frac{n}{k} \right\rfloor > n^{2/3} $, achieving $ O(n^{2/3}) $ time.
   - Uses the fact that distinct values of $ \left\lfloor \frac{n}{k} \right\rfloor $ are only $ O(\sqrt{n}) $, enabling memoization.

6. **Randomized Algorithms for Matrix Rank**:
   - Applies Schwartz-Zippel lemma to verify matrix rank equality after random assignment of variables.
   - Reduces error probability by choosing large primes.

7. **Low-Rank Updates**:
   - Uses Sherman-Morrison-Woodbury formula to maintain matrix inverse under low-rank perturbations, reducing update cost from $ O(n^3) $ to $ O(r^2) $.

8. **Weighted Problems via Polynomial Interpolation**:
   - Encodes weights using polynomial degrees (e.g., $ z^{w_i} $), then recovers maximum weight via degree extraction.
   - Uses Lagrange interpolation to reconstruct polynomials from point evaluations.

9. **Finger Search and Merge Optimizations**:
   - Applies finger search in treaps to merge sequences in $ O(m \log(n/m)) $ time.
   - Uses entropy-based analysis to bound total complexity across operations.

10. **Lagrange Duality and Minimax Theorems**:
    - Transforms constrained optimization into dual forms using Lagrange multipliers.
    - Applies minimax theorem when objective is convex-concave to swap min/max order.

These tricks allow handling otherwise intractable DP formulations by exploiting algebraic structure, sparsity, and randomness.