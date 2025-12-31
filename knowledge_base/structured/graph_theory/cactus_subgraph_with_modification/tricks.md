# 《神奇的子图》命题报告及其拓展

**Author:** 陈俊锟

### Key Ideas and Observations

- **Problem Constraint Analysis**: The condition that any 7 vertices contain a separating vertex implies that no biconnected component has size ≥7. Thus, all biconnected components have size ≤6, enabling brute-force enumeration over subgraphs within each block.

- **Round-Square Tree (圆方树)**: Transform the original graph into a tree by creating a square node for each biconnected component and connecting it to all its vertices (round nodes). This preserves structural information while converting the problem into a tree, allowing tree-based DP techniques.

- **Clear Separation of Responsibilities**:
  - Round nodes handle vertex weights and degrees.
  - Square nodes handle edge configurations and connectivity within biconnected components.
  This decoupling allows independent updates: modifying a vertex weight only affects its parent square node.

- **Chain-Based Divide and Conquer (Heavy-Light Decomposition + Segment Tree)**:
  - Perform HLD on the round-square tree.
  - For each heavy path, maintain a segment tree storing DP states for intervals.
  - Each segment tree node stores:
    - `cro(a, b)`: max weight when left/right endpoints have degrees `a`, `b`
    - `lef(a)`, `rig(b)`: one endpoint included
    - `mid`: neither endpoint included
  - Merge states by checking degree constraints across the boundary.

- **Efficient State Merging**:
  - Use precomputed tables for all valid subgraphs (by degree mask) in small biconnected components (size ≤6).
  - Precompute number of realizations for each (vertex set, degree vector) pair to count solutions efficiently.

- **Dynamic Updates**:
  - When a vertex weight changes, update its value in the corresponding round node.
  - Traverse up the heavy paths; for each heavy chain top’s parent, recompute the square node’s contribution using precomputed state transitions.
  - Update light child contributions using auxiliary data structures (e.g., segment trees or arrays maintaining sums over light subtrees).

- **Handling Square Nodes in Segment Trees**:
  - Define 'real left/right points' as adjacent round nodes in the heavy path.
  - During merging, ensure degree consistency at shared round nodes between segments.
  - For single-point (square node) initialization, enumerate all internal subgraph configurations and combine with light subtree DP results via背包-style combination.

- **Counting Solutions Modulo 64123**:
  - Maintain pairs `(value, count)` with custom addition:
    - `(v1,c1) + (v2,c2) = (max(v1,v2), c1 if v1>v2 else c2 if v2>v1 else c1+c2)`
    - Multiplication combines independent parts: `(v1+v2, c1*c2 mod 64123)`
  - Ensures correct counting without overcounting or undercounting due to non-invertible operations.

- **Generalization Power**:
  - The framework extends to other problems: cactus graphs, dynamic subtree queries, path queries on general graphs.
  - Can be combined with LCT for fully dynamic trees (supporting link/cut).