## Key Observations
- **Convolution as Combination**: Multiplying OGFs corresponds to convolving sequences, i.e., combining counts from two independent choices.
- **Closed Forms**: Many sequences have simple closed-form OGFs (e.g., geometric: 1/(1 - p x), binomial: (1 + x)^m). Converting between series and closed forms simplifies algebra.
- **Linear Recurrences**: OGF of a linear recurrence satisfies a rational function P(x)/Q(x). Partial fraction decomposition yields explicit coefficients.
- **Shift & Derivative**: Multiplying by x shifts indices; differentiating relates to weighted sums (e.g., ∑ n a_n x^n).

## Common Transformations
1. **Geometric Series**: ∑_{n≥0} p^n x^n = 1/(1 - p x).
2. **Binomial Theorem**: ∑_{n≥0} C(m, n) x^n = (1 + x)^m.
3. **Negative Binomial**: ∑_{n≥0} C(m + n - 1, n) x^n = 1/(1 - x)^m.
4. **Even/Odd Extraction**: (F(x) + F(-x))/2 gives even terms; (F(x) - F(-x))/2 gives odd terms.

## Optimization Tips
- Use **FFT/NTT** for fast convolution O(n log n).
- For rational OGFs, compute coefficients via **linear recurrence** (Bostan–Mori algorithm) in O(k log k log n).
- Factor denominators to apply **partial fractions** for explicit formulas.
- In counting problems, model constraints as simple OGFs (e.g., "even" → 1/(1 - x^2), "≤ k" → (1 - x^{k+1})/(1 - x)).

## Problem Patterns
- **Counting with Constraints**: Multiply OGFs for each independent constraint (see "食物" example).
- **Solving Recurrences**: Convert recurrence to OGF equation, solve for closed form, extract coefficients.
- **Summation Identities**: Convolution of sequences corresponds to sums like ∑ a_i b_{n-i}.
- **Combinatorial Identities**: OGF manipulations can prove binomial identities (e.g., Vandermonde).