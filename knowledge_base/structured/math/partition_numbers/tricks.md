## Key Observations

1. **Pentagonal Number Theorem**: The most efficient way to compute partition numbers p(n) in O(n√n) time using the recurrence:
   p(n) = p(n-1) + p(n-2) - p(n-5) - p(n-7) + p(n-12) + p(n-15) - ...
   where the indices are generalized pentagonal numbers k(3k-1)/2.

2. **k-Partition Numbers**: p(n,k) = p(n-1,k-1) + p(n-k,k)
   - First term: partitions with at least one part equal to 1
   - Second term: partitions with all parts ≥ 2 (subtract 1 from each part)

3. **Distinct Partitions**: pd(n,k) = pd(n-k,k-1) + pd(n-k,k)
   - Similar to k-partition numbers but with different combinatorial interpretation

4. **Odd Partitions = Distinct Partitions**: po(n) = pd(n) due to generating function identity
   ∏(1+x^i) = ∏(1-x^(2i))/∏(1-x^i) = ∏1/(1-x^(2i-1))

5. **Ferrers Diagram Transformations**:
   - Conjugate partition: flip diagram over main diagonal
   - Maximum part k ↔ number of parts k (via conjugation)
   - Transformations between even and odd distinct partitions explain pentagonal theorem

6. **Space Optimization**:
   - For distinct partitions, only need two columns (current and previous)
   - For k-partitions, can compute column by column

7. **Generating Functions**:
   - p(n): ∏ 1/(1-x^i)
   - pd(n): ∏ (1+x^i)
   - po(n): ∏ 1/(1-x^(2i-1))

8. **Bound on Number of Parts**: For distinct partitions, maximum k satisfies k(k+1)/2 ≤ n

## Common Problem Transformations

1. **Restricted Partitions**: Add constraints on part sizes (min, max, modulo conditions)
2. **Bounded Partitions**: Limit both number and size of parts
3. **Multiset Partitions**: Allow repeated parts with frequency constraints
4. **Composition vs Partition**: Order matters in compositions, not in partitions
5. **Young Tableaux**: Connect to representation theory and symmetric functions

## Optimization Tips

1. Use modulo arithmetic carefully with negative terms in pentagonal recurrence
2. Precompute pentagonal numbers up to n
3. For multiple queries, precompute entire p[] array
4. For very large n, use Euler's pentagonal theorem with FFT for O(n log n)
5. Distinct partitions DP needs only O(n√n) space and time