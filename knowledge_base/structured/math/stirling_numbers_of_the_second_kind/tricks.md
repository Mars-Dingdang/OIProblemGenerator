## Key Observations
- **Combinatorial interpretation**: S(n,k) counts partitions of n distinct items into k **unlabeled** non-empty subsets.
- **Recurrence**: S(n,k) = S(n-1,k-1) + k·S(n-1,k). Add new element either as a new subset or into an existing one.
- **Relation to Bell numbers**: Bell(n) = Σ_{k=0}^n S(n,k).
- **Polynomial expansion**: x^n = Σ_{k=0}^n S(n,k) x(x-1)...(x-k+1). Useful for converting between polynomial bases.
- **Explicit formula**: S(n,k) = (1/k!) Σ_{i=0}^k (-1)^{k-i} C(k,i) i^n. Allows O(n log n) computation of an entire row using convolution (NTT).

## Optimization Tricks
1. **Precomputation**: For multiple queries with n ≤ few thousand, precompute DP table O(N²).
2. **Single row via NTT**: Compute S(n,0..n) in O(n log n) using explicit formula and polynomial multiplication.
3. **Modular inverses**: Precompute factorials and inverse factorials for O(1) combinatorial terms.
4. **Symmetry**: S(n,k) = 0 for k > n; S(n,0) = [n=0]; S(n,1) = S(n,n) = 1.
5. **Memory optimization**: Use rolling arrays for DP if only final row needed.

## Problem Transformations
- **Surjective functions**: Number of surjections from n-element set to k-element set = k!·S(n,k).
- **Grouping problems**: Often appear in problems where objects must be grouped into indistinguishable boxes with no empty boxes.
- **Polynomial coefficient conversion**: Converting between monomial basis and falling factorial basis involves Stirling numbers.
- **Bell numbers**: Sum over k gives total partitions (Bell numbers), which satisfy Dobiński's formula.

## Common Pitfalls
- Remember subsets are **unlabeled** (order doesn't matter). For labeled boxes, multiply by k!.
- Modulo operations: k·S(n-1,k) may overflow before mod; use modular multiplication.
- Base cases: S(0,0)=1, S(n,0)=0 for n>0, S(0,k)=0 for k>0.

## Advanced Applications
- **Stirling transform**: If a_n = Σ S(n,k) b_k, then b_n = Σ s(n,k) a_k where s(n,k) are first-kind Stirling numbers (signed).
- **Generating functions**: Exponential generating function: Σ S(n,k) x^n/n! = (e^x - 1)^k / k!.
- **Moments of Poisson distribution**: E[X^n] = Σ S(n,k) λ^k.