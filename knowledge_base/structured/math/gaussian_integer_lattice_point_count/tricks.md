# 《整点计数》命题报告以及对高斯整数的若干研究

**Author:** 徐翊轩

### Key Ideas and Observations

- **Geometric Insight**: The number of integer points on a circle of radius $ r $ centered at the origin is equivalent to the number of integer solutions to $ x^2 + y^2 = r^2 $. This can be rephrased using complex numbers as counting Gaussian integers $ z = x + yi $ such that $ z \cdot \bar{z} = r^2 $.

- **Gaussian Integers and Unique Factorization**: The ring $ \mathbb{Z}[i] $ of Gaussian integers is a unique factorization domain (UFD). This allows us to decompose $ r^2 $ into Gaussian prime factors uniquely (up to units).

- **Fermat's Sum of Two Squares Theorem**: A prime $ p $ can be written as $ a^2 + b^2 $ if and only if $ p = 2 $ or $ p \equiv 1 \pmod{4} $. Such primes split in $ \mathbb{Z}[i] $ as $ p = (a+bi)(a-bi) $, while primes $ p \equiv 3 \pmod{4} $ remain inert (remain prime).

- **Structure of $ f(r) $**:
  - Let $ g(r) = f(r)/4 $, accounting for rotational symmetry (each point generates 4 symmetric points unless on axis).
  - If $ r^2 = \prod p_i^{e_i} $, then:
    - For $ p_i = 2 $: contributes factor 1 (special unit-related behavior).
    - For $ p_i \equiv 3 \pmod{4} $: contributes 1 if exponent $ e_i $ even, else 0.
    - For $ p_i \equiv 1 \pmod{4} $: contributes $ e_i + 1 $.
  - So: $ f(r) = 4 \times \prod_{p|r^2} \left(1 + [p\equiv1\pmod{4}] \cdot e_p\right) $

- **Multiplicativity**: The function $ g(r) $ is multiplicative, so $ h(r) = g(r)^k $ is also multiplicative. Thus, $ \sum_{i=1}^N h(i) $ is a prefix sum of a multiplicative function — suitable for advanced sieving.

- **Min25 Sieve Application**:
  - We need $ \sum_{i=1}^N h(i) $ where $ h(p^e) = (2e+1)^k $ for $ p\equiv1\pmod{4} $, and $ h(p^e)=1 $ for $ p\equiv3\pmod{4} $ (only even exponents allowed).
  - Use Min25 sieve framework by precomputing counts of primes $ \equiv1 $ and $ \equiv3 \pmod{4} $ via dynamic programming over sieving rounds.
  - Recurrence uses inclusion-exclusion based on smallest prime factor.

- **Efficient Preprocessing Trick**:
  - For small $ k $ (like 1 or 2), $ \sum f(i)^k $ grows slowly; we can precompute answers at intervals and hardcode them to reduce runtime.

- **Dirichlet Character Connection**:
  - Define $ \chi(n) = 1 $ if $ n\equiv1\pmod{4} $, $ -1 $ if $ n\equiv3\pmod{4} $, $ 0 $ if even.
  - Then $ f'(x) = 4 \sum_{d|x} \chi(d) $, where $ f'(x) $ counts points on circle of radius $ \sqrt{x} $.
  - This leads to the beautiful identity: $ \pi = 4 \sum_{n=1}^\infty \frac{\chi(n)}{n} = 4(1 - 1/3 + 1/5 - 1/7 + \cdots) $, known as the Leibniz formula for $ \pi $.

- **Optimization Insights**:
  - When $ k \geq 15 $, $ f(i)^k $ is divisible by $ 2^{30} $, so modulo any power of two less than $ 2^{30} $, result is zero.
  - Exploit this to return 0 directly for certain test cases.

These insights transform a geometric counting problem into deep number theory involving algebraic integers, character sums, and efficient sieve algorithms.