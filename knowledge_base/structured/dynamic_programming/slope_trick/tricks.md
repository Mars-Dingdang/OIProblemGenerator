## Key Observations
- **Convexity**: The DP state function f(i, x) is convex in x for each i. This allows maintaining slope differences or breakpoints.
- **Slope Representation**: For integer x, convexity means the discrete difference f(x+1)-f(x) is non-decreasing.
- **Breakpoint Maintenance**: When slopes change by ±1 (e.g., in absolute value problems), store breakpoints in a max-heap (for negative slopes) and/or min-heap (for positive slopes).
- **Slope Maintenance**: When slopes vary arbitrarily, maintain sorted slope segments using data structures like priority queues or balanced trees.

## Common Transformations
1. **Adding |x - a|**: Insert two breakpoints at a (one for negative slope, one for positive).
2. **Min over y ≤ x**: Remove all positive slope breakpoints (rightmost heap).
3. **Convolution (min-plus)**: Merge slope segments of two convex functions (Minkowski sum).
4. **Translation**: Shift all breakpoints by a constant (use lazy tags).
5. **Restricted Transitions (e.g., |y-x| ≤ h)**: Shift negative slopes left by h, positive slopes right by h, then rebalance heaps.

## Optimization Patterns
- **Dual Heaps**: Use a max-heap for negative slopes and a min-heap for positive slopes with lazy shifts for bounded difference constraints.
- **Cost Updates**: The minimum cost can be updated incrementally when breakpoints are popped (e.g., add heap.top() - a[i]).
- **Reconstruction**: Optimal sequence can be recovered by backtracking from final breakpoints and taking minima.
- **Connection to Greedy**: Many problems solvable with slope trick also have greedy or min-cost flow interpretations.

## Typical Problems
- Making sequences non-decreasing/minimizing absolute deviations.
- Stock trading with buy/sell operations.
- Earthmoving/landscaping with transportation costs.
- Problems with piecewise linear convex costs.