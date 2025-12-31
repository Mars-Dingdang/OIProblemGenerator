# 非常规大小分块算法初探

**Author:** 徐明宽

### Key Ideas and Tricks

- **Optimal Block Size via Balancing Terms**: For a total complexity of the form `O(A + B)`, where `A` decreases and `B` increases with block size `S`, the optimal `S` is found by solving `A = B`. This avoids calculus and simplifies derivation.

- **Generalization to Three Terms**: If complexity is `O(A + B + C)` with mixed monotonicity, solve `A = B`, `A = C`, etc., and compare results to find the best `S`.

- **Constant Optimization in Practice**:
  - Adjust block size based on actual runtime behavior, not just asymptotics.
  - Use reverse operations when unblocked elements exceed half a block: instead of updating partial blocks directly, update the full block and subtract changes from the outside part (only works for invertible operations like addition).

- **Method of Four Russians (MoFR)**:
  - Divide data into blocks of size `S = O(log n)`.
  - Preprocess all possible configurations of small blocks (e.g., ±1 sequences for RMQ, bracket sequences for LA) in `O(c^S * poly(S))` time.
  - Use precomputed tables to answer intra-block queries in `O(1)`.
  - Inter-block queries handled with standard structures (e.g., ST table over block minima).
  - Achieves `O(n)` preprocessing and `O(1)` query for ±1 RMQ, LCA, and LA.

- **Reduction Between Problems**:
  - **LCA → ±1 RMQ**: Via Euler Tour; depth differences are ±1.
  - **RMQ → LCA**: Build Cartesian Tree; RMQ[l,r] = LCA of nodes l and r.
  - **LA → LCA**: Using ladder decomposition and leaf clustering with MoFR.

- **Space Optimization in Sieve Algorithms**:
  - Apply blocking to the Sieve of Eratosthenes: process intervals of size `S`.
  - Precompute primes up to `√n`, then sieve each block.
  - Space complexity reduced from `O(n)` to `O(√n/log n + S)`; set `S = √n/log n` for `O(√n/log n)` space while maintaining `O(n log log n)` time.

- **FFT Optimization in String Matching**:
  - Break strings into blocks, compute pairwise convolutions via FFT.
  - Query: combine full block results with edge-case brute force.
  - Optimize block size `S = √(n w log n)` to minimize `O(n² log S / S + q(n/S + S/w))`.
  - Additional tricks: merge real FFTs, reduce precision, use bitset for final matching.

- **Efficient Preprocessing via Configuration Enumeration**:
  - When number of distinct block types is small (e.g., `2^S`, `4^{S²}`), exhaustive preprocessing is feasible.
  - Example: 01 matrix multiplication — precompute all `S×S` block products.

- **Cache Efficiency**: Smaller blocks improve cache locality. In segmented sieve, processing small chunks allows better use of CPU cache, improving practical performance even if asymptotic time is unchanged.