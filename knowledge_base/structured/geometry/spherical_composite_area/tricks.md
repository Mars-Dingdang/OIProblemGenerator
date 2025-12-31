# 计算球面复合区域面积的高效算法

**Author:** 周任飞

### Key Ideas and Tricks

1. **Green’s Theorem on Sphere**:
   - The core idea is transforming the area computation into a boundary integral using a variant of Green’s theorem on the sphere.
   - By mapping the sphere (minus poles) to a rectangular domain in longitude-latitude space (the "经纬平面"), the surface area integral becomes:
     
     $$
     S_\Omega = \oint_{\partial \Omega} (-\sin \phi - 1) \, d\lambda + [P_N \in \Omega] \cdot 4\pi
     $$
     
   - This allows reducing area calculation to computing line integrals over boundary arcs.

2. **Boundary Traversal via Sweep-Line**:
   - The boundary $\partial D^*$ of the composite region consists of arcs from the boundaries of individual spherical caps that lie on the edge of the final region.
   - For each cap $D_i$, determine which arcs of its boundary circle belong to $\partial D^*$, depending on whether the left/right side of the arc satisfies the Boolean condition.

3. **Boolean Expression Evaluation with Dynamic Updates**:
   - The membership of a point in $D^*$ is determined by a Boolean expression $F(\lambda_1, \dots, \lambda_n)$, where $\lambda_i = [P \in D_i]$.
   - As we sweep around the boundary of a cap, the values $\lambda_j$ change at intersection points with other caps.
   - We need to dynamically evaluate $F$ as these inputs flip.

4. **Expression Tree with Heavy-Light Decomposition**:
   - Represent the Boolean expression as a tree where leaves are variables $\lambda_i$ and internal nodes are operators.
   - To support fast updates when a leaf value changes, use **heavy-light decomposition** on the tree.
   - Each heavy chain is maintained with a segment tree storing **unary functions** $g_u(x)$ representing the effect of the heavy child’s value on the chain top.
   - Composing these unary functions along the chain gives the value at the top. Segment trees allow composition updates in $O(\log m)$ per modification (or $O(\log^2 m)$ with basic implementation).
   - Global balancing can reduce update time to $O(\log m)$.

5. **Sweep-Line over Angular Intervals**:
   - On each cap’s boundary, map points to polar angle $\theta \in [-\pi, \pi)$.
   - Events occur where another cap starts or stops covering this boundary.
   - At each event, flip the corresponding $\lambda_j$, update the expression tree, and record transitions in $F$ value (from 0 to 1 or vice versa) to identify segments contributing to the boundary.
   - Total events: $O(n)$ per cap → $O(n^2)$ total; each update takes $O(\log m)$ → total $O(nm \log m)$.

6. **Integral over Arcs**:
   - Once boundary arcs are identified, compute their contribution to the integral $\int (-\sin \phi - 1) d\lambda$.
   - For small circular arcs, decompose into spherical triangles and sectors.
   - Use known formulas:
     - Spherical triangle area: $A + B + C - \pi$
     - Spherical sector area: $2\pi h \theta$, where $h$ is height of cap, $\theta$ is angle.

7. **Random Rotation Trick**:
   - To avoid degeneracies (e.g., arcs passing through poles), randomly rotate the sphere so that no boundary arc passes through the north pole almost surely.
   - Ensures the Green’s theorem formula applies cleanly without special handling.

8. **Generalization to Plane and Other Shapes**:
   - Same method applies to planar regions with circles and half-planes.
   - Can solve classical problems like NOI 2004 'Rainfall' and NOI 2005 'Lemon Tree under Moonlight' efficiently.
   - For polygons, represent them via intersections of half-planes.

9. **Handling DAG-Structured Expressions**:
   - When expressions reuse subresults (like in CAD), the structure is a DAG, not a tree.
   - In such cases, recompute all dependent nodes after a change, leading to $O(n^2 m)$ time.

10. **Applications**:
    - Computing satellite coverage on Earth.
    - Surface area of union of spheres.
    - Volume estimation via numerical integration over cross-sectional areas.