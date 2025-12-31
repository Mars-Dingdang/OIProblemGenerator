# 浅谈格算法在整系数多项式分解中的应用

**Author:** 谢梓涵

### Key Ideas and Observations

1. **Reduction to Lattice Problem**: The core idea is transforming the problem of factoring a polynomial $ f(x) \in \mathbb{Z}[x] $ into finding a short vector in a specially constructed lattice $ L $. If $ f(x) = g(x)h(x) $ is a non-trivial factorization, then the coefficient vector of $ g(x) $ (padded with zeros) will be a relatively short vector in this lattice.

2. **Lattice Construction**: For a monic polynomial $ f(x) = x^n + a_{n-1}x^{n-1} + ... + a_0 $ of degree $ n $, the lattice $ L $ is defined as the set of all vectors $ (u_0, u_1, ..., u_{n-1}) \in \mathbb{Z}^{n} $ such that the corresponding polynomial $ u(x) = u_0 + u_1x + ... + u_{n-1}x^{n-1} $ satisfies $ u(\alpha) \equiv 0 \mod f(\alpha) $ in the ring $ \mathbb{Z}[\alpha] $, where $ \alpha $ is a root of $ f $. This condition ensures that $ u(x) $ is divisible by one of $ f $'s irreducible factors.

3. **LLL Algorithm Application**: The Lenstra–Lenstra–Lovász (LLL) lattice basis reduction algorithm is applied to find a short, non-zero vector $ \mathbf{v} $ in $ L $. The key insight is that if $ f $ has a non-trivial factor $ g $ of degree $ d < n $, then the coefficient vector of $ g $ (extended to length $ n $) will have a norm bounded by $ \|g\|_2 \leq 2^{d/2}\|f\|_2 $. The LLL algorithm guarantees a vector within an exponential factor of the shortest possible, which is sufficient to find such a $ g $ when it exists.

4. **Recovering the Factor**: Once a short vector $ \mathbf{v} $ is found, it corresponds to a polynomial $ v(x) $. The greatest common divisor (GCD) $ \gcd(f(x), v(x)) $ is computed over the integers. Due to the construction of the lattice, this GCD will yield a non-trivial factor of $ f(x) $ with high probability if $ f $ is reducible.

5. **Handling Non-Monic Polynomials**: For non-monic polynomials, the method involves first making them monic via a transformation like $ f'(x) = a_n^{n-1}f(x/a_n) $, factoring $ f' $, and then transforming the factors back.

6. **Correctness and Probability**: The algorithm is probabilistic but can be made deterministic by checking all sufficiently short vectors output by LLL or by using a different basis. The success relies on the geometric property that a true factor produces a vector significantly shorter than random vectors in the lattice.