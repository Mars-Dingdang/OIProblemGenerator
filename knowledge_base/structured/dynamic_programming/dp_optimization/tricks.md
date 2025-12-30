## Key DP Optimization Techniques

### 1. State Definition Swapping
- **Idea**: Swap the roles of "answer" and "state dimension" when one dimension is too large.
- **Example (LCS)**: Instead of `dp[i][j] = LCS length`, define `dp[i][j] = shortest prefix of A where LCS with B[0..i] has length j`.
- **Example (Knapsack)**: When volume ≤ 1e18 is too large, define `dp[i][j] = minimum volume to achieve value j` (since total value ≤ 1e3).
- **Benefit**: Reduces state space from infeasible to manageable.

### 2. Bitmask Compression
- **Idea**: Compress multiple boolean states into a single integer using bit operations.
- **Example (Hamiltonian Cycle)**: Store `dp[mask][i]` as bits within `dp[mask]`, allowing O(1) transitions.
- **Implementation**: Use bitwise OR for transitions, bitwise AND for checks.
- **Complexity**: Reduces O(n²·2ⁿ) to O((n²/w)·2ⁿ) where w is machine word size (e.g., 32/64).

### 3. Preprocessing for O(1) Transitions
- **Idea**: Precompute next occurrence positions to enable constant-time state transitions.
- **Example (LCS with alphabet)**: For each position in string A, precompute next position of each character ('a'..'z').
- **Benefit**: Eliminates inner loops, reducing O(nm) to O(m² + 26n).

### 4. General Optimization Patterns
- **Space Optimization**: Use rolling arrays when only previous state is needed.
- **Order Optimization**: Reverse loop order for in-place updates (e.g., knapsack).
- **Pruning**: Skip impossible states early (e.g., INF checks).
- **Symmetry Exploitation**: Use symmetries to reduce state space (e.g., undirected graphs).

### 5. Problem Transformation Guidelines
- When a dimension is too large (≤1e18), consider swapping it with the answer dimension.
- When states are booleans, consider bitmask compression.
- When transitions require searching, preprocess to enable direct jumps.
- Always verify that the new state definition still allows correct transitions and final answer extraction.