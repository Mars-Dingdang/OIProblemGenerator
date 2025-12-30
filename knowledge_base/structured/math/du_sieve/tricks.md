## Key Observations
- **Core Idea**: Construct a Dirichlet convolution identity to derive a recurrence for the prefix sum S(n) in terms of S(⌊n/i⌋).
- **General Formula**: For arithmetic functions f and g, we have:
  $$g(1)S(n) = \sum_{i=1}^n (f * g)(i) - \sum_{i=2}^n g(i) S(\lfloor n/i \rfloor)$$
  Choose g such that (f * g) and the prefix sum of g are easy to compute.
- **Non-multiplicative Functions**: Du Sieve can be applied even if f is not multiplicative, as long as a suitable g exists (e.g., f(n) = n·φ(n) with g(n)=1).

## Optimizations
- **Precomputation**: Use a linear sieve to precompute prefix sums up to m = Θ(n^{2/3}). This balances precomputation cost O(m) and query cost O(n/√m), achieving overall O(n^{2/3}) time.
- **Memoization**: Store computed S(k) in a hash map (unordered_map) for all distinct values k = ⌊n/i⌋ (there are O(√n) such values). This avoids repeated calculations and ensures sublinear complexity.
- **Number Theory Blocking**: The recurrence involves sums over ⌊n/i⌋; use blocking to evaluate them in O(√n) time.

## Common Problem Transformations
- **Möbius Function (μ)**: Use g = 1, since μ * 1 = ε (the identity under Dirichlet convolution).
- **Euler Totient (φ)**: Use g = 1, since φ * 1 = id (the identity function).
- **Weighted Functions**: For sums like ∑ i²·φ(i), consider convolving with id² to simplify the convolution to a polynomial sum (e.g., ((id²·φ) * id²)(i) = i³).
- **Combining with Other Techniques**: Often used together with:
  - **Möbius inversion** to transform gcd/lcm sums into multiplicative functions.
  - **Dirichlet convolution** to find suitable g.
  - **Modular arithmetic** for problems requiring results modulo a prime.

## Implementation Notes
- **Memory Management**: Precomputation arrays should be sized appropriately (typically ~2·10^6 for n up to 10^10).
- **Integer Overflow**: Use 64-bit integers (long long) for large n.
- **Hash Map Choice**: unordered_map is usually faster than map, but ensure custom hash for ll if performance is critical.
- **Recursion Depth**: The recursion depth is O(√n), which is safe for n up to 10^10.