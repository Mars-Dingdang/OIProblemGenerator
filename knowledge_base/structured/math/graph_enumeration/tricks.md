## Key Observations

1. **Labeled vs Unlabeled**: Labeled problems are often simpler; unlabeled require handling symmetries (Pólya/Burnside).
2. **Exponential Generating Functions (EGF)**: For labeled structures, EGF is natural: if $C(x)$ is EGF of connected objects, then $\exp(C(x))$ is EGF of all objects (Riddell's formula).
3. **Polynomial Log/Exp**: Computing $C = \ln(G)$ or $G = \exp(C)$ via polynomial algorithms ($O(n \log n)$) is key for large $n$.
4. **Euler Transform**: For unlabeled structures, the Euler transform relates OGF of objects and connected objects: $\mathcal{E}(A(x)) = \prod_i (1-x^i)^{-a_i} = \exp\left(\sum_i \frac{A(x^i)}{i}\right)$.
5. **Graphical Enumeration via Partitions**: For unlabeled graphs, enumerate integer partitions of $n$ to represent cycle structures of vertex permutations; compute weight $w(p)$ and cycle index $c(p)$ for edges.
6. **Bipartite Graphs**: Count 2-colored graphs with no monochromatic edges, then relate to connected bipartite graphs via $\sqrt{G(x)}$ or via exp/ln.
7. **Tree Counting**: Use Cayley's formula ($n^{n-2}$) for labeled trees; use Euler transform for unlabeled rooted trees; subtract overcount for unlabeled unrooted trees (centroid consideration).
8. **Connected Components**: The recurrence $c_n = g_n - \sum_{i=1}^{n-1} \binom{n-1}{i-1} c_i g_{n-i}$ is fundamental for labeled connected graphs.
9. **Optimizations**: Use precomputed binomial coefficients, modular inverses; for partition enumeration, generate partitions recursively with pruning.
10. **Polya for Edge Coloring**: For coloring edges of complete graph with $m$ colors, cycle index of edge permutation group (induced by vertex permutations) is computed via $\lfloor p_i/2\rfloor$ for intra-cycle edges and $\gcd(p_i, p_j)$ for inter-cycle edges.