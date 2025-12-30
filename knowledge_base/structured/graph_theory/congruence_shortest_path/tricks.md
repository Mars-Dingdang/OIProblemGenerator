- **State Compression via Modulo**: When dealing with linear combinations of integers, use the smallest number $ x $ as modulus to reduce state space to $ \mod x $. Each residue class represents an equivalence group.

- **Graph Construction**: For each allowed value $ y $, add edge $ i \to (i + y) \mod x $ with weight $ y $. This models transitions between residues.

- **Optimization Using Cycles**: If only one type of transition exists (e.g., adding fixed $ y $), the graph decomposes into $ \gcd(x, y) $ cycles of length $ x / \gcd(x, y) $. Use this to optimize relaxation: update each cycle twice (to propagate minima fully) in $ O(x) $ time.

- **Avoid Overflow**: Since target values can be near `LLONG_MAX`, initialize distances to `LLONG_MAX` and adjust input range (e.g., shift $ h \leftarrow h - 1 $).

- **Answer Aggregation**: After computing minimum distance $ d[i] $ for each residue $ i $, count valid numbers $ \leq h $ as $ \sum_{i=0}^{x-1} \max\left(0, \left\lfloor \frac{h - d[i]}{x} \right\rfloor + 1\right) $.

- **Connection to Diophantine Equations**: This method solves feasibility of $ ax + by + cz = k $ over non-negative integers using shortest path semantics on residue states.

- **Generalization to Digit Problems**: As in ARC084B, model digit construction via operations: $ \times 10 $ (cost 0) and $ +1 $ (cost 1), then run shortest path on modulo graph.