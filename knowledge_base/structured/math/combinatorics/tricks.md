## Key Observations & Tricks

### 1. **Precomputation of Factorials & Inverses**
- Precompute factorials and inverse factorials up to N in O(N) time.
- Use Fermat's little theorem for modular inverses when MOD is prime.

### 2. **Stars and Bars Transformations**
- **Positive solutions**: x₁ + … + xₖ = n, xᵢ ≥ 1 → C(n-1, k-1).
- **Non‑negative solutions**: x₁ + … + xₖ = n, xᵢ ≥ 0 → C(n+k-1, k-1).
- **Lower bounds**: If xᵢ ≥ aᵢ, substitute yᵢ = xᵢ - aᵢ, then use non‑negative formula with n' = n - Σaᵢ.

### 3. **Inclusion‑Exclusion for Bounded Variables**
- For x₁ + … + xₖ = r with xᵢ ≤ nᵢ, use inclusion‑exclusion over subsets of violated bounds.
- Number of solutions = Σ_{S ⊆ [k]} (-1)^{|S|} C(k + r - 1 - Σ_{i∈S} (nᵢ+1), k-1).

### 4. **Circular Permutations**
- n distinct objects arranged in a circle: (n-1)!.
- Partial circular permutations of r out of n: n! / (r·(n-r)!).

### 5. **Multinomial Coefficients**
- Number of ways to partition n items into groups of sizes n₁, n₂, …, nₖ: n! / (n₁! n₂! … nₖ!).
- Equivalent to coefficient of x₁^{n₁}…xₖ^{nₖ} in (x₁+…+xₖ)ⁿ.

### 6. **Binomial Inversion**
- If gₙ = Σ_{i=0}ⁿ C(n,i) fᵢ, then fₙ = Σ_{i=0}ⁿ (-1)^{n-i} C(n,i) gᵢ.
- Useful for transforming between “exactly k” and “at most k” counts.

### 7. **Common Identities**
- **Symmetry**: C(n,k) = C(n,n-k).
- **Pascal’s rule**: C(n,k) = C(n-1,k) + C(n-1,k-1).
- **Vandermonde’s identity**: Σ_{i=0}ᵏ C(n,i) C(m,k-i) = C(n+m,k).
- **Hockey‑stick identity**: Σ_{i=r}ⁿ C(i,r) = C(n+1, r+1).

### 8. **Handling Large n, k**
- Use Lucas theorem when MOD is small prime.
- For non‑prime MOD, factorize and use Chinese remainder theorem.
- For very large n (e.g., n ≤ 10¹⁸) but small k, compute C(n,k) directly as n·(n-1)…(n-k+1) / k!.

### 9. **Generating Functions**
- (1+x)ⁿ generates binomial coefficients.
- (1+x+x²+…)ᵏ generates stars‑and‑bars counts.
- Product of (1+x+…+x^{nᵢ}) gives bounded variable counts.

### 10. **Derangements & Permutations with Restrictions**
- Derangements !n = n! Σ_{i=0}ⁿ (-1)ⁱ / i!.
- Use inclusion‑exclusion for “no fixed points” or “forbidden positions” problems.

### 11. **Catalan Numbers & Dyck Paths**
- Cₙ = C(2n,n) / (n+1) counts balanced parentheses, binary trees, etc.
- Often appear in combinatorial structures with a “balance” constraint.

### 12. **Burnside’s Lemma for Symmetry**
- Count distinct colorings under group actions (rotations, reflections).
- Number of orbits = (1/|G|) Σ_{g∈G} fixed(g).

### 13. **Pigeonhole Principle**
- Simple but powerful: if n items are placed into m boxes and n > m, some box contains at least ⌈n/m⌉ items.

### 14. **Combinatorial Arguments**
- Instead of algebraic manipulation, often a bijective or double‑counting proof is shorter and more insightful.
- Example: C(n,k) counts k‑subsets directly, while the formula n!/(k!(n-k)!) is derived from arranging then un‑arranging.

### 15. **Modular Arithmetic Tips**
- Precompute factorials and inverse factorials modulo prime p.
- Use Lucas theorem for large n, small p.
- For composite modulus, compute modulo each prime power then combine with CRT.