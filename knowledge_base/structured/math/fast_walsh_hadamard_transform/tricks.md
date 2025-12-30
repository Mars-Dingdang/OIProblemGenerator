## Key Observations
- **Core Idea**: Transform sequences into frequency domain where convolution becomes element-wise multiplication, similar to FFT but for bitwise operations.
- **Formula**: For bitwise operation ⊕, compute C where C_i = Σ_{j⊕k=i} A_j * B_k.
- **Linear Transform**: FWT is linear: FWT(A+B) = FWT(A) + FWT(B) and FWT(c*A) = c*FWT(A).

## Optimizations
- **In-place Computation**: All FWT operations can be done in-place with O(1) extra space.
- **Unified Function**: Forward and inverse transforms can share the same function by passing type=1 (forward) or type=-1 (inverse).
- **Iterative Implementation**: Use iterative loops instead of recursion for better constant factors.

## Common Problem Transformations
1. **Subset Convolution**: For OR convolution, FWT effectively sums over subsets. Useful for problems involving subset sums or SOS DP.
2. **Bitmask DP Acceleration**: Many DP problems with bitmask states can be optimized using FWT to achieve O(n log n) instead of O(n²).
3. **K-dimensional Convolution**: Extend to K-ary digits for problems with base-K addition without carry (e.g., decimal digit convolution).

## Advanced Tricks
- **Matrix View**: Each bit operation corresponds to a 2×2 transformation matrix. Understanding these matrices helps derive new transforms.
- **Modulo Issues**: For XOR, inverse transform requires division by 2; use modular inverse of 2 or multiply by (MOD+1)/2 when MOD is odd.
- **Extension to K-ary**: For K-ary max/min/addition, construct K×K matrices using unit roots or cyclotomic polynomials when working in modular fields.
- **Cyclotomic Polynomials**: When modulus lacks primitive roots, work in extension fields modulo cyclotomic polynomials to handle K-ary transforms.

## Implementation Notes
- Ensure array size is a power of two.
- For XOR, forward transform uses (a+b, a-b); inverse uses ((a+b)/2, (a-b)/2).
- Always apply modulo operations carefully to avoid negative values.