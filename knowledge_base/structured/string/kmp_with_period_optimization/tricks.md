# 《Fim 4》命题报告

**Author:** 吴瑾昭

### Key Ideas and Observations

- **Problem Decomposition**: The occurrence of a query string $ t $ in the concatenated string $ S = s_{a_1} + \cdots + s_{a_m} $ can be split into two cases:
  1. Occurrences entirely within a single $ s_{a_i} $.
  2. Occurrences spanning two or more consecutive $ s_{a_i}, s_{a_{i+1}}, \ldots $

- **Use of SAM on Trie**:
  - A trie is built from all dictionary strings $ s_i $, and a suffix automaton (SAM) on this trie (SAM on Trie) is constructed to efficiently represent all substrings.
  - This allows efficient querying of substring occurrences using persistent segment trees over the parent tree to count appearances in specific ranges.

- **Cross-String Matching via $ \tau(s, t) = \text{suf}(s) \cap \text{pre}(t) $**:
  - For matches that cross boundaries, define $ \tau(s, t) $ as the set of common strings that are both suffixes of $ s $ and prefixes of $ t $.
  - The positions where such overlaps occur form sequences that can be compressed into $ O(\log n) $ many arithmetic progressions due to periodicity.

- **Periodicity and Border Properties**:
  - If a string has a border of length $ b $ with $ 2b \geq |s| $, then it is periodic with period $ l = |s| - b $.
  - **Lemma 3.1 (Fine Period Lemma)**: If $ p $ and $ q $ are periods of a string $ S $ and $ p + q \leq |S| $, then $ \gcd(p, q) $ is also a period.
  - **Lemma 3.2 (Next Array Structure)**: For a periodic string with shortest period $ l $, we have $ \text{next}[i] = i - l $ for all $ i > 2l $. This reveals a regular structure in the KMP failure array beyond double the period length.

- **Efficient Merging of Arithmetic Progressions**:
  - Since each $ \tau(s_{a_i}, t) $ yields $ O(\log n) $ arithmetic sequences, merging them (e.g., for adjacent strings) takes $ O(\log^2 n) $ per pair using merge-like techniques.

- **Optimized KMP with Jumping**:
  - Instead of naively simulating KMP across the entire master string, use structural knowledge of the next array:
    - When $ j \leq \text{next}[j] / 2 $: proceed normally.
    - When $ \text{next}[j] > j/2 $: the current prefix is highly repetitive; let $ l = j - \text{next}[j] $ be the period.
      - If another mismatch occurs after jumping to $ \text{next}[j] $, jump directly to position $ l + (j \bmod l) $ (**Case 1**), skipping redundant checks.
      - Otherwise, check how many full periods match consecutively in the text starting at current position (**Case 2**).
  - Use LCP queries via SAM on Trie + LCA (on Euler Tour with RMQ) to compute longest common prefixes in $ O(1) $ time.
  - Resetting $ i, j $ upon entering new dictionary strings uses dynamic tag propagation on the parent tree with LCT or similar.

- **Layered Analysis of Next Array**:
  - Define layers based on whether $ \text{next}[i] \geq i/2 $. Each layer corresponds to a coarser period.
  - Theorem: The period lengths grow by at least a factor of $ 3/2 $ between layers → only $ O(\log n) $ layers exist.
  - This bounds the total number of transitions between states during optimized KMP simulation to $ O(m \log n) $.

- **Balancing Strategy**:
  - Use threshold $ B = \sqrt{m \log n} $:
    - For short queries ($ |t| \leq B $): solve with precomputed data structures (e.g., SAM + segment trees).
    - For long queries: apply optimized KMP with periodic jumps.
  - Achieves overall complexity $ O((q + m) \sqrt{m \log n}) $.

- **Data Generation Insight**:
  - Avoid random strings (low periodicity); instead generate strings from small base periods with noise to ensure non-trivial structure and prevent brute-force from passing.