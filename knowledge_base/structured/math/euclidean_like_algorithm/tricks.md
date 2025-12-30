## Key Observations & Optimizations

1. **Recursive Reduction**: The core idea is to recursively transform the problem into smaller parameters via two steps:
   - **Modulo step**: Reduce `a, b` modulo `c` to make `0 ≤ a, b < c`.
   - **Swap step**: Swap the roles of `a` and `c` using the identity:
     `f(a,b,c,n) = n*m - f(c, c-b-1, a, m-1)` where `m = floor((a*n+b)/c)`.
   This mimics the Euclidean algorithm, giving logarithmic complexity.

2. **Geometric Interpretation**: The sum counts lattice points under the line `y = (a*x + b)/c` for `x ∈ [0, n]`. The recursion corresponds to:
   - Removing integer parts of slope/intercept (counting trapezoidal points).
   - Swapping axes (reflecting the point set) to reduce the bounding box.

3. **Handling Multiple Sums**: For sums involving `i*floor(...)` or `floor(...)²`, derive simultaneous recurrences for `f, g, h` and compute them together in one recursion to avoid repeated work.

4. **Irrational Slopes**: For slopes like `k = (a√r + b)/c`, the algorithm still works by rationalizing the reciprocal after axis swap. Ensure `gcd(a,b,c)=1` to keep numbers manageable; complexity remains `O(log n)`.

5. **Early Termination**: If `m = floor((a*n+b)/c)` becomes zero, the recursion can stop immediately, improving practical speed.

6. **Universal Euclidean Algorithm**: A more abstract framework that models the process as a sequence of `U` (up) and `R` (right) operations in a monoid. This generalizes to a wider class of sums by defining appropriate merge rules for contributions.

7. **Common Problem Transformations**:
   - Sums of `floor((a*i+b)/c)` modulo something: compute the basic sum first, then apply modulo.
   - Alternating sums like `∑ (-1)^floor(i*√r)`: express as linear combination of `f` with different parameters.
   - Finding minimal fraction in an interval: use the reciprocal step similar to the swap in Euclidean-like algorithm.

8. **Implementation Notes**:
   - Use `long long` to avoid overflow; intermediate values like `n*(n+1)/2` can be large.
   - For modulo versions, precompute modular inverses of small constants (2, 6).
   - The recursive depth is `O(log min{a,c,n})`, so stack overflow is not an issue.
   - For the extended version (`f,g,h`), ensure all recursive calls return the triple together to maintain efficiency.