# 多项式求和

**Author:** 袁宇韬

### Key Ideas and Observations

- **Recursive Polynomial Summation**: The recurrence resembles repeated prefix sums weighted by a quadratic polynomial, which naturally leads to consideration of generating functions.

- **Generating Function Transformation**: Define the generating function $ g_k(x) = \sum_{i=0}^{\infty} f_i(k) x^i $. From the recurrence, it can be derived that:
  $$
  g_k(x) = \frac{g_{k-1}(x)}{1 - (a k^2 + b k + c) x}
  $$
  with base case $ g_0(x) = \frac{1}{1 - c x} $. This yields a product form:
  $$
  g_k(x) = \prod_{i=0}^{k} \frac{1}{1 - (a i^2 + b i + c) x}
  $$

- **Denominator as a Polynomial**: Let $ E(x) = \prod_{i=0}^{k} (1 - (a i^2 + b i + c) x) $, so $ g_k(x) = 1 / E(x) $. Then $ f_k(m) $ corresponds to the coefficient of $ x^m $ in this generating function.

- **Newton's Identities and Power Sums**: Let $ p_i = \sum_{j=0}^{k} (a j^2 + b j + c)^i $. Using Newton's identities, elementary symmetric sums $ e_i $ of the roots can be computed from power sums $ p_i $ via:
  $$
  e_i = \frac{1}{i} \sum_{j=1}^{i} (-1)^{j-1} e_{i-j} p_j
  $$
  This allows construction of $ E(x) = \sum_{i=0}^{k+1} (-1)^i e_i x^i $.

- **Efficient Computation of Power Sums**:
  - When $ a = 0, b \neq 0 $: Reduce to summing $ (j + u)^i $ over an interval using Bernoulli numbers for fast computation of power sums.
  - When $ a \neq 0 $: Complete the square: $ a j^2 + b j + c = a((j + u)^2 + v - u^2) $, expand using binomial theorem, and reduce to sums of even powers $ (j + u)^{2t} $, again computable via Bernoulli-based methods.

- **Differential Equation Insight**: It holds that $ E'(x) = E(x) P(x) $, where $ P(x) = \sum_{i=0}^{\infty} (-1)^i p_{i+1} x^i $. Solving this ODE gives:
  $$
  E(x) = \exp\left( \int_0^x P(t) dt \right)
  $$
  This is a critical optimization — instead of computing symmetric polynomials iteratively, one can directly compute $ E(x) $ using polynomial exponentiation after obtaining $ \int P(t) dt $.

- **Polynomial Exponentiation (Algorithm Seven)**: The final optimal solution uses the identity above: compute $ P(x) $ efficiently (via precomputed power sums), integrate, then apply polynomial exp in $ O(n \log n) $ time using FFT-based convolution and Newton iteration.

- **Modular Arithmetic Context**: The modulus 1004535809 is a prime and supports NTT (Number Theoretic Transform), enabling efficient polynomial multiplication.

- **Subtask-Specific Optimizations**:
  - For small $ n, m $: Use direct DP ($ O(nm) $).
  - When $ a = b = 0 $: Closed-form $ f_k(x) = \binom{x+k}{k} c^k $.
  - When $ m $ is small: Interpolation after evaluating $ f_k $ at $ O(k) $ points suffices since degree of $ f_k $ is $ O(k) $.

- **Divide-and-Conquer FFT**: In intermediate algorithms, use D&C to compute the product $ E(x) $, updating right half via convolution with left half and $ P(x) $.

These ideas combine deep mathematical insights (generating functions, symmetric polynomials, calculus) with algorithmic efficiency (FFT, NTT, poly exp/integration) to solve what appears to be a combinatorial recurrence.