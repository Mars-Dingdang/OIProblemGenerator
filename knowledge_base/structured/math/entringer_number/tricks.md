## Key Observations
- **Entringer number E(n, k)** counts alternating permutations of {0, 1, ..., n} that start with k and follow the pattern: first element k, next element < k, then >, then <, etc. (alternating up/down).
- **Recurrence**: E(n, k) = E(n, k-1) + E(n-1, n-k). This allows O(n²) DP computation.
- **Zigzag numbers A_n** (Euler zigzag numbers) count all alternating permutations of size n (starting either up or down). They satisfy A_n = E(n, n).
- **Seidel–Entringer–Arnold triangle** arranges E(n, k) in a zigzag (ox-plowing) order that matches the recurrence visually.

## Relations and Identities
- **Generating function**: ∑_{n≥0} A_n xⁿ/n! = sec x + tan x.
- **Even indices**: A_{2n} = (-1)ⁿ E_{2n} where E_{2n} are Euler (secant) numbers (OEIS A000364).
- **Odd indices**: A_{2n+1} = (-1)ⁿ T_{2n+1} where T_{2n+1} are tangent numbers (OEIS A000182), related to Bernoulli numbers.
- **Recurrence for A_n**: 2 A_{n+1} = ∑_{k=0}^{n} C(n, k) A_k A_{n-k}.

## Problem Transformations
- Counting **alternating permutations** with a fixed first element → directly Entringer numbers.
- Counting **zigzag permutations** (alternating or reverse alternating) → zigzag numbers A_n.
- If a problem asks for permutations with alternating comparisons (e.g., in a tournament or ranking), consider mapping to Entringer numbers.
- The DP recurrence can be used to compute large n modulo a prime using O(n²) time and O(n) space (rolling array).

## Optimizations
- Use **modular arithmetic** for large n since numbers grow quickly.
- Compute **E(n, k)** for all k up to n in O(n) per row using the recurrence.
- For **zigzag numbers only**, you can compute A_n via the recurrence 2A_{n+1} = ∑ C(n,k) A_k A_{n-k} in O(n²) without computing the full Entringer table.
- Precompute factorials and inverses modulo MOD to compute binomial coefficients quickly.

## Common Pitfalls
- Remember that **E(n,0)=0** for n≥1, but E(0,0)=1.
- Zigzag permutations include both alternating (c₁ > c₂ < c₃ > ...) and reverse alternating (c₁ < c₂ > c₃ < ...) patterns.
- The generating function sec x + tan x gives the exponential generating function for A_n, not the ordinary one.