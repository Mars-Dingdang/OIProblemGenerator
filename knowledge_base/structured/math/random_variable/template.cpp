#include <bits/stdc++.h>
using namespace std;

// Example: Simulating a discrete random variable with given probabilities
// Returns a random sample from distribution defined by vector p (probabilities)
int discrete_random_variable(const vector<double>& p) {
    random_device rd;
    mt19937 gen(rd());
    discrete_distribution<> dist(p.begin(), p.end());
    return dist(gen);
}

// Example: Probability Density Function (PDF) for continuous uniform distribution
double uniform_pdf(double x, double a, double b) {
    if (x < a || x > b) return 0.0;
    return 1.0 / (b - a);
}

// Example: Cumulative Distribution Function (CDF) for continuous uniform distribution
double uniform_cdf(double x, double a, double b) {
    if (x < a) return 0.0;
    if (x > b) return 1.0;
    return (x - a) / (b - a);
}

int main() {
    // Example usage for discrete random variable
    vector<double> prob = {0.2, 0.3, 0.5}; // probabilities for outcomes 0,1,2
    int sample = discrete_random_variable(prob);
    cout << "Sampled value: " << sample << endl;
    
    // Example usage for continuous uniform distribution
    double a = 0.0, b = 1.0;
    double x = 0.7;
    cout << "PDF at " << x << ": " << uniform_pdf(x, a, b) << endl;
    cout << "CDF at " << x << ": " << uniform_cdf(x, a, b) << endl;
    
    return 0;
}