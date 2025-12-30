## Key Observations

1. **Existence Condition**: Equation \(a_1x_1 + a_2x_2 = b\) has integer solutions iff \(\gcd(a_1, a_2) \mid b\).

2. **General Solution Structure**: For two variables:
   - Particular solution \((x_0, y_0)\) from extended Euclidean algorithm
   - General solution: \(x = x_0 + \frac{b}{d}t\), \(y = y_0 - \frac{a}{d}t\) where \(d = \gcd(a, b)\), \(t \in \mathbb{Z}\)

3. **Multiple Variables**: Reduce n-variable equation to (n-1)-variable by combining first two coefficients:
   - Let \(d_1 = \gcd(a_1, a_2)\)
   - Solve \(d_1y_1 + a_3x_3 + \cdots + a_nx_n = b\)
   - Then solve \(a_1x_1 + a_2x_2 = d_1y_1\)

4. **Frobenius Coin Problem (Sylvester's Theorem)**: For coprime \(a, b\), largest unrepresentable integer as \(ax + by\) with \(x, y \geq 0\) is \(ab - a - b\).

## Optimization Patterns

1. **Dijkstra on GCD States**: When selecting numbers to achieve gcd=1 with minimum cost (CF 510D), treat each gcd value as a node, transition via gcd(current, lᵢ) with cost cᵢ.

2. **DP with Sparse States**: For the same problem, use DP with hashmap storing minimum cost for each gcd value encountered.

3. **Non-negative Solutions**: To find non-negative solutions to \(ax + by = c\), from general solution:
   - \(x_0 + \frac{b}{d}t \geq 0\) and \(y_0 - \frac{a}{d}t \geq 0\)
   - Solve for integer t range

4. **Counting Solutions in Range**: Number of integer solutions with \(x_1, x_2, \ldots, x_n\) in given bounds can be computed using inclusion-exclusion after finding general solution.

## Common Transformations

1. **Modular Inverse**: \(ax \equiv 1 \pmod{m}\) solvable iff \(\gcd(a, m) = 1\), solution via extended Euclidean algorithm.

2. **Chinese Remainder Theorem**: System \(x \equiv a_i \pmod{m_i}\) reducible to solving Bézout identities.

3. **Linear Combination Problems**: "Can value k be formed from given numbers?" → check if gcd of numbers divides k.

4. **Minimal Combination Cost**: When each number has cost, find cheapest combination achieving gcd=1 → graph/DP on gcd states.