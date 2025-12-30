## Key Observations

1. **Divisibility properties**:
   - If a|b and b|c then a|c (transitivity)
   - If a|b and a|c then a|(xb + yc) for any integers x, y
   - a|b if and only if a|(b mod a) - useful for reducing problems

2. **GCD/LCM relationships**:
   - gcd(a,b) * lcm(a,b) = |a*b|
   - gcd(ma, mb) = |m| * gcd(a,b)
   - lcm(ma, mb) = |m| * lcm(a,b)
   - gcd(a,b) = gcd(a, b mod a) - basis of Euclidean algorithm

3. **Modular arithmetic**:
   - (a ± b) mod m = ((a mod m) ± (b mod m)) mod m
   - (a * b) mod m = ((a mod m) * (b mod m)) mod m
   - But division requires modular inverse when m is prime
   - a ≡ b (mod m) implies (a, m) = (b, m)

4. **Prime number patterns**:
   - All primes > 3 are of form 6n±1
   - If p is prime and p|ab, then p|a or p|b (Euclid's lemma)
   - Fundamental theorem of arithmetic: every integer has unique prime factorization

5. **Residue systems**:
   - Complete residue system mod m has exactly m elements
   - Reduced residue system mod m has φ(m) elements (coprime to m)
   - Chinese Remainder Theorem: system of congruences with coprime moduli has unique solution mod product

6. **Number-theoretic functions**:
   - Multiplicative functions: f(ab)=f(a)f(b) when gcd(a,b)=1
   - Euler's φ, Möbius μ, divisor functions are multiplicative
   - This allows computation via prime factorization

## Common Problem Transformations

1. **Divisibility to congruence**: a|b ↔ b ≡ 0 (mod a)
2. **GCD problems to linear combinations**: gcd(a,b) = smallest positive integer of form ax+by
3. **LCM problems**: often combine with gcd using a*b = gcd(a,b)*lcm(a,b)
4. **Modular equations**: ax ≡ b (mod m) → solve ax + my = b using extended Euclidean algorithm
5. **Prime factorization**: many problems reduce to analyzing prime exponents
6. **Chinese Remainder Theorem**: break large modulus into smaller coprime moduli

## Optimization Techniques

1. **Sieve for primes**: O(n log log n) for all primes up to n
2. **Precompute φ(n)**: using sieve in O(n log log n)
3. **Binary GCD**: faster for large numbers, avoids modulo operation
4. **Modular exponentiation**: O(log n) using binary exponentiation
5. **Wilson's theorem**: (p-1)! ≡ -1 (mod p) for prime p
6. **Fermat's little theorem**: a^(p-1) ≡ 1 (mod p) for prime p and a not divisible by p