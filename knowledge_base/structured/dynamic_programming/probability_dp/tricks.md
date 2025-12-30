## Key Observations

1. **Forward vs Backward DP**: 
   - **Probability DP**: Usually solved with **forward DP** (from initial state to final state).
   - **Expectation DP**: Usually solved with **backward DP** (from final state to initial state) because expectation satisfies linearity and the "future" is known.

2. **Handling Aftereffects**: 
   - When DP has cycles or dependencies between states (e.g., random walks with left/right moves), use:
     - **Gaussian elimination** for solving linear systems.
     - **Matrix exponentiation** for linear recurrences.
     - **Iterative approximation** (value iteration) for Markov chains.

3. **State Design**: 
   - Often the state represents the **current situation** (e.g., number of white/black mice, bugs found, classrooms visited).
   - May need to include **additional dimensions** for resources (e.g., number of exchanges remaining in "换教室").

4. **Probability Calculation**: 
   - Carefully compute **conditional probabilities** using multiplication rule.
   - Use **law of total probability** when multiple cases lead to the same next state.
   - Normalize probabilities when necessary (e.g., in "Broken robot", the probabilities change at boundaries).

5. **Expectation Linearity**: 
   - E[X] = Σ P(event) * E[X | event] + 1 (for the current step).
   - This leads to equations like: `dp[i] = 1 + Σ p[j] * dp[next_state[j]]`.

## Common Transformations

1. **From Probability to Expectation**: 
   - If you need **expected steps to reach an absorbing state**, set dp[absorbing] = 0 and solve backward.
   - Example: `dp[i] = 1 + Σ p[i→j] * dp[j]`.

2. **Combining with Graph Algorithms**: 
   - Precompute shortest paths (Floyd-Warshall) when movement between states has variable costs (e.g., "换教室").
   - Use BFS/DFS for state space exploration.

3. **Optimizations**: 
   - **Memory optimization**: Use rolling arrays when only previous row/column is needed.
   - **Precision handling**: Use `double` with `fixed << setprecision`, beware of floating-point errors in comparisons.
   - **Symmetry reduction**: If states are symmetric, reduce state space.

4. **Boundary Cases**: 
   - Check for division by zero when computing probabilities like `i/(i+j)`.
   - Handle edge cases where probabilities sum to less than 1 (e.g., absorbing states).

## Problem Patterns

1. **Game Probability**: Two-player games with random moves (e.g., Bag of mice).
2. **Collection Problems**: Expected time to collect all items (e.g., Coupon collector, Collecting Bugs).
3. **Random Walks**: Expected steps to reach boundaries (e.g., Broken robot).
4. **Decision under Uncertainty**: Optimal decisions with probabilistic outcomes (e.g., 换教室).
5. **Markov Chains**: Steady-state probabilities or hitting times.