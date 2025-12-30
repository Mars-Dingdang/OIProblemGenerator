#include <bits/stdc++.h>
using namespace std;

// Example: Using Union Bound to bound probability of at least one event
// Suppose we have m independent events with probabilities p[i]
// Upper bound for P(at least one event occurs) <= sum(p[i])
double union_bound(const vector<double>& p) {
    double sum = 0.0;
    for (double prob : p) sum += prob;
    return min(sum, 1.0);
}

// Example: Markov Inequality for non-negative random variable X
// Returns upper bound for P(X >= a)
double markov_inequality(double expectation, double a) {
    if (a <= 0) return 1.0;
    return min(expectation / a, 1.0);
}

// Example: Chebyshev Inequality for random variable X
// Returns upper bound for P(|X - E[X]| >= a)
double chebyshev_inequality(double variance, double a) {
    if (a <= 0) return 1.0;
    return min(variance / (a * a), 1.0);
}

// Example: Chernoff bound for sum of independent Poisson trials
// X = sum of n independent Bernoulli(p) variables, mu = n*p
// Returns upper bound for P(|X - mu| >= eps * mu)
double chernoff_bound(double mu, double eps) {
    if (eps <= 0 || eps >= 1) return 1.0;
    return 2.0 * exp(-mu * eps * eps / 3.0);
}

// Example: Hoeffding bound for sum of bounded independent variables
// X_i in [a_i, b_i], X = sum X_i
// Returns upper bound for P(|X - E[X]| >= eps)
double hoeffding_bound(const vector<pair<double, double>>& ranges, double eps) {
    double sum_diff = 0.0;
    for (auto& [a, b] : ranges) {
        double diff = b - a;
        sum_diff += diff * diff;
    }
    if (sum_diff == 0) return 0.0;
    return 2.0 * exp(-2.0 * eps * eps / sum_diff);
}

int main() {
    // Example usage
    vector<double> probs = {0.1, 0.2, 0.3};
    cout << "Union bound: " << union_bound(probs) << endl;
    cout << "Markov (E[X]=5, a=10): " << markov_inequality(5.0, 10.0) << endl;
    cout << "Chebyshev (Var=4, a=3): " << chebyshev_inequality(4.0, 3.0) << endl;
    cout << "Chernoff (mu=100, eps=0.1): " << chernoff_bound(100.0, 0.1) << endl;
    
    vector<pair<double, double>> ranges = {{0, 1}, {0, 2}, {0, 3}};
    cout << "Hoeffding (eps=2): " << hoeffding_bound(ranges, 2.0) << endl;
    
    return 0;
}