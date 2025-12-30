## Key Observations
- **Generating Functions**: A generating function is a formal power series where coefficients encode a sequence (e.g., combinatorial counts). Operations on generating functions correspond to manipulations on sequences (e.g., convolution for combinatorial sums).
- **Convolution via FFT/NTT**: Polynomial multiplication is essentially convolution of coefficient sequences. Using FFT (complex) or NTT (modular) reduces complexity from O(n²) to O(n log n).
- **Inversion Condition**: A formal power series f(x) has a multiplicative inverse iff its constant term f₀ is invertible in the coefficient ring (e.g., f₀ ≠ 0 in fields).
- **Composition**: Composing f(g(x)) is well-defined when g₀ = 0 (no constant term) to avoid infinite sums. Practical algorithms use "divide-and-conquer FFT" or O(n²) DP.
- **Modular Reduction**: Working modulo xⁿ truncates a power series to the first n terms. This is common in generating function problems to ignore higher-order terms.
- **Point‑Value Representation**: Evaluating a degree‑n polynomial at n+1 distinct points gives a point‑value representation. Conversion between coefficient and point‑value forms is done via FFT (evaluation) and inverse FFT (interpolation).
- **Lagrange Inversion**: For a formal power series f with f₀=0 and f₁≠0, the coefficients of its compositional inverse g (i.e., g(f(x)) = x) can be obtained via the Lagrange inversion formula: [xⁿ]g = (1/n) [xⁿ⁻¹] (x/f(x))ⁿ.
- **Polynomial GCD**: The Euclidean algorithm works for polynomials over a field. Half‑GCD gives O(n log² n) complexity.
- **Common Expansions**: Memorize standard Maclaurin series (e.g., exp(x), log(1+x), (1+x)ᵃ, sin/cos) to quickly manipulate generating functions.

## Optimization Patterns
- **Pre‑compute Roots of Unity**: For NTT, pre‑compute all primitive roots to avoid repeated exponentiation.
- **Newton’s Method for Inversion/Division**: Iteratively double the number of correct coefficients (from constant term upward) to achieve O(n log n) inversion, square‑root extraction, etc.
- **CDQ Divide‑and‑Conquer for Unknown Recurrences**: When a generating function satisfies a recurrence that involves its own convolution (e.g., in DP optimizations), use CDQ splitting to compute coefficients in O(n log² n).
- **Bostan–Mori for Linear Recurrences**: To extract the n‑th term of a rational generating function P(x)/Q(x), use Bostan–Mori algorithm in O(d log d log n) where d is the degree of Q.
- **Shifting via Multiplication by xᵏ**: Multiplying a generating function by xᵏ shifts the sequence indices (delays the sequence).
- **Differential Equations**: Sometimes a generating function satisfies a simple ODE; solving it can yield a closed form.

## Problem Transformation Patterns
1. **Combinatorial Counting → Coefficient Extraction**: The answer is often the coefficient of xⁿ in some constructed generating function.
2. **Recurrence Relations → Generating Function Equations**: Translate a recurrence into an equation for the generating function, solve algebraically, then extract coefficients.
3. **Convolution of Sequences → Polynomial Multiplication**: If the answer involves summing over products of two sequences, it’s a convolution; compute via FFT.
4. **Weighted Sums → Substitution**: Replace x with a constant (or another series) in a generating function to obtain weighted sums.
5. **Multivariate Generating Functions**: Use multiple variables to track several parameters simultaneously (e.g., one variable for size, another for cost).
6. **Sieve‑like Counting → Inclusion‑Exclusion with Generating Functions**: Express inclusion‑exclusion as alternating sums of simpler generating functions.
7. **Polynomial Modulo (xⁿ‑1) → Cyclic Convolution**: Equivalent to convolution under cyclic indices, handled by DFT/FFT.
8. **Kronecker Substitution for Integer Multiplication**: Multiply two polynomials with large integer coefficients by evaluating at a large power of 10 (or 2), multiplying the resulting huge integers, then interpreting back.