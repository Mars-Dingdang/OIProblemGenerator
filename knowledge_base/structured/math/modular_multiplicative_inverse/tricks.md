## Key Observations

1. **Existence Condition**: Inverse exists iff `gcd(a, m) = 1` (a and m are coprime).
2. **Uniqueness**: When exists, inverse is unique modulo m.
3. **Prime Modulus Advantage**: For prime modulus p, use Fermat's little theorem: `a^(-1) ≡ a^(p-2) mod p`.
4. **General Modulus**: For non-prime m, use extended Euclidean algorithm to solve `ax ≡ 1 mod m`.

## Optimizations

1. **Batch Processing**: Compute inverses for multiple numbers in O(n + log m) using prefix products:
   - Compute prefix products `S_i = a_1 * ... * a_i mod m`
   - Compute total product inverse `inv_S_n`
   - Backward pass: `inv_S_{i-1} = a_i * inv_S_i mod m`
   - Individual inverses: `inv_a_i = S_{i-1} * inv_S_i mod m`

2. **Linear Preprocessing**: For prime p, compute inverses 1..n in O(n) using recurrence:
   ```
   inv[i] = (p - p/i) * inv[p % i] % p
   ```
   This is crucial for factorial inverses in combinatorics.

3. **Negative Handling**: Always normalize inverse to `[0, m-1]` using `(x % m + m) % m`.

## Common Transformations

1. **Division to Multiplication**: Replace `a / b mod m` with `a * inv(b) mod m`.
2. **Fraction Reduction**: Compute `(a/b) mod m` as `a * inv(b) mod m`.
3. **Linear Equation Solving**: Solve `ax ≡ b mod m` as `x ≡ b * inv(a) mod m` when gcd(a,m)=1.
4. **Combination Formulas**: Precompute factorial inverses for `C(n,k) = n! * inv(k!) * inv((n-k)!) mod p`.

## Edge Cases

- When m=1, all numbers are congruent to 0, so inverse doesn't exist (except trivial case).
- For a=0, inverse never exists.
- For negative a, compute inverse of `(a mod m + m) % m`.

## Performance Notes

- Extended Euclidean is generally faster than exponentiation for single inverses.
- For repeated queries with same modulus, precompute inverses linearly.
- Batch method is optimal when you need inverses of all elements in an array.