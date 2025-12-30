## Key Observations & Optimizations

### 1. **Base Representation (压位)**
- Store digits in a large base (e.g., 10^9) instead of decimal digits to reduce operations.
- Multiplication/division become faster due to fewer digits.
- Must handle carries carefully when base is not a power of 10 for I/O.

### 2. **Multiplication Algorithms**
- **Naive O(n²)**: Suitable for small numbers (n ≤ 1000).
- **Karatsuba O(n^1.585)**: Faster for medium-sized numbers (n ~ 10^4).
- **FFT-based O(n log n)**: Essential for huge numbers (n ≥ 10^5).

### 3. **Division Optimization**
- **Normalization**: Scale divisor to have leading digit ≥ BASE/2 for stable quotient estimation.
- **Double-based estimation**: Use floating-point to estimate quotient digits, reducing trial subtractions.
- **Newton's method**: Compute reciprocal of divisor and multiply for O(n log n) division.

### 4. **Subtraction Handling**
- Implement comparison before subtraction to avoid negative intermediate results.
- Use borrow propagation instead of signed digits.

### 5. **Common Problem Transformations**
- **Modular arithmetic**: Compute (a * b) mod m by reducing during multiplication.
- **Factorials**: Use prime factorization and exponent counting for large factorials.
- **GCD/LCM**: Use binary GCD algorithm to avoid division.
- **Power modulo**: Use fast exponentiation with multiplication optimized by FFT.

### 6. **Implementation Tips**
- Store digits in reverse order (least significant first) for easier carry propagation.
- Trim leading zeros after operations to maintain invariant.
- Use `long long` for intermediate results in multiplication to avoid overflow.
- For competitive programming, pre-allocate arrays instead of vectors if maximum size is known.

### 7. **Advanced Techniques**
- **Chinese Remainder Theorem**: Combine results from different moduli.
- **Miller-Rabin primality test**: Efficient for large numbers.
- **Pollard's Rho factorization**: For factoring large integers.
- **Discrete logarithm**: Baby-step giant-step algorithm.

### 8. **Performance Trade-offs**
- Base size vs. operation speed: Larger base reduces digits but increases risk of overflow.
- Memory vs. speed: Unrolled loops and pre-allocation can speed up critical sections.
- Algorithm choice: Select multiplication algorithm based on problem constraints.