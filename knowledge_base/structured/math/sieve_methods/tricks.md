## Key Observations

1. **Eratosthenes sieve** marks multiples from `i*i` because smaller multiples are already marked by smaller primes.
2. **Linear sieve (Euler sieve)** ensures each composite is marked exactly once by its smallest prime factor, achieving O(n).
3. **Optimizations for Eratosthenes**:
   - Sieve only up to √n.
   - Process only odd numbers (halves memory and operations).
   - Use bit compression (e.g., `bitset`, `vector<bool>`) for memory efficiency.
   - Block sieving for cache efficiency and reduced memory to O(√n + S).
4. **Simultaneous computation of multiplicative functions**:
   - Euler's totient φ(n): use φ(ab) = φ(a)φ(b) if gcd(a,b)=1; if p divides n, φ(np) = p·φ(n).
   - Möbius function μ(n): μ(p) = -1; if p divides n, μ(np) = 0; else μ(np) = -μ(n).
   - Divisor count d(n): if p divides n, d(np) = d(n)/(k+1)·(k+2) where k is exponent of p in n.
   - Divisor sum σ(n): similar recurrence using sum of powers of the smallest prime factor.
5. **Block sieving trick**:
   - Divide range [1, n] into blocks of size S (~10^4–10^5).
   - For each block, sieve using primes up to √n.
   - Reduces memory to O(√n + S) and improves cache performance.
6. **Using sieve for GCD sum problem**:
   - ∑_{i=1}^n ∑_{j=1}^n gcd(i, j) = ∑_{d=1}^n ⌊n/d⌋² φ(d) can be computed efficiently after linear sieve of φ.
7. **Note**: Linear sieve also provides the smallest prime factor for each number, useful for factorization.