## Key Observations
- **ν_p(n) definition**: ν_p(n) is the exponent of prime p in the prime factorization of n (p-adic valuation).
- **Case splitting**: LTE is divided into three main cases based on the prime p and the parity of n.
  - **Part 1**: For any prime p with p ∤ n, if p | (x - y) then ν_p(x^n - y^n) = ν_p(x - y). If p | (x + y) and n is odd, then ν_p(x^n + y^n) = ν_p(x + y).
  - **Part 2**: For odd prime p, if p | (x - y) then ν_p(x^n - y^n) = ν_p(x - y) + ν_p(n). If p | (x + y) and n is odd, then ν_p(x^n + y^n) = ν_p(x + y) + ν_p(n).
  - **Part 3**: For p = 2 and 2 | (x - y):
    - If n is odd: ν_2(x^n - y^n) = ν_2(x - y).
    - If n is even: ν_2(x^n - y^n) = ν_2(x - y) + ν_2(x + y) + ν_2(n) - 1.
    - Special case: If 4 | (x - y), then ν_2(x + y) = 1 and ν_2(x^n - y^n) = ν_2(x - y) + ν_2(n).

## Common Problem Transformations
- **Reducing exponents**: Use LTE to simplify expressions like x^n ± y^n modulo p^k by focusing on the p-adic valuation.
- **Divisibility proofs**: To prove p^a divides x^n ± y^n, show that ν_p(x^n ± y^n) ≥ a using LTE conditions.
- **Handling even primes**: Pay special attention to p = 2 due to its unique behavior (e.g., the extra ν_2(x + y) term).

## Optimization Tips
- **Precompute ν_p(n)**: For multiple queries, precompute ν_p for all relevant n using sieve-like techniques.
- **Condition checking**: Always verify preconditions (p ∤ x, p ∤ y, and divisibility of x ± y by p) before applying LTE.
- **Binary exponentiation**: When computing x^n or y^n modulo p^k for verification, use fast exponentiation to avoid overflow.

## Related Theorems
- **Chinese Remainder Theorem (CRT)**: Often combined with LTE to solve congruences modulo composite numbers.
- **Euler's theorem/Fermat's little theorem**: Useful for reducing exponents modulo p when p ∤ x or p ∤ y.
- **Binomial theorem**: Used in the proof of LTE for the case n = p.

## Common Pitfalls
- **Missing conditions**: Applying LTE without ensuring p ∤ x and p ∤ y leads to incorrect results.
- **Ignoring parity**: For p = 2, the formula changes drastically based on whether n is even or odd.
- **Overlooking special cases**: The case 4 | (x - y) for p = 2 simplifies the formula; forgetting this can complicate solutions.