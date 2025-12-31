# 浅谈 Thue-Morse 序列的性质及其应用

**Author:** 郑钧

## Key Ideas and Observations

### Equivalent Definitions
- **Parity Definition**: $ T_n = \text{popcount}(n) \bmod 2 $. This allows fast computation using bit operations.
- **Recursive Definition**: $ T_0 = 0 $, $ T_{2n} = T_n $, $ T_{2n+1} = 1 - T_n $. Enables divide-and-conquer or memoized computation.
- **Morphism Definition**: Start with `0`, apply the morphism $ \mu(0) = 01, \mu(1) = 10 $ repeatedly. The infinite fixed point gives the sequence.
- **Reversal Construction**: Let $ TM_0 = "0" $, then $ TM_{k+1} = TM_k + \overline{TM_k} $, where $ \overline{s} $ flips bits. This reveals symmetry and self-similarity.

### Power Sum Property
For $ X_k = \{ n \in [0, 2^{k+1}) \mid T_n = 0 \} $, $ Y_k = \{ n \in [0, 2^{k+1}) \mid T_n = 1 \} $, we have:
$$
\sum_{x \in X_k} f(x) = \sum_{y \in Y_k} f(y)
$$
for any polynomial $ f $ of degree at most $ k $. This follows by induction using $ f(n + 2^k) - f(n) $ having lower degree.

This enables solving summation problems like $ \sum_{i=0}^{n-1} T_i f(i) $ efficiently via binary decomposition and Lagrange interpolation.

### String Properties
- **Overlap-Free**: No substring of the form $ aua ua $ (with $ a \in \{0,1\}, u \in \{0,1\}^* $) appears. Proven via algebraic analysis of LCP and reverse prefix functions.
- **Cube-Free**: As a consequence, no substring $ uuu $ exists.
- **Square-Free over Ternary Alphabet**: Using run-length encoding between zeros in the Thue-Morse sequence yields a ternary infinite square-free string.

### Substring Structure
- A string $ w $ is a substring iff it has a **TM-splitting** $ (u,v) $ such that $ uv = w $, $ u^R $ and $ v $ are *quasi-TM prefixes* (prefixes of $ T $ or $ \overline{T} $).
- Any substring has at most **two** such splittings.
- This characterization helps count valid substrings or design efficient automata.

### Generating Function
Let $ A(x) = \sum_{T_n=0} x^n $, $ B(x) = \sum_{T_n=1} x^n $. Then:
$$
A(x) - B(x) = \prod_{k=0}^{\infty} (1 - x^{2^k})
$$
This product form explains many combinatorial identities and provides an alternative proof for the power sum property via generating function convolution.

### Hash Collision
The Thue-Morse sequence can be used to break natural overflow hashing (mod $ 2^k $):
- For odd base $ b $, the hash difference between $ TM_n $ and $ \overline{TM_n} $ is divisible by increasing powers of 2.
- After $ n \geq 11 $ iterations, $ \text{hash}(TM_n) \equiv \text{hash}(\overline{TM_n}) \pmod{2^{64}} $, creating collisions.

### Shevelev's Conjecture
For fixed $ a $, define sequences based on $ u(n+a) = u(n) $ or $ -u(n) $. These subsequences are periodic with period $ 2 \cdot \text{lowbit}(a) $, and their signs relate directly to the original Thue-Morse pattern.

### Efficient Computation Tricks
- Use bit-level parallelism: `__builtin_popcount(n) & 1` for $ T_n $.
- Precompute small blocks using morphism doubling.
- Exploit symmetry in sums: pair $ i $ and $ i \oplus (2^k - 1) $.
- In dynamic programming over binary expansions, use state compression based on current alignment with Thue-Morse structure.