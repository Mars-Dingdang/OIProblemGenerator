## Key Observations
- **Asymptotic Notation**: Big O (O) for upper bound, Big Omega (Ω) for lower bound, Big Theta (Θ) for tight bound. In contests, O is most common.
- **Constants Ignored**: Coefficients and lower-order terms are dropped (e.g., 3n² + 100n → O(n²)).
- **Logarithm Bases**: All logarithmic bases are equivalent in Big O (logₐ n = O(log n)).

## Common Complexity Patterns
- **Single Loop**: O(n)
- **Nested Loops**: O(nᵏ) for k nested loops over n.
- **Divide and Conquer**: Often O(n log n) (e.g., merge sort). Use Master Theorem for recurrences T(n) = aT(n/b) + f(n).
- **DFS/BFS on Graph**: O(V + E) for adjacency list.

## Optimization Tricks
- **Early Exit**: Break loops when possible to reduce average time.
- **Memoization/Dynamic Programming**: Trade space for time, turning exponential brute force into polynomial.
- **Two Pointers/Sliding Window**: Convert O(n²) to O(n) for subarray problems.
- **Binary Search**: Reduces O(n) search to O(log n).

## Problem Transformation
- **Sorting First**: Often enables O(n log n) solutions instead of O(n²).
- **Hash Map Lookup**: Use unordered_map for O(1) average lookups instead of O(n) linear search.
- **Prefix Sums**: Precompute sums to answer range queries in O(1).

## Master Theorem Cases
1. If f(n) = O(n^(log_b a - ε)), then T(n) = Θ(n^(log_b a)).
2. If f(n) = Θ(n^(log_b a) log^k n), then T(n) = Θ(n^(log_b a) log^(k+1) n).
3. If f(n) = Ω(n^(log_b a + ε)) and regularity condition holds, then T(n) = Θ(f(n)).