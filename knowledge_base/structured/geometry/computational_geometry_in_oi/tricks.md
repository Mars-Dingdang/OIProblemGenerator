# OI 中的几何

**Author:** 常瑞年

## Key Ideas and Tricks

### Point-Line Duality for Half-Plane Intersection
- Transform each line $ y = kx - b $ into a point $ (k, b) $ in dual space.
- A point lying below a line in primal space corresponds to a dual line above the dual point.
- The intersection of half-planes becomes the upper/lower convex hull of dual points.
- Use rotational perturbation (multiply coordinates by $ 1 + \sqrt{3}i $) to avoid vertical lines numerically.

### Grid-Based Randomized Incremental Method
- Divide the plane into grids of side length $ d $ (current best answer).
- Each grid cell contains $ O(1) $ points due to distance constraints.
- When inserting a new point, only check neighbors in adjacent 3×3 cells.
- Rebuild grid upon improving $ d $. Expected time complexity is $ O(n) $ due to low probability of updates.
- Applied to closest pair, smallest triangle, square covering, and circular coverage problems.

### Delaunay Triangulation via Randomized Incremental Insertion
- Add points in random order. Maintain triangulation incrementally.
- For each inserted point, connect it to vertices of containing triangle, then flip illegal edges using the *empty circumcircle* property.
- Edge flip: if quadrilateral ABCD has diagonal BC and D lies in circumcircle of ABC, replace BC with AD.
- Use queue to propagate flips. Flips increase minimum angle lexicographically → termination guaranteed.
- Maintain face-to-point containment lists for efficient localization. Expected total flips: $ O(n) $, overall complexity: $ O(n \log n) $.
- Applications:
  - Minimum Euclidean spanning tree: only consider Delaunay edges.
  - Nearest neighbor edges exist in Delaunay triangulation.
  - Voronoi diagram is dual; useful for maximizing minimum distance along paths.

### Circle Inversion
- Map point $ P $ to $ P^* $ such that $ |OP| \cdot |OP^*| = 1 $, collinear with origin $ O $.
- Properties:
  - Lines not through center ↔ circles through center.
  - Circles not through center ↔ circles not through center.
  - Tangency, intersection, disjointness preserved.
- Example: finding a circle through origin intersecting maximum number of given circles reduces to finding a line intersecting the most inverted circles (via angular sweep after inversion).

### 3D Convex Hull
- Represent faces using outward normal vectors computed via cross product.
- Determine point position relative to face using dot product with normal.
- Incremental construction: add point, remove all visible (front-facing) faces, fill hole with new triangular faces from horizon edges.
- Time complexity: $ O(n^2) $.
- Lift transformation: $ (x, y) \mapsto (x, y, x^2 + y^2) $ maps circumcircle tests to plane orientation tests (determinant sign). Lower convex hull → Delaunay triangulation; upper hull → anti-Delaunay (maximal enclosing circles).

### Geometric Data Structures
#### Dynamic Point Location
- Use segment tree over x-projections of segments.
- At each node, maintain balanced BST of segments sorted by y at mid-x.
- Query: collect $ O(\log n) $ nodes covering query x, binary search each → predecessor segment → total $ O(\log^2 n) $.
- Updates: insert/delete in $ O(\log n) $ nodes, each taking $ O(\log n) $.
- Persistent version allows $ O(\log n) $ queries for static subdivisions.

#### Orthogonal Range Queries
- **Static**: Use layered range trees with fractional cascading.
  - 2D: $ O(\log n + k) $ query, $ O(n \log n) $ space/preprocessing.
  - dD: $ O(\log^{d-1} n + k) $ query.
- **Dynamic**: Replace inner trees with weight-balanced trees (e.g., treaps). Update cost: amortized $ O(\log^d n) $.
- For 3D 6-sided queries: reduce to four 3-sided queries via "cat tree"-like decomposition. Preprocess with sweeping and fractional cascading on planar subdivisions for single-logarithmic query time.

### Planar Separator Theorem
- Any planar graph has a separator $ C $ of size $ O(\sqrt{n}) $ such that removing $ C $ splits vertex set into $ A, B $ with $ |A|, |B| \leq 2n/3 $.
- Construct via BFS layers: find level $ i $ with $ \geq n/2 $ nodes in first $ i $ layers, then pick sparse levels $ j \leq i $, $ k > i $ to form separator.
- Recurse on subgraphs. Used for divide-and-conquer: e.g., independent set counting in $ 2^{O(\sqrt{n})} $ time.
- Generalizes to genus-$ g $ graphs: separator size $ O(\sqrt{gn}) $.
- Spectral partitioning: use Fiedler vector (second eigenvector of Laplacian) to split graph heuristically. Good cut ratio when $ \lambda_2 $ small.

### Finite Geometry and Combinatorial Designs
- **Projective Plane** (order $ n $): $ n^2 + n + 1 $ points and lines; every two points define a unique line; every two lines meet uniquely.
- **Affine Plane**: derived by removing one line from projective plane → $ n^2 $ points, $ n^2 + n $ lines.
- Constructed via finite fields: PG(2, q) uses 1D and 2D subspaces of $ \mathbb{F}_q^3 $.
- **Block Design** $ t-(v,k,\lambda) $: each $ t $-subset appears in exactly $ \lambda $ blocks.
- Applications:
  - Avoid rectangles in grid: use projective plane incidence matrix → $ \Theta(n^{3/2}) $ ones without rectangle.
  - Mobius plane → 3-design: three points determine a unique cycle; construct via affine plane plus conics and infinite point.
  - K_{3,3}-free bipartite graphs: model right side as points, left as blocks; use geometric configurations (e.g., spheres in finite space).
  - Sidon sets (distinct XORs): relate to curves over $ \mathbb{F}_{2^k} $; aim for $ \Theta(\sqrt{n}) $ size.

General strategy: recognize numerical patterns (e.g., $ n = q^2 + q + 1 $), match to known finite geometry, exploit symmetry and uniformity for constructions.