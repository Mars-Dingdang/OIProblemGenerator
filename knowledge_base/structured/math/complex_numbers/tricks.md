## Key Observations
- **Geometric interpretation**: Complex numbers correspond to points/vectors in the 2D plane, enabling geometric transformations via arithmetic.
- **Polar form**: Multiplication/division become scaling and rotation: \(r_1 e^{i\theta_1} \cdot r_2 e^{i\theta_2} = r_1 r_2 e^{i(\theta_1+\theta_2)}\).
- **Conjugate trick**: Division \(\frac{a+bi}{c+di}\) is simplified by multiplying numerator and denominator by the conjugate \(c-di\).
- **Euler's formula**: \(e^{i\theta} = \cos\theta + i\sin\theta\) connects complex exponentials to trigonometry.

## Optimizations
- **Precompute roots of unity**: For FFT, precompute all \(n\)-th roots of unity to avoid repeated trigonometric calls.
- **Use std::complex**: The C++ `<complex>` library is optimized and handles special cases (e.g., infinities, NaN).
- **Avoid frequent conversions**: Stick to either Cartesian or polar form within a computational block to reduce overhead.

## Problem Transformation Patterns
1. **Rotation**: Multiplying by \(e^{i\theta}\) rotates a point by angle \(\theta\) around the origin.
2. **Scaling**: Multiplying by a real number scales the vector.
3. **Translation**: Addition corresponds to vector translation.
4. **Coordinate transformations**: Complex numbers can represent 2D Cartesian coordinates, simplifying problems involving distances, angles, and transformations.
5. **Polynomial evaluation**: Use complex roots to factor or solve equations.
6. **FFT**: Multiply polynomials or large integers efficiently by evaluating at roots of unity.

## Common Pitfalls
- **Floating-point precision**: Be cautious with equality checks; use tolerances (e.g., `abs(z1 - z2) < 1e-9`).
- **Branch cuts**: Functions like `arg()`, `log()`, and `sqrt()` have discontinuities; ensure arguments are within expected ranges.
- **Zero handling**: For point (0,0), polar coordinates (r=0, θ) are undefined; check `r == 0` before computing θ.
- **Overflow**: Large exponents in polar form can cause overflow; use logarithmic scaling if necessary.