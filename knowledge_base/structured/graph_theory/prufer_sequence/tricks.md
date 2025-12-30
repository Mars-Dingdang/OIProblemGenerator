- **Bijection**: Prüfer sequence establishes a bijection between labeled trees on $ n $ nodes and sequences of length $ n-2 $ with values in $ [1, n] $.
- **Degree Insight**: Each node appears in the Prüfer sequence exactly $ \text{deg}(v) - 1 $ times. This allows reconstruction of degrees from the sequence.
- **Cayley’s Formula**: The number of spanning trees in a complete graph $ K_n $ is $ n^{n-2} $, directly from the number of possible Prüfer sequences.
- **Connected Graph Construction**: For a graph with $ k $ connected components of sizes $ s_1, \dots, s_k $, the number of ways to add $ k-1 $ edges to make it connected is:
  $$
  \sum_{\substack{d_i \geq 1 \\ \sum d_i = 2k-2}} \binom{k-2}{d_1-1, \dots, d_k-1} \prod_{i=1}^k s_i^{d_i} = \left(\sum_{i=1}^k s_i\right)^{k-2} \prod_{i=1}^k s_i = n^{k-2} \prod_{i=1}^k s_i
  $$
  This powerful identity comes from multinomial expansion after substitution $ e_i = d_i - 1 $.
- **Linear Algorithms**: Both construction and decoding can be done in $ O(n) $ using pointer tracking instead of heaps, by exploiting monotonicity of leaf indices.
- **Edge Case**: A single-node tree has an empty Prüfer sequence (by convention).