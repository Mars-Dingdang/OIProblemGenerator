# 《无限地狱》命题报告

**Author:** 陈旭磊

### Key Ideas and Observations

- **Structural Constraints via GCD**: A critical insight is that if we let $ C $ be the set with the largest minimum element, then $ g = \gcd(C) > 1 $. This allows reduction by scaling: dividing all multiples of $ g $ by $ g $ leads to a smaller subproblem.

- **Modular Closure**: For any $ x \not\equiv 0 \pmod{g} $ in set $ A $ or $ B $, all $ y \equiv x \pmod{g} $ must also belong to the same set. This follows from an inductive argument using differences between elements in $ C $ and properties of linear combinations (Bézout’s identity).

- **Reduction to Subproblems**: By factoring out $ g $, the problem reduces recursively on $ \lfloor n/d \rfloor $, where $ d \geq 2 $. This enables a recursive formulation involving functions $ f(n) $, $ h(n) $, and $ g(n) $ representing different cases based on emptiness and divisibility conditions.

- **Möbius Inversion for GCD=1 Constraint**: To handle the condition that the scaled set $ C' $ has $ \gcd = 1 $, the solution uses Möbius inversion over divisors:
  $$
  \sum_{d=1}^n \mu(d) \cdot F\left(\left\lfloor \frac{n}{d} \right\rfloor\right)
  $$
  This eliminates unwanted cases where the gcd is greater than 1.

- **Case Analysis Based on Set Emptiness and Divisibility**:
  - $ h(n) $: counts configurations where $ B $ consists only of multiples of $ g $; here $ A' $ may be empty but order constraints apply.
  - $ g(n) $: handles cases where $ B $ contains non-multiples of $ g $; both $ A', B' $ can be empty, but $ C' $ cannot dominate in minima.

- **Recursive Formulation**:
  - $ f(n) = \sum_{d=2}^n h\left(\left\lfloor \frac{n}{d} \right\rfloor\right) + \sum_{d=2}^n (2^{\lfloor d/2 \rfloor - 1} - 1) g\left(\left\lfloor \frac{n}{d} \right\rfloor\right) $
  - Both $ h(n) $ and $ g(n) $ are expressed using Möbius sums over $ f(\lfloor n/d \rfloor) $ and powers of two, adjusted for boundary terms.

- **Optimization Techniques**:
  - **Number-Theoretic Sums with Memoization**: Since arguments $ \lfloor n/d \rfloor $ take only $ O(\sqrt{n}) $ distinct values, one can memoize results and reuse them across recursive calls.
  - **Fast Möbius Summation**: Using the classical identity $ s(n) = \sum_{i=1}^n \mu(i) = 1 - \sum_{d=2}^n s\left(\left\lfloor \frac{n}{d} \right\rfloor\right) $, the prefix sum of $ \mu $ can be computed efficiently in $ O(n^{3/4}) $ time.
  - **Difference DP for Prefix Updates**: Instead of recomputing $ f(n) $ from scratch, maintain differences $ \Delta f(n) = f(n) - f(n-1) $, which change only when $ d \mid n $. This yields an $ O(n \log n) $ method for computing all values up to $ n $.

- **Precomputation Needs**: Efficient implementation requires precomputing powers of 2 modulo 998244353 and storing intermediate Möbius-weighted sums to avoid logarithmic overhead during recursion.