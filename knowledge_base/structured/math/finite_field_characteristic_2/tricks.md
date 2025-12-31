# 浅谈有限域在OI 中的一些应用

**Author:** 戚朗瑞

### Key Ideas and Tricks

#### 1. **Finite Fields of Characteristic 2**
- In a finite field $ \mathbb{F}_{2^v} $, we have $ a + a = 0 $ for all elements $ a $. This means subtraction is equivalent to addition, and negation has no effect: $ -a = a $.
- This property allows cancellation of even-multiplicity terms — crucial for eliminating invalid configurations (like paths with repeated nodes).

#### 2. **Schwartz–Zippel Lemma for Randomized Checking**
- A nonzero multivariate polynomial of total degree $ d $ evaluates to zero on random inputs with probability at most $ d / |S| $, where $ S $ is the sampling set.
- Here, matrices $ X, Y, Z $ are filled with random values from $ \mathbb{F}_{2^v} $, making false negatives highly unlikely when $ v \gg k $.

#### 3. **Cancellation via Symmetry in Characteristic 2**
- For the **Longest Simple Path**, if a path repeats a vertex $ v_i = v_j $, then swapping labels $ p_i \leftrightarrow p_j $ in the permutation sum produces an identical term. Since each such pair appears twice, their sum cancels out: $ T + T = 0 $.
- Only simple paths (with distinct vertices) contribute nonzero values.

#### 4. **Polynomial Construction Using Permutation Encoding**
- To enforce uniqueness (e.g., no repeated vertices or same color-number pairs), use sums over permutations:
  
  $$
  \sum_{p \in \text{Perm}(k)} \prod_{i=1}^k Y_{v_i, p_i}
  $$

  This is analogous to computing a determinant-like structure but in characteristic 2 (so signs don’t matter).

#### 5. **Efficient Computation via Inclusion-Exclusion (容斥)**
- Instead of iterating over permutations, apply inclusion-exclusion to relax constraints:

  $$
  \sum_{p \in \text{Perm}(k)} \prod_i Y_{v_i,p_i} = \sum_{S \subseteq [k]} \prod_{i=1}^k \left( \sum_{j \in S} Y_{v_i,j} \right)
  $$

  Because $ -1 = 1 $ in $ \mathbb{F}_2 $, the alternating sign disappears.

- This transforms the hard-to-compute permutation sum into a sum over subsets, enabling dynamic programming with polynomial space.

#### 6. **Dynamic Programming over Subsets**
- Use DP states like $ f(u, s) $: sum of contributions of trees rooted at $ u $ with $ s $ nodes.
- Transition by adding subtrees along edges, multiplying edge variables $ X_{u,v} $ and node weights precomputed from $ Y $ and $ Z $.
- Even if intermediate steps include overlapping nodes, symmetry ensures invalid cases cancel out due to duplication.

#### 7. **Solution Reconstruction (Outputting the Path/Tree)**
- For both problems, reconstruct the solution greedily:
  - Fix one valid starting point (nonzero polynomial value).
  - Iteratively add neighbors that cause a change from zero to nonzero.
  - Contract nodes and reduce parameters recursively.
- Relies on the fact that any correct extension will make the overall expression nonzero.

#### 8. **Use of Multiple Random Matrices for Independence**
- Separate matrices $ X $ (edge indicators), $ Y $ (node labeling), and $ Z $ (color+label uniqueness) ensure independence between different parts of the construction.
- Prevents interference and maintains low collision probability.