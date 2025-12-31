# 浅谈图的列表着色问题

**Author:** 钟自厚

Key observations and techniques include:

- **Reduction to Standard Coloring**: When all lists are identical, the problem reduces to ordinary graph coloring.

- **Choosability (List Chromatic Number)**: A graph is $k$-choosable if it can be list-colored for any assignment of lists of size $k$. This is stronger than being $k$-colorable.

- **Greedy Algorithm**: For graphs with maximum degree $\Delta$, greedy coloring shows $\chi_\ell(G) \leq \Delta + 1$, similar to $\chi(G)$.

- **Erdős–Rubin–Taylor Theorem**: Characterizes 2-choosable graphs. A connected graph is 2-choosable iff it is a single edge or an even cycle.

- **Combinatorial Nullstellensatz**: Used to prove choosability results by constructing polynomials whose non-vanishing implies a valid coloring.

- **Kernelization and Reductions**: Apply degree-based reductions (e.g., removing vertices of degree less than list size) to simplify instances.

- **Planar Graphs**: Known results like Thomassen's theorem show every planar graph is 5-choosable, but not necessarily 4-choosable.

- **Bipartite Matching**: For bipartite graphs, list coloring can sometimes be reduced to matching problems in auxiliary graphs.

- **Dynamic Programming on Tree Decompositions**: For bounded treewidth graphs, list coloring can be solved efficiently using DP over tree decompositions.