# 《A + B Problem》命题报告

**Author:** 汪乐平

### Key Ideas and Observations

- **Decomposition via Strong Connectivity**: Any directed graph can be decomposed into strongly connected components (SCCs), which form a DAG when contracted. The problem asks for the expected number of source nodes (in-degree 0) in this DAG.

- **Generating Function Framework**: Use exponential generating functions (EGFs) to model:
  - $ D(x) $: EGF for strongly connected graphs.
  - $ H(x) $: EGF for all directed graphs.
  - $ E(x) $: EGF for sets of strongly connected components with inclusion-exclusion weights ($ e_i $).

- **Core Identity**: From combinatorial decomposition, we derive:
  $$
  E(x) = e^{-D(x)} \quad \Rightarrow \quad D(x) = -\ln E(x)
  $$
  This links the count of general directed graphs to that of strongly connected ones.

- **Restricted SCC Sizes**: Define $ d'_i = d_i \cdot s_i $, where $ s_i \in \{0,1\} $ indicates if size $ i $ is allowed. Then build $ D_1(x) = \sum d'_i \frac{x^i}{i!} $, and compute $ E_1(x) = e^{-D_1(x)} $, leading to restricted graph counts via $ \Delta H_1(x) = (\Delta E_1(x))^{-1} $.

- **Compositional Generating Functions**: To handle edge direction interactions in counting, introduce the *combinatorial generating function* operator $ \Delta $:
  $$
  \Delta F(x) = \sum_{i \geq 0} f_i \frac{x^i}{i!} \cdot 2^{\binom{i}{2}}
  $$
  This accounts for all possible edges within a set of $ i $ vertices.

- **Key Transformation**: Use identity:
  $$
  2^{i(n-i)} = \frac{2^{\binom{n}{2}}}{2^{\binom{i}{2}} \cdot 2^{\binom{n-i}{2}}}
  $$
  This allows convolution under $ \Delta $-transformed space, enabling efficient computation of:
  $$
  \Delta E(x) \cdot \Delta H(x) = 1
  $$

- **Answer Contribution via Linearity of Expectation**: Instead of summing over structures, use linearity — consider contribution of one SCC being a source. The total expected value is derived from:
  $$
  \Delta A(x) = \Delta H_1(x) \cdot \Delta D_1(x)
  $$
  Where $ A(x) $ encodes the sum of answers (number of sources) across all valid graphs.

- **Final Computation Steps**:
  1. Compute unrestricted $ h_n = 2^{n(n-1)} $ → $ H(x) $
  2. Compute $ \Delta H(x) $, then invert to get $ \Delta E(x) $
  3. Convert back to $ E(x) $, take logarithm to get $ D(x) $
  4. Zero out disallowed sizes → $ D_1(x) $
  5. Exponentiate: $ E_1(x) = e^{-D_1(x)} $
  6. Transform: $ \Delta E_1(x) $, invert to get $ \Delta H_1(x) $: number of valid graphs
  7. Compute $ \Delta A(x) = \Delta H_1(x) \cdot \Delta D_1(x) $: total answer sum
  8. Extract coefficients: $ \text{ans}_i = [x^i]A(x) $, $ \text{count}_i = [x^i]H_1(x) $
  9. Output $ \text{ans}_i \cdot \text{count}_i^{-1} \mod 998244353 $

- **Efficient Operations**:
  - Polynomial inversion, logarithm, exponentiation, and multiplication are all implemented in $ O(n \log n) $ using NTT (Number Theoretic Transform), doubling method, and Newton iteration.

- **Modular Arithmetic**: All operations performed modulo 998244353, a prime suitable for NTT.