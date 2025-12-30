## Key Observations
- **Divide and Conquer on Point Pairs**: CDQ splits point pairs into three categories: (left, left), (left, right), (right, right). Only the cross pairs (left, right) need explicit processing.
- **Sorting to Reduce Dimensions**: After sorting by one attribute (e.g., `a`), the condition `a_i ≤ a_j` becomes automatically satisfied for cross pairs, reducing a 3D problem to 2D.
- **Data Structure for Remaining Constraints**: Use a Fenwick Tree (BIT) or segment tree to handle the remaining constraints (e.g., `b` and `c`).
- **Two-Pointer Sweep**: Sort left and right halves by `b`, then use a two-pointer sweep to insert left points into the data structure as `b` increases, allowing O(n) insertions.

## Optimizations
- **Discretization**: Discretize values (e.g., `c`) to reduce BIT size and complexity.
- **Merge Sort Style Sorting**: Instead of `std::sort` in each CDQ call, pre-sort globally and use merge operations to maintain sorted order, reducing log factor.
- **Clearing BIT Efficiently**: Instead of resetting the entire BIT, undo additions by subtracting values (as shown in template) to keep O(n log n) complexity.

## Common Problem Transformations
1. **3D Partial Order**: Count pairs `(i, j)` with `a_i ≤ a_j, b_i ≤ b_j, c_i ≤ c_j`. Classic CDQ application.
2. **Dynamic Inversion Counting**: Convert to a 3D problem where dimensions are (index, value, deletion time).
3. **1D/1D DP Optimization**: For DP transitions like `dp[i] = max_{j < i, a_j < a_i, b_j < b_i} dp[j] + 1`, CDQ processes cross transitions similarly to 3D partial order.
4. **Dynamic to Static**: For offline problems with modifications and queries, CDQ treats time as a dimension, allowing processing of all modifications before queries in each divide step.

## Implementation Notes
- **Order Matters for DP**: When optimizing DP, the cross-step must be placed **between** the two recursive calls to ensure DP values are computed in correct order (like in-order traversal of recursion tree).
- **Handling Identical Elements**: In counting problems, identical elements need careful handling (merge duplicates and adjust counts).
- **Multi-Layer CDQ**: For higher dimensions (e.g., 4D), nest CDQ layers, each reducing by one dimension.