# 浅谈信息学竞赛中数据的构造与生成

**Author:** 刘一平

### Key Ideas and Tricks

#### **Random Permutations**
- **Algorithm 1 (Fisher-Yates variant)**: Iteratively swap `p[i]` with a random element from `[1, i]`. Proven to generate uniform permutations via induction.
- **Algorithm 2 (Classic Fisher-Yates)**: Swap `p[i]` with a random element from `[i, n]`. Also yields uniform distribution.

#### **Unique Element Sequences**
- When sampling `n` distinct values from `[1, m]`:
  - If `m ≤ 2n`, generate a full permutation of size `m` and take first `n` elements.
  - If `m > 2n`, use rejection sampling with expected `O(n)` time due to high success probability.

#### **Fixed-Sum Positive Integer Sequences**
- Transform problem into selecting `n-1` distinct split points in `[1, m-1]` → reduces to unique sequence generation.
- Generalized to bounded integers via shifting.

#### **Tree Generation**
- **Method 1 (Random Parent)**: Each node `i` chooses parent uniformly from `[1, i−1]`. Expected height is `Θ(log n)`.
- **Method 2 (Bounded Random Parent)**: Restrict parent choice to `[max(1, i−B), i−1]`. Smaller `B` creates deeper trees, better for testing path-based algorithms.
- **Method 3 (Prufer Sequence)**: Uniformly sample Prufer code of length `n−2`, then reconstruct tree. Enables degree-constrained trees.
- **Method 4 (Chain)**: Linear tree; useful for worst-case path length tests.
- **Method 5 (Complete Binary Tree)**: Node `i` has parent `⌊i/2⌋`; induces `Θ(n log n)` light subtree sum, good for testing heavy-light decomposition.
- **Method 6 (Hybrid Structure)**: Combine binary tree (first `B1 ≈ 2√n` nodes) with chains (each of length `B2 ≈ √n`) attached underneath. Balances long paths and large light subtrees.

#### **Cactus Graphs**
- **Method 1 (Via Block-Cut Tree / Round-Square Tree)**: Generate a tree as round-square tree, assign circles (original nodes), remove square leaves, build cactus from cycles.
- **Method 2 (DFS Back-Edge Addition)**: During DFS backtracking, with probability `P`, connect current node to an ancestor along unmarked edges, marking the entire path as part of a cycle.
- **Method 3 (Random Valid Edge Addition)**: Repeatedly attempt to add random edge between two nodes if their path contains no already-cycled edge.

#### **Bracket Sequences**
- Use path representation (`a_i`) to define balance and defect.
- A bijection `Φ` maps all balanced strings of defect `k` to valid (fully matched) ones using recursive transformation based on shortest balanced prefix.
- To generate random valid bracket string: uniformly pick any balanced string (by choosing positions for '('), apply `Φ` to convert it into a valid one.

#### **Hashing Pitfalls**
- **Birthday Paradox**: For modulus `M`, collisions likely when number of items reaches `~√(2M ln 2)`. In single mod ~1e9, collision risk becomes significant at ~3e4 entries. Solution: use double hashing with two mods.
- **Natural Overflow (Mod 2^64)**: Vulnerable even with odd base `B`.
  - Construct string `s_k` recursively: `t₀ = 'A'`, `tᵢ = tᵢ₋₁ + flip(tᵢ₋₁)` where flip swaps 'A'↔'B'.
  - At `k=11`, difference in hash becomes divisible by `2^64`, causing collision.
- **Tree Hashing Flaw**: Some linear-time hashes rely only on multiset of depth sequences (`H(T)`). Swapping subtrees with identical depth sequences preserves hash but changes structure → easy to break. Correct approach uses sorted children by `(hash, size)` to form canonical form.

### Observations
- Weak randomness leads to weak test data that fails to expose bugs in complex algorithms (e.g., HLD, DSU on tree).
- Targeted constructions (like deep trees, long chains, large cycles, hash collisions) are essential for robust testing.
- Always consider adversary design when validating solutions.