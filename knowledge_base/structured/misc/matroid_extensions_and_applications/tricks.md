# 浅谈拟阵的一些拓展及其应用

**Author:** 杨乾澜

### Key Ideas and Observations

- **Matroid Definition**: A matroid $ M = (S, \mathcal{I}) $ consists of a finite ground set $ S $ and a family of independent sets $ \mathcal{I} \subseteq 2^S $ satisfying:
  1. **Heredity**: If $ I \in \mathcal{I} $ and $ J \subseteq I $, then $ J \in \mathcal{I} $.
  2. **Exchange (Augmentation)**: If $ I, J \in \mathcal{I} $ with $ |I| < |J| $, there exists $ z \in J \setminus I $ such that $ I \cup \{z\} \in \mathcal{I} $.

- **Rank Function**: The rank function $ r(U) $ gives the size of the largest independent subset in $ U \subseteq S $. It satisfies:
  - Boundedness: $ 0 \leq r(U) \leq |U| $
  - Monotonicity: $ A \subseteq B \Rightarrow r(A) \leq r(B) $
  - Submodularity: $ r(A \cup B) + r(A \cap B) \leq r(A) + r(B) $

  These properties allow an algebraic approach—defining a valid rank function implies a matroid.

- **Duality**: The dual matroid $ M^* $ has independent sets $ \mathcal{I}^* = \{ I : \exists \text{ base } B \text{ of } M, B \subseteq S \setminus I \} $. Its rank function is $ r^*(U) = |U| - r(S) + r(S \setminus U) $.

- **Deletion and Contraction**:
  - Deletion $ M \setminus Z $ removes elements $ Z $ from $ S $.
  - Contraction $ M / Z = (M^* \setminus Z)^* $, with rank $ r_{M/Z}(U) = r_M(Z \cup U) - r_M(Z) $. Intuitively, contraction forces inclusion of a basis in $ Z $.

- **Matroid Intersection**:
  - Given two matroids $ M_1, M_2 $ over the same ground set, find the largest common independent set.
  - Not necessarily a matroid itself.
  - **Min-Max Theorem**: 
    $$
    \max_{I \in \mathcal{I}_1 \cap \mathcal{I}_2} |I| = \min_{U \subseteq S} \left( r_1(U) + r_2(S \setminus U) \right)
    $$
  - **Algorithm**:
    - Use an exchange graph $ D_{M_1,M_2}(I) $: directed edges from $ y \in I $ to $ x \notin I $ if $ I - y + x \in \mathcal{I}_1 $, and reverse direction if $ \in \mathcal{I}_2 $.
    - Define $ X_1 = \{x \notin I : I + x \in \mathcal{I}_1\}, X_2 = \{x \notin I : I + x \in \mathcal{I}_2\} $.
    - Repeatedly find shortest path from $ X_1 $ to $ X_2 $, update $ I \gets I \Delta P $ (symmetric difference), until no path exists.
    - Final $ I $ achieves maximum size.
  - **Time Complexity**: $ O(r^2 n) $, where $ r = \max(r_1(S), r_2(S)) $, due to at most $ r $ augmentations, each involving BFS on $ O(n) $ nodes and $ O(rn) $ edges.

- **Weighted Matroid Intersection**:
  - Maximize total weight $ \sum \omega(e) $ over common independent sets.
  - Modified min-max theorem:
    $$
    \max_I \sum_{e \in I} \omega(e) = \min_{\omega_1+\omega_2=\omega} \left( \max_{I_1 \in \mathcal{I}_1} \omega_1(I_1) + \max_{I_2 \in \mathcal{I}_2} \omega_2(I_2) \right)
    $$
  - Algorithm uses vertex weights in the exchange graph: $ f(x) = \omega(x) $ for $ x \notin I $, $ f(x) = -\omega(x) $ for $ x \in I $. Find min-weight path (by sum of node weights), breaking ties by edge count. No negative cycles exist.

- **Multiple Matroid Intersection**:
  - For $ \geq 3 $ matroids, the problem is NP-hard (reduction from Hamiltonian Path).

- **Matroid Union**:
  - Union of $ k $ matroids $ M_1, \dots, M_k $ over possibly overlapping ground sets: a set is independent iff it can be partitioned into $ k $ parts, each independent in its respective matroid.
  - Rank function:
    $$
    r_M(U) = \min_{T \subseteq U} \left( |U \setminus T| + \sum_{i=1}^k r_i(T \cap S_i) \right)
    $$
  - Proven via transformation to disjoint ground sets and using a mapping function.

- **Applications**:
  - **Bipartite Matching**: Can be modeled as intersection of two partition matroids (degree ≤1 on left/right), or as union of star-shaped matroids.
  - **Minimum Arborescence (Tree-Shaped Graph)**: Intersection of graphic matroid (acyclic when undirected) and partition matroid (in-degree ≤1 except root).
  - **Colorful Tree / Rainbow Spanning Tree**: Intersection of graphic matroid and partition matroid based on colors.
  - **Covering Edges with Trees**: Using matroid union—graph can be covered by $ k $ spanning trees iff $ \forall U \subseteq V, |E(U)| \leq k(|U| - 1) $.

- **Representability**:
  - A matroid is representable over field $ \mathbb{F} $ if its independence corresponds to linear independence of vectors in $ \mathbb{F}^k $.
  - **Regular Matroid**: Representable over all fields. Graphic matroids are regular.
  - **Binary Matroid**: Representable over $ GF(2) $. A matroid is binary iff it does not have $ U_2^4 $ as a minor.

- **Minors and Characterization**:
  - Minors (via deletion/contraction) help characterize representability. E.g., a matroid is regular iff it has no $ U_2^4, F_7, F_7^* $ minors.

- **Key Insight**: Many combinatorial structures satisfy matroid axioms. Operations like intersection and union enable decomposition of complex constraints into simpler ones, enabling algorithmic solutions via greedy or augmenting-path techniques.