## Key Observations

1. **Euler's Criterion**: For odd prime p, a is quadratic residue iff a^((p-1)/2) ≡ 1 (mod p). This gives O(log p) test.

2. **Legendre Symbol Properties**:
   - (ab/p) = (a/p)(b/p) (complete multiplicativity)
   - (-1/p) = (-1)^((p-1)/2) = 1 if p ≡ 1 mod 4, -1 if p ≡ 3 mod 4
   - (2/p) = (-1)^((p²-1)/8) = 1 if p ≡ ±1 mod 8, -1 if p ≡ ±3 mod 8

3. **Quadratic Reciprocity**: For distinct odd primes p, q:
   (p/q)(q/p) = (-1)^((p-1)(q-1)/4)
   This allows efficient computation of Legendre symbols via Euclidean-like reduction.

## Algorithm Selection

### Special Cases:
- **p ≡ 3 mod 4**: Simple formula: x ≡ a^((p+1)/4) mod p
- **p ≡ 5 mod 8**: Atkin's algorithm
- **General odd prime**: Cipolla or Tonelli-Shanks

### Cipolla Algorithm:
- Find r such that r² - a is quadratic non-residue (expected 2 tries)
- Compute (r - √(r²-a))^((p+1)/2) in extension field F_p[√(r²-a)]
- Result lies in F_p (coefficient of √ term is 0)
- Complexity: O(log p) field operations

### Tonelli-Shanks:
- Based on discrete logarithms in cyclic group of order 2^n
- More complex but deterministic after finding non-residue
- Good when p-1 has high power of 2

## Optimizations

1. **Randomization**: Both algorithms need random quadratic non-residue. Expected 2 tries.
2. **Precomputation**: For fixed p, precompute a non-residue.
3. **Early Exit**: Check Euler criterion first to avoid work when no solution exists.
4. **Field Arithmetic**: Optimize multiplication in extension field for Cipolla.

## Problem Transformations

1. **Composite Modulus**: Use Chinese Remainder Theorem to reduce to prime powers.
2. **Prime Power Modulus**: Hensel lifting from solution modulo p to p^k.
3. **General Quadratic Equation**: Complete square: ax² + bx + c ≡ 0 → (2ax + b)² ≡ b² - 4ac.
4. **Finding Quadratic Non-residues**: Random search works; deterministic methods exist but are slower.

## Common Pitfalls

- Remember to handle a ≡ 0 separately
- Check that p is odd prime (algorithm assumes this)
- For p = 2, trivial: x ≡ a mod 2
- Jacobi symbol (a/m) for composite m doesn't indicate quadratic residuosity, only that (a/p) = -1 for some prime factor p

## Extensions

- **Jacobi Symbol**: Generalization to odd composite moduli
- **k-th Residues**: Higher power residues using primitive roots
- **Elliptic Curve Point Counting**: Uses quadratic residue computations
- **Primality Testing**: Quadratic residue tests in some primality proofs