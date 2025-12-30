- **Topological Order is Key**: Since the graph is acyclic and directed, processing nodes in topological order ensures that all dependencies (incoming edges) are resolved before updating a node.

- **Unified Handling of Negative Weights**: Unlike Dijkstra, this DP approach works with negative weights because there’s no risk of negative cycles in a DAG.

- **Longest Path in DAG**: A rare case where longest path can be computed efficiently — transform by negating weights and run shortest path, or directly maximize during DP.

- **Combine with DFS for Tree-Like DAGs**: In problems resembling trees (e.g., binary tree as DAG), you can do a DFS-based DP without explicit topological sort.

- **Initialization Matters**: For disconnected components, ensure only nodes reachable from source are updated; initialize unreachable as `INF` or `-INF` accordingly.

- **Use Kahn’s Algorithm for Simplicity**: It naturally integrates with DP since each node is processed once its prerequisites are complete.