# 浅谈亚log 数据结构在OI 中的应用

**Author:** 钱易

### Key Ideas and Observations

#### **Dynamic Predecessor Problem**
- Maintain a dynamic set of integers under insert, delete, predecessor, and successor operations.
- Traditional solutions like `std::set` (balanced BST) are too slow and memory-heavy; Fenwick trees use O(V) space which is prohibitive.

#### **Bit-Compressed Trie (压位trie)**
- A recursive trie with branching factor $ w $ (typically word size, e.g., 64).
- Each node splits a number into high and low bits: $ \text{high}(x) = \lfloor x / 2^{k-c} \rfloor $, $ \text{low}(x) = x \mod 2^{k-c} $, where $ c = \log_2 w $.
- Uses a bitmask $ B $ to track which child tries are non-empty, enabling fast navigation via bit operations (`__builtin_ctz`, `__builtin_clz`).
- Operations recurse down one path, achieving $ O(\log_w V) $ time.
- **Optimized Implementation**: Uses bottom-up updates with early termination—if a subtree was already non-empty during insert (or still non-empty after delete), no need to propagate further.
- **Extensibility**: Can be augmented to support order statistic queries using Method of Four Russians and batched rebuilding for counting.

#### **van Emde Boas Tree (vEB Tree)**
- Recursively partitions the domain $ [0, 2^k) $ into $ 2^{\lceil k/2 \rceil} $ clusters of size $ 2^{\lfloor k/2 \rfloor} $.
- Stores min/max directly at each node to optimize base cases.
- Uses an auxiliary vEB tree $ B $ to index which clusters are non-empty.
- Insert/Delete only recurse into one substructure (either cluster or summary), leading to recurrence $ T(k) = T(k/2) + O(1) $, hence $ O(\log \log V) $ time.
- **Predecessor Query Logic**:
  - If the predecessor lies in the same cluster (i.e., $ \text{low}(x) > \min $ of $ A_{\text{high}(x)} $), recurse within.
  - Else, find the largest active cluster before $ \text{high}(x) $ in $ B $, then return max of that cluster.
- **Successor Symmetry**: Analogous logic applies.
- **Optimizations**:
  - For small domains ($ 2^k \leq w $), use single integer bitsets instead of recursion.
  - Template-based implementation in C++ allows compile-time specialization for small sizes.

#### **Performance Comparison**
- **Speed**: Both structures outperform `std::set` and Fenwick trees significantly on random data.
  - vEB has faster queries but slower inserts/deletes than bit-compressed trie.
- **Space**: Both use ~2MB vs. 64MB (Fenwick) and 455MB (`std::set`) for $ 10^7 $ operations.
- **Practicality**: Bit-compressed trie is simpler to implement and often sufficient.

#### **Applications**
- **Problem 1 (北大集训2018)**: Used to maintain DFS-order point sets dynamically, updating traversal cost via predecessor/successor lookups. Achieves $ O(nk \log n \log \log n) $, better than standard $ O(nk \log^2 n) $.
- **Problem 2 (ZJOI 2019)**: Dynamic merging of dfn-order sets using compressed trie merging with heuristic (large-root merging), similar to segment tree merge but with lower constants. Space optimized via heavy-light decomposition and memory reuse.

#### **Implementation Tricks**
- Use GCC built-ins (`__builtin_ctz`, `__builtin_clz`) for $ O(1) $ bit scanning.
- Avoid full recursion in bit-compressed trie by stopping propagation when state doesn’t change.
- In vEB tree, always handle min/max separately to reduce recursion depth.
- Use templates and small-case specialization to reduce overhead.
- For merging tries, adopt union-by-size strategy to bound total complexity.