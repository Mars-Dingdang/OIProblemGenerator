## Key Observations & Optimizations

### 1. **Space Optimization**
- 0/1 knapsack can be optimized from O(n*m) to O(m) space by iterating capacity in reverse
- This prevents reusing items multiple times (which would give unbounded knapsack)

### 2. **K-th Best Knapsack**
- Maintain K best values for each capacity instead of just the optimal
- Merge two sorted lists: dp[j] (without current item) and dp[j-w[i]] + v[i] (with current item)
- Complexity: O(n * m * K) with careful merging

### 3. **Problem Transformations**
- **Subset Sum**: Set values equal to weights
- **Partition Problem**: Check if subset sum equals total/2
- **Coin Change**: Unbounded knapsack variant
- **Target Sum**: Add +/- signs to weights

### 4. **Common Optimizations**
- **Monotonic Queue**: For bounded knapsack with identical items
- **Binary Optimization**: Split bounded items into powers of 2 for 0/1 knapsack
- **Slope Trick**: For convex cost functions

### 5. **Special Cases**
- **Group Knapsack**: Process groups, then items within groups
- **Dependency Knapsack**: Tree DP with knapsack on each node
- **Multiple Constraints**: Add more dimensions to dp array

### 6. **Initialization Tricks**
- Maximization: Initialize with 0 or -INF
- Minimization: Initialize with INF
- Exact sum: dp[0] = 0, others = -INF
- At least sum: Different initialization strategy

### 7. **Order Matters**
- For 0/1: iterate capacity descending
- For unbounded: iterate capacity ascending
- For group: iterate capacity outside, items inside

### 8. **Debugging Tips**
- Print dp table for small cases
- Check initialization values
- Verify iteration order matches problem type
- Test edge cases: empty set, full capacity, zero items