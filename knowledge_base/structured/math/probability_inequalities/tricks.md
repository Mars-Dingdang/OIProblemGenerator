## Key Observations

1. **Union Bound (Boole's Inequality)**:
   - Most useful when events are "rare" (probabilities small)
   - Can be tightened using inclusion-exclusion principle
   - Often used in probabilistic method to show existence

2. **Markov Inequality**:
   - Only uses expectation, no distribution information
   - Very loose bound in practice
   - Best for non-negative random variables with heavy tails

3. **Chebyshev Inequality**:
   - Uses variance information
   - Much tighter than Markov when variance is small
   - Useful for concentration around mean

4. **Chernoff Bound**:
   - Exponential decay in deviation
   - Very tight for sums of independent Bernoulli variables
   - Two-sided: P(|X-μ| ≥ εμ) ≤ 2exp(-ε²μ/3)
   - One-sided variants exist with better constants

5. **Hoeffding Bound**:
   - Works for bounded random variables
   - Independent of distribution shape
   - Good when variables have known bounds [a_i, b_i]

## Common Problem Transformations

1. **Randomized Algorithm Analysis**:
   - Use union bound to bound failure probability across multiple bad events
   - Apply Chernoff to show concentration of running time

2. **Sampling Problems**:
   - To guarantee all k special items are sampled: use union bound with n log(k/ε) samples
   - For estimating probability p: need Ω(ε⁻² log(1/δ)) samples for (ε,δ)-approximation

3. **Monte Carlo Integration**:
   - Like π estimation example: error decays as O(1/√n)
   - Use Chernoff to determine sample size for desired accuracy

4. **Load Balancing**:
   - Balls-into-bins analysis often uses Chernoff/Hoeffding
   - Show maximum load is O(log n / log log n) with high probability

## Optimization Tips

1. **Choose the Right Inequality**:
   - Small variance → Chebyshev
   - Independent Bernoulli → Chernoff
   - Bounded variables → Hoeffding
   - Only expectation known → Markov

2. **Parameter Tuning**:
   - In Chernoff, optimize t to get tightest bound
   - Sometimes better to apply inequality to transformed variable

3. **Combine Inequalities**:
   - Use union bound with other inequalities for complex events
   - Chain inequalities: Markov → Chebyshev → Chernoff as more info available

4. **Symmetry Exploitation**:
   - Many problems symmetric: analyze one case and multiply by n
   - Use linearity of expectation even when variables dependent

## Common Pitfalls

1. Markov inequality gives trivial bound (≥1) when a ≤ E[X]
2. Union bound can be >1, need to cap at 1
3. Chernoff requires independence, not just pairwise independence
4. Hoeffding requires boundedness, unbounded variables need different approach