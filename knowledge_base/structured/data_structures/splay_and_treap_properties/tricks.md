# 浅谈Splay与Treap的性质及其应用

**Author:** 董炜隽

### Key Ideas and Tricks

#### **Splay Tree**
- **Splaying**: After accessing a node, it is moved to the root using zig/zig-zig/zig-zag rotations. This self-adjusting behavior leads to amortized $ O(\log n) $ performance.
- **Dynamic Finger Theorem**: Accessing elements in sequence with small rank differences takes $ O(\sum \log(d_i + 1)) $ total time, making Splay ideal for sequential or localized access patterns.
- **Potential Method Proof**: Uses potential function $ \Phi = \sum \log \text{size}(x) $. Rotation sequences are shown to have bounded potential change, leading to amortized bounds.
- **Finger Search Native Support**: Since every operation splays a node, starting from recent accesses naturally exploits locality.

#### **Treap**
- **Randomized Priority + BST**: Each node has a key (BST order) and random priority (heap order). Structure mimics a random insertion BST, giving expected $ O(\log n) $ depth.
- **Expected Depth Analysis**: Probability that node $ i $ is an ancestor of $ x $ depends on relative priorities along the path — only nodes with higher priority than all between can be ancestors.
- **Join/Split Recursion**: Join compares root priorities and recurses on appropriate subtrees. Split uses key comparison to partition.
- **Fast Join/Split via Finger Search**: Instead of full recursion, use bottom-up merging of right/left chains. Complexity improves to $ O(\log \min(n, m)) $ expected by exploiting shorter paths.

#### **Finger Search Applications**
- **Heuristic Merging Optimization**:
  - Merge smaller tree into larger one, inserting elements in sorted order.
  - For Splay: insertions benefit from dynamic finger (consecutive inserts near each other).
  - For Treap: perform finger search from last inserted position to find next location.
  - Total cost becomes $ O\left(m \log \frac{n}{m}\right) $ per merge → overall $ O(n \log n) $ across all merges.
- **Proof of Total Complexity**: Each element’s contribution is $ \sum \log(s_i / s_{i-1}) = \log n $, telescoping sum over growth of its set size.

#### **Weighted Variants**
- **Weighted Splay**:
  - Redefine `size(x)` as total weight in subtree.
  - Potential becomes $ \log \text{weight-size}(x) $ → splay cost becomes $ O(\log(W / w_x)) $.
- **Weighted Treap**:
  - Assign priority proportional to weight: generate max of $ w $ uniform random variables.
  - Efficient simulation: use transformation $ f(x) = x^{1/w} $ or store $ \log(x)/w $ for comparison.
  - Node depth becomes $ O(\log(W / w_x)) $ due to increased chance of high-priority assignment.
  - Weight update: recompute priority; rotation count bounded by $ O(\log \max(w,w') / \min(w,w')) $.

#### **Multi-Layer Tree Nesting**
- **Idea**: In hierarchical structures (e.g., segment trees over heavy paths), define node weights as sizes of nested subtrees.
- **Static Case**: Build weighted-optimal trees at each level → global depth $ O(k + \log n) $ for $ k $-level nesting.
- **Dynamic Case**: Use Splay/Treap at each layer with above weighting → maintain $ O(k + \log n) $ access time.
- **Application Example – 鏖战表达式 (Expression War)**:
  - Represent expressions as Treaps with operator precedence as priority.
  - Support persistent modifications (element/operator change, flip) via split/join.
  - Fast split/join ensures $ O(k + \log n) $ per operation.
- **Limitation with Link-Cut Tree**: Using Treap instead of Splay fails to achieve single-log complexity because weight updates during access may trigger unbounded downward rotations not confined to access path.

#### **Implementation Insights**
- **Persistent Treap**: Avoid storing fixed priorities; simulate comparison probabilistically based on subtree sizes: $ P(\text{priority}_{T1} > \text{priority}_{T2}) = \frac{|T1|}{|T1|+|T2|} $.
- **Lazy Information Update**: In sequence maintenance, delay updating subtree sums on fast joins; update only when necessary (split/visit), analyzed via potential method.
- **Avoid Degenerate Split Implementations**: Some naive splits depend on $ \log(W / \min(w_p, w_{p+1})) $, which degrades performance; must ensure dependence on maximum weight around split point.