### Key Concepts and Tricks
1. **Burnside's Lemma**: Counts distinct objects under group actions. Formula: |X/G| = (1/|G|) Σ_{g∈G} |X^g|, where X^g is the set of elements fixed by g.
2. **Pólya Enumeration Theorem**: Generalizes Burnside's lemma to count colorings with weights; uses cycle index polynomial.
3. **Orbit-Stabilizer Theorem**: |Gx| = |G| / |G_x|, where Gx is the orbit and G_x is the stabilizer. Useful for analyzing symmetry.
4. **Lagrange's Theorem**: For finite groups, the order of any subgroup divides the order of the group.
5. **Sylow Theorems**: For finite groups, guarantees existence of p-subgroups and provides constraints on their number and conjugacy.
6. **Cayley's Theorem**: Every group is isomorphic to a permutation group (subgroup of symmetric group).
7. **Conjugacy Classes**: Elements in the same conjugacy class have the same order and similar properties; used in class equation.
8. **Normal Subgroups and Quotient Groups**: Allow decomposition of groups into simpler structures.
9. **Group Homomorphisms and Isomorphisms**: Compare group structures; kernel and image reveal substructures.
10. **Applications in Combinatorics**:
    - Counting distinct necklaces, bracelets under rotations/reflections (dihedral group).
    - Graph automorphisms (symmetry groups).
    - Coloring problems under symmetry.
11. **Optimizations**:
    - For cyclic groups, fixed points under rotation by i are m^{gcd(n,i)}.
    - For dihedral groups, handle even/odd n separately for reflections.
    - Use modular exponentiation for large m in Burnside's lemma.
12. **Common Problem Transformations**:
    - Model symmetry operations as group actions.
    - Reduce counting problems to counting fixed points under group elements.
    - Use cycle index for Pólya counting with multiple colors or constraints.