## Key Observations

1. **Fermat's Little Theorem**: For prime p and a not divisible by p, a^(p-1) ≡ 1 (mod p). This is the foundation for Fermat primality test.

2. **Euler's Theorem**: Generalization to any modulus m where gcd(a,m)=1: a^φ(m) ≡ 1 (mod m). φ(m) is Euler's totient function.

3. **Extended Euler Theorem**: Handles cases where gcd(a,m) ≠ 1:
   - If gcd(a,m)=1: reduce exponent modulo φ(m)
   - If gcd(a,m)≠1 and exponent < φ(m): compute directly
   - If gcd(a,m)≠1 and exponent ≥ φ(m): reduce exponent modulo φ(m) then add φ(m)

4. **Power Tower Reduction**: For computing a↑↑b mod m (tetration), recursively apply extended Euler theorem with φ(m), φ(φ(m)), etc. Since φ(φ(n)) ≤ n/2 for n≥2, recursion depth is O(log m).

5. **Implementation Trick**: Use helper function `mod(v, m)` that returns v % m + m when v ≥ m, to distinguish between "value < m" and "value ≥ m" cases needed for extended theorem.

## Common Problem Patterns

1. **Large Exponent Modular Exponentiation**: Given a^b mod m where b is huge (e.g., 10^1000), reduce b using φ(m) via extended Euler theorem.

2. **Power Tower Problems**: Compute a^(a^(a^...)) mod m by recursive reduction of modulus to φ(m), φ(φ(m)), etc.

3. **Primality Testing**: Fermat test checks if a^(n-1) ≡ 1 (mod n) for several a; if false for any a, n is composite (but beware of Carmichael numbers).

4. **Modular Inverse**: When modulus is prime, a^(-1) ≡ a^(p-2) mod p by Fermat's theorem.

## Optimization Notes

- Precompute φ values if multiple queries with same modulus range.
- For power towers, stop recursion when modulus becomes 1 (result is always 0 mod 1).
- Use binary exponentiation (fast pow) for all modular exponentiations.
- Watch for integer overflow: use long long for intermediate products in modular multiplication.

## Edge Cases

- a = 0, b = 0: 0^0 is typically defined as 1 in competitive programming contexts.
- m = 1: anything mod 1 is 0.
- b = 0: a^0 = 1 for any a (including 0 if defined as 1).
- When gcd(a,m)=1, exponent reduction works directly with φ(m).
- When gcd(a,m)≠1, need to check if exponent < φ(m) before reduction.