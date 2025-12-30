- **Transform the fraction**: To solve $\max \frac{\sum a_i w_i}{\sum b_i w_i}$, reframe as checking whether $\frac{\sum a_i w_i}{\sum b_i w_i} \geq \text{mid}$, which transforms to $\sum (a_i - \text{mid} \cdot b_i) w_i \geq 0$.

- **Binary search on real values**: Use binary search over the answer with sufficient precision (typically `1e-6` to `1e-9`). Avoid integer-based logic.

- **Greedy when possible**: If selection is unconstrained (like choosing exactly $k$ items), sort by $a_i - \text{mid} \cdot b_i$ and pick top $k$.

- **Use DP when constraints bind**: For weight lower bounds (e.g., $\sum b_i \geq W$), use knapsack-style DP where value is $a_i - \text{mid} \cdot b_i$ and weight is $b_i$. Cap states at $W$.

- **Graph adaptations**:
  - For MST problems (e.g., Desert King), assign edge weights $a_e - \text{mid} \cdot b_e$ and compute MST. Check total sign.
  - For cycle problems (e.g., Minimum Cycle Mean), use Bellman-Ford or SPFA to detect negative cycles after setting edge weights to $w_e - \text{mid}$.

- **Add dummy node for connectivity**: In cycle detection, connect a super-source to all nodes with zero weight to ensure reachability.

- **Dinkelbach algorithm (iterative)**: Instead of binary search, use previous optimal value as next guess. Often faster convergence in practice.

- **Precision handling**: Be cautious with floating-point comparisons. Use `fabs(l - r) > eps` and avoid using `==`.

- **Problem transformation patterns**:
  - Ratio maximization → binary search + feasibility check
  - Fractional objective → linearize via subtraction
  - Global ratio constraint → local weight adjustment