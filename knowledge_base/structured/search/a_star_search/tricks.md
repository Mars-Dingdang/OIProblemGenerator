## Key Observations
- **Admissible Heuristic**: If h(x) ≤ h*(x) for all x, A* guarantees optimality. Common heuristics include Manhattan distance for grids, Euclidean distance for continuous spaces, and pattern database for puzzles.
- **Consistency (Monotonicity)**: If h(x) ≤ d(x,y) + h(y) for all edges (x,y), then A* never reopens nodes from the closed set, improving efficiency.
- **Tie-breaking**: When f values are equal, prefer larger g (depth-first bias) or larger h (best-first bias) depending on problem.

## Optimizations
- **Bidirectional A***: Run two A* searches from start and goal simultaneously.
- **Weighted A***: Use f = g + ε·h with ε > 1 for suboptimal but faster solutions (ε = 0 gives Dijkstra, ε = ∞ gives Greedy BFS).
- **Jump Point Search**: For uniform-cost grids, prune symmetric paths.
- **Iterative Deepening A* (IDA*)**: Use depth-first search with cutoff f, increasing cutoff iteratively. Saves memory.
- **Bounded Relaxation**: Allow h to slightly overestimate (non-admissible) for speed when optimality isn't critical.

## Problem Transformations
- **k-Shortest Paths**: Run A* to find 1st shortest, then use deviation paths or Eppstein's algorithm.
- **State Space Search (like 8-puzzle)**: Encode state as hash; use heuristic like Manhattan distance sum or pattern databases.
- **Constraint Satisfaction**: Use A* with heuristic counting unsatisfied constraints.
- **Any-Angle Pathfinding**: Use Theta* or Lazy Theta* variants.

## Implementation Tips
- Store g-values separately in a map for efficient updates.
- Use specialized heaps (Fibonacci heap) if many decrease-key operations.
- For grid maps, use binary heap with array indexing for speed.
- Break ties deterministically to avoid exploring duplicate states.