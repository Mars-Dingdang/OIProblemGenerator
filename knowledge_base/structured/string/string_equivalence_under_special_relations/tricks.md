# 特殊等价关系下的字符串问题

**Author:** 章弥炫

### Key Ideas and Observations

- **Generalized Equivalence via Context Functions**: Two strings $ S \sim T $ if their generated sequences $ F_l(S) = F_l(T) $, where $ F_l(S)[i] = f_l(S[1,i-1], S[i]) $. This allows defining non-trivial equivalences like equality patterns, order types, or palindrome structures.

- **Hereditary Property of Substrings (Lemma 2.1)**: If $ S \sim T $, then all corresponding substrings $ S[i,j] \sim T[i,j] $. This is crucial for recursive and incremental algorithms.

- **Efficient Hashing with Persistent Segment Trees**: Maintain $ F_l(j,i) $ hashes dynamically. Only update positions where $ f_l(S[j-1,i-1], S[i]) \neq f_l(S[j,i-1], S[i]) $. The number of such changes is bounded by $ G(S) $, leading to $ O(G(S) \log n) $ complexity.

- **Suffix Sorting via Recursive Grouping**: Use hashing to group suffixes by their first $ 2^k $ characters, then recursively sort within and between groups. Total complexity: $ O(n \log^2 n + G(S) \log n) $.

- **KMP Adaptation**: The standard KMP failure function works under this framework by comparing $ f_l $ values at candidate borders. Valid because equivalence preserves prefix-suffix structure.

- **AC Automaton Compression**: Merge child nodes in the trie when $ f_l(S_u, c) $ yields the same value, ensuring state minimization. Correctness follows from Lemma 2.2: appending the same character to equivalent strings produces equal $ f_l $ outputs.

- **Border Structure Theorem (Theorem 2.1)**: All borders of a string form $ O(\log n) $ arithmetic progressions. Proof uses the fact that if $ x < y < 2x $ are borders, then $ 2x - y $ is also a border — a generalized periodicity lemma under equivalence.

- **Suffix Automaton Construction**: Built incrementally from right to left. Transition count is $ O(G(S)) $ due to limited number of distinct $ f_r $-based transitions. Each edge stores transitions indexed by $ f_r $ values.

- **Ukkonen-style Online Suffix Tree**: Maintain implicit suffix tree with active point and remainder. Use balanced trees on edges to manage `link` pointers for intermediate nodes. Complexity: $ O(n \log n) $ ignoring $ f_l $ evaluation.

- **Bidirectional Suffix Tree Maintenance**: Support front and back insertions by maintaining both forward and reverse suffix trees, linked via LCT (Link-Cut Trees). Forward insertion uses reverse tree to locate matching substrings, then updates forward tree accordingly.

- **Basic Substring Structure Construction**: From suffix tree, extract equivalence classes as intervals of substring occurrences. Merge overlapping ones with consistent occurrence counts to build a 2D “staircase” partition of substrings.

- **Dynamic Programming on Equivalent Classes**: In problems involving concatenation under permutation, use DP over boundaries of equivalent substrings. Multiply by factorial of new character types introduced at zero-$f_l$ positions.