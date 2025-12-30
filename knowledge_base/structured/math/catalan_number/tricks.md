## Key Observations

1. **Recursive Structure**: Many Catalan problems can be split into two independent subproblems by fixing a "boundary" (e.g., first return to diagonal, root of a tree, first matched parenthesis). This leads to the convolution recurrence: C_n = Σ C_i * C_{n-1-i}.

2. **Bijections**: The classic problems (parentheses, stack sequences, binary trees, triangulations, etc.) are all in bijection. Recognizing that a new problem is equivalent to one of these can immediately give the Catalan answer.

3. **Explicit Formulas**:
   - `C_n = binom(2n, n) - binom(2n, n+1)` is useful for proofs via reflection principle.
   - `C_n = (4n-2)/(n+1) * C_{n-1}` is efficient for sequential computation (O(n) time, O(1) space).
   - `C_n ≈ 4^n / (n^(3/2) * sqrt(π))` for asymptotic behavior.

4. **Modular Arithmetic**: When computing Catalan numbers modulo a prime, use factorials and modular inverses (or Lucas theorem). The recurrence `C_n = (4n-2)/(n+1) * C_{n-1}` requires modular inverse of (n+1).

5. **Generalizations**:
   - **k‑Catalan**: Number of ways to parenthesize a product of n+1 factors using a k‑ary operation.
   - **Narayana numbers**: Count Dyck paths with a given number of peaks.
   - **Motzkin numbers**: Like Catalan but allow flat steps.

6. **DP with Catalan**: In some problems, the state transition is exactly a Catalan recurrence. For example, counting full binary trees with n leaves.

7. **Avoiding Overflow**: When n is large, use modular arithmetic or big integers. The iterative recurrence is more stable than computing huge binomials directly.

8. **Generating Function**: The ordinary generating function satisfies C(x) = 1 + x C(x)^2, which solves to C(x) = (1 - sqrt(1-4x))/(2x). Useful for analytic combinatorics.

9. **Probability Interpretation**: The probability that a random Dyck path of length 2n never goes below the diagonal is C_n / binom(2n, n) ≈ 1/(n+1).

10. **Catalan’s Triangle**: A triangular array where entry (n,k) counts Dyck paths of length 2n with k peaks. Useful for refined counting.