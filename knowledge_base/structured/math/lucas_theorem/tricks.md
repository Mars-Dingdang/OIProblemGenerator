## Key Observations
- **Lucas Theorem**: For prime modulus p, binom(n, k) ≡ binom(⌊n/p⌋, ⌊k/p⌋) * binom(n mod p, k mod p) (mod p). This reduces large n, k to smaller values.
- **Recursive Application**: Recursively apply until n, k < p, then compute directly using precomputed factorials and inverses.
- **Precomputation**: Precompute factorials and inverse factorials modulo p up to p-1 in O(p) time for O(1) queries.
- **Wilson's Theorem**: Used to compute inverse factorials efficiently: (p-1)! ≡ -1 (mod p).

## Optimizations
- **Early Termination**: If k > n, binom(n, k) = 0.
- **Modular Multiplication**: Use long long to avoid overflow during multiplication before modulo.
- **Iterative vs Recursive**: The iterative version (as in template) avoids recursion overhead and is often preferred.

## Problem Transformation Patterns
- **Composite Modulus**: Use exLucas algorithm: factor modulus into prime powers, compute binom modulo each prime power, combine via CRT.
- **Prime Power Modulus**: Separate p's multiplicity using Legendre's formula and compute factorial modulo p^a via recursion.
- **Large n, Small Modulus**: Lucas theorem is ideal when n ~ 1e18 and modulus ~ 1e6.
- **Multiple Queries**: Preprocess factorials and inverses once to answer each query in O(log_p n) time.

## Common Pitfalls
- Ensure modulus p is prime for basic Lucas theorem; for composite, use exLucas.
- Handle cases where n mod p < k mod p, leading to binom = 0.
- In exLucas, check if multiplicity v >= a (exponent in p^a) to return 0 early.
- Use efficient modular inverse computation (e.g., extended Euclidean algorithm).