# 关于积性函数求和问题的一些进展

**Author:** 周康阳

### Key Ideas and Tricks

#### 1. **Dirichlet Convolution and Möbius Inversion**
- For multiplicative functions $ f $, if $ f = g * h $ (Dirichlet convolution), then:
  $$
  \sum_{i=1}^n f(i) = \sum_{j=1}^n g(j) \cdot S_h\left(\left\lfloor \frac{n}{j} \right\rfloor\right)
  $$
- This allows recursive computation of $ S_f(n) $ if $ S_g $ and $ S_h $ are known.
- A classic example is $ \mu * I = \epsilon $, leading to:
  $$
  S_\mu(n) = 1 - \sum_{k=2}^n S_\mu\left(\left\lfloor \frac{n}{k} \right\rfloor\right)
  $$

#### 2. **Sublinear Algorithm Framework ("Min-25" Style)**
- The set $ \left\{ \left\lfloor \frac{n}{k} \right\rfloor \mid k \in \mathbb{Z}^+ \right\} $ has only $ O(\sqrt{n}) $ distinct values.
- Use memoization to store $ S_f(m) $ only for $ m \in \left\{ \left\lfloor \frac{n}{k} \right\rfloor \right\} $.
- Precompute $ f(i) $ for $ i \leq n^{2/3} $ in $ O(n^{2/3}) $ time.
- For $ m > n^{2/3} $, compute recursively using the formula above, resulting in total complexity:
  $$
  O\left(\sum_{i=1}^{n^{1/3}} \frac{n}{i}\right) = O(n^{2/3})
  $$

#### 3. **Powerful Numbers and Factorization**
- A **powerful number** (or square-full number) is one where every prime factor $ p $ satisfies $ p^2 \mid x $.
- Every powerful number can be uniquely written as $ a^2 b^3 $.
- The count of powerful numbers $ \leq n $ is $ O(\sqrt{n}) $, which enables efficient enumeration.
- Used to handle functions defined on prime powers by isolating their behavior on powerful numbers.

#### 4. **Exponential and Logarithmic Series (Exp/Log Trick)**
- For a multiplicative function $ q $ defined only on primes, define $ f = \exp(q) $ via:
  $$
  f(p^k) = \frac{q(p)^k}{k!}
  $$
- Then $ q = \log(f) $, and this transformation preserves multiplicativity.
- This allows reducing complex functions to sums of simpler ones.
- Efficiently compute $ \exp(q) $ and $ \log(f) $ using Dirichlet generating functions and convolution.

#### 5. **Optimized Exp/Log Computation**
- To compute $ \exp(q) $:
  - Split $ q = q_0 + q_1 $, where $ q_0 $ contains terms with small prime factors ($ \leq \sqrt{n} $), and $ q_1 $ large ones.
  - Compute $ \exp(q_0) $ and $ \exp(q_1) $ separately.
  - Use a sieve-like method over powerful numbers to compute $ \exp(q_0) $ efficiently.
- Complexity can be reduced to $ O\left(\frac{\sqrt{n} \log^2 n}{\sqrt{\log \log n}}\right) $ using optimized sieving and bucketing techniques.

#### 6. **Handling General Multiplicative Functions**
- For a multiplicative function $ f $ with $ f(p) = q(p) $, find $ h $ such that $ f = h * \exp(q) $.
- Since $ h $ is supported only on powerful numbers, it has $ O(\sqrt{n}) $ non-zero values.
- Thus, $ S_f $ can be computed from $ S_h $ and $ S_{\exp(q)} $ via convolution.

#### 7. **Fast Dirichlet Product for Sparse Functions**
- When one function (e.g., $ h $) is sparse (nonzero only on $ O(\sqrt{n}) $ arguments), the Dirichlet product can be computed faster.
- Use hashing or direct iteration over the support of the sparse function.
- Combined with precomputed prefix sums, this leads to near-linear overhead in the sparsity size.

These tricks collectively allow solving summatory problems for a wide class of multiplicative functions in significantly sublinear time, far beyond naive $ O(n) $ or even $ O(n^{3/4}) $ approaches.