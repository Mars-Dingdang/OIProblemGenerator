- **Randomized Priority Ensures Balance**: By assigning random priorities and maintaining heap property, Treap avoids degeneration into a chain, ensuring expected depth $ O(\log n) $.

- **Rotation Maintains Two Invariants**: Rotations preserve BST order while adjusting structure to maintain heap property on priority. Left/right rotation swaps parent-child relationship without breaking BST.

- **Expected Depth Proof via Indicator Variables**: Use of indicator variable $ Y_{i,j} $ and linearity of expectation to prove $ \mathbb{E}[\text{dep}(x_i)] = O(\log n) $. Key insight: node $ x_i $ is ancestor of $ x_j $ iff $ x_i $ has minimum priority in the range $ X_{i,j} $.

- **Split and Merge in Non-Rotating Treap**: FHQ-Treap uses `split` and `merge` as core operations, enabling clean implementation of insert/delete and supporting persistence and sequence operations.

- **Value-Based vs Rank-Based Split**: 
  - `split(root, key)` partitions by value (≤ key and > key).
  - `split_by_rank(root, rk)` partitions by order statistic (first rk nodes).

- **Merge Requires Ordered Trees**: Always ensure all values in left tree ≤ all values in right tree before merging. The root is chosen based on min priority (for small-root heap).

- **Insertion Using Split/Merge**: To insert `val`, split by `val`, then split left part by `val-1`, insert node or increment count, then merge back in order.

- **Lazy Propagation Not Applicable**: Unlike segment trees, Treap does not naturally support lazy propagation due to dynamic structure, but supports split/merge for interval extraction.

- **Global Temp Variables for Prev/Nex Queries**: Use temporary global variables (`q_prev_tmp`, `q_nex_tmp`) that track last valid candidate during traversal — a common trick in recursive BST queries.

- **Handling Duplicates with `rep_cnt`**: Instead of multiple nodes, use count field to avoid unnecessary splits and improve efficiency.

- **Constant Factor Advantage**: Rotating Treap often has lower constant factor than other balanced BSTs like AVL or Red-Black Tree, making it competitive in practice despite being randomized.