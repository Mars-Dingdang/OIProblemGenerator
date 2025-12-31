# 一类调整算法在信息学竞赛中的应用

**Author:** 邓明扬

### Key Ideas and Observations

- **Local Search Framework**: The core idea is to define a feasible solution space $ T \subset S $, with a value function $ F(x) $. From an initial $ x \in T $, repeatedly search its neighborhood $ N(x) $ for a better or equally good solution and update.

- **Neighborhood Design**: For each problem, design a meaningful neighborhood $ N(x) $ where changes are small (e.g., flipping one edge in matching, reassigning one vertex color in coloring). This ensures gradual improvement while maintaining feasibility.

- **Randomization Helps Escape Local Optima**: Even when no improving move exists, randomly selecting equal-value neighbors helps explore the solution space and avoid stagnation.

- **Adjustment in Matching Problems**:
  - In general graph matching, maintain a current matching $ S $. Randomly pick an unmatched vertex; if it has an unmatched neighbor, match them. Otherwise, force a swap via a matched neighbor, possibly increasing matching size over time.
  - The symmetric difference between current and optimal matchings forms alternating paths/cycles. The algorithm implicitly searches for augmenting paths through stochastic moves.

- **Implicit Matching via Adjustment**:
  - Some problems (like CF Round 562 E) reduce to constructing permutations satisfying XOR constraints. Interpreted as a bipartite-like assignment, adjustment mimics matching: try to assign values without conflict, otherwise perform swaps.

- **Graph Coloring Adjustment**:
  - Start with random coloring. Iteratively pick a vertex and recolor it to minimize conflicting edges. Though not guaranteed to reach global optimum, works well on average due to high connectivity in random graphs guiding descent.

- **Hamiltonian Path via Edge Selection**:
  - Maintain a set of edges forming a pseudo-path (in/out-degree ≤1, acyclic). Use LCT to dynamically check cycles. Allow probabilistic replacement of conflicting edges to escape dead ends.

- **Approximation via Rounding + Adjustment**:
  - Solve LP relaxation to get fractional solution.
  - Instead of independent randomized rounding, use adjustment: fix variables involved in tight constraints, then adjust others toward 0 or 1 while preserving constraint satisfaction.
  - This hybrid approach often yields better approximation ratios than pure randomization.

- **Robustness on Random Data**:
  - Despite lack of formal guarantees, these methods excel in real contests because test data is often not adversarial.
  - Especially effective in **answer-only problems** where even suboptimal solutions earn partial credit.

- **Optimization Techniques**:
  - **Local Multiple Adjustments**: After modifying a variable, focus subsequent adjustments nearby to exploit locality and reduce wasted steps.
  - **Integration with Simulated Annealing**: Accept worse solutions with some probability to escape deep local optima — trades monotonicity for broader exploration.