# 浅谈一类基于概率的约瑟夫问题

**Author:** 叶卓睿

### Key Observations and Techniques

- **Survival Probability (Lemma 1):** A node that has been passed by the pointer $ i $ times survives with probability $ q^i $, where $ q = 1 - p $. This is derived by imagining nodes are not removed but marked, so survival requires avoiding deletion over $ i $ passes.

- **Symmetric Disappearance (Lemma 2):** When the pointer is at position $ c $, all nodes in $ [1, c-1] $ have been passed the same number of times and thus have equal disappearance probabilities; similarly for $ [c+1, n] $. This symmetry simplifies state modeling.

- **Generating Functions:** Used extensively to model probabilities across multiple states. For example, in Example 2, the generating function $ A(x) $ encodes the probability that a fixed node is the $ (i+1) $-th to disappear. Expanding this using binomial transforms and interchanging summations leads to convolution forms.

- **Convolution via FFT:** Many derived formulas involve sums of the form $ \sum \binom{a}{i}\binom{b}{j} q^i $ or similar, which can be expressed as convolutions. These are efficiently computed using Fast Fourier Transform (FFT), reducing time complexity from $ O(n^2) $ or worse to $ O(n \log n) $.

- **Recursive Generation of Coefficients:** In Example 2, instead of direct FFT on raw data, the author derives a recurrence for coefficients $ f_i $ using derivatives of generating functions:
  $$
  f_{i+1} = \frac{((c-1)q + n - c - (q+1)i)f_i + q(n-i)f_{i-1}}{i+1}
  $$
  This allows precomputing coefficients in $ O(n) $, followed by one FFT, improving from two FFTs.

- **Dynamic Programming with Linearity of Expectation:** In Example 3, the expected lexicographic rank is decomposed using linearity of expectation: contribution from each pair $ (i,j) $ where $ A_i > A_j $ and $ i $ vanishes before $ j $. This avoids dealing with full permutations.

- **Reduction Using Symmetry (Lemma 3):** The expected value of $ (n-t)! $ when 1 disappears before 2 is the same as before $ n $, due to symmetric exposure of other nodes after 1’s removal. This reduces redundant computation.

- **Efficient DP via Structural Analysis:** Instead of brute-force $ O(n^5) $ methods, the solution uses auxiliary arrays like $ f_{i,0,a}, f_{i,1,a} $ to precompute combinatorial weights, collapsing nested sums into $ O(n^3) $, then further optimized via FFT-based convolution to $ O(n \log n) $.

- **Circular DP Optimization:** For DPs with cyclic dependencies (e.g., $ f_{n,1} $ depending on $ f_{n,n} $), the method sets $ x = f_{n,n} $, expresses all $ f_{n,i} $ as linear functions $ k_i x + b_i $, and solves for $ x $ using the closure condition — enabling $ O(n) $ resolution per layer.

- **Decomposition by Pointer Position:** A core idea is shifting the problem so the target node becomes effectively 'position 1' via rotation, leveraging known results about starting configurations.