# 浅谈几种分解质因数方法

**Author:** 罗思远

### Key Ideas and Observations

#### **Miller-Rabin Primality Test**
- Based on Fermat's Little Theorem and properties of strong pseudoprimes.
- For odd $ n $, write $ n - 1 = 2^d \cdot r $, then test with base $ a $: compute $ a^r \mod n $, then square up to $ d $ times.
- If during squaring we get $ x^2 \equiv 1 \pmod{n} $ but $ x \not\equiv \pm1 \pmod{n} $, then $ n $ is composite.
- Using the first 9–12 small primes as bases ensures correctness for numbers up to $ 10^{18} $ or $ 2^{64} $.

#### **Trial Division Optimization**
- Only need to check primes up to $ \sqrt{n} $, since smallest prime factor $ \leq \sqrt{n} $.
- Precompute small primes using sieve; use Barrett reduction to optimize modular operations.
- In some cases, e.g., Möbius function computation, only trial divide up to $ \sqrt[3]{x} $, then analyze remainder via Miller-Rabin and square testing.

#### **Continued Fractions Background**
- Any real number $ x $ has a unique continued fraction representation $ [a_0; a_1, a_2, \ldots] $.
- For $ \sqrt{n} $ (non-square), this expansion is periodic.
- Define sequences:
  $ P_0 = 0, Q_0 = 1, a_0 = \lfloor \sqrt{n} floor $
  $ P_{i+1} = a_i Q_i - P_i $
  $ Q_{i+1} = \frac{n - P_{i+1}^2}{Q_i} $
- Important property: $ A_{i-1}^2 - n B_{i-1}^2 = (-1)^i Q_i $, where $ A_i/B_i $ is the $ i $-th convergent.
- $ Q_i < 2\sqrt{n} $, so values stay bounded.

---

### **SQUFOF (Square Form Factorization)**
- **Core Idea**: Find an even index $ i $ such that $ Q_i = t^2 $ is a perfect square → then $ A_{i-1}^2 \equiv t^2 \pmod{n} $ ⇒ $ \gcd(n, A_{i-1} \pm t) $ likely gives nontrivial factor.
- Use recurrence to generate $ P_i, Q_i, a_i $ until $ Q_i $ is square.
- Avoid computing $ A_i $ directly when $ n $ is large by using a second 'inverse' iteration:
  - After finding $ Q_k = w^2 $, start new sequence from $ P'_0 = -P_k, Q'_0 = w $.
  - Iterate until $ P'_i = P'_{i+1} $, then return $ \gcd(Q'_i, n) $.
- Optimizations:
  - Use modulo pre-checks (e.g., mod 64) to quickly reject non-squares.
  - Replace division in $ Q_{i+1} $ update using identity: $ Q_{i+1} = Q_{i-1} + a_i(P_i - P_{i+1}) $.
  - Roll variables (no arrays needed).
- Expected time: $ O(n^{1/4}) $; works well in practice for $ n \sim 10^{30} $.

---

### **CFRAC (Continued Fraction Method)**
- Instead of waiting for single square $ Q_i $, collect many $ Q_i $ and find subset whose product is a square.
- Represent each $ (-1)^i Q_i $ as exponent vector mod 2 over small primes (include -1).
- Goal: find linearly dependent set in $ \mathbb{F}_2 $ → product is square.
- Use Gaussian elimination (bitset optimized) to solve.
- Pruning:
  - Only consider $ B $-smooth $ Q_i $ (all prime factors ≤ B).
  - Pre-filter primes $ p $: require $ \left(\frac{n}{p}\right) = 1 $ (i.e., $ n $ is quadratic residue mod $ p $) — eliminates ~half the primes.
- **Optimization**: If two residues after factoring are equal ($ r $), combine them: $ (a_1 a_2 / r)^2 \equiv q_1 q_2 \pmod{n} $, giving another usable relation.
- Complexity dominated by trial division; overall sub-exponential: $ \exp\left((1 + o(1))\sqrt{2 \log n \log \log n}\right) $.
- Practical for `__int128` range (~39 digits).

---

### **Quadratic Sieve (QS)**
- Simpler idea: let $ f(x) = (\lfloor\sqrt{n}\rfloor + x)^2 - n $. Then $ f(x) \equiv y^2 \pmod{n} $.
- Want $ f(x) $ to be $ B $-smooth.
- Instead of testing one-by-one, use **sieving**:
  - For each small prime $ p $, solve $ x^2 \equiv n \pmod{p} $ → get roots $ r $.
  - Mark arithmetic progressions $ x \equiv r \pmod{p} $ as divisible by $ p $.
  - Accumulate logs or counts; identify candidates likely to be smooth.
- Use multiple polynomials to keep values small:
  - $ f(x) = (Ax + B)^2 - n = A(Ax^2 + 2Bx + C) $, choose $ A = p^2 $, $ B^2 \equiv n \pmod{A} $.
  - Ensures $ Ax^2 + 2Bx + C $ stays small and amenable to sieving.
- Same linear algebra phase as CFRAC.
- Final complexity: $ \exp\left((1 + o(1))\sqrt{\log n \log \log n}\right) $ — faster than CFRAC asymptotically.
- Can factor ~200-bit integers in seconds.

---

### General Insights
- **Smooth Numbers** are central: both CFRAC and QS rely on finding many $ B $-smooth values.
- **Congruence of Squares**: Once $ x^2 \equiv y^2 \pmod{n} $ and $ x \not\equiv \pm y $, $ \gcd(x-y, n) $ yields factor.
- **Linear Algebra over $ \mathbb{F}_2 $** is efficient due to sparsity; bitset optimization crucial.
- **Preprocessing Filters** (quadratic residue check, early abort on large cofactors) greatly improve practical speed.
- All three algorithms outperform trial division for large $ n $, especially beyond $ 10^{18} $.