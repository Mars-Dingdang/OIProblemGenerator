# 浅谈一类实现简易的动态树型结构信息维护方法

**Author:** 肖岱恩

### Key Ideas and Observations

- **Dual Semigroup Model**: The algorithm operates under a dual semigroup framework `(D, O)` where `D` represents data values (e.g., node weights), and `O` represents operators (e.g., lazy tags). This allows unified handling of point/path updates and queries via associative and distributive operations.

- **Real-Path Decomposition with Splay Trees**:
  - Each path from root to leaf is split into *real edges* (forming solid paths) and *virtual edges* (dashed).
  - Real paths are maintained using splay trees, ordered by depth: left child = shallower, right child = deeper.
  - Virtual children (non-real sons) are stored in an auxiliary structure called *Splay Leafy Tree (SLT)*, where only leaves represent actual nodes.

- **Access Operation (`access(x)`)**:
  - Makes the path from `x` to the root a single real path.
  - Internally performs repeated `splice(x)` operations: disconnect current real son of parent, make `x`'s splay root the new real son.
  - Uses potential function based on `F(k) = ⌈log₂ k⌉`, weighted by subtree sizes including virtual subtrees.
  - Potential analysis shows each `splice` contributes at most `O(log n)` amortized cost.

- **Handling Subtree Information with SLT**:
  - Each node has a middle child pointing to an SLT storing its virtual children.
  - When splicing, if the parent already has a real son, it becomes a virtual child; otherwise, remove self from SLT.
  - These changes affect potential by at most `2(h(fax) − h(x))`, preserving amortized bounds.

- **Weight-Balanced Leafy Trees (WBLT)**:
  - Replaces splay trees for both real paths and virtual children.
  - Merging two WBLTs `L` and `R` (assume `|L| ≤ |R|`) takes `O(log(|R|) − log(|L|) + 1)` time.
  - Maintains balance condition: after every 3 upward steps, size increases by factor `≥ 1/α` (α ≈ 0.65–0.85).

- **Dynamic Absolute Heavy-Path Decomposition**:
  - Ensures all *heavy edges* (to sons with subtree > half parent's) are real edges.
  - After `access`, check affected chains: if a non-bottom node has a heavy son not currently real, promote it.
  - On a real chain (maintained by WBLT), binary search for the first light real edge (i.e., real but light edge).
  - Split the chain there, then inspect the middle child (virtual children) of the top node to find the heavy son among O(1) levels.
  - If found, extract its subtree and merge into the main chain.
  - Merge strategy: use priority queue or sorting to repeatedly combine smallest subtrees (since number is O(1)).

- **Strict Complexity via Weight Balancing**:
  - Cost of merging chains involving `x`, `y`, `z` (parent, light real son, heavy son) is bounded by `O(|log(size_x) − log(size_z)|)`.
  - Since `size_y ≤ min(size_x, size_z)` and new sizes don’t exceed old `size_y`, telescoping sum over operations gives total `O(log n)`.
  - Chain bottom’s heavy son is handled similarly post-processing.

- **Advantages**:
  - Simpler than traditional Link-Cut Tree implementations due to structured decomposition.
  - WBLT version avoids amortization issues and supports strict guarantees.
  - Naturally extends to problems requiring block-like tree management (e.g., CTS2022 WBTT).