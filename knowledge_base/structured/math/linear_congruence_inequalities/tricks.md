# 浅谈一类线性同余不等式问题

**Author:** 杨鑫和

### Key Ideas and Tricks

#### 1. **Single Linear Congruence Inequality**
- Problem: Find the smallest $ x \in \mathbb{Z}_m $ such that $ L \leq ax \bmod m \leq R $.
- **Geometric Interpretation**: View $ (x, y) $ such that $ ax - my \in [L, R] $. The valid points form rows in the plane, each row corresponding to fixed $ y = \lfloor ax/m \rfloor $.
- **Recursive Reduction**:
  - If the first row ($ y=0 $) has a solution, check $ \lceil L/a \rceil a \leq R $.
  - Otherwise, when $ R - L + 1 < a $, each row has at most one red point.
  - Transform condition $ L \leq ax - my \leq R $ into existence of $ x $, leading to $ (-L - my) \bmod a \leq R - L $.
  - This becomes a new congruence inequality on $ y $: $ my \bmod a \in [0, R-L] $, solvable recursively.
  - Time complexity mirrors extended GCD: $ O(\log^2 m) $.

#### 2. **k-th Smallest Solution**
- When $ R - L + 1 \geq m $: every row has solutions; enumerate $ y $, solve for interval of $ x $, collect until $ k $ solutions.
- When $ R - L + 1 < m $: at most one solution per row; recurse as above, then reconstruct all $ k $ smallest $ x $ values from $ y $; total cost $ O(k \log^2 m) $.

#### 3. **Linear Congruence Inequality Systems**
- Goal: Compute either the **density** $ |S'|/m' $ or the **minimal period** $ m'_{\min} $ of solutions to:
  $$
  \begin{cases}
    x \equiv S_1 \pmod{m_1} \\
    \cdots \\
    x \equiv S_k \pmod{m_k}
  \end{cases}
  $$
- **Key Insight – Prime Exponent Halving**:
  - Let $ T = \prod_{p \leq B} p^{\lfloor v_p(B)/2 \rfloor} $, where $ B = \max m_i $.
  - Enumerate $ x \equiv r \pmod{T} $, then substitute $ x = yT + r $ into each congruence.
  - Each $ x \bmod m_i \in S_i $ transforms into $ y \bmod \frac{m_i}{\gcd(m_i,T)} \in S'_i $.
  - Crucially, $ \frac{m_i}{\gcd(m_i,T)} $ is either 1 or a prime power (due to exponent halving).
  - After merging equations with nested moduli, we reduce to a system with pairwise coprime moduli → apply Chinese Remainder Theorem (CRT).
  - Sum over all $ r \bmod T $: each subproblem solved independently.

#### 4. **Minimal Period of Solution Set**
- Naive idea: compress each equation $ x \bmod m \in S $ to smallest equivalent $ x \bmod n \in T $, then take LCM — but this fails due to *invalid elements*.
- **Definition of Validity**: An element $ r \in S_i $ is *valid* if there exists some global solution $ e $ such that $ e \equiv r \pmod{m_i} $.
- **Algorithm**:
  - Remove invalid elements across all sets.
  - Compress each equation to minimal modulus.
  - Take LCM of resulting moduli → gives minimal period $ m'_{\min} $.
- **Efficient Validation**:
  - Use same $ T $-based enumeration as above.
  - For each residue $ r \bmod T $, reduce system to coprime moduli → all remaining residues are valid.
  - Thus, any original residue appearing in any valid sub-solution is globally valid.

#### 5. **Complexity Analysis**
- Bottleneck: $ \prod_{p \leq B} p^{\lfloor v_p(B)/2 \rfloor} $.
- Let $ \psi'(B) = \sum_{p \leq B} \left\lfloor \frac{v_p(B)}{2} \right\rfloor \ln p = \psi(\lfloor \sqrt{B} \rfloor) $, where $ \psi(x) = \ln(\mathrm{lcm}[1..x]) $.
- Known: $ \psi(x) \sim x $ ⇒ $ \psi'(B) \sim \sqrt{B} $ ⇒ growth rate is $ e^{\sqrt{B} + o(\sqrt{B})} $.
- Final complexity: $ O(B^2 \cdot e^{\sqrt{B} + o(\sqrt{B})}) $, significantly better than naive $ O(\mathrm{lcm}[1..B]) $.

#### 6. **Applications**
- Traffic Blights (ICPC WF): probability car passes all green lights.
- Graph cycle period: after long enough path, existence of length-$x$ path becomes periodic; use strong connectivity and tree-based potential to compute cycle GCDs, then reduce to congruence system.