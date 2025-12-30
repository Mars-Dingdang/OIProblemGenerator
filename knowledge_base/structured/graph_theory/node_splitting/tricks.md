- **Node splitting** transforms node constraints into edge constraints by splitting each node $u$ into two: $u_{in}$ and $u_{out}$, connected by an edge with capacity equal to the node's flow limit. This is essential in network flow problems where nodes have capacity limits.

- In **layered graph shortest path**, each node $u$ is duplicated $k+1$ times (for $k$ free moves), where $u_i$ represents reaching $u$ after using $i$ free passes. This allows modeling state-dependent transitions.

- The state in Dijkstra becomes `(node, used_free_count)`; transitions are:
  - Use a free pass: `dis[v][cnt+1] = min(dis[v][cnt+1], dis[u][cnt])`
  - Pay normally: `dis[v][cnt] = min(dis[v][cnt], dis[u][cnt] + w)`

- Always initialize `dis[start][0] = 0` and push `(start, 0, 0)` into the priority queue.

- Final answer is `min{dis[target][i]}` for all $i \in [0, k]$.

- This technique generalizes to other DP-over-graph scenarios like time-based layers or repair limits.