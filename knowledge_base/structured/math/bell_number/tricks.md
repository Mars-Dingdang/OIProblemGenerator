## Key Observations

1. **Recurrence Relation**: 
   - Bell numbers satisfy: 
     $$B_{n+1} = \sum_{k=0}^{n} \binom{n}{k} B_k$$
   - This can be derived by considering where the (n+1)-th element goes in a partition

2. **Connection to Stirling Numbers**:
   - Bell numbers are sums of Stirling numbers of the second kind:
     $$B_n = \sum_{k=0}^{n} S(n, k)$$
   - Where S(n,k) counts partitions of n elements into exactly k non-empty subsets

3. **Bell Triangle Method**:
   - Construct triangle where:
     - a(0,0) = 1
     - a(n,0) = a(n-1,n-1)
     - a(n,m) = a(n,m-1) + a(n-1,m-1)
   - First element of each row is the Bell number
   - Time complexity: O(n²)

4. **Exponential Generating Function**:
   - Bell numbers have EGF: 
     $$B(x) = e^{e^x - 1}$$
   - This allows O(n log n) computation using polynomial exponentiation

5. **Modular Arithmetic**:
   - For large n, compute modulo prime using modular inverses for binomial coefficients
   - Touchard's congruence: For prime p, 
     $$B_{n+p} \equiv B_n + B_{n+1} \pmod{p}$$

6. **Dobinski's Formula**:
   - Alternative representation:
     $$B_n = \frac{1}{e} \sum_{k=0}^{\infty} \frac{k^n}{k!}$$
   - Useful for theoretical analysis and approximations

## Optimization Techniques

1. **Precompute Factorials**: For recurrence using binomial coefficients, precompute factorials and inverse factorials modulo MOD
2. **Memory Optimization**: Bell triangle only needs previous row, so O(n) space is possible
3. **Fast Polynomial Methods**: Using FFT/NTT with exponential generating functions for O(n log n) computation
4. **Caching Results**: Bell numbers are frequently reused in combinatorial problems

## Common Problem Transformations

1. **Set Partition Problems**: Any problem asking "in how many ways can n distinguishable items be partitioned into groups" is a Bell number problem
2. **Equivalence Relations**: Bell numbers count the number of equivalence relations on a set of n elements
3. **Restaurant Table Problem**: Number of ways n people can sit at tables (tables are indistinguishable)
4. **Graph Components**: Connected components in certain graph structures relate to Bell numbers

## Implementation Notes

- For n ≤ 5000, triangle method is sufficient
- For larger n, use exponential generating functions with FFT
- Watch for integer overflow when n > 20 without modulo
- Bell numbers grow very fast: B₁₀ = 115975, B₂₀ ≈ 5.8×10¹³