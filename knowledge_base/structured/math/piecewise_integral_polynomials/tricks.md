# 浅谈连续型随机变量的相关问题

**Author:** 周桓毅

### Key Ideas and Tricks

- **Transformation via Continuous Random Variables**: For problems with only partial order constraints (e.g., $x_i < x_j$), one can transform combinatorial counting over permutations into probabilistic integration over continuous uniform variables in $[0,1]$, leveraging symmetry and uniform distribution properties.

- **Integer-Fractional Splitting (Method A)**: In integer difference constraint problems ($x_i - x_j \geq c$, $c \in \mathbb{Z}$), split each variable $x_i = y_i + z_i$ into integer part $y_i = \lfloor x_i \rfloor$ and fractional part $z_i \in [0,1)$. Once integer parts are fixed, constraints reduce to inequalities on $z_i$, which become partial orders — solvable using permutation-based DP or inclusion-exclusion.

- **Constraint Elimination Tree (Method B)**: By successively eliminating variables using tightest constraints, the feasible region becomes a tree-structured set of bounds. A tree-DP computes the volume as a piecewise polynomial, achieving $O(2^n n! n^2)$ time. Suitable for small $n$, but impractical for larger instances.

- **Integral Polynomial Operator (I)**: Defined as $If(x) = \sum a_i i! x^i$ for polynomial $f(x) = \sum a_i x^i$. This operator linearizes operations:
  - Linearity: $I(f + g) = If + Ig$, $I(kf) = kIf$
  - Convolution-like operation (class convolution): $I(f * g) = (If)(Ig)$, where class convolution is defined as:
    $$
    (f * g)(x) = \int_0^x f'(y)g(x-y)\,dy + f(0)g(x)
    $$
  This models merging two segments with unique decomposition (end of first segment must be marked).

- **Piecewise Integral Polynomials**: Extend integral polynomials to piecewise form: $F(x) = \sum f_i(x - l_i)[x \geq l_i]$, then apply $I$ per segment. Enables modeling complex measure functions arising from geometric or coverage constraints.

- **Multivariate Generating Functions**: Use generating functions in multiple variables (e.g., $x$: size, $y$: count, $z$: shift/segment key) to encode combinatorial structures. Operations like $(1 - G)^{-1}$ model unconnected unions (analogous to generating function inversion), while $G/(1-G)$ handles connected components.

- **Efficient Computation via Interpolation**: Due to sparsity and bounded degrees (e.g., degree in $y$ up to $n$, in $z$ up to $\lfloor n/2 \rfloor$), use Lagrange interpolation on selected points instead of full polynomial inversion. Reduces effective dimensionality and avoids high constant factors from symbolic manipulation.

- **Exponential Weighted Integral Transform (Essence of I)**: The integral polynomial operator $I$ is a special case of a more general transform:
  $$
  Ef(x) = \int_0^\infty f(xy)e^{-y}\,dy
  $$
  Which satisfies $E(f * g) = (Ef)(Eg)$, showing that $I \equiv E$ when $f$ is a polynomial. This reveals the analytic foundation behind the algebraic tricks.

- **Nonlinear Applications**: The framework extends beyond linear constraints. Example: computing $\Pr(\sum x_i^2 \leq 1)$ uses the same transform to derive high-dimensional ball volumes via gamma functions.

- **Volume-to-Probability Conversion**: After computing total measure (volume), divide by total space volume (e.g., $m^n$ for $n$ variables in $[0,m]$) to get probability.

- **Handling Circularity (Arcs on a Circle)**: Fix a point (e.g., 0), consider uncovered cases, break circle at gap, convert to line coverage problem. Use connected component analysis across arcs, weighted by gap length.

- **Avoiding Enumeration Blowup**: Instead of enumerating all permutations of fractional parts ($O((n-1)!)$), embed ordering into DP state using ranks or use subset convolution to manage dependencies efficiently.