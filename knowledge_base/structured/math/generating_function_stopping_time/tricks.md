# 使用生成函数刻画随机过程停时的一类技巧

**Author:** 叶开

### Key Ideas and Techniques

1. **Problem Transformation via Generating Functions**:
   - The core idea is to characterize the stopping time or cumulative behavior of a random process using generating functions, especially Dirichlet generating functions for multiplicative arithmetic functions.
   - For a multiplicative function $ f $, its Dirichlet generating function is defined as $ F(s) = \sum_{n=1}^\infty \frac{f(n)}{n^s} $. The sum $ S_f(n) = \sum_{i=1}^n f(i) $ can be analyzed through properties of $ F(s) $.

2. **Exponential and Logarithmic Operators (Exp/Log)**:
   - Define $ \text{Exp}(q) $ for a function $ q $ supported only on prime powers: $ \text{Exp}(q)(x) = \sum_{k=0}^\infty \frac{q^{*k}(x)}{k!} $, where $ * $ denotes Dirichlet convolution.
   - Conversely, $ \text{Log}(d) $ recovers $ q $ from $ d = \text{Exp}(q) $ using Möbius inversion: $ \text{Log}(d) = \sum_{k=1}^\infty \frac{(-1)^{k-1}}{k} (d - \epsilon)^{*k} $.
   - These operators allow decomposition: if $ f(p^k) = p^c \lfloor k/2 \rfloor $, one can find $ q $ such that $ f = \text{Exp}(q) $, simplifying the analysis of $ S_f(n) $.

3. **Efficient Computation via Truncation and Optimization**:
   - Compute $ S_q(m) $ for $ m \leq O(n^{1/2}) $ directly, then use it to derive $ S_f(n) $ via convolution with another auxiliary function $ g $.
   - Use the identity $ S_f(n) = \sum_{j \in PN, j \leq m} g(j) \left\lfloor \frac{m}{j} \right\rfloor $, where $ PN $ are powerful numbers, reducing the problem to summing over $ O(\sqrt{n}) $ terms.

4. **Optimized Complexity Using Power Series Tricks**:
   - To compute $ \text{Exp}(f) $ efficiently, split $ f $ into $ f_0 $ (supported on small primes $ \leq \sqrt{n} $) and $ f_1 $ (large primes).
   - Then $ \text{Exp}(f) = \text{Exp}(f_0) \cdot \text{Exp}(f_1) $, where $ \text{Exp}(f_1) = \epsilon + f_1 $ is trivial.
   - For $ \text{Exp}(f_0) $, use a scaling parameter $ S $ and discretize $ \lceil S \log p \rceil $ to reduce the state space, enabling convolution in $ O(S \log^2 n) $ time.
   - Combine with interval sieving over $ [n-L, n] $ to achieve total complexity $ O\left(\frac{\sqrt{n} \log^2 n}{\sqrt{\log \log n}}\right) $ after balancing parameters.

5. **Handling Logarithmic Convolutions**:
   - For $ \text{Log}(f) $, assume $ f = \text{Exp}(g) $ and recover $ g $ up to $ \sqrt{n} $, then use recursive relations to extend.
   - Solve the equation $ A * B = C $ given $ B $ and $ C $, which reduces to a recursive summation over divisors, solvable in $ O(\sqrt{n} \log n) $ time.

6. **Interval Sieving and Divisor Sum Estimation**:
   - Estimate sums like $ \sum_{v \in [n-L,n]} d_3(v) $ (number of ways to write $ v $ as $ xyz $) using known asymptotics: $ \sum_{i \leq n} d_3(i) = n P_3(\log n) + O(n^{43/96+\epsilon}) $.
   - This bounds the error term when sieving intervals of length $ L $, ensuring accuracy within acceptable limits.

7. **Parameter Balancing**:
   - Choose $ S = \sqrt{n} / \sqrt{\log \log n} $ and $ L = \log n $ to minimize the combined complexity of the main loop and sieve steps, leading to the final $ O(\sqrt{n} \, \mathrm{polylog}\, n) $ bound.