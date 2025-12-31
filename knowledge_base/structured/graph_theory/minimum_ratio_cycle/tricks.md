# 浅谈最小比率环及其应用

**Author:** 魏佳泽

## Key Ideas and Tricks

1. **Problem Transformation via Binary Search**:
   - The core idea is to use binary search on the possible values of the minimum ratio $\lambda$.
   - For a given candidate ratio $\lambda$, transform the graph by setting the weight of each edge $e$ to $c(e) - \lambda \cdot t(e)$, where $c(e)$ is the cost and $t(e)$ is the time.
   - A cycle exists with a ratio less than $\lambda$ if and only if this transformed graph contains a negative cycle.

2. **Negative Cycle Detection**:
   - Use the Bellman-Ford algorithm or SPFA (Shortest Path Faster Algorithm) to detect negative cycles in the transformed graph.
   - If a negative cycle is found, it means the current $\lambda$ is too high, so we can search lower. Otherwise, we must search higher.

3. **Convergence and Precision**:
   - The binary search continues until the desired precision is achieved.
   - The initial search bounds can be set based on the minimum and maximum individual edge ratios.

4. **Application to Fractional Programming**:
   - This technique is an instance of Dinkelbach's algorithm or parametric search applied to fractional programming problems.
   - It converts a non-linear optimization problem (minimizing a ratio) into a series of linear decision problems (detecting negative cycles).