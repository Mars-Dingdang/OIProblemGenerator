## Key Observations
1. **Powerful Number (PN) Definition**: A positive integer n is a PN if in its prime factorization, all exponents are ≥2. All PN can be expressed as a²b³.
2. **PN Count**: There are only O(√n) PN ≤ n, enabling efficient enumeration via DFS.
3. **Core Idea**: For a multiplicative function f, find a multiplicative function g such that:
   - g is easy to prefix-sum.
   - For primes p, g(p) = f(p).
   Define h = f / g (Dirichlet convolution inverse). Then h is multiplicative and h(p) = 0 for primes p, so h(n) ≠ 0 only when n is PN.
4. **Prefix Sum Formula**: F(n) = Σ_{d is PN} h(d) * G(⌊n/d⌋), where G is prefix sum of g.

## Optimizations
- **Precomputation**: Pre-calculate h(pᶜ) for primes p ≤ √n and small c using recurrence h(pᶜ) = f(pᶜ) - Σ_{i=1}^{c} g(pⁱ)h(p^{c-i}).
- **DFS Pruning**: Stop DFS when d > n / p² to avoid unnecessary branches.
- **Caching**: Use memoization (e.g., std::map) for G(n) if computed via Dirichlet convolution (like in Dujiao sieve).
- **Combining with Dujiao Sieve**: When g is not trivial, compute G using Dujiao sieve, achieving O(n^{2/3}) total time.

## Common Problem Transformations
- **Example 1 (Luogu P5325)**: f(pᵏ) = pᵏ(pᵏ - 1). Choose g(n) = id(n)φ(n). Then h(pᵏ) = (k-1)(p-1)pᵏ.
- **Example 2 (LOJ #6053)**: f defined piecewise. Construct g(n) = φ(n) or 3φ(n) based on parity. Compute G via S₁(n) = Σ φ(i) and S₂(n) = Σ φ(2i).
- **General Approach**:
  1. Identify f(p) and choose suitable g.
  2. Compute G efficiently (often via Dujiao sieve).
  3. Compute h(pᶜ) via recurrence or closed form.
  4. DFS over PN, accumulating h(d)G(⌊n/d⌋).

## Complexity Notes
- **Time**: O(√n log n) for h(pᶜ) computation + O(√n) for DFS if G is O(1). With Dujiao sieve for G, total O(n^{2/3}).
- **Space**: O(√n) for storing h(pᶜ).