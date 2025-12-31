# 浅谈一类容斥和反演方法的应用

**Author:** 董亦骐

## Key Ideas and Techniques

### 1. **Dirichlet Convolution and Multiplicative Functions**
- The paper leverages the algebraic structure of multiplicative functions under Dirichlet convolution.
- For a multiplicative function `f`, its prefix sum `S_f(n)` can be computed using known convolutions like `μ * I = ε` (where μ is Möbius, I is identity, ε is zero except at 1).
- If `f = g * h`, then `∑_{i=1}^n f(i) = ∑_{j=1}^n g(j) S_h(⌊n/j⌋)`.

### 2. **Sublinear Summation via Recursive Structure**
- Uses the observation that values `⌊n/i⌋` take only `O(√n)` distinct values.
- Recursively computes `S_f(m)` for all `m ∈ {⌊n/i⌋}`.
- For `m ≤ n^{2/3}`, precompute directly; for larger `m`, use recursive formula with already computed smaller values.
- This achieves `O(n^{2/3})` time complexity.

### 3. **Power Series Methods (exp and log)**
- For functions where `f(p^k)` has a specific form (e.g., `f(p) = p(p-1)`), uses generating functions.
- Defines `q` such that `q(p) = f(p)` and `q` is zero on non-primes.
- Then constructs `d = exp(q)` as a multiplicative function with `d(p^k) = q(p)^k / k!`.
- Shows that `f` can be recovered from `d` via `f = d * g` for some simple `g`, enabling efficient computation.

### 4. **Optimized exp and log Computation**
- To compute `exp(f)` or `log(f)` for multiplicative functions:
  - Split `f = f_0 + f_1` where `f_0` contains small prime powers (`≤ √n`) and `f_1` large ones.
  - Use `exp(f) = exp(f_0) × exp(f_1)` and `exp(f_1) ≈ ε + f_1` since higher terms are negligible.
  - Compute `exp(f_0)` using segmented techniques based on magnitude of `log(prime)`.
  - This reduces complexity to `O(√n log²n / √log log n)`.

### 5. **Segmented Convolution for Efficiency**
- When computing convolutions like `A * B`, instead of iterating over all pairs, use magnitude-based grouping.
- Group indices by `⌈S log x⌉` for a parameter `S`, reducing effective state space.
- Use polynomial multiplication (FFT-like ideas) within groups to speed up computation.
- Achieves `O(√n log²n)` complexity for certain operations.

### 6. **Key Observations**
- The number of distinct values of `⌊n/i⌋` is `O(√n)`.
- Many multiplicative functions can be expressed as Dirichlet convolutions involving well-known functions (μ, ϕ, etc.).
- Power series operations (exp/log) preserve multiplicativity under appropriate definitions.
- Precomputation and recursion over quotient values enable sublinear algorithms.