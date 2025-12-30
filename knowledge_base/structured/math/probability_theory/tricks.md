1. **Linearity of Expectation**: E(aX + bY) = aE(X) + bE(Y) always holds if expectations exist, regardless of independence.
2. **Indicator Variables**: For complex sums, define indicator I_A for event A, then E(I_A) = P(A). This simplifies many problems.
3. **Variance via E(X^2)**: D(X) = E(X^2) - (E(X))^2 is often easier than direct definition.
4. **Independence vs. Uncorrelated**: Independent ⇒ uncorrelated (Cov=0), but converse is false. Uncorrelated only means no linear relationship.
5. **Conditional Expectation and Total Expectation**: E[E[X|Y]] = E[X] (law of total expectation) is powerful for recursive problems (e.g., HDU 5984 Pocky).
6. **Covariance as Inner Product**: Cov(X,Y) behaves like inner product, enabling geometric interpretations.
7. **Pearson Correlation**: ρ_{X,Y} = Cov(X,Y)/(σ_X σ_Y) measures linear dependence, |ρ| ≤ 1, with ±1 indicating perfect linear relationship.
8. **Expectation of Product**: E(XY) = E(X)E(Y) if X,Y independent, but independence is not necessary (counterexample: Y = X^2 with X uniform on [-1,1]).
9. **Variance of Sum**: D(X+Y) = D(X) + D(Y) + 2Cov(X,Y). For independent (or uncorrelated) variables, Cov=0 and variances add.
10. **Handling Continuous Variables**: Replace sums with integrals; same principles apply.
11. **Non-existence of Expectation**: Expectation may not exist if sum/integral is not absolutely convergent (e.g., Cauchy distribution).
12. **Transformation of Variables**: For independent X,Y, f(X) and g(Y) are independent for any functions f,g.