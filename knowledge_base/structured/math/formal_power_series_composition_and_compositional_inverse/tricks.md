## Key Observations

1. **Lagrange Inversion**: For formal power series \(f(x), g(x)\) with \(f(g(x)) = g(f(x)) = x\), we have:
   \[
   [x^n] \Phi(f(x)) = [x^{n-1}] \Phi'(x) \left(\frac{x}{g(x)}\right)^n
   \]
   This allows computing coefficients of compositional inverses.

2. **Kinoshita–Li Algorithm**: Reduces composition to computing \([y^0] \frac{f(y^{-1})}{1 - y \cdot g(x)}\) modulo \(x^n\). Uses recursion with halving of \(x\)-degree and doubling of \(y\)-degree, achieving \(O(M(n) \log n)\) time.

3. **Handling g(0) ≠ 0**: Apply Taylor shift: compute \(F(x) = f(x + g(0))\) and \(G(x) = g(x) - g(0)\), then compute \(F(G(x))\).

4. **Power Projection**: General problem: compute \([x^{n-1}] \frac{P(x,y)}{Q(x,y)}\) modulo \(y^m\). Solved by recursively reducing \(n\) via parity separation and using \(Q(x,y)Q(-x,y)\) to eliminate odd powers in \(x\).

5. **Kronecker Substitution**: For bivariate polynomial multiplication, substitute \(y \mapsto x^N\) with sufficiently large \(N\) to avoid coefficient mixing, reducing to univariate multiplication.

## Common Transformations

- **Elementary Functions via Composition**:
  - Inverse: \(g^{-1} = 1 + (1-g) + (1-g)^2 + \cdots\) (requires \(g(0)=1\))
  - Logarithm: \(\log g = -\frac{1-g}{1} - \frac{(1-g)^2}{2} - \cdots\) (requires \(g(0)=1\))
  - Exponential: \(\exp g = 1 + \frac{g}{1!} + \frac{g^2}{2!} + \cdots\) (requires \(g(0)=0\))
  - Power: \(g^e = 1 + e(g-1) + \frac{e(e-1)}{2!}(g-1)^2 + \cdots\) (requires \(g(0)=1\))

- **Compositional Inverse via Lagrange Inversion**:
  \[
  [x^{n-1}] f(x)^k = \frac{k}{n-1} [x^{n-1-k}] \left(\frac{g(x)}{x}\right)^{-(n-1)}
  \]
  Compute for \(k = 0,1,\dots,n-1\) to recover \(g(x)\).

## Optimizations

1. **Avoid Full Inverse Computation**: In recursive steps, \(Q(0,y)^{-1}\) can be derived directly without general power series inversion.
2. **Coefficient Pruning**: Only keep \(y\)-coefficients that contribute to the final \(y^0\) term.
3. **FFT Acceleration**: Use NTT/FFT for polynomial multiplications, with Kronecker substitution for bivariate cases.
4. **Even-Odd Separation**: Exploit symmetry in \(Q(x,y)Q(-x,y)\) to reduce problem size by half in each recursion.

## Implementation Notes

- Ensure \(g(0) = 0\) for base composition algorithm; handle nonzero constant term via Taylor shift.
- For compositional inverse, require \(f'(0) \neq 0\) (otherwise inverse doesn't exist as formal power series).
- Use iterative FFT with precomputed roots for better constant factors.
- The algorithm works over any field where FFT is available (e.g., \(\mathbb{F}_{998244353}\)).