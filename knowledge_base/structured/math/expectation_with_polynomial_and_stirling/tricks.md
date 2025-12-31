# 《小H爱染色》命题报告

**Author:** 陈嘉乐

### Key Ideas and Observations

- **Problem Transformation**: Instead of simulating all colorings, compute the contribution of each possible minimum black ball position A via combinatorial counting.

- **Expectation Linearity**: For polynomial $ F(x) = \sum_{i=0}^m a_i x^i $, use linearity of expectation: $ \mathbb{E}[F(A)] = \sum_{i=0}^m a_i \mathbb{E}[A^i] $. This allows reducing the problem to computing expectations of monomials.

- **Combinatorial Interpretation of $ x^c $**:
  - $ \mathbb{E}[A^c] $ can be interpreted as the expected number of ways to choose c (possibly repeated) elements less than A.
  - Using **binomial inversion**, relate this to selecting exactly q distinct elements less than A, which connects to **second-kind Stirling numbers**: $ x^c = \sum_{q=0}^c S(c,q) \cdot q! \cdot \binom{x}{q} $.

- **Counting Valid Configurations**:
  - Let $ H_k $: number of ways that total k distinct balls are colored in two rounds (each round picks m balls).
    - $ H_k = \binom{k}{m} \cdot \binom{m}{2m - k} $, derived by fixing overlap between two sets.
  - Precompute $ H_k $ for $ k \in [m, 2m] $ using precomputed factorials and inverse factorials modulo 998244353.

- **Define G_q**: Number of ways to select q distinct positions (from those < A) such that they contribute to $ F(q) $ after inversion.
  - $ G_q = \sum_{i=0}^q (-1)^{q-i} \binom{q}{i} F(i) $ → equivalent to $ G_q = \sum_{i=0}^q \frac{(-1)^{q-i}}{(q-i)!} \cdot \frac{F(i)}{i!} $ when normalized.
  - This convolution can be computed efficiently with **NTT (Number Theoretic Transform)** in $ O(m \log m) $.

- **Combine Counts**:
  - Define $ T_i = \sum_{j=0}^i G_j \cdot H_{i-j} $: total configurations involving i total distinct balls (selected + colored).
  - Again, this is a convolution → use NTT.

- **Final Answer**:
  - $ \text{ans} = \sum_{i=0}^{3m} \binom{n}{i} \cdot T_i \mod 998244353 $
  - Since $ \binom{n}{i} $ can be computed iteratively even for large $ n \leq 998244353 $, and only up to $ i \leq 3m $ is needed, this step is $ O(m) $.

- **Alternative Approach (Algorithm 5)**:
  - The individual term $ \binom{n - A}{m}^2 \cdot F(A) $ is a polynomial in A of degree at most $ 3m $.
  - Sum over $ A = 0 $ to $ n-1 $: the prefix sum is a polynomial of degree $ 3m+1 $.
  - Evaluate this polynomial at $ n-1 $ using **Lagrange interpolation** on $ 3m+2 $ points, computable in $ O(m^2) $ or optimized to $ O(m \log m) $ with advanced methods.

- **Modular Arithmetic & Preprocessing**:
  - Use precomputed factorials and inverse factorials up to $ \max(3m, 2m) $ for combinations.
  - Efficiently compute $ \binom{n}{k} \mod 998244353 $ for large $ n $ using:
    $ \binom{n}{k} = \frac{n(n-1)\cdots(n-k+1)}{k!} $

- **Key Insight**: Both approaches (combinatorial convolution and polynomial summation) lead to efficient solutions; the former (Algorithm 6) is optimal due to NTT-based convolutions.