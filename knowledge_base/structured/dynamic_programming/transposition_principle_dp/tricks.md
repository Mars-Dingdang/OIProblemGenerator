# 转置原理在一类动态规划问题中的应用

**Author:** 徐骁扬

### Key Ideas and Observations

- **Transposition Principle**: For any linear transformation $ b = Aa $, its transpose is $ b' = A^\top a' $. The principle states that if we can solve the transposed problem efficiently, then the original problem can also be solved in the same time and space complexity by reversing the steps of the transposed algorithm.

- **Elementary Matrix Representation**: Any linear transformation can be decomposed into elementary operations:
  - Swap: $ a_i \leftrightarrow a_j $
  - Scale: $ a_i \leftarrow k \cdot a_i $
  - Add: $ a_i \leftarrow a_i + k \cdot a_j $
  
  The transpose of these operations:
  - Swaps and scales remain unchanged.
  - Add operation $ a_i \leftarrow a_i + k \cdot a_j $ becomes $ a_j \leftarrow a_j + k \cdot a_i $ under transposition.

- **Algorithm Reversal via Transpose**: To compute the transpose algorithm:
  1. Express the original algorithm as a sequence of elementary operations.
  2. Reverse the order of operations.
  3. Replace each add-type operation $ x \leftarrow x + k \cdot y $ with $ y \leftarrow y + k \cdot x $.

- **Application to Segment Tree Operations**:
  - **Interval Add, Point Query** transposes to **Point Add, Interval Sum**.
  - This duality allows optimization: instead of optimizing interval updates directly, one can design an efficient solution for the dual problem and apply reversal.

- **Segment Tree Merging and Splitting**:
  - **Merging** two segment trees corresponds to combining DP states (e.g., in tree-shaped DP).
  - **Splitting** (i.e., reverse of merging) enables undoing merges, crucial for handling transposed DP transitions.
  - Maintaining a log of modifications during merge allows $ O(n \log n) $ splitting.

- **MAX Convolution and Its Transpose**:
  - Define $ H = F \otimes G $ where $ h_k = \sum_{\max(i,j)=k} f_i g_j $.
  - The transposed operation $ F = H \otimes^\top G $ computes $ f_i = \sum_{j} h_{\max(i,j)} g_j $.
  - Efficiently computed using segment tree techniques by reversing the merge procedure.

- **Linearity Requirement in DP**:
  - To apply transposition, the DP must be linear in some variable (e.g., auxiliary array $ c_{i,j} $), while others (like $ d_{i,j} $) are treated as constants.

- **Two Approaches for Transposing Segment Tree Algorithms**:
  1. **Direct Analysis**: Analyze the segment tree operations and derive their transpose directly.
  2. **Via Brute-force Dual**: First find the brute-force version's transpose (e.g., point-add/range-sum), then optimize it using data structures.
  - Choice depends on simplicity; sometimes the second approach leads to non-trivial optimization challenges.

- **Tree DP Optimization Example**:
  - In problems like counting paths or summing weights over subtrees, transposing converts hard-to-optimize forward DP into easier-to-analyze backward propagation.
  - Enables use of known efficient algorithms (e.g., prefix sums, segment trees) on the dual form.

- **Insight from Examples**:
  - Often, the meaning of arrays in the transposed problem reveals combinatorial interpretations (e.g., $ t_{x,j} $ represents total weight from ancestors at depth $ j $).
  - These insights help validate correctness and guide implementation.