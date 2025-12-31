# 浅谈函数的凸性在OI 中的应用

**Author:** 郭羽冲

## Key Ideas and Tricks

### Convexity Definitions
- A function $ f(x) $ is **upper convex (concave)** if:
  $$
  \forall x_1,x_2,\quad f\left(\frac{x_1+x_2}{2}\right) \geq \frac{f(x_1)+f(x_2)}{2}
  $$
- A function $ f(x) $ is **lower convex (convex)** if:
  $$
  \forall x_1,x_2,\quad f\left(\frac{x_1+x_2}{2}\right) \leq \frac{f(x_1)+f(x_2)}{2}
  $$

These discrete midpoint definitions imply useful structural properties in DP.

### Slope Optimization
- Used when a DP transition can be rewritten as:
  $$
  dp_i = \min_j \{ dp_j + (x_i - x_j)^2 \} \Rightarrow \text{Rewrite as linear function in } x_j
  $$
- Each state $ j $ corresponds to a point $ (x_j, y_j) $, and query becomes finding the point minimizing intercept of a line with given slope.
- Optimal decision lies on the lower/upper convex hull depending on inequality direction.
- If queries and insertions are monotonic (e.g., increasing $ x_j $, increasing query slope), use deque to maintain hull in $ O(n) $.
- Otherwise, use balanced BST (e.g., `std::set`) to support arbitrary insertions and binary search for tangents in $ O(n \log n) $.

### WQS Binary Search (Alien's Trick)
- Applies when answer $ f(k) $ — optimal value using exactly $ k $ items — is convex/concave.
- Instead of computing full DP table over $ k $, binary search on a **penalty/lagrange multiplier** $ \lambda $ that penalizes each selection.
- Transform problem: maximize $ \sum \text{value} - \lambda \cdot \text{count} $, then recover count of selected elements.
- Due to convexity, there exists $ \lambda $ such that optimal solution uses exactly $ m $ items.
- Reduces dimensionality: from $ O(nm) $ to $ O(n \log V) $ per query.
- Use helper array $ z_i $ to track number of selections during DP to determine current count at optimum.
- Can be combined with divide-and-conquer or segment trees for range queries.

### Maintaining Convex Functions
- Represent piecewise linear convex functions by their **slope changes**.
- Support operations:
  - Add constant → global offset
  - Add absolute value term $ |x - a| $ → decrease prefix slopes by 1, increase suffix slopes by 1
  - Take $ \max(f(x), c) $ or $ \min(f(x), c) $ → truncate function
  - Merge two convex functions via (min,+) or (max,+) convolution → merge slope sequences
- Use dual heaps (one max-heap for left part, one min-heap for right) around median slope to simulate slope adjustments efficiently.
- Example: maintaining $ f(j) = \text{DP value at } j $, where updates involve adding $ |j - x_k| $.

### Quadrilateral Inequality & Sequence Partitioning
- Matrix $ A_{i,j} $ satisfies quadrilateral inequality if:
  $$
  \forall i < j \leq k < l,\quad A_{i,k} + A_{j,l} \leq A_{i,l} + A_{j,k}
  $$
- Implies decision monotonicity in DP: optimal split points are non-decreasing.
- Also implies that total cost $ f(m) $ of partitioning into $ m $ segments is **convex** in $ m $.
- Enables WQS binary search to optimize over $ m $.

### Combining Techniques
- **WQS + Convex Hull Maintenance**: When WQS reduces dimension, remaining DP may still benefit from slope optimization.
- **WQS + Segment Tree**: Precompute convex functions per segment tree node; answer queries via WQS and merging truncated results.
- **Heavy-Light Decomposition + Convexity**: In tree DP (e.g., matching), use HLD and process light subtrees separately; exploit convexity to merge heavy paths in $ O(\text{length}) $ time.
- **Global Balanced Binary Trees**: Advanced technique to achieve $ O(n \log n) $ instead of $ O(n \log^2 n) $ in some cases.

### Proving Convexity
- **Direct proof via definition** or induction on DP transitions preserving convexity.
- **Via cost flow model**:
  - Minimum cost w.r.t. flow amount is convex.
  - Maximum cost w.r.t. flow amount is concave.
  - Modeling selection problems as flows provides immediate convexity.

### Observations
- Many seemingly non-convex problems become convex after proper transformation.
- The combination of convexity and data structures enables powerful optimizations beyond standard DP.
- Always check whether the objective function in a parameter (like number of selections) is convex — it often is due to diminishing returns.