# 浅谈生成函数在掷骰子问题上的应用

**Author:** 杨懋龙

### Key Ideas and Tricks

- **Probability Generating Function (PGF)**: For a discrete non-negative integer random variable $ X $, define $ F(z) = \mathbb{E}[z^X] = \sum_{i=0}^{\infty} \Pr(X=i) z^i $. Then:
  - $ F(1) = 1 $
  - Expectation: $ \mathbb{E}[X] = F'(1) $
  - Variance: $ \text{Var}(X) = F''(1) + F'(1) - (F'(1))^2 $

- **Auxiliary Generating Function**: Introduce $ G(x) $, the ordinary generating function for the probability that the process has not yet terminated at length $ i $. This helps form equations between terminating and non-terminating states.

- **Core Equation Setup**:
  - $ F(x) + G(x) = 1 + xG(x) $: Adding one roll either keeps the game going or ends it.
  - When appending the target sequence (or its border), use matching conditions via border array (from KMP) or hashing:
    $$
    G(x) \cdot P(A) x^L = \sum_{i=1}^{L} a_i F(x) \cdot P(\text{suffix}) x^{L-i}
    $$
    where $ a_i = [A[1,i] \text{ is a border of } A] $.

- **Solving for Expectation**:
  - Differentiate the first equation and evaluate at $ x=1 $: $ F'(1) = G(1) $
  - Plug $ x=1 $ into the second equation to get $ G(1) = \sum_{i=1}^{L} a_i \cdot m^i $ (for fair dice)
  - Final result: $ \mathbb{E}[X] = \sum_{i=1}^{L} a_i \cdot m^i $

- **Variance Calculation**:
  - Use second derivative: $ F''(1) = 2G'(1) $
  - Derive $ G'(1) = \sum_{i=1}^{L} a_i m^i (F'(1) - i) $
  - Combine to compute variance.

- **Min-Max Convolution (Inclusion-Exclusion)**: For multiple target sequences, use:
  $$
  \mathbb{E}\left[\max T_i\right] = \sum_{S \subseteq [n]} (-1)^{|S|+1} \mathbb{E}\left[\min_{i\in S} T_i\right]
  $$
  Reduce problem to computing expectation until any sequence in subset $ S $ appears.

- **System of Equations for Multiple Sequences**:
  - Define $ F_i(x) $ as PGF for ending with sequence $ i $
  - Use combined equation:
    $$
    \sum_{i=1}^n F_i(x) + G(x) = 1 + xG(x)
    $$
  - For each sequence $ i $:
    $$
    G(x) P(A_i) x^{L_i} = \sum_{j,k} a_{i,j,k} F_j(x) P(A_i[k+1:L_i]) x^{L_i-k}
    $$
  - Solve linear system using $ \sum F_i(1) = 1 $ and Gaussian elimination.

- **Fuzzy Matching Patterns**:
  - For patterns like 'last n rolls equal' or 'all different', aggregate all valid terminal sequences algebraically.
  - Example: last $ n $ same → equation involves $ (x/m)^{n-1} $ due to repeated values.
  - Use symmetry and combinatorial coefficients (e.g., permutations $ \frac{m!}{(m-n)!} $) to encode transition weights.

- **State Redefinition for Complex States**:
  - In counter-reset problems (odd resets, even increments), redefine $ g_i $ as expected number of visits to state $ i $, not termination probability.
  - Leverage linearity of expectation and functional equations in generating functions.

- **Efficient Computation Tips**:
  - Precompute borders using KMP failure function.
  - Use hashing for fast comparison of substrings across sequences.
  - Exploit structural similarities between adjacent states to update sums incrementally (as in optimizing $ \sum [j \neq A_{i+1}] \sum_{k < f_{i,j}} E_k $).

These techniques avoid traditional DP with high dimensionality or messy recurrence solving, offering cleaner, more extensible solutions.