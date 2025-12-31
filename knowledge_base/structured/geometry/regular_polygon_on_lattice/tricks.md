# 《正多边形》命题报告

**Author:** 杨景钦

## Key Observations and Tricks

### 1. **Only Regular Quadrilaterals Exist on Lattice Points**
A crucial insight from number theory and geometry: **no regular k-gon with k ≠ 4 can have all vertices on integer coordinates**, except for squares (k=4). This is proven using:
- **Pick's Theorem**: For a simple polygon with integer vertices,
  
  \[ S = a + \frac{b}{2} - 1 \]
  
  where $ S $ is area, $ a $ is interior lattice points, $ b $ is boundary lattice points. Thus, the area must be a half-integer.

- **Contradiction for k = 3**: Area of equilateral triangle is $ \frac{\sqrt{3}}{4}a^2 $. Since $ a^2 \in \mathbb{Z} $, this area is irrational → contradicts Pick’s theorem.

- **k = 5,6,≥7**: Proven impossible via infinite descent or reduction to smaller impossible shapes (e.g., k=6 implies an equilateral triangle; k≥5 uses construction of smaller congruent regular polygon via vector shifts, contradicting minimality).

Thus, **only axis-aligned or rotated squares** need to be considered.

### 2. **Valid Points Must Be on Convex Hull**
Any point strictly inside the convex hull lies inside some triangle formed by three hull points (via triangulation), violating condition 2. Hence, only convex hull points are candidates.

Moreover, points on the hull cannot lie strictly inside any triangle due to convexity and no-three-collinear assumption.

### 3. **Efficient Square Enumeration**
Instead of enumerating all subsets, we:
- Compute the convex hull.
- Use a hash set to store all points for O(1) lookups.
- Enumerate every pair of hull points as adjacent vertices of a potential square.
- For each such pair, compute the next two vertices of the square (two possible orientations: clockwise and counter-clockwise rotation by 90°).
- Check if those two computed points exist in the input.
- If yes, verify all four points are on the hull and form a valid square.

Each square will be counted multiple times (once per edge), so divide total count accordingly or use symmetry-aware counting.

### 4. **Complexity Reduction via Hull Size Bound**
The number of points $ N_B $ on the convex hull of $ N $ lattice points within $ [1, R]^2 $ is bounded by $ O(R^{2/3}) $, not $ O(N) $.

This is derived by analyzing slopes between consecutive hull points. Each slope $ p/q $ (in reduced form) contributes at least $ p+q $ to the sum $ x_i + y_i $. Using distribution of coprime pairs and summation bounds, it’s shown that the maximum number of such segments before exceeding coordinate limits is $ O(R^{2/3}) $.

Hence, even though $ N \leq 50000 $, the effective working set size $ N_B $ is much smaller.

### 5. **Avoiding Redundant Checks**
Use a visited marker (like `vis[i][j][k]`) for directed edges used in a k-gon. But since only k=4 matters, just track whether a directed edge has been used in a square check.

Alternatively, canonicalize squares by their lexicographically smallest vertex and orientation to avoid overcounting.

### 6. **Implementation Notes**
- Precompute convex hull using Andrew’s monotone chain.
- Store points in unordered_set with custom hash (e.g., `x * BASE + y`).
- Rotate vectors: rotating $ (dx, dy) $ by 90° gives $ (-dy, dx) $ or $ (dy, -dx) $.
- Ensure floating-point-free computation using integers only.