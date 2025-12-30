## Key Observations

### 1. **Manhattan Distance Optimization**
- For maximizing/minimizing Manhattan distance between points, use the transformation:
  - Let `u = x + y`, `v = x - y`
  - Then `|x1 - x2| + |y1 - y2| = max(|u1 - u2|, |v1 - v2|)`
- This reduces the problem to finding max difference in transformed coordinates

### 2. **Chebyshev Distance Optimization**
- For Chebyshev distance problems, the inverse transformation helps:
  - Let `u' = (x + y)/2`, `v' = (x - y)/2`
  - Then `max(|x1 - x2|, |y1 - y2|) = |u1' - u2'| + |v1' - v2'|`

### 3. **Geometric Interpretation**
- Manhattan distance: L1 norm, measures distance along grid lines
- Chebyshev distance: L∞ norm, measures distance as maximum coordinate difference
- Euclidean distance: L2 norm, the "straight line" distance

### 4. **Problem Transformation Patterns**
- **Maximum Manhattan distance between points**:
  - Compute transformed coordinates `(x+y, x-y)`
  - Answer = `max(max_u - min_u, max_v - min_v)`
  - Complexity: O(n) instead of O(n²)

- **Minimum enclosing square (Chebyshev)**:
  - Transform to Manhattan space
  - Solve using median finding techniques

### 5. **Common Pitfalls**
- Floating-point precision with Euclidean distance
- Integer overflow when squaring large coordinates
- Off-by-one errors in grid-based problems

### 6. **Dimensionality Reduction**
- For high-dimensional distance problems, consider:
  - Random projections (Johnson-Lindenstrauss lemma)
  - Locality-sensitive hashing
  - Space partitioning trees (KD-trees, R-trees)

### 7. **Monotonicity Properties**
- Manhattan distance satisfies triangle inequality
- Chebyshev distance is rotationally invariant at 45° increments
- All three metrics are translation invariant