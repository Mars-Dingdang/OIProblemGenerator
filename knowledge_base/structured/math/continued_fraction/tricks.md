## Key Observations

1. **Connection with Euclidean Algorithm**: Computing continued fraction for rational p/q is identical to Euclidean algorithm steps.

2. **Best Approximations**: Convergents provide the best rational approximations:
   - Every convergent is a best approximation of the second kind.
   - Every best approximation of the first kind is an intermediate fraction.

3. **Error Bounds**: For convergent p_k/q_k of x:
   - |x - p_k/q_k| < 1/(q_k * q_{k+1}) ≤ 1/(q_k²)
   - |p_k * q_{k-1} - p_{k-1} * q_k| = 1 (determinant formula)

4. **Alternating Property**: Even-indexed convergents are below x, odd-indexed are above x.

5. **Fast Growth**: Denominators q_k grow at least as fast as Fibonacci numbers.

## Optimization Patterns

1. **Intermediate Fractions**: For better approximations between convergents, use:
   - x_{k,t} = (t*p_k + p_{k-1})/(t*q_k + q_{k-1}) for 0 ≤ t ≤ a_{k+1}
   - These are first-kind best approximations when t > a_{k+1}/2

2. **Hurwitz Theorem**: For any irrational x, infinitely many convergents satisfy |x - p/q| < 1/(√5 * q²)

3. **Diophantine Equations**: Solve Ax + By = C by:
   - Compute continued fraction of A/B
   - Use last two convergents to find particular solution
   - All solutions: x = x₀ + (B/g)*t, y = y₀ - (A/g)*t

4. **Quadratic Irrationals**: Periodic continued fractions correspond to quadratic irrationals.

## Common Transformations

1. **Rational to Continued Fraction**: Use Euclidean algorithm.
2. **Continued Fraction to Rational**: Use convergent recurrence.
3. **Finding Best Denominator-Bounded Approximation**: Generate convergents until denominator exceeds bound, then consider intermediate fractions.
4. **Comparing Irrationals**: Compare continued fraction expansions lexicographically.

## Implementation Notes

- Use `long long` for numerators/denominators as they grow exponentially.
- For quadratic irrationals, period detection can optimize infinite expansions.
- The determinant formula provides quick verification of convergent correctness.