# 论现代硬件上的常数优化

**Author:** 宋佳兴

### Key Ideas and Tricks

1. **Powerful Numbers (PN)**:
   - A powerful number is defined as a positive integer $ m $ where every prime factor $ p $ satisfies $ p^2 \mid m $. These numbers can be expressed in the form $ a^2b^3 $.
   - The count of powerful numbers up to $ n $ is $ O(\sqrt{n}) $, which allows efficient enumeration and processing.

2. **Dirichlet Convolution Optimization**:
   - For multiplicative functions $ f $, decompose $ f = g * h $ such that $ g $ has non-zero values only on powerful numbers.
   - This decomposition reduces the number of terms involved in summations from $ O(n) $ to $ O(\sqrt{n}) $, significantly lowering computational overhead.

3. **Exponential and Logarithmic Transformations**:
   - Use formal power series transformations such as $ \exp(f) $ and $ \log(f) $ to convert between different types of arithmetic functions.
   - These transformations allow manipulation of function representations while preserving multiplicativity, enabling more efficient computation via convolution.

4. **Segmented Sieve over Powerful Numbers**:
   - Instead of sieving all integers, restrict operations to powerful numbers using their sparse distribution.
   - Precompute values for small primes and use segmented processing to handle large intervals efficiently.

5. **Optimized Summation via Floor Division Sets**:
   - Leverage the fact that the set $ \left\{ \left\lfloor \frac{n}{i} \right\rfloor \mid i \in \mathbb{Z}^+ \right\} $ has only $ O(\sqrt{n}) $ distinct values.
   - This enables dynamic programming approaches with state reduction, avoiding redundant calculations across equivalent quotient classes.

6. **Recursive Computation with Memoization**:
   - Apply recursive strategies with memoization for computing summatory functions $ S_f(n) $, reusing previously computed results for smaller arguments.
   - Combine this with precomputed tables for $ m \leq n^{2/3} $ to balance preprocessing cost and query speed.

7. **Efficient Handling of Multiplicative Function Properties**:
   - Exploit known identities (e.g., $ \mu * I = \epsilon $) to simplify expressions involving Möbius inversion or Euler totient functions.
   - Use these identities to derive faster evaluation schemes for classical number-theoretic sums.

8. **Hardware-Aware Optimizations**:
   - Although not explicitly detailed, the title implies consideration of cache-friendly memory access patterns, loop unrolling, and SIMD instructions when implementing sieves and convolutions.
   - Focus on reducing constant factors through low-level optimizations suitable for modern CPU architectures.