# 连分数与欧几里得算法在 OI 中的应用

**Author:** 柯怿憬

## Key Ideas and Tricks

### 1. **Dirichlet Convolution and Möbius Inversion**
- The core idea is to express a target multiplicative function $ f $ as a Dirichlet convolution $ f = g * h $, where one of the functions (often $ g $) has an easily computable prefix sum.
- For example, since $ \mu * I = \epsilon $, we can compute the prefix sum of $ \mu $ using the identity:
  $$ S_\mu(n) = 1 - \sum_{k=2}^n S_\mu\left(\left\lfloor \frac{n}{k} \right\rfloor\right) $$
- This allows recursive computation using memoization over the distinct values of $ \left\lfloor \frac{n}{k} \right\rfloor $.

### 2. **Distinct Values Optimization**
- The number of distinct values of $ \left\lfloor \frac{n}{k} \right\rfloor $ for $ k = 1, 2, ..., n $ is only $ O(\sqrt{n}) $. This is crucial because it limits the number of states in the recursion.
- When calculating $ S_f(n) $, we only need to compute $ S_f(m) $ for $ m \in \left\{ \left\lfloor \frac{n}{k} \right\rfloor \mid k \in \mathbb{Z}^+ \right\} $, which are $ O(\sqrt{n}) $ in number.

### 3. **Sublinear Algorithm Framework (Min_25-like)**
- For multiplicative functions $ f $ with known $ f(p) $ on primes, we can use a two-part strategy:
  1. Precompute $ f(p^k) $ for small primes $ p \leq n^{2/3} $ up to $ O(n^{2/3}) $ terms.
  2. Use a recursive formula for larger values:
     $$ S_f(n) = C(n) - \sum_{k=2}^n B(k) S_A\left(\left\lfloor \frac{n}{k} \right\rfloor\right) $$
     where $ A * B = C $, and $ B, C $ have easy prefix sums.
- This achieves $ O(n^{2/3}) $ time complexity by balancing the precomputation and recursion costs.

### 4. **Power Series Techniques (Exp and Log)**
- To handle more complex multiplicative functions, the paper uses formal power series.
- If $ d = \mathrm{Exp}(q) $, then $ q = \mathrm{Log}(d) $, allowing us to decompose a function into simpler components.
- For instance, if $ f(p) = p(p-1) $, we can write $ f = q_1 - q_2 $ with $ q_1(p)=p^2 $, $ q_2(p)=p $, and use $ \mathrm{Exp} $ to reconstruct the full function from its prime values.

### 5. **Optimized Exp and Log for Sublinear Time**
- Direct computation of $ \mathrm{Exp}(f) $ takes $ O(\sqrt{n} \log^3 n) $.
- The paper introduces optimizations using auxiliary variables $ S $ and $ L $:
  - For $ \mathrm{Exp}(f) $: choose $ S = \sqrt{n / \log \log n} $ to reduce complexity to $ O\left( \frac{\sqrt{n} \log^2 n}{\sqrt{\log \log n}} \right) $.
  - For $ \mathrm{Log}(f) $: similar techniques apply, achieving $ O(\sqrt{n} \log n \log \log n) $.
- These optimizations rely on segmenting the computation based on the size of prime factors and using sieve methods within intervals.

### 6. **Interval Sieve and Divisor Summatory Function**
- To count contributions from numbers in $ [n-L, n] $, the paper uses the divisor summatory function $ D(x) = \sum_{i=1}^x d(i) $, which has an asymptotic form $ D(x) = x \log x + (2\gamma-1)x + O(x^{1/3}) $.
- By analyzing the contribution of triples $ (x,y,t) $ such that $ xyt \in [n-L,n] $, the error term is bounded using properties of $ d_3(v) = \sum_{xyz=v} 1 $.
- This leads to tighter bounds on the computational complexity of intermediate steps.

### 7. **Application to Power Numbers**
- A 'power number' is defined as a number divisible by $ p^2 $ for some prime $ p $.
- The paper shows how to enumerate them efficiently in $ O(\sqrt{n}) $ time by expressing them as $ a^2 b^3 $ and iterating over $ a $.

These techniques collectively allow solving difficult number-theoretic problems in competitive programming with significantly better efficiency than brute-force or standard sieve methods.