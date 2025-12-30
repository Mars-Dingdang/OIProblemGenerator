## Key Observations
- BFS finds the shortest path in terms of **number of edges** in an unweighted graph.
- The queue maintains nodes in **non-decreasing order of distance** from the source.
- Each node is visited **exactly once** via its shortest path.

## Common Problem Transformations
1. **Multi-source BFS**: Initialize queue with multiple sources (all distance 0). Used for problems like "nearest exit" or "fire spread".
2. **0-1 BFS (Deque BFS)**: For graphs with edge weights 0 or 1. Push nodes reached via weight-0 edges to front, weight-1 to back. Complexity O(n+m).
3. **BFS on Implicit Graphs**: State space search where nodes are game states and edges are valid moves.
4. **BFS Tree**: Record parent pointers to reconstruct shortest paths or analyze graph structure.
5. **BFS for Bipartite Checking**: Color nodes alternatingly during BFS; if conflict, graph is not bipartite.

## Optimization Patterns
- **Early Termination**: Stop BFS when target node is reached.
- **Bidirectional BFS**: Run BFS from both source and target simultaneously, meeting in the middle. Reduces search space exponentially.
- **BFS with Bitmask States**: Represent visited states as bitmasks for problems with small sets (e.g., traveling salesman with BFS).
- **BFS on Grid with Direction**: Store (x, y, direction) for problems involving turning costs (like the laser example).

## Applications Beyond Shortest Path
- **Finding Connected Components**: BFS from each unvisited node.
- **Cycle Detection in Undirected Graphs**: If you encounter an already-visited node that's not the parent, a cycle exists.
- **Topological Sort (Kahn's Algorithm)**: BFS-based algorithm using indegree counts.
- **Finding Bridges/Articulation Points**: Modified BFS with DFS timestamps.
- **Level Order Traversal in Trees**: BFS naturally processes tree by levels.

## Implementation Tricks
- Use `deque` for 0-1 BFS.
- Use `priority_queue` for weighted graphs (becomes Dijkstra).
- Store parent array to reconstruct paths.
- Use distance array initialized to -1/INF to track unvisited nodes.
- For grid BFS, define direction arrays: `int dx[] = {1, -1, 0, 0}; int dy[] = {0, 0, 1, -1};`