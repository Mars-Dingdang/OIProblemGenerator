## Key Observations
- **Symbolic method** translates combinatorial constructions directly into generating function operations: union (`+`), product (`×`), sequence (`SEQ`), multiset (`MSET`), powerset (`PSET`), cycle (`CYC`).
- **OGF for unlabeled systems**: `A(z) = Σ a_n z^n` where `a_n` counts objects of size `n`.
- **Neutral class** `ℰ` has OGF `1`, atom class `𝒵` has OGF `z`.

## Constructions and OGFs
- **Union (`𝒜 + ℬ`)**: OGF = `A(z) + B(z)`.
- **Product (`𝒜 × ℬ`)**: OGF = `A(z) · B(z)`.
- **Sequence (`SEQ(𝒜)`)**: OGF = `1 / (1 - A(z))`, requires `𝒜` has no size‑0 objects.
- **Multiset (`MSET(𝒜)`)**: OGF = `exp( Σ_{k≥1} A(z^k) / k )` (Euler transform).
- **Powerset (`PSET(𝒜)`)**: OGF = `exp( Σ_{k≥1} (-1)^{k-1} A(z^k) / k )`.
- **Cycle (`CYC(𝒜)`)**: OGF = `Σ_{k≥1} φ(k)/k · ln(1 / (1 - A(z^k)))`.

## Restricted Constructions
- `SEQ_k(𝒜)` → OGF = `A(z)^k`.
- `MSET_k(𝒜)` → OGF is a symmetric polynomial in `A(z), A(z^2), …, A(z^k)`.
- Useful formulas:
  - `MSET2(𝒜)`: `(A(z)^2 + A(z^2)) / 2`
  - `PSET2(𝒜)`: `(A(z)^2 - A(z^2)) / 2`
  - `CYC2(𝒜)`: `(A(z)^2 + A(z^2)) / 2`
  - `MSET3(𝒜)`: `(A(z)^3 + 3A(z)A(z^2) + 2A(z^3)) / 6`

## Optimization Tricks
- Use **generating function exponentiation** via Newton’s method or polynomial `exp/log` for `MSET`/`PSET`.
- For partition‑like problems, the **Euler transform** can be computed in `O(n log n)` using divisor sums.
- **Labeled vs. unlabeled**: switch between OGF (unlabeled) and EGF (labeled) as needed.
- **Composition of constructions** corresponds to composition of generating functions (e.g., trees as `𝒯 = 𝒵 × SEQ(𝒯)` gives Catalan OGF).
- In contests, often only the first `n` coefficients are needed; compute via DP or polynomial operations modulo `x^{n+1}`.

## Common Problem Patterns
1. **Integer partitions**: `MSET(ℐ)` where `ℐ = SEQ_{≥1}(𝒵)`.
2. **Unlabeled rooted trees**: `𝒯 = 𝒵 × MSET(𝒯)` (OEIS A000081).
3. **Unlabeled unrooted trees**: Otter’s formula `T(z) - T(z)^2/2 + T(z^2)/2`.
4. **Subset sums**: `PSET(𝒜)` where objects have weights.
5. **Sequences with restrictions**: use `SEQ_{k..m}(𝒜)` and extract coefficients via `[u^k] 1/(1 - u A(z))`.

## Implementation Notes
- Use NTT/FFT for polynomial multiplication in `O(n log n)`.
- Precompute needed transforms (`A(z^k)` for `k` up to `n`) efficiently.
- For large `n`, use **linear recurrences** (Berlekamp‑Massey) if the generating function is rational.