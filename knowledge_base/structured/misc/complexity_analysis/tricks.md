# 浅谈复杂度及其在解决问题方面的应用

**Author:** 杨敏行

### Key Ideas and Tricks

1. **Dirichlet Convolution for Summatory Functions**:
   - For a multiplicative function $ f $, its prefix sum $ S_f(n) = \sum_{i=1}^n f(i) $ can be computed using Dirichlet convolution.
   - If $ f = g * h $ (Dirichlet convolution), then:
     $$
     S_f(n) = \sum_{k=1}^n \sum_{d|k} g(d)h(k/d) = \sum_{d=1}^n g(d) S_h\left(\left\lfloor \frac{n}{d} \right\rfloor\right)
     $$
   - This allows recursive computation if one of the functions has an easy-to-compute prefix sum.

2. **Powerful Number Sieve**:
   - A *powerful number* is a positive integer $ m $ such that for every prime $ p $ dividing $ m $, $ p^2 $ divides $ m $. These numbers have the form $ a^2b^3 $.
   - The number of powerful numbers $ \leq n $ is $ O(\sqrt{n}) $.
   - To compute $ S_f(n) $ for certain multiplicative functions $ f $, express $ f = g * h $ where $ g $ is supported only on powerful numbers. Then:
     $$
     S_f(n) = \sum_{j \in \text{PN}, j \leq n} g(j) \left\lfloor \frac{n}{j} \right\rfloor
     $$
     which runs in $ O(\sqrt{n}) $ due to the sparsity of powerful numbers.

3. **Square Root Decomposition of States**:
   - Use thresholds based on $ \log n $ or $ \sqrt{n} $ to split computations into heavy and light parts.
   - Example: In computing convolutions over divisors, separate small and large factors to optimize memory and speed.

4. **Logarithmic Partitioning Trick**:
   - When dealing with products $ xy \leq n $, partition states by $ \lceil S \log x \rceil + \lceil S \log y \rceil $ for some parameter $ S $.
   - This transforms multiplicative constraints into additive ones modulo $ S $, enabling FFT-like optimizations.
   - Combined with interval sieving, achieves $ O\left(\frac{n \log^2 n}{S}\right) $ time.

5. **Recursive Optimization via Subproblems**:
   - Many summatory functions depend only on values $ S_f(\lfloor n/k \rfloor) $ for $ k = 1, 2, ..., n $.
   - There are only $ O(\sqrt{n}) $ distinct values among these.
   - Memoize results and use recursion with precomputed small values up to $ n^{2/3} $, leading to total complexity $ O(n^{2/3}) $.

6. **Exponential Generating Functions (EGF)**:
   - For multiplicative functions defined on prime powers as $ f(p^k) = \frac{f(p)^k}{k!} $, define $ d = \exp(q) $ where $ q(p) = f(p) $.
   - Compute $ q $ from $ d $ using $ q = \log(d) $, implemented via series expansion:
     $$
     \log(d) = \sum_{i=1}^\infty \frac{(-1)^{i-1}(d - \epsilon)^i}{i}
     $$
   - This enables efficient reconstruction of underlying functions through generating series manipulation.

7. **Optimized Sieve Techniques**:
   - Use segmented sieve approaches combined with hashing to handle dense intervals.
   - Apply double-layered sieves: first sieve up to $ n^{1/2} $, then use it to compute contributions from higher ranges.

8. **Parameter Balancing**:
   - Choose parameters like $ S \sim \sqrt{n} $ or $ L \sim \log n $ to balance terms in complexity expressions.
   - Final optimized complexity reaches $ O\left(\frac{\sqrt{n} \log^2 n}{\sqrt{\log \log n}}\right) $.

9. **Reduction to Known Identities**:
   - Leverage known identities like $ \mu * I = \epsilon $, $ \phi * I = \text{id} $, etc., to simplify derivations.
   - Build new functions via convolution to exploit sparsity or closed-form formulas.