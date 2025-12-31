# 超立方体（Hypercube）及其相关算法初探

**Author:** 管晏如

### Key Ideas and Observations

- **Binary Representation & Bit Manipulation**: Each vertex of $ Q_n $ is labeled from $ 0 $ to $ 2^n - 1 $, and an edge exists between $ x $ and $ y $ iff $ \text{popcount}(x \oplus y) = 1 $. This allows efficient neighbor computation via bit flipping.

- **Spherical Layering**: Partition vertices by popcount (number of 1s in binary). Layer $ i $ has $ \binom{n}{i} $ nodes. Edges only exist between adjacent layers. Useful for BFS-based reconstruction and symmetry exploitation.

- **Graph Isomorphism Testing** ([JSOI2013]):
  - Check basic invariants: $ |V| = 2^n $, $ |E| = n \cdot 2^{n-1} $, all degrees equal $ n $, connected.
  - Fix node 0 arbitrarily; assign its neighbors as $ 2^0, \dots, 2^{n-1} $.
  - Use BFS to layer nodes by distance from 0 (equivalent to popcount if valid).
  - Reconstruct labels: For each node $ v \in S_k $, set label as bitwise OR of neighbors in $ S_{k-1} $.
  - Verify consistency across all edges.

- **Edge Coloring / Vertex Coloring Constraints**:
  - In [CF1543 E], color vertices so that each node’s neighbors have distinct colors.
  - Requires $ n \mid 2^n \Rightarrow n = 2^k $. Solution: $ \text{col}(v) = \bigoplus_{\text{bit } i \text{ set in } v} i $.

- **Hamiltonian Cycles via Gray Code**:
  - Recursive construction: $ G_1 = [0,1] $, $ G_n = G_{n-1} \frown (G_{n-1} + 2^{n-1}) $ reversed.
  - Ensures consecutive values differ by one bit.

- **Dilworth’s Theorem Application**:
  - On poset $ (2^{[n]}, \subseteq) $, maximum antichain size is $ \binom{n}{\lfloor n/2 \rfloor} $ (Sperner's Theorem).
  - Minimum chain cover equals max antichain size.
  - Constructed using perfect matchings between spherical layers.

- **Möbius Inversion on Subset Lattice**:
  - Möbius function: $ \mu(A,B) = (-1)^{|B|-|A|} $ when $ A \subseteq B $, else 0.
  - Corresponds to inclusion-exclusion principle.
  - Enables transformation between functions $ f(S) = \sum_{T \subseteq S} g(T) $ and $ g(S) = \sum_{T \subseteq S} \mu(T,S)f(T) $.

- **Subgraph Embedding – Grids** ([eJOI2021]):
  - Embed $ n \times m $ grid into $ Q_d $ such that adjacent cells differ in one bit.
  - Construct arbitrary-length Gray-like sequences by concatenating scaled Gray codes of powers of two.
  - Assign dimensions independently: row transitions affect disjoint bits from column transitions.
  - Optimize total range using greedy or DP over bit allocation.

- **Magic Labeling (Vertex)**:
  - Exists iff $ n \equiv 2 \pmod{4} $.
  - Construction uses linear combinations over $ \mathbb{F}_2 $: map input bits to carefully chosen vectors ensuring balanced sums.

- **Magic Labeling (Edge)**:
  - Exists iff $ n $ even and $ n > 2 $.
  - Key lemma: If a 2-regular bipartite graph decomposes into two Hamiltonian cycles, then edge-magic labeling exists.
  - Inductive extension: Build $ Q_{n+2} $ from four copies of $ Q_n $, shift labels appropriately, and fill inter-copy $ C_4 $ edges uniformly.

- **Symmetry and Automorphisms**:
  - Any vertex can be mapped to any other via XOR.
  - Coordinate permutations preserve structure.
  - Allows fixing labels during reconstruction (e.g., assume node 0 has known neighbors).