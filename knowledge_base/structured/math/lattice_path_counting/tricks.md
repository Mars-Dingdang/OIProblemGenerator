# 再谈格路计数

**Author:** 吴畅

### Key Ideas and Tricks

1. **Dirichlet Convolution and Möbius Inversion**:
   - Use the identity $ f = g * h \Rightarrow S_f(n) = \sum_{k=1}^n g(k) S_h(\lfloor n/k \rfloor) $ to recursively compute prefix sums.
   - For multiplicative functions like $ \mu $ and $ \phi $, use known identities: $ \mu * I = \epsilon $, $ \phi * I = \text{id} $.

2. **Sublinear Prefix Sum Computation ("Min-25 Sieve" style)**:
   - Only compute $ S_f(m) $ for $ m \in \{ \lfloor n/i \rfloor \mid i \in \mathbb{Z}^+ \} $, which has only $ O(\sqrt{n}) $ distinct values.
   - Precompute base cases up to $ n^{2/3} $ via linear sieve, then use recursive formula for larger values.
   - Total complexity: $ O(n^{2/3}) $ due to harmonic sum bounds.

3. **Powerful Numbers Optimization**:
   - A *powerful number* is of the form $ a^2b^3 $. The count of powerful numbers $ \leq n $ is $ O(\sqrt{n}) $.
   - Exploit this sparsity: if $ f(p^k) $ depends only on $ p $ and small $ k $, express $ f = g * h $ where $ h $ is supported only on powerful numbers.
   - Then $ S_f(n) = \sum_{j \in PN, j \leq n} g(j) S_f(\lfloor n/j \rfloor) $, requiring only $ O(\sqrt{n}) $ terms.

4. **Exponential and Logarithm of Multiplicative Functions**:
   - Define $ \exp(f) $ for a multiplicative function $ f $ supported on primes as:
     $$
     \exp(f)(x) = \sum_{k=0}^\infty \frac{f^{*k}(x)}{k!}
     $$
     where $ f^{*k} $ is the $ k $-fold Dirichlet convolution.
   - This allows transforming problems involving $ f(p)^k / k! $ into standard prefix sum computations.
   - Similarly, $ \log(f) $ can be used to decompose complex multiplicative functions.

5. **Segmented Sieve and Harmonic Lemma**:
   - To compute $ \sum_{i=n-L}^n d_3(i) $ efficiently, use the identity:
     $$
     \sum_{i \leq x} d_3(i) = x P_3(\log x) + O(x^{43/96+\epsilon})
     $$
     where $ d_3(i) $ counts the number of ways to write $ i $ as a product of three integers.
   - Combined with bounds on divisor functions, this enables faster evaluation over intervals.

6. **Optimized Exp/Log Computation**:
   - To compute $ \exp(f) $ in $ O(\sqrt{n} \log^2 n / \sqrt{\log \log n}) $:
     - Split $ f = f_0 + f_1 $, where $ f_0 $ is supported on $ \leq \sqrt{n} $, $ f_1 $ on $ > \sqrt{n} $.
     - Compute $ \exp(f_0) $ via convolution on segments defined by $ \lceil S \log p \rceil $, reducing state space.
     - Use a threshold $ L $ and parameter $ S $ to balance the cost of handling small and large prime powers.

7. **Fast Log Computation**:
   - Use the identity $ \log(f) = \sum_{k=1}^\infty (-1)^{k-1} \frac{(f - \epsilon)^{*k}}{k} $.
   - Compute iteratively, truncating at $ k > \log n $ since higher convolutions vanish.
   - Combine with low-rank update techniques to solve the resulting system efficiently.

8. **Generalized Sublinear Algorithm**:
   - For a multiplicative function $ f $ where $ f(p) $ is a polynomial in $ p $, the prefix sum $ S_f(n) $ can be computed in $ O(\sqrt{n} \log n \log \log n) $ or better.
   - This unifies and generalizes several previous results on computing $ \sum \mu(i), \sum \phi(i), \sum i^k $, etc., under one framework.