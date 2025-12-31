# 一些特殊的数论函数求和问题

**Author:** 朱震霆

### Key Ideas and Tricks

#### **Min_25 Sieve (Multiplicative Function Summation)**
- The algorithm leverages the structure of multiplicative functions by enumerating numbers based on their smallest prime factor.
- It defines two auxiliary functions:
  - $ h_n = \sum_{p \leq n, p \text{ prime}} f(p) $: sum over primes.
  - $ g_{n,m} = \sum_{\substack{2 \leq x \leq n \\ x \text{ has no prime factor } \leq m}} f(x) $: sum over composites with restricted smallest prime factors.
- Uses the observation from Lemma 1.3 that $ \left\lfloor \frac{n}{m} \right\rfloor $ takes only $ O(\sqrt{n}) $ distinct values, enabling state compression.
- Computes $ h_i $ using a sieve-like process inspired by the Eratosthenes sieve: maintain $ h'_{i,j} $ as the sum of $ p^s $ for remaining unsieved numbers up to $ j $ after processing first $ i $ primes.
- Transition: $ h'_{i,j} = h'_{i-1,j} - p_i^s \left( h'_{i-1,\lfloor j/p_i \rfloor} - h'_{i-1,p_i-1} \right) $ when $ j \geq p_i^2 $.
- Final result is obtained via recursive decomposition: $ g_{n,0} $ gives total sum excluding 1.
- Time complexity analysis uses Dickman function and smooth number density estimates to show practical efficiency despite theoretical bounds.

#### **Prime k-th Power Prefix Sum (Meissel-Lehmer Style)**
- Introduces $ \pi_k(n) = \sum_{p \leq n} p^k $, generalizing prime counting.
- Defines $ \phi_k(n,a) $: sum of $ i^k $ for integers $ \leq n $ whose smallest prime factor > $ p_a $.
- Uses inclusion-exclusion: $ \phi_k(n,a) = \phi_k(n,a-1) - p_a^k \cdot \phi_k(\lfloor n/p_a \rfloor, a-1) $.
- Expresses $ \pi_k(n) = \phi_k(n,a) - P_{2,k}(n,a) + \pi_k(p_a) - 1 $, where $ P_{2,k} $ counts semiprimes $ pq $ with both $ p,q > p_a $.
- Efficiently computes $ P_{2,k} $ by iterating over small primes and using precomputed prefix sums.
- For large $ a $, uses DFS with pruning and tree-based data structures (e.g., Fenwick tree) to aggregate contributions efficiently.
- Optimizes by splitting cases based on size of smallest prime $ p $:
  - $ p \leq \sqrt{B} $: brute-force with precomputation.
  - $ p > x^{1/3} $: direct summation due to limited range.
  - Intermediate case optimized using coordinate transformation and batch queries.
- Achieves $ \tilde{O}(x^{2/3}) $ time via balanced choice of $ B = x^{1/3} \log^{2/3} x $.

#### **Divisor Summatory Function via Stern-Brocot Tree**
- Goal: compute $ D(n) = \sum_{i=1}^n \sigma_0(i) = \sum_{ab \leq n} 1 $, equivalent to counting integer points under $ xy = n $.
- Naive: $ O(\sqrt{n}) $ using symmetry: $ D(n) = 2\sum_{i=1}^{\lfloor\sqrt{n}\rfloor} \left\lfloor \frac{n}{i} \right\rfloor - \lfloor\sqrt{n}\rfloor^2 $.
- For very large $ n $ (e.g., near $ 2^{63} $), this is too slow.
- Novel idea: use **Stern-Brocot Tree** to recursively partition the region under the curve.
- Define recursive function $ S(x_0,y_0,a,b,c,d) $ representing count in a triangular region bounded by rays of slopes $ -a/b $, $ -c/d $ from point $ (x_0,y_0) $.
- Use coordinate transformation: map to $ (u,v) $-space where axes align with current bounding rays.
  - Transformation: $ x = x_0 + ud - vb, y = y_0 - uc + va $
  - Inverse exists because $ ad - bc = 1 $ (Farey neighbor condition).
- In transformed space, the hyperbola becomes another quadratic form amenable to recursive slicing.
- Recursively cut at point where tangent has slope $ -1 $ in local coordinates, then recurse on subregions.
- Alternatively, directly fit a piecewise linear approximation (staircase) along the curve using Stern-Brocot Tree navigation:
  - At each step, find next best rational slope $ -a/b $ such that line stays below curve.
  - Move from $ (x,y) $ to $ (x+a, y-b) $, adding area of vertical strip.
- Complexity improved to $ \tilde{O}(n^{1/3}) $ by showing number of segments is small due to curvature and Farey sequence properties.
- Generalizes to other convex/concave curves (e.g., circle lattice point counting).