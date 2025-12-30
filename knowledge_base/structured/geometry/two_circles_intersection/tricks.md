1. **Symmetry**: If two circles intersect, they have two intersection points symmetric about the line connecting their centers. This allows computing one point and reflecting to get the other.
2. **Avoiding floating-point errors**: Use EPS for comparisons. For integer coordinates, consider using integer arithmetic where possible (e.g., using squared distances).
3. **Edge cases**: Circles may be separate, tangent (one intersection), identical (infinite intersections), or concentric (no intersection unless radii equal). Handle these with care.
4. **Polar ordering**: In problems like counting non‑intersecting triangles, fix a pole (origin), convert points to polar coordinates, sort by angle, and use sweep‑line techniques.
5. **Divide by 4**: In the JOISC 2014 problem, each pair of triangles is counted 4 times due to double‑counting of common tangents; final answer must be divided by 4.
6. **Complexity**: Sorting by polar angle gives O(n² log n) for problems where you enumerate all points as poles.
7. **Generalization**: The method of rotating a direction vector by the computed angle is applicable to other intersection problems (e.g., circle‑line intersection).