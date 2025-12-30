## Key Observations
- **Möbius function μ(n)** is multiplicative, not completely multiplicative. Key identity: ∑_{d|n} μ(d) = [n=1].
- **Standard transformation**: [gcd(i,j)=1] = ∑_{d|gcd(i,j)} μ(d) = ∑_{d} [d|i][d|j] μ(d). This decouples i and j.
- **Extract common factor**: When dealing with gcd(i,j)=k, substitute i' = i/k, j' = j/k to reduce to gcd=1 case.
- **Swap summation order**: After applying μ, swap sums to separate variables, often leading to terms like ⌊n/d⌋.

## Common Problem Patterns
1. **Double sum with gcd condition**: ∑_{i=1}^{n} ∑_{j=1}^{m} [gcd(i,j)=k] → after extraction and μ: ∑_{d} μ(d) ⌊n/(kd)⌋ ⌊m/(kd)⌋.
2. **Sum involving lcm**: lcm(i,j) = i*j / gcd(i,j). Often rewrite as ∑_{k} k * ∑_{i',j'} i'*j' * [gcd(i',j')=1] after extracting k=gcd.
3. **Dirichlet convolution view**: f = 1 * g ⇔ g = μ * f. Many identities (e.g., φ = μ * id) come from this.
4. **Linear sieve for multiplicative functions**: Compute μ, φ, or custom multiplicative functions in O(n).

## Optimization Techniques
- **Preprocess μ and its prefix sums** with linear sieve O(n). Then queries with number theory blocking run in O(√n).
- **Dirichlet prefix sum/difference** in O(n log log n) using sieve-like iteration over primes.
- **For sums over divisors**, consider changing variable ℓ = k*d to swap summation order.
- **Exploit multiplicativity**: If target function is multiplicative, compute only on prime powers and combine via sieve.

## Extended Forms
1. **Multiple form**: f(n) = ∑_{n|d} g(d) ⇔ g(n) = ∑_{n|d} μ(d/n) f(d).
2. **Multiplicative form**: f(n) = ∏_{d|n} g(d) ⇔ g(n) = ∏_{d|n} f(d)^{μ(n/d)}.
3. **With completely multiplicative t**: f(n) = ∑_{d|n} t(n/d) g(d) ⇔ g(n) = ∑_{d|n} μ(n/d) t(n/d) f(d).
4. **Continuous version**: F(x) = ∑_{n=1}^{⌊x⌋} G(x/n) ⇔ G(x) = ∑_{n=1}^{⌊x⌋} μ(n) F(x/n).

## Implementation Notes
- Always handle n=1 case separately in μ.
- In linear sieve, break when x % p == 0 to maintain linear time.
- For Dirichlet prefix sums, iterate over primes and add contributions to multiples.
- Use long long for sums to avoid overflow when n up to 1e7.
- Combine with number theory blocking for efficient O(√n) queries.