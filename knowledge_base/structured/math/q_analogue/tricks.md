# 浅谈 q-analogue

**Author:** 李铭乐洋

### 关键思想与技巧

#### 1. **积性函数与 Dirichlet 卷积**
- 积性函数 $ f $ 满足：若 $ \gcd(a,b)=1 $，则 $ f(ab) = f(a)f(b) $。
- 常见积性函数包括：
  - $ \epsilon $ 函数：$ \epsilon(p^k) = 0 $
  - $ \mu $ 函数（莫比乌斯函数）：$ \mu(p^k) = -[k=1] $
  - $ \phi $ 函数（欧拉函数）：$ \phi(p^k) = (p-1)p^{k-1} $
  - $ I $ 函数：$ I(p^k) = 1 $
  - $ \text{id}_t $ 函数：$ \text{id}_t(p^k) = p^{tk} $
- **Dirichlet 卷积**定义为：
  $$
  (f * g)(x) = \sum_{d|x} f(d)g\left(\frac{x}{d}\right)
  $$
  其满足结合律、交换律和分配律，并且 $ \epsilon $ 是单位元。

#### 2. **完全平方因子（Powerful Number, PN）**
- 若一个正整数 $ m $ 的每个质因数 $ p $ 都满足 $ p^2 \mid m $，则称 $ m $ 为 Powerful Number。
- 任意 PN 可表示为 $ a^2b^3 $，其中 $ a,b $ 为整数。
- 不超过 $ n $ 的 PN 数量是 $ O(\sqrt{n}) $，这使得我们可以枚举所有 PN 来进行优化。

#### 3. **构造辅助函数以加速求和**
对于目标积性函数 $ f $，我们希望快速计算其前缀和 $ S_f(n) = \sum_{i=1}^n f(i) $。

核心思想是找到两个函数 $ g $ 和 $ h $，使得 $ f = g * h $，并且 $ g $ 在 PN 外部取值为 0，这样可以利用 PN 的稀疏性。

具体步骤如下：
- 找到一个简单的积性函数 $ g $，使其与 $ f $ 在单个质数上一致：$ g(p) = f(p) $。
- 定义 $ h = f * g^{-1} $，即 $ h $ 是 $ f $ 相对于 $ g $ 的“除法”结果。
- 因为 $ f(p) = g(p)h(1) + g(1)h(p) $，而 $ h(1)=1 $，所以 $ h(p)=0 $。因此 $ h(p^k) $ 只依赖于 $ h(p^j), j < k $，可通过递推唯一确定。
- 由于 $ h(p^k) $ 仅由低次项决定，且 $ h(p)=0 $，故 $ h $ 在非 PN 上可能非零，但在 PN 上可被高效预处理（共 $ O(\sqrt{n}) $ 个）。
- 利用卷积公式：
  $$
  \sum_{i=1}^m f(i) = \sum_{j \in \text{PN}, j \leq m} g(j) \left\lfloor \frac{m}{j} \right\rfloor
  $$
  枚举所有不超过 $ m $ 的 PN $ j $，乘以 $ g(j) $ 并累加 $ \left\lfloor \frac{m}{j} \right\rfloor $。

#### 4. **指数生成函数（Exp）与对数生成函数（Log）**
为了系统地处理积性函数的构造，引入形式幂级数工具：

- **指数生成函数（Exp）**：
  对于只在质数幂上有定义的函数 $ q $，定义其对应的积性函数 $ d = \text{Exp}(q) $，满足：
  $$
  d(p^k) = \frac{q(p)^k}{k!}
  $$
  这样 $ d $ 就是一个完整的积性函数。

- **对数生成函数（Log）**：
  给定一个积性函数 $ d $，定义其对数 $ q = \text{Log}(d) $ 为：
  $$
  \text{Log}(d) = \sum_{i=1}^\infty \frac{(-1)^{i-1}(d - \epsilon)^i}{i}
  $$
  满足 $ \text{Exp}(\text{Log}(d)) = d $，且 $ \text{Log}(\text{Exp}(q)) = q $，二者互逆。

这一框架允许我们将复杂的积性函数分解为更简单的“基本块”，并通过多项式操作实现组合。

#### 5. **复杂度优化技巧**
原始算法复杂度为 $ O(\sqrt{n} \log^3 n) $，但可通过以下方式优化至 $ O\left(\frac{\sqrt{n} \log^2 n}{\sqrt{\log \log n}}\right) $：

- **分段处理**：将小素因子和大素因子分开处理。
- **阈值划分**：设定参数 $ S $，将 $ \lceil S \log x \rceil $ 作为桶号，把数值按大小分组。
- **区间筛法**：考虑形如 $ xy t \in [n-L, n] $ 的三元组，其中 $ L = O(n/S) $，然后在长度为 $ L $ 的区间内使用线性筛法统计符合条件的三元组数量。
- **双重优化**：选择最优的 $ S = \sqrt{n} / \sqrt{\log \log n} $，平衡不同部分的时间开销。

#### 6. **关键引理与数学基础**
- **Schwartz-Zippel 引理**：用于随机化算法中判断多项式是否恒为零的概率分析。
- **Mertens' 第二定理**：$ \sum_{p \leq S} \frac{1}{p} = O(\log \log S) $，用于估计素数倒数和。
- **Divisor Function Estimation**：$ \sum_{i=n-L}^n d_3(i) = O(L \log n) $，其中 $ d_3(n) $ 表示 $ n $ 的三因子分解数。

这些理论支撑了上述算法的正确性和效率保证。