# 浅谈Lyndon 分解

**Author:** 胡昊

### Key Ideas and Observations

- **Lyndon Word Definition**: A string $ S $ is a Lyndon word (or simple string) if it is strictly smaller in lexicographical order than all of its nontrivial cyclic rotations (equivalently, all of its proper suffixes).

- **Uniqueness of Decomposition**: Every string has a unique Lyndon decomposition $ S = w_1 w_2 \ldots w_m $ such that each $ w_i $ is a Lyndon word and $ w_1 \geq w_2 \geq \cdots \geq w_m $. This can be proven by contradiction: assuming two different decompositions leads to an inequality contradiction based on the ordering.

- **Duval’s Algorithm Insight**:
  - The algorithm processes the string in linear time using three pointers: `i` (start of current approximate Lyndon prefix), `j` (current character being compared), and `k` (reference pointer within the base Lyndon block).
  - It maintains an *approximately simple* string $ s_2 = w^a w' $, where $ w $ is a Lyndon word and $ w' $ is a prefix of $ w $.
  - When $ S[j] = S[k] $: extend the repetition; increment both `j` and `k`.
  - When $ S[j] > S[k] $: the current extended string remains lexicographically minimal under rotation — continue extending with reset reference (`k ← i`).
  - When $ S[j] < S[k] $: the structure breaks; we finalize as many full copies of $ w $ as possible (from position `i` up to `k`) into the decomposition, then restart from after those segments.

- **Key Lemma**: During decomposition, once a segment fails to maintain the Lyndon property upon extension, all complete repetitions of the base Lyndon word so far can be safely output because they satisfy the decreasing condition.

- **Applications**:
  - **Minimum String Representation**: Concatenate $ S + S $, compute its Lyndon decomposition, and find the last Lyndon factor starting in the first half. Its start index gives the minimal rotation.
  - **Optimal Partitioning**: To minimize the maximum part when splitting into at most $ k $ substrings, use the Lyndon decomposition $ w_1^{m_1} w_2^{m_2} \ldots $. The answer depends on how $ k $ compares to total number of factors.
  - **Queries on Suffixes**: Using the $ O(n \log n) $ method via suffix arrays allows precomputing Lyndon heads for every suffix, enabling efficient query responses.
  - **Prefix Minimum Suffix**: While processing with Duval's algorithm, one can track the smallest suffix of each prefix — it often corresponds to the last complete or partial Lyndon block.

- **Proof Techniques**:
  - Use of contradiction in uniqueness proof.
  - Structural analysis of cyclic shifts to prove Lyndon properties.
  - Amortized analysis for Duval’s algorithm: each character is involved in comparisons at most twice, leading to $ O(n) $ total time.