# Leafy Tree 及其实现的加权平衡树

**Author:** 王思齐

### Key Ideas and Observations

- **Leafy Tree Structure**: All data is stored in leaf nodes. Internal nodes only store metadata — specifically, the value of the right child (i.e., maximum in the subtree) and subtree size. This eliminates special cases during insertion and deletion since modifications always occur at leaves.

- **Simplified Insert/Delete**: When inserting into a leaf, it is split into two leaves and promoted to an internal node. Deletion of a leaf causes its parent to be replaced by its sibling. These operations avoid complex restructuring seen in classical BSTs (e.g., two-child deletions).

- **Weight-Balanced Tree (BB[α])**: Uses subtree sizes (weights) to maintain balance. A node is α-balanced if both children have weight ≥ α × total weight. With appropriate α (≤ 1 − √2/2 ≈ 0.292), rotations can restore balance after updates.

- **Rotation Strategy**: After insert/delete, imbalance propagates along a single path. For each unbalanced node:
  - If one child is too light (< α·size), perform rotation.
  - Use single or double rotation based on the inner child’s size: if `T.child[d].child[1-d].size >= T.child[d].size * (1−2α)/(1−α)`, do a double rotation; else, single.

- **Efficient Merging**: Given two trees A and B where max(A) ≤ min(B):
  - If their sizes are comparable (within α factor), merge directly.
  - Otherwise, recursively merge smaller tree with appropriate subtree of larger one.
  - Achieves logarithmic complexity relative to size ratio.

- **Splitting**: Recursively descend and use comparisons to route elements, then combine results using merge. Maintains O(log n) time.

- **Persistence-Friendly**: Only nodes along the access path are modified. Path copying allows full persistence with low overhead due to minimal node creation compared to other persistent structures like non-rotating Treap.

- **Advantages Over Other Structures**:
  - Simpler than Splay/Treap (no random priorities or splaying logic).
  - Better worst-case guarantees than Splay (amortized) or scapegoat tree (global rebuilds).
  - More flexible than red-black trees (no color bits needed; size info useful for k-th element).
  - Enables advanced operations (merge/split/persistence) naturally.