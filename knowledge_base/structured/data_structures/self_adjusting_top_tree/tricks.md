- **Tree Contraction via Compress & Rake**: The core idea is to represent tree updates through recursive clustering using two operations: `Compress` (for degree-2 nodes on a path) and `Rake` (for leaf-like subtrees). This allows representing any tree as a single edge (Root Cluster) through successive merging.

- **Three-Child Node Design**: Each node in Self-Adjusting Top Tree has up to three children: left, right, and middle. The middle child represents the contracted path (in Compress Tree), while left/right handle side branches (via Rake Tree). This enables efficient separation of path vs. subtree information.

- **Access(x) Controls Update Cost**: Calling `access(x)` brings node `x` to the root of the top tree and ensures its data is only included at the latest stage of contraction. Thus, updating `x` only requires modifying one node (`compress(x)`), achieving $ O(\log n) $ amortized time.

- **Lazy Propagation Separation**: Maintain separate lazy tags for path-related values and subtree-related values. During `pushdown`, propagate accordingly:
  - Path tags affect left/right children (on-path).
  - Subtree tags affect all three children (including middle, which holds off-path clusters).

- **Global vs Local Splay**: Use `local splay` within Rake/Compress trees during `splice`, then `global splay` at the end of `access` to maintain balance and ensure amortized efficiency.

- **Exposing a Path**: To query/update path between `x` and `y`, use `expose(x,y)` = `makeroot(x)` + `access(y)`. After this, the entire path lies in the root’s Compress Tree, so root stores aggregated path info.

- **Subtree Queries via Middle Child**: After `access(x)`, the true subtree of `x` is represented in its **middle child**. So subtree sum = `sum[ms(x)] + val[x]` (if applicable).

- **Efficient Link/Cut**: Always `makeroot` on one endpoint before linking or cutting to preserve orientation and correctness of cluster endpoints.

- **Node Recycling**: Use a stack-based allocator (`new_node()` / reuse from freed nodes) to avoid allocation overhead in competitive environments.

- **In-Order Consistency**: Maintain in-order traversal consistency across rotations (especially important when swapping children under reversal tags) to preserve depth order along the compressed path.