### Key Observations
1. **Effective Values**: Only O(√n) distinct values of ⌊n/i⌋ are needed. Store them in arrays `le` (≤√n) and `ge` (>√n via n/v).
2. **Polynomial Decomposition**: If f(p) = Σ a_i p^{c_i}, handle each term separately as a completely multiplicative function g(p)=p^{c_i}.
3. **G_k Recursion**: G_k(n) = G_{k-1}(n) - [p_k^2 ≤ n] g(p_k) (G_{k-1}(n/p_k) - G_{k-1}(p_{k-1})). This simulates the sieve of Eratosthenes.
4. **F_k Recursion**: F_k(n) = Σ_{i≥k, p_i^2 ≤ n} Σ_{c≥1, p_i^{c+1} ≤ n} ( f(p_i^c) F_{i+1}(n/p_i^c) + f(p_i^{c+1}) ) + F_prime(n) - F_prime(p_{k-1}).
5. **Precomputation**: Precompute s_k = Σ_{i=1}^{k} g(p_i) and spri[k] = Σ_{i=1}^{k} p_i (or other polynomial terms) for O(1) access.

### Optimizations
- **Space O(√n)**: Only store values for effective arguments.
- **Time O(n^{2/3}/log n)**: Use the second method (suffix optimization) for faster computation.
- **Early Termination**: Stop recursion when p_k^2 > n.
- **Linear Sieve**: Precompute primes and f(p^c) up to √n in O(√n).

### Common Transformations
- **Euler Totient φ**: f(p)=p-1, decompose into g1(p)=p and g2(p)=1.
- **Möbius μ**: f(p)=-1, use g(p)=-1.
- **Divisor Functions**: Express f(p) as polynomial via binomial expansion.
- **LOJ 6053**: f(p)=p-1+2*[p=2], handle p=2 separately.

### Implementation Notes
- Use `long long` for n up to 10^12.
- Modular arithmetic if needed.
- Memoization of F(k,n) is possible but often unnecessary due to limited states.
- For multi‑query, precompute once and answer each n via recursion.