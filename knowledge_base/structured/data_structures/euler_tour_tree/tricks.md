- **ETT as a Transformation Technique**: Euler Tour Tree is not just a data structure but a method of transforming dynamic tree operations into sequence operations. This allows using any balanced BST (like Splay, Treap, or B-tree) to maintain the Euler Tour Representation (ETR).

- **Subtree vs Path Queries**: Unlike LCT which excels at path queries, ETT naturally supports subtree queries (e.g., subtree min/max/sum) because the entire subtree appears as a contiguous interval in the ETR.

- **Efficient Root Swapping via Rotation**: The `MakeRoot(u)` operation is implemented by splitting the sequence at `(u,u)` and concatenating the second part before the first — effectively rotating the Euler tour so that `u` becomes the root.

- **Bottom-Up Split Optimization**: Instead of computing node positions explicitly, use bottom-up tree restructuring (`SplitUp2`, `SplitUp3`) during traversal from node to root. This avoids extra log-factor overhead and maintains parent pointers efficiently.

- **Edge Representation**: Each undirected edge `(u,v)` is represented as two directed edges `(u→v)` and `(v→u)` in the ETR. These are inserted between the split parts when linking trees.

- **Handling Arbitrary Edge Deletion**: When deleting an edge, ensure `(u→v)` comes before `(v→u)` in the sequence by swapping if necessary. Then split out both edges and merge the outer segments to form two separate Euler tours.

- **Connectivity Check via Root Comparison**: Two nodes are connected if their corresponding nodes belong to the same treap (i.e., have the same root in the BST maintaining the ETR).

- **Memory Management Note**: Always clear `parent` pointers after splitting and reassign them during merges to maintain correct tree structure.

- **Initialization with Self-loops**: Represent each node `u` as a self-loop `(u,u)` initially so it appears in the ETR and can be split upon.