## Key Observations
- **Norm is multiplicative**: For quadratic integers α and β, N(αβ) = N(α)N(β). This allows reduction of problems to integer factorization.
- **Units are norm ±1**: In quadratic integer rings, units (invertible elements) are exactly elements with norm ±1.
- **Gaussian integers**: Z[i] is a Euclidean domain with norm N(a+bi)=a²+b². Primes in Z are:
  - Inert if p ≡ 3 (mod 4) (remain prime)
  - Split if p ≡ 1 (mod 4) (factor as (a+bi)(a-bi))
  - Ramified if p = 2 (factor as (1+i)²)
- **Eisenstein integers**: Z[ω] with ω = (-1+√-3)/2 has norm N(a+bω)=a²-ab+b². Primes in Z are:
  - Inert if p ≡ 2 (mod 3)
  - Split if p ≡ 1 (mod 3)
  - Ramified if p = 3

## Optimization Techniques
1. **Circle point counting**: For x²+y²=n, solutions exist iff all primes ≡3 (mod 4) in n's factorization have even exponents. Number of solutions is 4∑_{d|n} χ₄₋₃(d) where χ₄₋₃ is Dirichlet character mod 4.
2. **Pythagorean triple generation**: All primitive triples (x,y,z) with x²+y²=z² and gcd(x,y,z)=1 are given by:
   x = m²-n², y = 2mn, z = m²+n² where m>n>0, gcd(m,n)=1, and m-n odd.
3. **Elliptic point counting**: For x²-xy+y²=n (Eisenstein norm), solutions exist iff all primes ≡2 (mod 3) have even exponents. Number of solutions is 6∑_{d|n} χ₃₋₂(d).
4. **Matrix representation**: Quadratic integer a+b√d can be represented as matrix [[a, db], [b, a]], with operations corresponding to integer operations.

## Problem Transformation Patterns
1. **Diophantine to factorization**: Equations like x²+y²=n become N(x+yi)=n in Gaussian integers.
2. **Pell equation connection**: Units in real quadratic fields correspond to solutions of Pell's equation u²-dv²=±1.
3. **Ideal factorization**: When unique factorization fails in quadratic integer rings, use ideal factorization into prime ideals.
4. **Variable substitution**: For x²+3y²=n, substitute x=(u+v)/2, y=(u-v)/2 to get u²-uv+v²=n (Eisenstein norm).

## Common Pitfalls
- **Not all quadratic rings are UFD**: e.g., Z[√-5] lacks unique factorization (9=3·3=(2+√-5)(2-√-5)).
- **Unit structure varies**: Gaussian integers have 4 units (±1, ±i), Eisenstein integers have 6 (±1, ±ω, ±ω²).
- **Care with ω definition**: For Eisenstein integers, standard ω = (-1+√-3)/2, not (1+√-3)/2.
- **Even/odd parity matters**: In x²+3y²=n with n odd, only 1/3 of Eisenstein integer solutions yield integer (x,y) pairs.