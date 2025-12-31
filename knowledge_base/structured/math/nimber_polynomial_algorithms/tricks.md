# 浅谈Nimber 和多项式算法

**Author:** 罗煜翔

### 关键思想与技巧

- **Nimber 的代数结构**：
  - Nimber 在 $[0, 2^{32})$ 上构成一个有限域，支持加法（异或 ⊕）和乘法（Nim 积 ⊗）。
  - Nim 和即为按位异或；Nim 积可通过递归公式计算，利用 $2^{2n} \otimes 2^{2m}$ 的特殊性质，时间复杂度为 $O(m \cdot 3^m)$，可优化至接近 $O(1)$（通过预处理原根的指数表）。

- **Nim 积快速计算**：
  - 使用分治：设 $x = a \cdot 2^n + b$, $y = c \cdot 2^n + d$，则：
    $$
x \otimes y = (a \otimes c \otimes 2^{n-1}) \oplus ((a \oplus b) \otimes (c \oplus d) \oplus b \otimes d) \cdot 2^n \oplus (b \otimes d)
    $$
  - 利用记忆化或原根预处理（指数/对数表）大幅提升性能。

- **Nimber 多项式乘法**：
  - **Karatsuba**：标准三分支递归，复杂度 $O(n^{\log_2 3})$。
  - **Cantor 算法**：基于三进制 FFT，避免二进制 DFT 因 $x \oplus x = 0$ 导致无法进行的问题。使用循环卷积优化后复杂度为 $O(n \log n \log \log n)$。
  - **DFT 可行性**：仅当长度 $n \mid 2^{32}-1$ 时可定义 DFT，因存在原根。

- **半在线卷积优化**：
  - 传统分治复杂度 $O(n \log^2 n \log \log n)$。
  - 改进：将序列分为 $K = O(\log n \log \log n)$ 段，利用 DFT 将段间转移线性化，总复杂度降至 $O(n \log^2 n)$。

- **牛顿迭代法适用性**：
  - 在 Nimber 域上仍适用，形式为：
    $$
    X_{t+1} = X_t \oplus \frac{F \circ X_t}{F' \circ X_t} \mod x^{2^{t+1}}
    $$
  - 导数定义为移除偶数项后左移一位（等价于除以 $x$）。
  - 可用于多项式求逆、开方、复合等，复杂度 $O(n \log n \log \log n)$。

- **子集卷积（二项卷积模2）**：
  - 本质是集合幂级数的子集不交并卷积：$f_S = \bigoplus_{L \cup R = S, L \cap R = \emptyset} g_L \otimes h_R$。
  - 解法：引入占位多项式 $z^{|S|}$，先对 $g, h$ 做莫比乌斯变换（高维前缀和），再对每个集合的占位多项式做普通乘法，最后逆变换。
  - 时间复杂度 $O(m^2 2^m) = O(n \log^2 n)$，其中 $n = 2^m$。

- **Nimber exp/ln**：
  - 利用微分关系 $g' = g \circledast f'$，结合牛顿迭代求解。
  - 公式：$\text{exp}(f)$ 满足 $g' = g \circledast f'$，可通过迭代 $f_{t+1} = 1 \oplus (1 \oplus f_t) \circledast (1 \oplus \ln(1 \oplus f_t) \oplus g)$ 求解。

- **中国剩余定理（CRT）与插值**：
  - 插值使用 Lagrange 公式，结合多点求值与导数技巧（$Q_i = M'(x_i)$）转化为线性组合问题。
  - CRT 类似，需计算模逆元，使用欧几里得算法配合分治取模。

- **应用实例建模**：
  - 游戏状态的 SG 值常为坐标或参数的 Nim 积或多项式表达式。
  - 例题中将几何翻转游戏转化为解二次方程 $x^2 \oplus a \otimes x \oplus a \otimes b = 0$。
  - 图论问题中连通块组合对应指数生成函数：$\text{SG}_{\text{total}} = \text{exp}(f)$。