# 浅谈回文串问题的相关算法及其应用

**Author:** 徐安矣

### Key Ideas and Observations

- **Arithmetic Sequence Structure of Palindromic Suffixes**: 
  A crucial lemma states that the lengths of all palindromic suffixes of a string can be partitioned into $ O(\log |S|) $ arithmetic sequences. This structural insight enables compact representation and efficient updates.

- **Efficient Update via Sequence Merging**:
  When appending a character $ c $, new palindromic suffixes are formed either as:
  - The single character $ c $,
  - Or by extending existing palindromic suffixes if both ends match $ c $.
  For each arithmetic sequence of palindromic suffixes represented as $ A, BA, BBA, \dots, B^kA $, only those where the last character of $ B $ is $ c $ can potentially extend. The last term $ B^kA $ must be checked individually based on its left neighbor.

- **Merging in Segment Tree Nodes**:
  In dynamic problems (e.g., range queries with modifications), a segment tree stores palindromic prefixes and suffixes for intervals. To merge two strings $ S $ and $ T $:
  1. Palindromic suffixes entirely in $ T $ are inherited.
  2. Those crossing $ S $ and $ T $ with center in $ T $: derived from palindromic *prefixes* of $ T $. If there’s an arithmetic progression of prefixes $ A, AB, ABB, \dots $, then extensions depend on whether the leftover part of $ T $ matches the reverse of $ B $.
  3. Center at boundary: at most one new palindrome may appear.
  4. Center in $ S $: similar to appending $ T $ symmetrically — involves checking symmetric expansion using reversed $ T $.

- **Binary Search for Extension Length**:
  During merge, when trying to extend a palindrome across $ S $ and $ T $, binary search over possible repetition counts $ k' $ is used to find maximal valid extension, leveraging string hashing for $ O(1) $ equality checks.

- **Hashing with Rollback Support**:
  Uses polynomial rolling hash with modulus and base chosen to minimize collisions. Implemented with block-based structure to support $ O(\sqrt{n}) $ update and $ O(1) $ query for dynamic hash values under character changes.

- **Use of Fail Pointers and Palindromic Trees (PAM)**:
  Palindromic tree provides unique node per distinct palindrome and supports incremental construction. Each node has a `fail` pointer to the longest proper palindromic suffix. Useful for counting occurrences via tree prefix sums (e.g., APIO2014).

- **Manacher Preprocessing for Static Queries**:
  For internal longest palindrome queries, precompute radii with Manacher. Then use RMQ (via ST-table or optimized block methods) to answer interval maximum radius queries. Combine with longest palindromic prefix/suffix detection to bound candidate centers.

- **Amortized Analysis Justification**:
  The logarithmic number of arithmetic sequences is justified by periodicity arguments (see reference [1]): long palindromic suffixes imply periodic structures, limiting how many non-overlapping periods can exist — hence $ O(\log n) $ segments.

- **Symmetry Exploitation**:
  Since palindromes are symmetric, operations on prefixes mirror those on suffixes. Thus, maintaining one implies the other under reversal.