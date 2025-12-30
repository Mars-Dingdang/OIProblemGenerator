## Key Observations
- **Empty Circle Property**: The circumcircle of any triangle contains no other input points. This is the defining property.
- **Max-Min Angle**: Among all triangulations, Delaunay maximizes the minimum angle, avoiding skinny triangles.
- **Duality**: The Delaunay triangulation is the dual of the Voronoi diagram; edges correspond to adjacent Voronoi cells.

## Optimization & Implementation Tricks
- **Sort by x-coordinate** as a preprocessing step for divide-and-conquer.
- **Use 3D lifting** (paraboloid lifting) to test the in-circle condition robustly via determinant computation.
- **Maintain adjacency lists** (like `std::list<Edge>`) for efficient edge insertion/deletion during merging.
- **Base LR-edge merging**: In the divide-and-conquer algorithm, find the lower common tangent (base LR-edge) and iteratively add valid LR-edges while deleting conflicting LL/RR edges.
- **Handling degeneracies**: Use epsilon comparisons for floating-point; ensure no four points are cocircular (or handle them consistently).

## Common Problem Transformations
- **Voronoi construction**: Compute Delaunay, then take the dual.
- **Nearest neighbor graph**: The Delaunay triangulation contains the Euclidean minimum spanning tree (EMST) as a subset.
- **Mesh generation**: Delaunay triangulations produce high-quality triangular meshes for finite element methods.
- **Interpolation**: Use Delaunay to triangulate scattered data points for piecewise linear interpolation.
- **Convex hull**: The outer boundary of the Delaunay triangulation is the convex hull of the point set.

## Pitfalls
- **Floating-point precision**: Use robust geometric predicates (e.g., Shewchuk's adaptive precision).
- **Collinear/cocircular points**: May cause non-uniqueness; need tie-breaking rules.
- **Large point sets**: O(n log n) algorithms are practical, but O(n²) naive ones are not.