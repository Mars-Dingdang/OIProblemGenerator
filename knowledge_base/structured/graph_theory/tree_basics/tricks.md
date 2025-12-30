## Key Observations & Tricks

### 1. **Tree Properties**
- A tree with `n` nodes always has `n-1` edges.
- Any two nodes have a unique simple path.
- Removing any edge disconnects the tree (all edges are bridges).
- Adding any new edge creates exactly one cycle.

### 2. **Traversal Insights**
- **DFS** is natural for recursive problems (subtree DP, depth calculation).
- **BFS/Level-order** is ideal for shortest path (unweighted) and layered processing.
- **Morris Traversal** allows O(1) space inorder/preorder traversal by temporarily threading nodes.

### 3. **Binary Tree Reconstruction**
- Given **inorder** + (**preorder** or **postorder**), the binary tree can be uniquely reconstructed.
- **Rule**: First element in preorder (or last in postorder) is the root. Find root in inorder to split left/right subtrees.
- Works because inorder gives left-root-right ordering.

### 4. **Storage Optimizations**
- **Adjacency List**: Most common, O(n) space.
- **Left-Child Right-Sibling**: Efficient for trees with many children, reduces pointer overhead.
- **Parent Array**: Useful for bottom-up problems (e.g., union-find on trees).

### 5. **Common Problem Transformations**
- **Rooting an Undirected Tree**: Pick any node as root, run DFS to assign parent/child relationships.
- **Tree → Bipartite Graph**: Trees are always bipartite (2-colorable via BFS/DFS).
- **Path Queries**: Often solved by lifting to LCA (Lowest Common Ancestor).
- **Subtree Queries**: Use DFS order (Euler tour) to map subtree to contiguous array segment.

### 6. **Special Trees**
- **Chain**: Degenerate tree, behaves like a linked list.
- **Star**: One central node connected to all others.
- **Binary Tree Variations**:
  - **Full/Proper**: Every node has 0 or 2 children.
  - **Complete**: All levels filled except possibly last, filled left to right.
  - **Perfect**: All internal nodes have 2 children, all leaves same depth.

### 7. **Implementation Tricks**
- Use `0` or `-1` as dummy parent for root.
- In BFS level-order, record level size before iterating to separate layers cleanly.
- For Morris traversal, remember to restore modified `right` pointers to avoid corrupting the tree.
- When reconstructing binary trees, use hash maps to find inorder indices in O(1) time.

### 8. **Complexity Notes**
- Most tree operations are O(n) time.
- Recursive DFS may cause stack overflow for deep trees; consider iterative stack or BFS.
- Morris traversal trades time for space: O(n) time, O(1) space, but modifies the tree temporarily.