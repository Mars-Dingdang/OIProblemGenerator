# 《组合数求和》命题报告

**Author:** 吴思扬

### Key Ideas and Observations

- **Binomial Theorem and Generating Functions**: 
  Recognize that $\sum_{i=0}^{n-1} \binom{i \cdot d}{j}$ corresponds to the coefficient of $x^j$ in the generating function:
  $$
  C_n(x) = \sum_{i=0}^{n-1} (x+1)^{i \cdot d}
  $$
  This transforms the combinatorial sum into a polynomial coefficient extraction problem.

- **Geometric Series Analogy**:
  The sum $C_n(x)$ is a geometric-like series in polynomials:
  $$
  C_n(x) = \frac{(x+1)^{n\cdot d} - 1}{(x+1)^d - 1}
  $$
  After factoring out $x$ from both numerator and denominator (since constant terms vanish), define:
  $$
  A(x) = \sum_{k=1}^{n\cdot d} \binom{n\cdot d}{k} x^{k-1},\quad B(x) = \sum_{k=1}^{d} \binom{d}{k} x^{k-1}
  $$
  Then $B(x) \cdot C(x) \equiv A(x) \pmod{x^m}$, leading to a recurrence:
  $$
  \sum_{j=0}^{d-1} [x^j]B(x) \cdot [x^{i-j}]C(x) = [x^i]A(x)
  $$

- **Modular Inversion Challenges**:
  When $\gcd(d, M) = 1$, the constant term $[x^0]B(x) = d$ has an inverse modulo $M$, allowing direct iterative computation of $[x^i]C(x)$ using:
  $$
  [x^i]C(x) = \frac{[x^i]A(x) - \sum_{j=1}^{d-1} [x^j]B(x) \cdot [x^{i-j}]C(x)}{d} \mod M
  $$

- **Chinese Remainder Theorem (CRT)**:
  For general $M$, factor $M = \prod p_i^{q_i}$, solve the problem modulo each $p_i^{q_i}$, then combine via CRT.

- **Handling Non-Coprime Cases ($\gcd(d, p) > 1$)**:
  When $d \equiv 0 \pmod{p}$, standard inversion fails. Use Lucas's Theorem to analyze divisibility:
  - $\binom{d}{i} \equiv 0 \pmod{p}$ unless $i \equiv 0 \pmod{p}$.
  - Find smallest $t$ such that $[x^t]B(x) \not\equiv 0 \pmod{p}$, move this term to the left:
    $$
    [x^t]B(x) \cdot [x^i]C(x) = [x^{i+t}]A(x) - \sum_{j \ne t} [x^j]B(x) \cdot [x^{i+t-j}]C(x)
    $$

- **Iterative Elimination of Higher Terms**:
  To compute $[x^i]C(x) \mod p^q$, maintain a linear combination involving higher-degree $C(x)$ coefficients. Since these are multiplied by powers of $p$, iteratively eliminate them by substituting using the recurrence. Crucially:
  - Only higher-degree terms with coefficients divisible by increasing powers of $p$ need substitution.
  - Process from highest degree downward ('right-to-left') to avoid introducing non-$p$-divisible coefficients at lower degrees.
  - After $q-1$ rounds, all residual $C(x)$ terms vanish modulo $p^q$.

- **Efficient Computation of $A(x)$**:
  Compute $\binom{n\cdot d}{k}$ for small $k \le m$ using falling factorial:
  $$
  \binom{N}{k} = \frac{N(N-1)\cdots(N-k+1)}{k!}
  $$
  Handle lack of inverse by factoring out $p$-parts, computing co-prime part's inverse, and combining.

- **Final Combination via CRT**:
  Once results modulo all $p_i^{q_i}$ are computed, reconstruct final answer modulo $M$ using CRT.

These ideas collectively allow solving the problem even when $M$ is composite and many standard algebraic operations (like division) are not directly available.