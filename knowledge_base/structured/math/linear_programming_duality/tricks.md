# 再探线性规划对偶在信息学竞赛中的应用

**Author:** 丁晓漫

## Key Ideas and Observations

### **1. Linear Programming Duality**
- Any linear program (LP) in standard form:
  
  \[
  \max c^T x \quad \text{s.t.} \quad Ax \leq b,\ x \geq 0
  \]
  
  has a dual:
  
  \[
  \min b^T y \quad \text{s.t.} \quad A^T y \geq c,\ y \geq 0
  \]
  
- **Weak Duality**: $\max c^T x \leq \min b^T y$
- **Strong Duality**: Under mild conditions, equality holds: $\max c^T x = \min b^T y$. This allows solving the dual instead when it's structurally simpler.

### **2. Interpretation via Weighted Constraints
- Dual variables $y_i$ represent weights on constraints. If we take a linear combination of constraints with weights $y$, and ensure that the resulting coefficient for each variable $x_j$ is at least $c_j$, then the weighted sum of RHS ($b^T y$) gives an upper bound on the objective.

### **3. Connection to Minimum Cost Flow**
- The dual of a minimum cost flow LP leads to a potential-based formulation:
  
  \[
  \min \sum_u b_u p_u + \sum_{uv} c_{uv} \max(0, p_v - p_u - w_{uv})
  \]
  
  where $p_u$ are node potentials. Problems matching this form can be solved via min-cost flow.

- **Integer Solution Guarantee**: If all edge costs $w_{uv}$ are integers, there exists an optimal solution with integer potentials $p_u$. Proven via an adjustment argument: if fractional parts exist, perturb them without worsening the objective until integrality improves (induction on number of distinct fractional parts).

### **4. Lagrangian Duality**
- For problem $\max f(x)$ s.t. $g(x) \leq 0$, define Lagrangian:
  
  \[
  L(\lambda) = \max_x f(x) - \lambda g(x),\quad \lambda \geq 0
  \]
  
  Then: $\max f(x) \leq \min_\lambda L(\lambda)$ (weak duality). $L(\lambda)$ is convex in $\lambda$, so ternary/binary search applies.

- In LPs, Lagrangian duality yields the same result as standard LP duality, but offers a different perspective useful for min-max problems.

### **5. Applications to Problem Solving**

#### **A. Transforming to Min-Cost Flow**
- Example: [ZJOI2013] 防守战线 — Cover intervals with towers at minimal cost.
  - Let $p_i$: total towers built up to position $i$.
  - Constraints: $p_{R_i} - p_{L_i-1} \geq D_i$, $p_i \geq p_{i-1}$.
  - Objective becomes compatible with dual of min-cost flow → solve via flow.

- Example: [Aizu 2230] How to Create a Good Game — Maximize total edge weight increase while preserving longest path.
  - Use node potentials $p_v$ as distances.
  - Transformed objective matches dual form → solvable via shortest paths / flow.

#### **B. Transforming to Dynamic Programming**
- After duality, if dual variables are bounded (e.g., in [0,1]) and exhibit integrality, enumerate discrete states.
- Example: [XX Open Cup] Circles — Maximize sum of balanced sequence under cyclic constraints.
  - Dual: $\min \sum y_i s_i$ s.t. $y_i + y_{i+1} \geq 1$, $y_i \in [0,1]$.
  - Show optimal $y_i \in \{0, 0.5, 1\}$, and except for uniform 0.5 case, they’re binary.
  - Solve with DP over first two values: $dp[i][y_1][y_i]$.

- Example: [ZJOI2020] 序列 — Reduce sequence to zero with three types of interval decrements.
  - Original LP hard; take dual.
  - Show dual variables $Y_i, Z_i \in \{0,1\}$ due to integrality of underlying flow structure.
  - Use DP: $dp[i][Y_{i-1}][Z_{i-2}][Z_{i-1}]$.

#### **C. Handling Min-Max Problems via Lagrangian Duality**
- When problem is $\max_\lambda \min_f F(f, \lambda)$, interpret $\lambda$ as Lagrange multipliers.
- Example: [Utpc2012.10] きたまさの逆襲 — Maximize min-weight perfect matching minus upgrade cost.
  - Dualizing recovers a constrained matching problem: minimize total weight subject to $\sum_{u\in U_i} \text{flow}_u \leq b_i$.
  - Solved via min-cost flow.
  - Integer optimality follows from integrality lemma of cost flow duals.

### **6. General Strategy**
1. Model the problem as an LP (primal).
2. Take the dual.
3. Analyze structure of dual: does it resemble known problems (flow, DP)?
4. Prove integrality if needed (adjustment method, induction on fractional components).
5. Design efficient algorithm based on dual interpretation.

### **7. Common Techniques for Integrality Proof**
- **Adjustment Method**: Suppose optimal solution has fractional values. Perturb them slightly (e.g., add/subtract $\epsilon$) across a subset of variables. Show total cost doesn't increase in at least one direction. Keep adjusting until some variable becomes integral or structure changes. Use induction on number of non-integral components.
- Works well when objective is piecewise linear and constraints are symmetric.