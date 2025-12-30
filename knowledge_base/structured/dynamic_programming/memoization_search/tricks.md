## Key Observations

1. **State Uniqueness**: Memoization ensures each state `(pos, tleft)` is computed exactly once, transforming exponential DFS into polynomial DP.

2. **Top-down Recursion**: The recursion naturally follows the problem's decision tree (take/skip items), making the state transition intuitive.

3. **Lazy Evaluation**: States are computed only when needed, unlike iterative DP which may compute all states upfront.

## Common Patterns

- **Memo Array Initialization**: Initialize with `-1` (or another sentinel) to indicate uncomputed states.
- **Base Cases**: Handle terminal states (e.g., `pos > n`) and invalid states (e.g., `tleft < 0`) explicitly.
- **State Representation**: Choose parameters that uniquely identify a subproblem; often these match the dimensions of the DP table in iterative version.

## Optimization Notes

- **Memory Order**: For multi-dimensional memo, ensure dimensions match parameter order to maximize cache locality.
- **Sentinel Values**: Use `-1` for uncomputed states, but be careful if `-1` is a valid result (use a separate `visited` array if needed).

## When to Use

- **Complex State Transitions**: When the order of iteration is non-trivial (e.g., DAG DP, tree DP).
- **Boundary Simplicity**: Recursive base cases can be easier to write correctly than iterative loops.
- **Debugging**: The call stack shows the exact path to a state, aiding debugging.

## Limitations

- **Stack Overflow**: Deep recursion may cause stack overflow; consider iterative DP or increasing stack size.
- **Overhead**: Function call overhead and cache misses may make it slower than iterative DP.
- **Optimization Barriers**: Hard to apply space optimizations like rolling arrays.

## Transformation Pattern

1. Write naive recursive solution.
2. Identify state parameters.
3. Add memo array of size `state_dimensions`.
4. At start of recursive function, check if state already computed; if yes, return stored value.
5. At end of function, store result in memo before returning.