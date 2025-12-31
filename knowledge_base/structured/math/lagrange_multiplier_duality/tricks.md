# 浅谈拉格朗日乘数及对偶在 OI 中的应用

**Author:** 施开成

## Key Ideas and Tricks

### **Lagrange Multipliers for Constrained Optimization**
- For a problem `max f(x)` subject to `g_i(x) = 0`, introduce Lagrange multipliers `λ_i` and form the Lagrangian: 
  `F(x, λ) = f(x) + Σ λ_i g_i(x)`.
- The solution satisfies `∇F = 0`, leading to a system of equations that can be solved numerically or analytically.
- This converts a constrained problem into an unconstrained one in a higher-dimensional space.

### **Duality and the Min-Max Theorem**
- The primal problem `max_x min_λ F(x, λ)` is related to the dual `min_λ max_x F(x, λ)`.
- By the **weak duality theorem**, `max min ≤ min max`. If equality holds, it's called **strong duality**.
- Strong duality occurs under certain conditions (e.g., when the function is convex-concave and domains are compact), allowing us to solve the dual instead of the primal.

### **Handling Inequality Constraints**
- For inequality constraints `g(x) ≥ 0`, the Lagrangian becomes `F(x, λ) = f(x) + λ^T g(x)` with `λ ≥ 0`.
- The dual function is `L(λ) = max_x F(x, λ)`, and the dual problem is `min_{λ≥0} L(λ)`.
- The non-negativity of `λ` ensures that violating `g(x) ≥ 0` incurs a penalty in the objective.

### **Complementary Slackness and KKT Conditions**
- At the optimum, if a constraint `g_i(x) > 0` is not tight, then its corresponding `λ_i = 0`.
- This allows for iterative algorithms where we guess which constraints are active and solve accordingly.

### **Applications in OI Problems**
1. **Resource Allocation**: Transform problems like maximizing `Σ s_i / v_i` under energy constraints into dual problems solvable via binary search on `λ`.
2. **Min-Max Problems**: Use the minimax theorem to swap `max` and `min` when the objective is linear in one variable and constraints are linear.
3. **Linear Programming Duality**: Convert standard LP (`max c^Tx s.t. Ax ≤ b, x ≥ 0`) to its dual (`min b^Ty s.t. A^Ty ≥ c, y ≥ 0`). This is used in problems like interval covering or assignment.
4. **Convex Optimization**: When the objective is convex and constraints are linear, strong duality holds, making the dual problem equivalent.

### **Algorithmic Techniques**
- **Binary Search on Dual Variables**: For problems where the dual function `L(λ)` is monotonic, perform binary search on `λ` to satisfy the original constraint.
- **Brute Force on Active Constraints**: Enumerate subsets of constraints that are tight at the optimum, then solve the resulting system.
- **Greedy Interpretation of Dual Variables**: Often, dual variables `λ` represent prices or marginal values, guiding greedy strategies.

### **Key Observations**
- The dual problem often has fewer variables than the primal, especially when there are many constraints.
- Solving the dual provides a certificate of optimality via weak duality.
- In discrete problems, even if strong duality doesn't hold, the dual bound can guide approximation algorithms.