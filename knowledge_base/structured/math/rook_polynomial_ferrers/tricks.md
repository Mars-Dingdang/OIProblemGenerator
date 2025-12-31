# 浅谈棋盘模型在计数问题中的应用

**Author:** 彭思进

### Key Ideas and Observations

- **Rook Model Basics**: A chessboard is a set of grid cells, and placing k non-attacking rooks (no two in same row/column) defines the k-rook number $ r_k(S) $. The rook polynomial $ F_S(x) = \sum r_k(S) x^k $ encodes these counts.

- **Hit Numbers and Rook Numbers**: The relationship between hit numbers $ h_k $ (number of permutations with exactly k positions hitting a forbidden board S) and rook numbers is given by:
  $$
  \sum_{k=0}^n h_k(S) x^k = \sum_{k=0}^n r_k(S) (n-k)! (x-1)^k
  $$
  This allows transforming hit-counting problems into rook-counting ones.

- **Ferrers Boards and Falling Powers**: For a Ferrers board $ S = F(a_1, \dots, a_n) $ (columns non-decreasing in height), the rook polynomial satisfies the **falling factorial decomposition**:
  $$
  \sum_{k=0}^n r_k(S) x^{\underline{n-k}} = \prod_{i=1}^n (x + a_i - i + 1)
  $$
  where $ x^{\underline{m}} = x(x-1)\cdots(x-m+1) $. This powerful identity enables efficient computation via divide-and-conquer FFT.

- **Combinatorial Interpretations**:
  - The number of ways to place $ n-k $ non-attacking rooks on the staircase Ferrers board $ F(0,1,2,\dots,n-1) $ equals the Stirling number of the second kind $ \left\{ n \atop k \right\} $.
  - Similarly, without row restrictions (only column uniqueness), it relates to unsigned first-class Stirling numbers $ [n \atop k] $.

- **q-Analogue for Inversion Counting**: By assigning weight $ q^{\text{val}_S(T)} $ to each rook placement $ T $, where $ \text{val}_S(T) $ counts unmarked cells after marking rules, one can derive:
  $$
  \sum_{k=0}^n [r_k(S)]_q [x]^{\underline{n-k}}_q = \prod_{i=1}^n [x + a_i - i + 1]_q
  $$
  This allows computing generating functions for permutation inversions constrained within a Ferrers board.

- **Cover Polynomial for Cycle Counting**: Extends rook theory to track cycles in permutation digraphs. For a Ferrers board $ S $, the cover polynomial $ C(S,x,y) $, which tracks both chains ($ x $) and cycles ($ y $), factors as:
  $$
  C(S,x,y) = \prod_{i: a_i \ge i} (x + a_i - i + y) \cdot \prod_{i: a_i < i} (x + a_i - i + 1)
  $$
  This provides a direct way to compute cycle distributions in restricted permutations.

- **Reduction via Equivalence Classes**: Two Ferrers boards are rook-equivalent iff their transformed sequences $ b_i = a'_i - i + 1 $ (after padding zeros) form the same multiset. Every Ferrers board is equivalent to a unique strictly increasing one.

- **Transformation Techniques**:
  - Foata's First Fundamental Transformation bijectively maps descents to exceedances, enabling translation between descent and exceedance statistics.
  - For X-Y descent/exceedance problems, any restriction set corresponds to an equivalent Y=N case via board equivalence.

- **Efficient Computation Tricks**:
  - Use divide-and-conquer FFT to compute the product polynomial $ \prod (x + a_i - i + 1) $, then convert from standard basis to falling factorial basis efficiently.
  - Exploit symmetry and sorting (e.g., rotating diagonal constraints into Ferrers shape) to apply decomposition theorems.
  - For circular structures (e.g., spouse seating), break symmetry and use inclusion-exclusion over connected components.

- **Generalization Tools**:
  - $ m $-level rook numbers group rows into blocks; analogues of decomposition exist using generalized falling powers.
  - Weighted rook numbers with parameter $ \alpha $ lead to generalizations involving rising/falling factorials and connect to sequence subsequence sum problems.