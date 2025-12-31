# 《最小连通块》命题报告

**Author:** 潘骏跃

### Key Observations and Techniques

- **Minimal Connected Subtree Characterization**: A node `x` is in the minimal connected subtree of a set `S` if and only if there exist two nodes `u, v ∈ S` such that `x` lies on the path between `u` and `v`. This allows us to reframe queries.

- **Ancestor-Descendant Detection**: For rooted trees (with root 1), querying `query({1, u}, v)` returns true iff `v` is an ancestor of `u`. This enables building ancestor sets for each node.

- **Finding a Node's Father**: Once we have the ancestor set `Anc[u]` for each node `u`, the parent of `u` is the ancestor with the largest `|Anc[f]|` such that `Anc[f] ⊂ Anc[u]`.

- **Efficient Descendant Search via Binary Search on Sets**:
  - To find *one* descendant of `u` in a set `S`, partition `S` recursively and use `query(S_part ∪ {1}, u)` to check which part contains a descendant.
  - Each step halves the size, so finding one descendant takes `O(log |S|)` queries.

- **Leaf Identification**: A node `u` is a leaf in the current tree iff `query(V \ {u}, u)` is false — i.e., removing `u` from the full vertex set `V` means no path between remaining nodes passes through `u`.

- **Topological Order Reconstruction**:
  - In a rooted tree, a valid topological order requires every node appears before its ancestors.
  - One approach: maintain a list; insert node `i` at the earliest position `p` such that `query({1} ∪ {a_p, ..., a_{i-1}}, i)` is false — ensuring no future ancestor violates ordering.

- **Divide and Conquer via Randomized Subtree Splitting (Algorithm 6)**:
  - Use a random descendant `y` of `x` to split the subtree.
  - Color nodes based on connectivity after removing `y`; simulate coloring by checking consistency via queries.
  - Use binary search over sorted node lists to detect segments of same color (same component).
  - Prove complexity via light/heavy child argument: each node contributes `O(log n)` times across levels → total `O(n log²n)`.

- **Optimal Divide and Conquer (Algorithm 7)**:
  - Recursively extract subtrees: for current `solve(x, S)`, pick any unprocessed descendant `y ∈ S`, solve `y`'s subtree, remove those nodes from `S`, and repeat.
  - Each node becomes `y` exactly once; finding a descendant costs `O(log n)` → overall `O(n log n)`.

- **Randomized Leaf Hopping (Algorithm 4)**:
  - Start at root, repeatedly jump to a random descendant until reaching a leaf.
  - Expected number of jumps per leaf is `O(log n)` due to exponential decrease in subtree size (like heavy-light decomposition).
  - Finding each descendant takes `O(log n)` → `O(n log²n)` total expected.

- **Accelerated Leaf Pruning Using Virtual Trees (Algorithm 5)**:
  - Exploit fact: trees without degree-2 nodes have ≥ half the nodes as leaves.
  - Contract chains of degree-2 nodes into virtual edges.
  - In each round, peel not just leaves but entire paths leading up to them (nodes whose only leaf descendant is unique).
  - Group peeled nodes by their corresponding leaf and sort internally using ancestor queries.
  - Reduces rounds from `O(n)` to `O(log n)`, though per-round cost is `O(n log n)` → total `O(n log²n)`.

- **Query Optimization Insight**:
  - All methods aim to minimize query count (critical for scoring: score = min(⌊2.2e6 / step⌋, 100)).
  - Best algorithms achieve ~O(n log n) queries (~10k–15k for n=1000), well under 22k limit for full score.