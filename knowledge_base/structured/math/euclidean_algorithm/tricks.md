## Key Observations & Optimizations

### 1. Complexity Guarantee
- Euclidean algorithm reduces the larger number by at least half every two iterations.
- Worst case: consecutive Fibonacci numbers (e.g., gcd(Fn, Fn-1)).
- For integers up to 1e9, recursion depth ≤ ~45.

### 2. Handling Negative Numbers
- gcd(a, b) = gcd(|a|, |b|) — algorithm works with negatives if you take absolute values first.
- In contests, usually inputs are positive.

### 3. Multiple Numbers GCD/LCM
- gcd(a, b, c) = gcd(gcd(a, b), c)
- lcm(a, b, c) = lcm(lcm(a, b), c)
- Can compute in sequence during input reading.

### 4. Relationship between GCD and LCM
- **Fundamental identity**: gcd(a, b) × lcm(a, b) = a × b
- Always compute lcm as `a / gcd(a, b) * b` (divide first to avoid overflow!).

### 5. Binary GCD (Stein's Algorithm)
- Uses only subtraction and bit operations, no division/modulo.
- Faster when hardware division is slow or for big integers.
- Key steps:
  1. Remove common factors of 2
  2. Use identity: gcd(a, b) = gcd(a/2, b) if a even, b odd
  3. Use gcd(a, b) = gcd(|a-b|/2, min(a, b)) for both odd

### 6. Extended Euclidean Algorithm Applications
- Solve linear Diophantine equations: a·x + b·y = c
- Find modular inverses: a⁻¹ mod m exists iff gcd(a, m) = 1
- Generate all solutions: if (x₀, y₀) is a solution, then (x₀ + k·b/g, y₀ - k·a/g) are solutions for any integer k

### 7. Common Problem Transformations
- **Simplify fractions**: (a/g, b/g) where g = gcd(a, b)
- **Check coprimality**: gcd(a, b) = 1
- **Array operations**: Many problems reduce to finding gcd of all elements or gcd of differences
- **Number theory problems**: Often combine with prime factorization

### 8. Implementation Notes
- Recursive version is cleaner but iterative avoids stack overflow for huge inputs.
- For C++17+, prefer `std::gcd` and `std::lcm` from `<numeric>`.
- Avoid `std::__gcd` in C++14 (implementation detail, not guaranteed).
- For extended gcd, the iterative version is slightly faster and avoids recursion.

### 9. Overflow Considerations
- When computing lcm, always divide before multiplying: `a / g * b` not `a * b / g`
- For large numbers (> 1e9), use 64-bit integers (long long).
- For extremely large numbers, use big integer implementations with binary gcd.

### 10. Contest Tricks
- If gcd(a, n) = 1, then a has a multiplicative inverse modulo n.
- gcd(a, b) = gcd(a, b ± a) — useful for problems with additive operations.
- For array problems: gcd of all elements divides every element's difference with any other element.