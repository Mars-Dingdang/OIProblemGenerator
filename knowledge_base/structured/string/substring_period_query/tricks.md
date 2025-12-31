# 子串周期查询问题的相关算法及其应用

**Author:** 陈孙立

### Key Ideas and Observations

- **Periodicity Lemma (Weak Version)**: If $ p $ and $ q $ are periods of a string $ S $ and $ p + q \leq |S| $, then $ \gcd(p, q) $ is also a period. This underpins much of the structural analysis.

- **Minimal Period Property**: If $ p = \min\text{per}(S) \leq |S|/2 $, then every period $ x \geq p $ satisfies $ p \mid x $. This implies that large periods form an arithmetic progression with difference $ p $.

- **Border and Period Duality**: A length-$x$ border corresponds to a period of length $ |S| - x $. Thus, studying borders helps characterize periods.

- **Large Borders Form Arithmetic Progressions**: All borders of length $ \geq |S|/2 $ form an arithmetic progression. By recursively considering intervals $[2^{i-1}, 2^i)$, the entire set of borders (and hence periods) can be represented in $ O(\log n) $ space as $ O(\log n) $ arithmetic sequences.

- **Dictionary of Basic Factors (DBF)**: A hierarchical structure similar to the construction of suffix arrays via doubling. For each power-of-two length $ 2^t $, it assigns names to substrings of that length such that lexicographic order is preserved. Built in $ O(n \log n) $, allows efficient substring comparison and occurrence queries.

- **Efficient Occurrence Queries with Segmented DBF**: To avoid binary search for `succ`/`pred`, the DBF is extended by segmenting the string into blocks of size $ 2^t $. For each distinct substring of length $ 2^t $, store its occurrences within each block as arithmetic progressions (using Lemma 2 on bounded pattern occurrences). Hash tables index non-empty segments, enabling expected $ O(1) $ access.

- **Fast Arithmetic Progression Intersection**: When intersecting two APs from LargePS computations:
  - If either has fewer than 3 elements, brute-force check.
  - Otherwise, use **Lemma 5**: under the conditions of the algorithm, both APs have the same minimal period (thus same common difference), so intersection becomes $ O(1) $.

- **Query Decomposition**: For a query $ S[l..r] $, decompose potential periods by checking each interval $[2^{i-1}, 2^i)$ using prefix-suffix comparisons via DBF lookups and segmented occurrence lists.

- **Applications Beyond Period Queries**:
  - $ O(1) $ substring comparison after $ O(n \log n) $ preprocessing.
  - Finding all $ k $-th power substrings (especially primitive ones) using DBF traversal.
  - Enumerating cubic runs via detection of primitive cube substrings.