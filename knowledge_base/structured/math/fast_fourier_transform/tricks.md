## Key Observations
- **Convolution Theorem**: Polynomial multiplication is equivalent to convolution, which FFT computes efficiently via point-value representation.
- **Roots of Unity**: Using the nth roots of unity allows divide-and-conquer with symmetry properties: ωₙᵏ⁺ⁿ/² = -ωₙᵏ.
- **Bit-Reversal Permutation**: Non-recursive FFT uses bit-reversal to reorder coefficients for iterative merging.

## Optimizations
- **Iterative FFT**: Avoids recursion overhead and reduces memory usage.
- **In-place Computation**: Uses butterfly operations to compute results directly in the input array.
- **Precomputed Roots**: Store powers of ωₙ to avoid repeated trigonometric calculations.
- **Real-valued FFT**: For real input data, exploit symmetry to reduce computations by half.

## Common Transformations
- **Polynomial Multiplication**: Convert coefficients to point values, multiply pointwise, then convert back.
- **Large Integer Multiplication**: Treat integers as polynomials with base B (e.g., B=10 or B=2³²).
- **Circular Convolution**: Pad with zeros to avoid wrap-around effects.
- **Multiplying Multiple Polynomials**: Use divide-and-conquer with FFT at each merge step.

## Implementation Tips
- Ensure array size is a power of two by padding zeros.
- For IDFT, use inverse roots (ωₙ⁻ᵏ) and divide by n.
- Use `std::complex<double>` for simplicity, but beware of precision issues with large coefficients.
- For integer results, round real parts after IDFT.
- Use NTT (Number Theoretic Transform) for exact integer results modulo a prime.