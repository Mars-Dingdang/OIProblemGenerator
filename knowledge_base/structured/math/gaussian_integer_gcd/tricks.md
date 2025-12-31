# 算法竞赛中一些数论问题的推广与高斯整数初探

**Author:** 李佳衡

## 关键思想与技巧

### 1. **高斯整数的基本性质**
- 高斯整数集合 $\mathbb{Z}[i] = \{a + bi \mid a,b \in \mathbb{Z}\}$ 构成一个**交换整环**，且是**唯一分解整环 (UFD)**。
- 定义**范数**：$N(\alpha) = a^2 + b^2$ 对于 $\alpha = a + bi$，满足 $N(\alpha\beta) = N(\alpha)N(\beta)$，且若 $\alpha \mid \beta$ 则 $N(\alpha) \mid N(\beta)$。
- 范数提供了类似于绝对值的“大小”度量，使得可以在没有全序的情况下进行带余除法。

### 2. **带余除法与 Euclid 算法的推广**
- 在 $\mathbb{Z}[i]$ 中仍存在带余除法：对任意 $\alpha, \beta \neq 0$，存在 $\eta, \gamma$ 使得
  $$
  \beta = \eta\alpha + \gamma, \quad N(\gamma) < N(\alpha)
  $$
  这是因为在复平面上可以找到离商最近的高斯整数作为商。
- 因此可定义 $\gcd(\alpha, \beta)$ 并使用递归的 Euclid 算法计算，每次迭代范数至少减半，故时间复杂度为 $O(\log N(\alpha))$。

### 3. **最大公约数的存在性与 Bezout 恒等式**
- 设集合 $S = \{\alpha x + \beta y \mid x,y \in \mathbb{Z}[i]\}$，取其中范数最小的非零元素 $\delta$，则 $\delta = \gcd(\alpha, \beta)$（相伴意义下）。
- 存在 $x,y \in \mathbb{Z}[i]$ 使得 $\alpha x + \beta y = \gcd(\alpha, \beta)$，即 Bezout 恒等式成立。

### 4. **高斯素数的判定（定理 6.8）**
一个高斯整数 $\xi$ 是素数当且仅当满足以下之一：
1. $N(\xi) = 2$ → 如 $1+i$
2. $N(\xi) = p$，其中 $p \equiv 1 \pmod{4}$ 是有理素数
3. $\xi \sim p$，其中 $p \equiv 3 \pmod{4}$ 是有理素数（即其本身不可分）

> 证明关键：利用范数分解和二次剩余理论。例如，若 $p \equiv 1 \pmod{4}$，则 $-1$ 是模 $p$ 的二次剩余，存在 $z$ 使 $z^2 \equiv -1 \pmod{p}$，从而 $\gcd(p, z+i)$ 给出一个范数为 $p$ 的因子。

### 5. **标准分解算法优化**
- 分解 $\alpha = a + bi$ 时先提取 $d = \gcd(a,b)$，然后处理 $\alpha_1 = \alpha / d$，此时 $\gcd(\Re(\alpha_1), \Im(\alpha_1)) = 1$，避免了有理整数因子干扰。
- 对 $N(\alpha)$ 做有理整数分解，从小到大尝试每个素因子 $p$：
  - 若 $p=2$，用 $1+i$ 试除；
  - 若 $p\equiv1\pmod{4}$，用 $\gcd(p, z+i)$ 得到素因子；
  - 若 $p\equiv3\pmod{4}$，则 $p$ 本身是高斯素数，但不能整除 $\alpha_1$（否则矛盾），跳过。
- 使用 Pollard-Rho 可将整体复杂度降至 $O(n^{1/4})$。

### 6. **数论函数与求和方法的推广**
#### （1）积性函数定义
$f: D^+ \to \mathbb{C}$ 是积性的，如果 $\gcd(\alpha,\beta)=1$ 时 $f(\alpha\beta)=f(\alpha)f(\beta)$。

#### （2）Dirichlet 卷积
$$
(f * g)(\alpha) = \sum_{\delta \mid \alpha} f(\delta)g\left(\frac{\alpha}{\delta}\right)
$$
并利用恒等式如 $\mu * 1 = \epsilon$, $\varphi * 1 = N$ 来构造快速求和算法。

#### （3）杜教筛类方法
设 $F(n) = \sum_{\alpha \in S(n)} f(\alpha)$，若有辅助函数 $g$ 使得 $f*g$ 和 $g$ 易求和，则：
$$
g(1)F(n) = \sum_{\alpha \in S(n)} (f*g)(\alpha) - \sum_{i=2}^n \sum_{\beta \in T(i)} g(\beta) F\left(\left\lfloor \frac{n}{i} \right\rfloor\right)
$$
记忆化递归实现，配合预处理可达到 $O(n^{2/3})$ 复杂度。

#### （4）Min_25 筛类方法
基于扩展埃拉托斯特尼筛的思想，按范数排序枚举，维护不含前 $m$ 个素因子的部分和。由于高斯素数个数为 $O(\pi(n))$，复杂度仍为 $O(n^{3/4}/\log n)$ 或 $O(n^{2/3})$ 配合优化。

### 7. **完全剩余系与 Euler 函数**
- 模 $\gamma = a+bi$ 的完全剩余系大小为 $R(\gamma) = N(\gamma)$。
- 存在一个显式构造：
  $$
x_{m,n} = m + ni,\quad 0 \le m < \frac{N(\gamma)}{g},\; 0 \le n < g,\; g = \gcd(a,b)
  $$
- Euler 函数 $\varphi(\gamma)$ 表示既约剩余系大小，满足：
  $$
  \sum_{\delta \mid \gamma} \varphi(\delta) = N(\gamma),\quad \varphi(\gamma) = N(\gamma)\prod_{\xi \mid \gamma}\left(1 - \frac{1}{N(\xi)}\right)
  $$