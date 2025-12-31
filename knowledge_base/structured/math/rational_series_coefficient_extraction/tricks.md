# 浅谈一类提取有理分式系数的方法

**Author:** 黄建恒

## Key Ideas and Tricks

### 1. **From Rational Generating Functions to Closed Forms**
- A sequence $ f_n $ satisfies a linear recurrence if and only if its generating function $ F(x) = \sum f_n x^n $ is a rational function $ P(x)/Q(x) $.
- By factoring $ Q(x) $ and performing **partial fraction decomposition**, $ F(x) $ can be written as:
  $$
  F(x) = \sum_{i=1}^l \frac{P_i(x)}{(1 - \xi_i^{-1}x)^{d_i}}
  $$
  where $ \xi_i $ are the (possibly complex) roots of $ Q(x) = 0 $, each with multiplicity $ d_i $.
- This leads to a closed-form expression:
  $$
  f_n = \sum_{i=1}^l P_i(n) \xi_i^{-n}
  $$
  where $ \deg P_i < d_i $. Thus, the asymptotics are dominated by the root(s) with smallest modulus.

### 2. **Asymptotic Analysis via Dominant Root**
- When analyzing growth rates (e.g., time complexity), only the root $ \xi $ of $ Q(x)=0 $ with minimal absolute value matters.
- If all other roots have larger moduli, their contributions vanish exponentially faster.
- Example: For $ T(n) = T(n-1) + T(n-3) + 1 $, the characteristic equation $ 1 - x - x^3 = 0 $ has one real root $ \xi \approx 0.682 $, so $ f_n \sim c \cdot \xi^{-n} \approx 1.456^n $.

### 3. **Puiseux Expansions and Diagonals of Bivariate Rational Series**
- For bivariate rational functions $ F(x,y) $, the diagonal $ \text{diag} F = \sum f_{n,n} x^n $ is **algebraic** (by Deligne's theorem / Puiseux’s theorem).
- Technique:
  - Substitute $ x \to x/y $, forming $ G(x,y) = F(x/y, y) $, then extract $ [y^0]G(x,y) $.
  - Factor the denominator in $ y $: $ Q(x,y) = \prod (y - \xi_i)^{d_i} $, where $ \xi_i \in K^{\text{fra}}((x)) $ (Puiseux series).
  - Perform partial fractions over these algebraic roots.
  - Use binomial expansions:
    $$
    \frac{1}{(1 - \alpha y^{-1})^c} = \sum_k \binom{c+k-1}{c-1} \alpha^k y^{-k},\quad
    \frac{1}{(1 - \beta^{-1} y)^d} = \sum_k \binom{d+k-1}{d-1} \beta^{-k} y^k
    $$
  - Extract $ [y^0] $ term-by-term.

### 4. **Handling Algebraic Roots Efficiently**
- In practice, instead of symbolic manipulation, maintain expressions like $ A + B\sqrt{\Delta} $ under field extensions.
- Multiplication and inversion rules allow recursive updates when raising terms like $ \beta^{-1} $ to powers.
- Enables efficient computation of $ [x^n y^{kn+b}]F(x,y) $ via recurrence or fast power methods.

### 5. **Combination with Lagrange Inversion**
- When dealing with implicitly defined generating functions (e.g., $ u = F(x, xy) $), use **Lagrange inversion** to extract coefficients.
- Standard form:
  $$
  [x^n] H(F^{-1}(x)) = \frac{1}{n}[x^{n-1}]H'(x)\left(\frac{x}{F(x)}\right)^n
  $$
- Useful when combined with algebraic structure derived from diagonal extraction.

### 6. **Reduction to Prefix Sums of Binomial Coefficients**
- Many final answers reduce to sums like $ \sum_{i=0}^n \binom{m+n+1}{i} $, which are prefix sums of binomial coefficients.
- These can be handled efficiently using Mo's algorithm or precomputation if queries are offline.

### 7. **Practical Implementation Tips**
- Use Berlekamp-Massey to recover shortest linear recurrence from initial terms when closed form is hard.
- Use Newton iteration or NTT-based techniques for high-degree polynomial operations (e.g., $ 1/\sqrt{\Delta} $).
- Matrix exponentiation works well when state dimension is small (e.g., constant-order recurrence).