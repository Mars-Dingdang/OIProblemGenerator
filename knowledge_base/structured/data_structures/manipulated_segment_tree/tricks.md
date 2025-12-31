# 《被操纵的线段树》命题报告

**Author:** 沈睿

### Key Ideas and Observations

#### **Idea 1: Interval Counting via 2D Point Query**
- **Insight**: The answer for query $[l, r]$ equals:
  \[
  \text{ans} = 2 \times (r - l + 1) - (\text{number of intervals fully contained in } [l, r])
  \]
  This comes from modeling the selected intervals as a forest where leaves are unit segments and internal nodes represent merged intervals.
- **Transformation to 2D Geometry**: Each interval $[l', r']$ becomes a point $(l', r')$. Querying how many such points satisfy $l' \geq l$, $r' \leq r$ becomes a *dominant point counting* problem (top-left quadrant).
- **Offline Solution**: Use event-based sorting + Fenwick tree (BIT) → $O(N \log N)$.
- **Online Static**: Use tree-on-tree (e.g., BIT over balanced BST or segment tree) → $O((N+Q) \log^2 N)$.
- **Dynamic Updates (Rotations)**: A rotation removes one interval and adds another. Treat as dynamic 2D point insertion/deletion.
  - Offline: Time-based divide and conquer (CDQ-style), reducing to offline 2D range sum → $O(Q \log^2 Q)$.
  - Online: Maintain dynamic 2D structure (tree-of-trees), but high memory cost.
  - Alternative: Use KD-tree with periodic rebuilding; empirical performance good despite theoretical uncertainty.

#### **Idea 2: Greedy Jumping with LCT**
- **Greedy Strategy**:
  - From left end $l$, greedily jump right using the largest interval starting at current position.
  - From right end $r$, greedily jump left using the largest interval ending at current position.
  - Total steps = answer.
- **Jumping Forms Trees**: All “jump-to” relationships form trees (left-jump tree and right-jump tree).
- **Efficient Jumps**: Preprocess with binary lifting if static → $O(\log N)$ per query.
- **Support Rotation**: Rotations only change jump targets for specific endpoints ($L_b$, $R_b$ in paper).
- **Use Link-Cut Tree (LCT)**: Dynamically maintain jump trees.
  - `link`/`cut` to update parent-child relations after rotation.
  - For query: use `access` and splay traversal to count ancestors within bounds → $O(\log N)$ per operation.

#### **Idea 3: Abstract Tree with In-Order Labeling**
- **Abstraction**: Build a new tree where non-leaf nodes are labeled by their `mid`. Add sentinels $0$ and $N$ at root level.
- **Key Properties**:
  - In-order traversal gives $0, 1, ..., N$.
  - Subtree rooted at $[l, r]$ corresponds to node labels $l$ to $r-1$.
  - Structure remains valid after rotations.
- **Answer Formula**:
  Let $t = \text{LCA}(l-1, r)$. Then:
  \[
  \text{ans} = (\# \text{left children on path from } l-1 \to t, \text{excluding } t)
  + (\# \text{right children on path from } r \to t, \text{excluding } t)
  \]
- **Implementation Options**:
  1. **LCT**: Directly maintain dynamic tree, support `lca`, path queries → $O(\log N)$.
  2. **Segment Tree on In-Order Traversal** (Better):
     - Maintain three arrays over in-order indices:
       - $L[i]$: total left-child edges from node $i$ to root.
       - $R[i]$: total right-child edges from node $i$ to root.
       - $Dep[i]$: depth (used to find LCA).
     - Update: When a node changes status (left→right child), apply range updates to its subtree.
     - Query LCA: Find minimum depth node in $[l-1, r]$ using range-min segment tree.
     - Answer = $(L[l-1] - L[t]) + (R[r] - R[t])$.
     - Efficient, clean, uses only segment trees.

#### **Rotation Impact**
- A single rotate affects at most one interval (removed) and one new interval (added).
- Changes at most two jump pointers and two parent/child relationships in abstract tree.

#### **Data Generation Trick**
- Avoid random midpoints (leads to $O(\log N)$ depth).
- Use 'large chain + small subtrees' pattern to force deep trees → breaks naive $O(N)$ traversal.