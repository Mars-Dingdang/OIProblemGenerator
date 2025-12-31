# 《黑白树》命题报告

**Author:** 闫书弈

### Key Observations and Tricks

- **Expectation Transformation**: Instead of directly computing expectation over edge sets and colorings, reframe the problem using linearity of expectation and combinatorial counting.

- **Critical Insight - Invalid Edge Sets Form Chains**:
  - For a fixed coloring, an edge is *bad* if the number of black nodes in both components after removal is equal.
  - The key structural insight: unless all nodes are white, the set of bad edges forms either the empty set or a simple path (i.e., a chain).
  - This is proven by contradiction: if three branches meet at a node and all incident edges are bad, it forces all subtrees to have zero black nodes → only possible when all are white.

- **Combinatorial Counting of Valid Colorings**:
  - For a fixed path between nodes `a` and `b`, let `sa` and `sb` be sizes of the subtrees hanging off the ends of the path (excluding the path).
  - The number of colorings where the two sides have equal black nodes is `C(sa + sb, sa)` — choose `sa` black nodes among `sa + sb` total positions such that both end-subtrees have same count.

- **Inclusion–Exclusion over Paths**:
  - Use Möbius-style subtraction: count all paths as potentially bad, then subtract contributions from subpaths to ensure exactness.

- **Algebraic Reformulation Using Inverse**:
  - Let `t = (m+1)^(-1) mod MOD`. Then `(m+1)^x = (m+1)^{n-1} * t^{n-1-x}`.
  - Now interpret `t^{n-1-x}` as weight over edge sets where only *bad* edges contribute.
  - This transforms the sum into weighted counting over configurations where bad edges form chains.

- **Tree Centroid Decomposition + FFT Optimization**:
  - To efficiently sum over all paths: use centroid decomposition.
  - For each point in a subtree, define polynomial term: `(t-1)^k / sa! * x^sa`, where `k` is distance to centroid, `sa` is size of detached subtree.
  - Convolve polynomials from different subtrees via FFT to get combined contributions.
  - Subtract intra-subtree contributions to avoid overcounting.

- **Hybrid FFT / Brute-force Strategy**:
  - Set threshold `K ≈ √(n log n)`.
  - When component size ≤ K: compute pairwise interactions in O(K²).
  - Otherwise: use FFT for convolution.
  - Total complexity becomes `O(n² log n / K + nK)`, minimized at `K = Θ(√(n log n))` → `O(n√(n log n))`.

- **Special Case Handling**:
  - When `m = 998244352`, then `m+1 ≡ 0 mod MOD`, so only `x=0` contributes.
  - Only valid configurations: all white, or tree is a chain with endpoints black and others white.

- **Modular Arithmetic Note**:
  - Output is scaled by `2^(2n−1)` to make values integral; this cancels denominators from probabilistic model.